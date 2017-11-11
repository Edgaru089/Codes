/*
DOCUMENT CODE "ClipboardSync.cpp"
CREATION DATE 2017-08-23
SIGNATURE CODE_20170823_CLIPBOARDSYNC
TOPIC Clipboard Synchronization
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20170823_CLIPBOARDSYNC

#include <cstdlib>
#include <iostream>
#include <thread>
#include <mutex>

#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

const string compileTime = string(__DATE__) + " " + string(__TIME__);

int main(int argc, char* argv[]) {

	cout << "Compile Time: " << compileTime << endl;
	cout << "Local Subnet IP Address: " << IpAddress::getLocalAddress().toString() << endl;
	cout << "Public IP Address: "; cout << IpAddress::getPublicAddress(seconds(8.0f)).toString() << endl << endl;

	string code;
	Uint16 port;
	String contentCache = L"";
	UdpSocket socket;

	cout << "Enter Passphrase: ";
	cin >> code;
	cout << "Enter Port Number: ";
	cin >> port;

	cout << endl << "Starting..." << endl;

	thread th([code, port]() {
		cout << "Listener Starting... Port: " << port << endl;

		UdpSocket socket;

		if (socket.bind(port) != Socket::Done) {
			cout << "Listener: Port binding failed" << endl;
			return;
		}

		Packet packet;
		IpAddress sender;
		Uint16 senderPort;

		string senderCode;
		String content;

		while (socket.receive(packet, sender, senderPort) == Socket::Done) {

			if (sender == IpAddress::getLocalAddress())
				continue;

			if (!(packet >> senderCode >> content))
				cout << "Listener: Invaild packet from " << sender.toString() << ":" << senderPort << endl;
			else
				cout << "Listener: Vaild packet from " << sender.toString() << ":" << senderPort << endl;

			if (senderCode == code) {
				Clipboard::setString(content);
			}

		}
	});
	th.detach();

	while (true) {
		sleep(milliseconds(1000));

		if (contentCache != Clipboard::getString()) {

			cout << "Sending Difference Packet" << endl;

			contentCache = Clipboard::getString();

			Packet packet;

			packet << code << contentCache;

			socket.send(packet, IpAddress::Broadcast, port);
		}

	}



	return 0;
}

#endif
