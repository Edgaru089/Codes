/*
DOCUMENT CODE "NetworkInputStreamServer.cpp"
CREATION DATE 2017-09-03
SIGNATURE CODE_20170903_NETWORKINPUTSTREAMSERVER
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20170903_NETWORKINPUTSTREAMSERVER

#include <cstdlib>
#include <iostream>
#include <thread>

#include <SFML/Network.hpp>

using namespace std;
using namespace sf;

class StringPraser {
public:

	//将各种整数/浮点数转换为字符串
	static const string toString(bool                   data) { char buff[48]; sprintf(buff, "%d", data);   return string(buff); }
	static const string toString(short                  data) { char buff[48]; sprintf(buff, "%d", data);   return string(buff); }
	static const string toString(unsigned short         data) { char buff[48]; sprintf(buff, "%d", data);   return string(buff); }
	static const string toString(int                    data) { char buff[48]; sprintf(buff, "%d", data);   return string(buff); }
	static const string toString(unsigned int           data) { char buff[48]; sprintf(buff, "%u", data);   return string(buff); }
	static const string toString(long long              data) { char buff[48]; sprintf(buff, "%lld", data); return string(buff); }
	static const string toString(unsigned long long     data) { char buff[48]; sprintf(buff, "%llu", data); return string(buff); }
	static const string toString(float                  data) { char buff[48]; sprintf(buff, "%f", data);   return string(buff); }
	static const string toString(double                 data) { char buff[48]; sprintf(buff, "%lf", data);  return string(buff); }

	//将字符串转换为各种整数/浮点数
	static const bool      toBool(string&     data) { int x;       sscanf(data.c_str(), "%d", &x);   return x; }
	static const short     toShort(string&    data) { int x;       sscanf(data.c_str(), "%d", &x);   return x; }
	static const int       toInt(string&      data) { int x;       sscanf(data.c_str(), "%d", &x);   return x; }
	static const long long toLongLong(string& data) { long long x; sscanf(data.c_str(), "%lld", &x); return x; }
	static const float     toFloat(string&    data) { float x;     sscanf(data.c_str(), "%f", &x);   return x; }
	static const double    toDouble(string&   data) { double x;    sscanf(data.c_str(), "%lf", &x);  return x; }

};

class NetworkInputStreamServer {
public:

	void listen(Uint16 port) {
		cout << "Listening on port " << port << endl;
		listener.close();
		listener.listen(port);

		listener.accept(socket);

		thread th(&NetworkInputStreamServer::onProcessCommands, this);
		th.detach();
	}

	void stop() {
		socket.disconnect();
	}

private:

	void sendResponse(bool isOk, vector<string> response = vector<string>()) {
		Packet pack;
		cout << "Sending response: " << (isOk ? "OK" : "ERROR");
		pack << (isOk ? "OK" : "ERROR");
		for (string& i : response)
			pack << i;
		socket.send(pack);
	}

	void onProcessCommands() {
		Packet pack;
		string str;
		cout << "LsLoop Engaged" << endl;
		while (socket.receive(pack) == Socket::Done) {
			pack >> str;
			cout << "Command \"" << str << "\" received" << endl;
			if (str == "HELLO")
				sendResponse(true);
			else if (str == "OPEN") {
				pack >> str;
				sendResponse(stream.open(str));
			}
			else if (str == "READ") {
				Int64 toRead, size;
				pack >> str;
				toRead = StringPraser::toLongLong(str);
				cout << "Param: " << str << endl;
				cout << "CurPos: " << stream.tell() << endl;

				char* data = new char[toRead + 1];
				size = stream.read(data, toRead);
				cout << "Read: " << size << endl;
				sendResponse(true, { StringPraser::toString(size), string(data, size) });
				delete[toRead + 1] data;
			}
			else if (str == "SEEK") {
				Int64 pos;
				pack >> str;
				pos = StringPraser::toLongLong(str);

				sendResponse(true, { StringPraser::toString(stream.seek(pos)) });
			}
			else if (str == "TELL") {
				sendResponse(true, { StringPraser::toString(stream.tell()) });
			}
			else if (str == "GETSIZE") {
				sendResponse(true, { StringPraser::toString(stream.getSize()) });
			}
		}
		cout << "LsLoop Terminating" << endl;
	}

	TcpListener listener;
	TcpSocket socket;

	FileInputStream stream;

};

int main(int argc, char* argv[]) {
	Uint16 port;

	cout << "Port: ";
	cin >> port;
	NetworkInputStreamServer server;
	server.listen(port);




	server.stop();

	return 0;
}

#endif
