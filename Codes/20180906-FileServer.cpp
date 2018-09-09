/*
DOCUMENT NAME "20180906-FileServer.cpp"
CREATION DATE 2018-09-06
SIGNATURE CODE_20180906_FILESERVER
COMMENT Network file transfer server
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180906_FILESERVER

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <thread>
#include <mutex>
#include <atomic>
#include <fstream>
#include <list>

#include <Windows.h>

#include <SFML/Network.hpp>

using namespace std;
using namespace sf;

#pragma region Log System

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

#pragma endregion

#pragma region Config Reader

class OptionFile {
public:
	bool loadFromFile(string filename) {
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

#pragma endregion

int bufferSize = 8 * 1024 * 1024;

#pragma region Response & Command Codes

enum Command {
	Hello,              ///< Say hello to the oterh peer
	NoOp,               ///< No operation, used to keep the connection alive
	DownloadFile,       ///< Download a file
	DownloadFileOffset, ///< Download a part of a file with a begining offset
	QueryFileSize       ///< Query the size of a file
};

enum Response {
	Ok,                ///< Command ok
	FileSize,          ///< Telling the client the size of a queried file
	ClosingConnection, ///< Service closing control connection
	SendingFileData,   ///< File request ok, sending file data
	FileDataSent,      ///< File data sending done

	CommandUnknown,     ///< Syntax error, command unrecognized
	BadCommandSequence, ///< Bad sequence of commands
	FileUnavailable     ///< Requested action not taken, file unavailable
};

typedef unsigned char CommandType;
typedef unsigned char ResponseType;

#pragma endregion

#pragma region Client Handler

class ClientHandler :public NonCopyable {
public:
#define SOCKET (*(this->socket))
#define PACKET_COMMAND(command) \
Packet ret;                    \
ret << command
#define CHECKED_SEND(packet)                                         \
{	Socket::Status mstat;                                            \
	while ((mstat = SOCKET.send(packet)) == Socket::Partial);        \
	if (mstat == Socket::Disconnected || mstat == Socket::Error) \
		connected = false; }

	ClientHandler(shared_ptr<TcpSocket> socket) :socket(socket) {
		socket->setBlocking(false);
		connected = true;
		// This is a **Control Connection** handler
		handlerThread = make_shared<thread>([this]() {
			mlog << "[ClientHandler] Client from " << this->socket->getRemoteAddress().toString() << " connected" << dlog;
			Packet pack;
			Socket::Status status;
			// Receive the packets
			while (connected) {
				while (connected && (status = this->socket->receive(pack)) == Socket::Partial);
				if (status == Socket::NotReady) {
					sleep(milliseconds(150));
					continue;
				}
				if (status == Socket::Disconnected || status == Socket::Error)
					break;
				CommandType commandByte;
				Command command;
				pack >> commandByte;
				command = Command(commandByte);
				if (command == Hello) {
					mlog << "[ClientHandler] Client said hello to server" << dlog;
					PACKET_COMMAND(ResponseType(Hello));
					CHECKED_SEND(ret);
				}
				else if (command == QueryFileSize) {
					String filename;
					pack >> filename;
					mlog << "[ClientHandler] Client queried the size of the file " << filename.toAnsiString() << dlog;
					ifstream fin(filename.toWideString());
					fin.seekg(0, ifstream::end);
					Uint64 size = fin.tellg();
					fin.close();
					PACKET_COMMAND(ResponseType(FileSize));
					ret << size;
					CHECKED_SEND(ret);
				}
				else if (command == DownloadFile) {
					String filename;
					pack >> filename;
					// Just send the file
					mlog << "[ClientHandler] Client requested download of the file " << filename.toAnsiString() << dlog;
					ifstream fin(filename.toWideString(), ifstream::binary);
					if (!fin) {
						PACKET_COMMAND(ResponseType(FileUnavailable));
						mlog << "[ClientHandler] Client requested file not found." << dlog;
						CHECKED_SEND(ret);
					}
					else {
						char* buffer = new char[bufferSize];
						PACKET_COMMAND(ResponseType(SendingFileData));
						Uint64 filesize;
						ret << (filesize = Uint64(fin.seekg(0, ifstream::end).tellg()));
						mlog << "[ClientHandler] The file has a size of " << filesize << dlog;
						mlog << "[ClientHandler] Sending data" << dlog;
						CHECKED_SEND(ret);
						fin.seekg(0, ifstream::beg);
						while (!fin.eof() && connected) {
							Socket::Status stat;
							fin.read(buffer, bufferSize);
							size_t sentsize = 0, sentall = 0;
							while (sentall < fin.gcount()) {
								stat = this->socket->send(buffer + sentall, fin.gcount() - sentall, sentsize);
								sentall += sentsize;
							}
							if (stat == Socket::Disconnected || stat == Socket::Error)
								connected = false;
						}
						delete[] buffer;
						if (connected) {
							mlog << "[ClientHandler] Data sent" << dlog;
							ret.clear();
							ret << ResponseType(FileDataSent);
							CHECKED_SEND(ret);
						}
					}
				}
			}
			connected = false;
		});
	}
	~ClientHandler() {
		connected = false;
		if (socket)
			socket->disconnect();
		if (handlerThread->joinable())
			handlerThread->join();
	}

	bool isConnected() { return connected; }
	void disconnect() {
		connected = false;
		socket->disconnect();
		if (handlerThread->joinable())
			handlerThread->join();
	}

private:
	shared_ptr<thread> handlerThread;
	shared_ptr<TcpSocket> socket;
	atomic_bool connected;
};


#pragma endregion

#pragma region Server Handler

class ServerHandler {
public:

	~ServerHandler() {
		stop();
	}

	void listen() {
		handlers.clear();
		listening = true;
		maintainer = make_shared<thread>([this]() {
			while (listening) {
				listLock.lock();
				for (auto i = handlers.begin(); i != handlers.end();)
					if (!(*i)->isConnected())
						i = handlers.erase(i);
					else
						i++;
				listLock.unlock();
				sleep(milliseconds(200));
			}
		});
		listener = make_shared<thread>([this]() {
			Socket::Status s;
			TcpListener listener;
			shared_ptr<TcpSocket> sock = make_shared<TcpSocket>();
			listener.setBlocking(false);
			listener.listen(port);
			while ((s = listener.accept(*sock)) != Socket::Error) {
				if (s == Socket::NotReady) {
					sleep(milliseconds(150));
					continue;
				}
				else if (s == Socket::Done) {
					shared_ptr<ClientHandler> c = make_shared<ClientHandler>(sock);
					listLock.lock();
					handlers.push_back(c);
					listLock.unlock();
				}
			}
		});
	}

	void stop() {
		if (listening) {
			listening = false;
			maintainer->join();
		}
		listLock.lock();
		handlers.clear();
		listLock.unlock();
	}

	Uint16 port;
	atomic_bool listening;
private:
	shared_ptr<thread> maintainer, listener;
	list<shared_ptr<ClientHandler>> handlers;
	mutex listLock;
};

#pragma endregion

ServerHandler server;

const string compileTime = string(__DATE__) + " " + string(__TIME__);

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
	server.stop();
	return true;
}

int main(int argc, char* argv[]) {

	cout << "File Hosting Server, Compile Time: " << compileTime << endl;
	cout << "Copyright(c) Edgaru089 (https://github.com/Edgaru089)" << endl << endl;

	server.port = 22346;
	if (!option.loadFromFile("fileserver.ini")) {
		cout << "WARNING: File Server config loading failed!" << endl;
		cout << "Is there a file named \"fileserver.ini\" in the working directory?" << endl;
		cout << "Create that file, and put a line \"port=<Listening port>\" with an endline after it." << endl;
		cout << "Now using the default port 22346." << endl;
	}
	else {
		if (!option.getContent("port").empty())
			server.port = StringParser::toInt(option.getContent("port"));
		if (!option.getContent("buffer_size").empty())
			bufferSize = StringParser::toInt(option.getContent("buffer_size"));
	}

	dlog.addOutputStream(cout);
	mlog << "Listening on port " << server.port << dlog;

	server.listen();

	while (server.listening)
		sleep(milliseconds(500));

	return 0;
}

#endif

