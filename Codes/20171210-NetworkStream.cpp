/*
DOCUMENT CODE "20171210-NetworkStream.cpp"
CREATION DATE 2017-12-10
SIGNATURE CODE_20171210_NETWORKSTREAM
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20171210_NETWORKSTREAM

#include <cstdlib>
#include <iostream>
#include <vector>

#include <SFML/Network.hpp>

using namespace std;
using namespace sf;

class NetworkStreamListener {

};

class NetworkStreamConnector {

};

class NetworkStream {
public:

	void open(TcpSocket* socket) {

	}

private:
	TcpSocket* mainSocket;

	vector<char> receivedBufferedData;
	vector<char> sendBufferedData;
};

int main(int argc, char* argv[]) {

	return 0;
}

#endif

