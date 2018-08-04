/*
DOCUMENT NAME "20180725-screen.cpp"
CREATION DATE 2018-07-25
SIGNATURE CODE_20180725_SCREEN
COMMENT Network server for screen
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180725_SCREEN

#include <functional>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <thread>
#include <atomic>
#include <ctime>
#include <mutex>
#include <queue>
#include <SFML/Network.hpp>
#include <Windows.h>
using namespace std;
using namespace sf;


class StringParser {
public:
	//将各种整数/浮点数转换为字符串
	//或者考虑std::to_string()??? 
	static const string toString(bool                   data) { return to_string((int)data); }
	static const string toString(short                  data) { return to_string((int)data); }
	static const string toString(unsigned short         data) { return to_string((int)data); }
	static const string toString(int                    data) { return to_string(data); }
	static const string toString(unsigned int           data) { return to_string(data); }
	static const string toString(long long              data) { return to_string(data); }
	static const string toString(unsigned long long     data) { return to_string(data); }
	static const string toString(float                  data) { return to_string(data); }
	static const string toString(double                 data) { return to_string(data); }

	//将字符串转换为各种整数/浮点数
	static const bool      toBool(string&     data) { int x;       sscanf(data.c_str(), "%d", &x);   return x; }
	static const short     toShort(string&    data) { int x;       sscanf(data.c_str(), "%d", &x);   return x; }
	static const int       toInt(string&      data) { int x;       sscanf(data.c_str(), "%d", &x);   return x; }
	static const long long toLongLong(string& data) { long long x; sscanf(data.c_str(), "%lld", &x); return x; }
	static const float     toFloat(string&    data) { float x;     sscanf(data.c_str(), "%f", &x);   return x; }
	static const double    toDouble(string&   data) { double x;    sscanf(data.c_str(), "%lf", &x);  return x; }
};
#define AUTOLOCK(a) lock_guard<mutex> __mutex_lock(a)

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
		lock.lock();
		buffers.push_back(final);
		for (ostream* i : out) {
			(*i) << final << '\n';
			i->flush();
		}
		for (const auto& i : outf)
			i(final);
		lock.unlock();
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

	const vector<string>& getBuffers() { AUTOLOCK(lock); return buffers; }
	void clearBuffer() { AUTOLOCK(lock); buffers.clear(); }

private:
	vector<ostream*> out;
	vector<function<void(const string&)>> outf;
	mutex lock;
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

class OptionFile
{
public:

	bool loadFromFile(string filename)
	{
		string line, mark, cont;
		this->data.clear();
		ifstream file(filename);
		if (file.fail())
			return false;
		while (!file.eof()) {
			getline(file, line);
			if (line[0] == '#')
				continue;
			size_t pos = line.find_first_of('=');
			if (pos == string::npos)
				continue;
			mark = line.substr(0, pos);
			cont = line.substr(pos + 1, line.length() - pos - 1);
			this->data[mark] = cont;
		}
		return true;
	}

	string getContent(string key) {
		map<string, string>::iterator i;
		if ((i = this->data.find(key)) != this->data.end()) {
			return i->second;
		}
		else
			return "";
	}

private:
	map<string, string> data;
};

OptionFile option;
const string optionFilename = "screen-server.ini";

string command = "C:\\Windows\\System32\\cmd.exe";
string workingDir;
string stopCommand = "stop";
Uint16 listenPort = 22344;


wchar_t convertBufferWStr[32 * 1024];
char convertBufferStr[32 * 1024];
const UINT codepage = 54936;
void convert936ToUtf8(string& str) {
	convertBufferWStr[MultiByteToWideChar(codepage, 0, str.c_str(), str.size(), convertBufferWStr, 32 * 1024)] = '\0';
	auto u8result = sf::String(convertBufferWStr).toUtf8();
	str.clear();
	str.reserve(u8result.size());
	for (auto i : u8result)
		str.push_back((char)i);
}
void convertUtf8To936(string& str) {
	wstring wstr = String::fromUtf8(str.begin(), str.end()).toWideString();
	convertBufferStr[WideCharToMultiByte(codepage, 0, wstr.c_str(), wstr.size(), convertBufferStr, 32 * 1024, NULL, NULL)] = '\0';
	str = string(convertBufferStr);
}

atomic_bool isRunning;

void ErrorExit(string message) {
	mlog << Log::FatalError << "[ErrorExit] " << message << dlog;
	isRunning = false;
	ExitProcess(1);
}


HANDLE childStdInPipeRead, childStdInPipeWrite;
HANDLE childStdOutPipeRead, childStdOutPipeWrite;

HANDLE childProcessHandle;

string totalStdOutData, newStdOutData;
mutex strStdOutLock;

thread* pipeStdOutReader;
char pipeReadBuffer[65536];
DWORD pipeReadSize;

thread* processRunningChecker;


const Uint16 port = 22344;
class Connection {
public:
	bool listen() {
		TcpListener listener;
		listener.setBlocking(false);
		listener.listen(port);
		bool flag = false;
		while (isRunning && !flag) {
			if (listener.accept(socket) == Socket::Done)
				flag = true;
			else
				Sleep(4);
		}
		if (flag) {
			mlog << "[Connection] Connected: " << socket.getRemoteAddress().toString() << dlog;
			connected = true;
			// HACK BEGIN
			newStdOutData.clear();
			swap(newStdOutData, totalStdOutData);
			notifyOutData();
			// HACK END
			maintainThread = new thread(&Connection::maintain, this);
		}
		return flag;
	}

	void notifyOutData() {
		totalStdOutData += newStdOutData;
		Packet p;
		p << "OUTPUT" << newStdOutData;
		newStdOutData.clear();
		sendQueue.push(p);
	}

	atomic_bool connected;
private:

	void maintain() {
		Packet pack;
		Socket::Status status;
		socket.setBlocking(false);
		while ((status = socket.receive(pack)) != Socket::Disconnected) {
			if (status == Socket::Partial)
				continue;
			string command;
			if (pack >> command) {
				if (command == "INPUTLN") {
					string str;
					DWORD size;
					pack >> str;
					convertUtf8To936(str);
					mlog << "[Connection] InputLn: " << str << dlog;
					str.append("\r\n");
					WriteFile(childStdInPipeWrite, str.c_str(), str.size(), &size, NULL);
				}
			}
			// Send queue contents
			queueLock.lock();
			while (!sendQueue.empty()) {
				while ((status = socket.send(sendQueue.front())) == Socket::Partial || status == Socket::NotReady);
				sendQueue.pop();
			}
			queueLock.unlock();
			sleep(milliseconds(3));
		}
		connected = false;
	}

	TcpSocket socket;
	thread* maintainThread;
	queue<Packet> sendQueue;
	mutex queueLock;
};

Connection connection;


BOOL systemExitEventHandler(DWORD dwCtrlType) {
	if (dwCtrlType == CTRL_C_EVENT)
		mlog << Log::Error << "[Main/EVENT] Control-C Console Exit" << dlog << Log::Info;
	else if (dwCtrlType == CTRL_BREAK_EVENT)
		mlog << Log::Error << "[Main/EVENT] Control-Break Console Exit" << dlog << Log::Info;
	else if (dwCtrlType == CTRL_CLOSE_EVENT)
		mlog << Log::Error << "[Main/EVENT] Control-Close Console Exit" << dlog << Log::Info;
	else if (dwCtrlType == CTRL_LOGOFF_EVENT)
		mlog << Log::Error << "[Main/EVENT] System-Logoff Exit" << dlog << Log::Info;
	else if (dwCtrlType == CTRL_SHUTDOWN_EVENT)
		mlog << Log::Error << "[Main/EVENT] System-Shutdown Exit" << dlog << Log::Info;
	else
		return false;
	string buffer = stopCommand + "\r\n";
	DWORD size;
	WriteFile(childStdInPipeWrite, buffer.c_str(), buffer.size(), &size, NULL);
	DWORD exitCode;
	while (GetExitCodeProcess(childProcessHandle, &exitCode)) {
		if (exitCode != STILL_ACTIVE)
			break;
		Sleep(2);
	}
	isRunning = false;
	return true;
}

const string compileTime = string(__DATE__) + " " + string(__TIME__);
int main(int argc, char* argv[]) {

	dlog.addOutputStream(cout);

	SetConsoleCtrlHandler((PHANDLER_ROUTINE)systemExitEventHandler, true);

	option.loadFromFile(optionFilename);
	command = option.getContent("command");
	workingDir = option.getContent("working_dir");
	stopCommand = option.getContent("stop_command");
	listenPort = StringParser::toInt(option.getContent("listen_port"));

	mlog << "Screen Server, Compile Time: " << compileTime << dlog;
	mlog << "Command: " << command << dlog;
	mlog << "WorkingDir: " << workingDir << dlog;
	mlog << "StopCommand: " << stopCommand << dlog;
	mlog << "ListenPort: " << listenPort << dlog;

	isRunning = true;


	// Open pipes
	SECURITY_ATTRIBUTES saAttr;
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	saAttr.bInheritHandle = TRUE;
	saAttr.lpSecurityDescriptor = NULL;
	// Create a pipe for the child process's STDOUT. 
	if (!CreatePipe(&childStdOutPipeRead, &childStdOutPipeWrite, &saAttr, 0))
		ErrorExit("Error on StdoutRd CreatePipe");
	// Ensure the read handle to the pipe for STDOUT is not inherited.
	if (!SetHandleInformation(childStdOutPipeRead, HANDLE_FLAG_INHERIT, 0))
		ErrorExit("Error on Stdout SetHandleInformation");
	// Create a pipe for the child process's STDIN. 
	if (!CreatePipe(&childStdInPipeRead, &childStdInPipeWrite, &saAttr, 0))
		ErrorExit("Error on Stdin CreatePipe");
	// Ensure the write handle to the pipe for STDIN is not inherited. 
	if (!SetHandleInformation(childStdInPipeWrite, HANDLE_FLAG_INHERIT, 0))
		ErrorExit("Error on Stdin SetHandleInformation");

	if (workingDir == "") {
		size_t pos = command.find_last_of('\\');
		if (pos == string::npos)
			workingDir = "";
		else
			workingDir = command.substr(0, pos + 1);
	}

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	si.hStdError = childStdOutPipeWrite;
	si.hStdOutput = childStdOutPipeWrite;
	si.hStdInput = childStdInPipeRead;
	si.dwFlags |= STARTF_USESTDHANDLES;
	ZeroMemory(&pi, sizeof(pi));

	// Start the child process.
	if (!CreateProcess(NULL,                                // No module name (use command line)
					   const_cast<LPTSTR>(command.c_str()), // Command line
					   NULL,                                // Process handle not inheritable
					   NULL,                                // Thread handle not inheritable
					   TRUE,                                // Handles are inherited 
					   0,                                   // No creation flag
					   NULL,                                // Use parent's environment block
					   workingDir == "" ? NULL : workingDir.c_str(),
					   &si,                                 // Pointer to STARTUPINFO structure
					   &pi)                                 // Pointer to PROCESS_INFORMATION structure
		) {
		mlog << Log::FatalError << "CreateProcess failed (" << (int)GetLastError() << ")." << dlog;
		ExitProcess(1);
	}
	// Close handles.
	childProcessHandle = pi.hProcess;
	CloseHandle(pi.hThread);

	pipeStdOutReader = new thread([&] {
		while (isRunning && ReadFile(childStdOutPipeRead, pipeReadBuffer, 65535, &pipeReadSize, NULL)) {
			string str(pipeReadBuffer, pipeReadSize);
			mlog << "[PipeStdOutReader] StdOut: " << str << dlog;
			convert936ToUtf8(str);
			if (connection.connected) {
				newStdOutData += str;
				connection.notifyOutData();
			}
			else {
				if (newStdOutData.size() > 0) {
					totalStdOutData += newStdOutData;
					newStdOutData.clear();
				}
				totalStdOutData += str;
			}
		}
		isRunning = false;
	});

	processRunningChecker = new thread([&] {
		DWORD exitCode;
		while (GetExitCodeProcess(childProcessHandle, &exitCode)) {
			if (exitCode != STILL_ACTIVE)
				break;
			Sleep(10);
		}
		isRunning = false;
	});

	while (isRunning) {
		if (connection.connected) {
			Sleep(10);
		}
		else {
			connection.listen();
		}
	}


	return 0;
}

#endif

