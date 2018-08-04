/*
DOCUMENT NAME "20180803-DataGenerator.cpp"
CREATION DATE 2018-08-03
SIGNATURE CODE_20180803_DATAGENERATOR
COMMENT 数据生成器
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180803_DATAGENERATOR

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
	static const string format(const string& formatStr, Args... args) {
		char buffer[256];
		sprintf(buffer, formatStr.c_str(), args...);
		return string(buffer);
	}
};

class Log {
public:

	const string logLevelName[5] = {"DEBUG", " INFO", " WARN", "ERROR", "FATAL ERROR"};

	enum LogLevel {
		Debug,
		Info,
		Warning,
		Error,
		FatalError
	};

	Log() :ignoreLevel(-1) {}
	Log(ostream& output) :out({&output}), ignoreLevel(-1) {}
	Log(ostream* output) :out({output}), ignoreLevel(-1) {}

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

	int nrange[11] = {0, 5, 7, 10, 20, 30, 36, 40, 50, 70, 80};

	for (dataset.openDatasetFiles("./data.%02d.in", "./data.%02d.out", 10, Dataset::LF);
		 dataset.isDatasetOpen();
		 dataset.nextDataset()) {
		int id = dataset.getDataId();

		int n = nrange[id];
		int t = min(rand(n - 3, n + 3), 80);
		int k = min(rand(n - 3, n + 3), 80);

		dataset.putFormat("%d %d %d\n", t, k, n);

		vector<int> vec;
		vec.reserve(n + 1);
		for (int j = 0; j <= n; j++)
			vec.push_back(j);
		for (int i = 1; i <= k; i++) {
			int h = rand(n / 2, n);
			dataset.putInt(h);
			shuffle(vec.begin(), vec.end(), randomEngine);
			for (int j = 0; j < h; j++)
				dataset.putSpace().putInt(vec[j]);
			dataset.putEndline();
		}
		for (int i = 1; i <= t; i++) {
			for (int j = 1; j <= k; j++) {
				if (j != 1)
					dataset.putSpace();
				dataset.putInt(rand(10, 99));
			}
			dataset.putEndline();
		}
		for (int i = 1; i <= t; i++) {
			for (int j = 1; j <= n; j++) {
				if (j != 1)
					dataset.putSpace();
				dataset.putFormat("%d %d", rand(10, 99), rand(10, 60));
			}
			dataset.putEndline();
		}
	}

	dataset.callStdProgram("./std");


	return 0;
}

#endif

