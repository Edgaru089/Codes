/*
DOCUMENT NAME "20180811-ktx65-datagen.cpp"
CREATION DATE 2018-08-11
SIGNATURE CODE_20180811_KTX65_DATAGEN
COMMENT 河童重工的计算机 数据生成器
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180811_KTX65_DATAGEN

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <ctime>
#include <fstream>
#include <cstring>
#include <random>
#include <chrono>
#include <algorithm>
using namespace std;

class StringParser {
public:
	static const string toString(bool                   data) { return to_string((int)data); }
	static const string toString(short                  data) { return to_string((int)data); }
	static const string toString(unsigned short         data) { return to_string((int)data); }
	static const string toString(int                    data) { return to_string(data); }
	static const string toString(unsigned int           data) { return to_string(data); }
	static const string toString(long long              data) { return to_string(data); }
	static const string toString(unsigned long long     data) { return to_string(data); }
	static const string toString(float                  data) { return to_string(data); }
	static const string toString(double                 data) { return to_string(data); }

	static const bool      toBool(string&     data) { int x;       sscanf(data.c_str(), "%d", &x);   return x; }
	static const short     toShort(string&    data) { int x;       sscanf(data.c_str(), "%d", &x);   return x; }
	static const int       toInt(string&      data) { int x;       sscanf(data.c_str(), "%d", &x);   return x; }
	static const long long toLongLong(string& data) { long long x; sscanf(data.c_str(), "%lld", &x); return x; }
	static const float     toFloat(string&    data) { float x;     sscanf(data.c_str(), "%f", &x);   return x; }
	static const double    toDouble(string&   data) { double x;    sscanf(data.c_str(), "%lf", &x);  return x; }

	template<typename... Args>
	static const string format(const string& formatStr, const Args&... args) {
		char buffer[256];
		sprintf(buffer, formatStr.c_str(), args...);
		return string(buffer);
	}
};

class Log {
public:

	const string logLevelName[5] = { "DEBUG", " INFO", " WARN", "ERROR", "FATAL ERROR" };

	enum LogLevel {
		Debug,
		Info,
		Warning,
		Error,
		FatalError
	};

	Log() :ignoreLevel(-1) {}
	Log(ostream& output) :out({ &output }), ignoreLevel(-1) {}
	Log(ostream* output) :out({ output }), ignoreLevel(-1) {}

	void log(string content, LogLevel level = Info) {
		if (level <= ignoreLevel) return;
		time_t curtime = time(NULL);
		char buffer[64];
		strftime(buffer, 63, "[%T", localtime(&curtime));
		string final = string(buffer) + " " + logLevelName[level] + "]: " + content;
		buffers.push_back(final);
		for (ostream* i : out) {
			(*i) << final << '\n';
			i->flush();
		}
		for (const auto& i : outf)
			i(final);
	}

	template<typename... Args>
	void logf(LogLevel level, string format, Args... args) {
		char buf[2560];
		sprintf(buf, format.c_str(), args...);
		log(string(buf), level);
	}

	void operator() (string content, LogLevel level = Info) {
		log(content, level);
	}

	void addOutputStream(ostream& output) { out.push_back(&output); }
	void addOutputStream(ostream* output) { out.push_back(output); }
	void addOutputHandler(function<void(const string&)> output) { outf.push_back(output); }

	// Lower and equal; use -1 to ignore nothing
	void ignore(int level) { ignoreLevel = level; }
	int getIgnoreLevel() { return ignoreLevel; }

	const vector<string>& getBuffers() { return buffers; }
	void clearBuffer() { buffers.clear(); }

private:
	vector<ostream*> out;
	vector<function<void(const string&)>> outf;
	int ignoreLevel;

	vector<string> buffers;
};

Log dlog;

class LogMessage {
public:

	LogMessage() :level(Log::Info) {}
	LogMessage(Log::LogLevel level) :level(level) {}

	LogMessage& operator <<(bool                data) { buffer += StringParser::toString(data); return *this; }
	LogMessage& operator <<(char                data) { buffer += (data); return *this; }
	LogMessage& operator <<(unsigned char       data) { buffer += StringParser::toString(data); return *this; }
	LogMessage& operator <<(short               data) { buffer += StringParser::toString(data); return *this; }
	LogMessage& operator <<(unsigned short      data) { buffer += StringParser::toString(data); return *this; }
	LogMessage& operator <<(int                 data) { buffer += StringParser::toString(data); return *this; }
	LogMessage& operator <<(unsigned int        data) { buffer += StringParser::toString(data); return *this; }
	LogMessage& operator <<(long long           data) { buffer += StringParser::toString(data); return *this; }
	LogMessage& operator <<(unsigned long long  data) { buffer += StringParser::toString(data); return *this; }
	LogMessage& operator <<(float               data) { buffer += StringParser::toString(data); return *this; }
	LogMessage& operator <<(double              data) { buffer += StringParser::toString(data); return *this; }
	LogMessage& operator <<(const char*         data) { buffer += string(data); return *this; }
	LogMessage& operator <<(const std::string&  data) { buffer += data; return *this; }

	LogMessage& operator <<(Log::LogLevel      level) { this->level = level;  return *this; }
	LogMessage& operator <<(Log&                 log) { flush(log);  return *this; }

public:

	void setLevel(Log::LogLevel level) { this->level = level; }
	void flush(Log& log) { logout(log); clear(); }
	void logout(Log& log) { log(buffer, level); }
	void clear() { buffer = ""; }

private:
	string buffer;
	Log::LogLevel level;
};

#define mlog LogMessage()
#define mlogd LogMessage(Log::Debug)


class Dataset {
public:
	enum Endline {
		LF,
		CRLF,
		CR,
		Linux = LF,
		Windows = CRLF,
		Mac = CR
	};

	// "problem.%02d.in"
	void openDatasetFiles(string inDataName, string outDataName, int count, Endline endline = CRLF) {
		dataCount = count;
		this->endline = endline;
		this->inDataName = inDataName;
		this->outDataName = outDataName;
		dataId = 1;
		if (!_openFile(StringParser::format(inDataName, dataId))) {
			mlog << Log::Error << "[Dataset] Dataset file open failed!" << dlog;
			dataId = 0;
			return;
		}
	}

	void nextDataset() {
		_closeFile();
		dataId++;
		if (dataId > dataCount)
			dataId = 0;
		else
			if (!_openFile(StringParser::format(inDataName, dataId))) {
				mlog << Log::Error << "[Dataset] Dataset file open failed!" << dlog;
				dataId = 0;
				return;
			}
	}

	bool isDatasetOpen() { return dataId != 0; }

	int getDataId() { return dataId; }

	Dataset& putSpace(int count = 1) {
		for (int i = 1; i <= count; i++)
			fout.put(' ');
		return *this;
	}

	Dataset& putChar(char c) {
		fout.put(c);
		return *this;
	}

	template<typename IntType>
	Dataset& putInt(IntType x) {
		string str = to_string(x);
		fout.write(str.c_str(), str.size());
		return *this;
	}

	template<typename FloatType>
	Dataset& putDecimal(FloatType x, int digits = -1) {
		char buf[64];
		if (digits == -1)
			sprintf(buf, "%.*lf", digits, (double)x);
		else
			sprintf(buf, "%lf", (double)x);
		fout.write(buf, strlen(buf));
		return *this;
	}

	template<typename... Args>
	Dataset& putFormat(const string& format, const Args&... args) {
		char buffer[1024];
		sprintf(buffer, format.c_str(), args...);
		size_t len = strlen(buffer);
		for (int i = 0; i < len; i++) {
			if (buffer[i] == '\n')
				putEndline();
			else
				putChar(buffer[i]);
		}
		return *this;
	}

	Dataset& putString(const string& str) {
		for (int i = 0; i < str.length(); i++) {
			if (str[i] == '\n')
				putEndline();
			else
				putChar(str[i]);
		}
		return *this;
	}

	Dataset& putEndline() {
		if (endline == CR || endline == CRLF)
			fout.put('\r');
		if (endline == LF || endline == CRLF)
			fout.put('\n');
		return *this;
	}


	void callStdProgram(string exeFile) {
		chrono::high_resolution_clock c;
		chrono::time_point<chrono::high_resolution_clock> start = c.now();

		for (int i = 1; i <= dataCount; i++) {
			mlog << "[Dataset/Std] Calling Std for dataset " << i << dlog;
			start = c.now();

			// TODO Fix this!
			string command = StringParser::format("%s < " + inDataName + " > " + outDataName, exeFile.c_str(), i, i);
			int ret = system(command.c_str());

			mlog << "[Dataset/Std] Std returned with code " << ret << " in " << chrono::nanoseconds((c.now() - start)).count() / 1000000ll << "ms" << dlog;
		}

	}


private:
	bool _openFile(string filename) {
		mlog << "[Dataset/IO] Opening file: " << filename << dlog;
		fout.open(filename, fstream::out | fstream::binary);
		if (fout.fail()) {
			mlog << Log::Error << "[Data] File open failed!" << dlog;
			return false;
		}
		return true;
	}

	void _closeFile() {
		mlog << "[Dataset/IO] Closed file, wrote " << (int)fout.tellp() << " bytes." << dlog;
		fout.close();
	}

	string inDataName, outDataName;

	ofstream fout;
	Endline endline = CRLF;

	int dataId = 0, dataCount = 0;
};

mt19937 randomEngine((random_device())());

// [0, 1)
double rand01() {
	return uniform_real_distribution<double>(0.0, 1.0)(randomEngine);
}

// [x, y]
int rand(int x, int y) {
	return uniform_int_distribution<int>(x, y)(randomEngine);
}


Dataset dataset;

int main(int argc, char* argv[]) {

	dlog.addOutputStream(cout);

	int nrange[11] = { 0, 50000, 50000, 50000, 50000, 50000, 50000, 50000, 50000, 50000, 50000 };

	for (dataset.openDatasetFiles("./data.%02d.in", "./data.%02d.out", 10, Dataset::LF);
		 dataset.isDatasetOpen();
		 dataset.nextDataset()) {
		int id = dataset.getDataId();

		int n = nrange[id];

		if (id == 1) {
			string commands[2] = { "rint", "wint" };
			string regs[10] = { "r1", "r2", "r3", "r4", "e1", "e2", "e3", "e4", "val", "flag" };
			dataset.putInt(n).putEndline();
			int intcnt = 0;
			for (int i = 1; i <= n - 1; i++) {
				string comm = commands[rand(0, 1)];
				if (comm == "rint")
					intcnt++;
				dataset.putFormat("%s %%%s;\n", comm.c_str(), regs[rand(0, 9)].c_str());
			}
			dataset.putFormat("hlt;\n");
			for (int i = 1; i <= intcnt; i++)
				dataset.putInt(rand(0, 65535)).putEndline();
		}
		else if (id == 2) {
			string commands[5] = { "rint", "wint", "wch", "add", "add" };
			string regs[10] = { "r1", "r2", "r3", "r4", "e1", "e2", "e3", "e4", "val", "flag" };
			dataset.putInt(n).putEndline();
			int intcnt = 0;
			for (int i = 1; i <= n - 1; i++) {
				string comm = commands[rand(0, 4)];

				if (comm == "rint")
					intcnt++;

				if (comm == "rint" || comm == "wint")
					dataset.putFormat("%s %%%s;\n", comm.c_str(), regs[rand(0, 9)].c_str());
				else if (comm == "wch") {
					if (rand01() > 0.85)
						dataset.putFormat("wch 10;\n");
					else
						dataset.putFormat("wch %d;\n", rand(32, 126));
				}
				else {
					if (rand01() > 0.8)
						dataset.putFormat("%s %%%s %%%s %%%s;\n",
										  comm.c_str(),
										  regs[rand(0, 9)].c_str(),
										  regs[rand(0, 9)].c_str(),
										  regs[rand(0, 9)].c_str());
					else
						dataset.putFormat("%s %%%s %%%s;\n",
										  comm.c_str(),
										  regs[rand(0, 9)].c_str(),
										  regs[rand(0, 9)].c_str());
				}
			}
			dataset.putFormat("hlt;\n");
			for (int i = 1; i <= intcnt; i++)
				dataset.putInt(rand(0, 65535)).putEndline();
		}
		else if (id == 3 || id == 4 || id == 5) {
			string commands[13] = {
				"rint", "wint", "wch",
				"add", "add",
				"sub", "sub",
				"mult",
				"lsft", "rsft", "band", "bor", "bxor"
			};
			string regs[10] = { "r1", "r2", "r3", "r4", "e1", "e2", "e3", "e4", "val", "flag" };
			dataset.putInt(n).putEndline();
			int intcnt = 0;
			auto genCommand = [&] {
				string comm = commands[rand(0, 12)];
				if (comm == "rint")
					intcnt++;

				if (comm == "rint" || comm == "wint")
					dataset.putFormat("%s %%%s;\n", comm.c_str(), regs[rand(0, 9)].c_str());
				else if (comm == "wch") {
					if (rand01() > 0.85)
						dataset.putFormat("wch 10;\n");
					else
						dataset.putFormat("wch %d;\n", rand(32, 126));
				}
				else
					if (rand01() > 0.8)
						dataset.putFormat("%s %%%s %%%s %%%s;\n",
										  comm.c_str(),
										  regs[rand(0, 9)].c_str(),
										  regs[rand(0, 9)].c_str(),
										  regs[rand(0, 9)].c_str());
					else
						dataset.putFormat("%s %%%s %%%s;\n",
										  comm.c_str(),
										  regs[rand(0, 9)].c_str(),
										  regs[rand(0, 9)].c_str());
			};
			for (int i = 1; i <= n - 1; i++)
				genCommand();
			dataset.putFormat("hlt;\n");
			for (int i = 1; i <= intcnt; i++)
				dataset.putInt(rand(0, 65535)).putEndline();
		}
		else {
			char chars[] = { "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" };
			int funcinc = n * 0.01;
			int funccnt = n / (funcinc + 2) - 1;
			int maininc = n - 1 - (funcinc + 2)*funccnt - funccnt;

			vector<string> funcnames;
			funcnames.resize(funccnt);
			for (int i = 0; i < funccnt; i++) {
				int len = rand(6, 12);
				for (int j = 0; j < len; j++)
					funcnames[i].push_back(chars[rand(0, 51)]);
			}

			string commands[13] = {
				"rint", "wint", "wch",
				"add", "add",
				"sub", "sub",
				"mult",
				"lsft", "rsft", "band", "bor", "bxor"
			};
			string regs[11] = { "r1", "r2", "r3", "r4", "e1", "e2", "e3", "e4", "val", "flag", "ret" };
			dataset.putInt(n).putEndline();
			int intcnt = 0;
			vector<string> commandprevfunc;
			auto genCommand = [&regs, &commands, &intcnt]()->string {
				string comm = commands[rand(0, 12)];
				string ans;
				if (comm == "rint")
					intcnt++;
				if (comm == "rint" || comm == "wint")
					ans = StringParser::format("%s %%%s;\n", comm.c_str(), regs[rand(0, 10)].c_str());
				else if (comm == "wch") {
					if (rand01() > 0.85)
						ans = StringParser::format("wch 10;\n");
					else
						ans = StringParser::format("wch %d;\n", rand(32, 126));
				}
				else
					if (rand01() > 0.8)
						ans = StringParser::format("%s %%%s %%%s %%%s;\n",
												   comm.c_str(),
												   regs[rand(0, 10)].c_str(),
												   regs[rand(0, 10)].c_str(),
												   regs[rand(0, 10)].c_str());
					else
						ans = StringParser::format("%s %%%s %%%s;\n",
												   comm.c_str(),
												   regs[rand(0, 10)].c_str(),
												   regs[rand(0, 10)].c_str());
				return ans;
			};
			mlog << "n: " << n << ", funccnt: " << funccnt << ", funcinc: " << funcinc << ", maininc: " << maininc << dlog;
			for (int i = 1; i <= maininc; i++)
				commandprevfunc.push_back(genCommand());
			for (int i = 0; i < funccnt; i++)
				commandprevfunc.push_back(StringParser::format("callfunc $%s;\n", funcnames[i].c_str()));
			shuffle(commandprevfunc.begin(), commandprevfunc.end(), randomEngine);
			for (auto& i : commandprevfunc)
				dataset.putString(i);
			dataset.putFormat("hlt;\n");
			shuffle(funcnames.begin(), funcnames.end(), randomEngine);
			for (int i = 0; i < funccnt; i++) {
				dataset.putFormat("function $%s;\n", funcnames[i].c_str());
				for (int j = 1; j <= funcinc; j++)
					dataset.putString(genCommand());
				if (rand01() > 0.6)
					dataset.putFormat("ret;\n");
				else
					dataset.putFormat("ret %s;\n", regs[rand(0, 10)].c_str());
			}

			for (int i = 1; i <= intcnt; i++)
				dataset.putInt(rand(0, 65535)).putEndline();
		}

	}

	dataset.callStdProgram("./std");

	return 0;
}

#endif

