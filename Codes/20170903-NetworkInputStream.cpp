/*
DOCUMENT CODE "NetworkInputStream.cpp"
CREATION DATE 2017-09-03
SIGNATURE CODE_20170903_NETWORKINPUTSTREAM
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20170903_NETWORKINPUTSTREAM

#include <cstdlib>
#include <iostream>
#include <vector>

#include <SFML/System.hpp>
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

class NetworkInputStream: public InputStream, NonCopyable {
public:

	~NetworkInputStream() { close(); }

	bool connect(IpAddress server, Uint16 port, Time timeout = Time::Zero) {

		Socket::Status status = socket.connect(server, port, timeout);

		if (status != Socket::Done)
			return false;

		sendCommand("HELLO");
		if (!isResponseOk)
			return false;
		else
			return true;
	}

	bool open(string filename) {
		sendCommand("OPEN", vector<string>{filename});
		if (!isResponseOk)
			return false;
		else
			return true;
	}

	virtual Int64 read(void* data, Int64 size) {
		sendCommand("READ", vector<string>{StringPraser::toString(size)});
		if (!isResponseOk)
			return -1;
		if (response[1].length() != StringPraser::toLongLong(response[0])) {
			cout << "Failure: Data chunk size mismatch" << endl;
			return -1;
		}
		memcpy(data, response[1].c_str(), StringPraser::toLongLong(response[0]));
		return StringPraser::toLongLong(response[0]);
	}

	virtual Int64 seek(Int64 position) {
		sendCommand("SEEK", vector<string>{StringPraser::toString(position)});
		if (!isResponseOk)
			return -1;
		else
			return StringPraser::toLongLong(response[0]);
	}

	virtual Int64 tell() {
		sendCommand("TELL");
		if (!isResponseOk)
			return -1;
		else
			return StringPraser::toLongLong(response[0]);
	}

	virtual Int64 getSize() {
		sendCommand("GETSIZE");
		if (!isResponseOk)
			return -1;
		else
			return StringPraser::toLongLong(response[0]);
	}

	void close() {
		socket.disconnect();
	}

private:

	bool sendCommand(string command, vector<string> params = vector<string>()) {
		cout << "Command sent: " << command;
		for (string& i : params)
			cout << " " << i;
		cout << endl;

		Packet packet;
		packet << command;
		for (string& i : params)
			packet << i;

		if (socket.send(packet) != Socket::Done)
			return false;
		else {
			getResponse();
			return true;
		}
	}

	void getResponse() {
		Packet pack;

		if (socket.receive(pack) != Socket::Done) {
			isResponseOk = false;
			return;
		}

		string ok, str;
		pack >> ok;
		isResponseOk = (ok == "OK");

		response.clear();
		while (pack >> str)
			response.push_back(str);

		cout << "Response: " << ok;
		cout << endl;
	}


	TcpSocket socket;
	Int64 positionCache;

	vector<string> response;
	bool isResponseOk;

};


int main(int argc, char* argv[]) {
	string ip, rfilename, lfilename;
	Uint16 port;

	cout << "Target IP address: ";
	cin >> ip;
	cout << "Port: ";
	cin >> port;

	NetworkInputStream stream;
	if (stream.connect(ip, port))
		cout << "Connected" << endl;

	//FileInputStream stream;
	cout << "Remote filename: ";
	cin >> rfilename;
	cout << "Local filename: ";
	cin >> lfilename;

	if (!stream.open(rfilename) || stream.seek(0)) {
		cout << "Error" << endl;



		return 1;
	}

	FILE* file = fopen(lfilename.c_str(), "wb");

	Uint16 chunkSize = 32768, read;
	char* data = new char[chunkSize + 1];
	while ((read = stream.read(data, chunkSize)) > 0) {
		fwrite(data, sizeof(char), read, file);
		cout << "Written " << read << " bytes" << endl;
	}
	fclose(file);


	return 0;
}

#endif
