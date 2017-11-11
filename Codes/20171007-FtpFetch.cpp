/*
DOCUMENT CODE "FtpFetch.cpp"
CREATION DATE 2017-10-07
SIGNATURE CODE_20171007_FTPFETCH
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20171007_FTPFETCH

#include <cstdlib>
#include <iostream>

#include <SFML/Network.hpp>

using namespace std;
using namespace sf;

int main(int argc, char* argv[]) {

	bool connected = false, loggedIn = false;
	string server, user, pass, filename;

	cout << "Server Address: ";
	cin >> server;

	Ftp ftp;
	Ftp::Response response;
	Ftp::TransferState state;

	cout << "Connecting...";
	response = ftp.connect(IpAddress(server), 21, seconds(10.0f));

	if (!response.isOk()) {
		cout << endl << "Connection failed." << endl;





		return 0;
	}
	else
		cout << "Done" << endl;
	connected = true;

	cin.ignore(10000, '\n');

	do {
		cout << "Username: ";
		getline(cin, user);

		if (user == "") {
			cout << "Logging in as anonymous" << endl;
			response = ftp.login();
		}
		else {
			cout << "Password: ";
			getline(cin, pass);
			cout << "Logging in" << endl;
			response = ftp.login(user, pass);
		}

		if (response.isOk()) {
			cout << "Logged in." << endl;
			loggedIn = true;
		}
		else
			cout << "Login failed" << endl;
	} while (!loggedIn);

	Int64 size;
	do {
		cout << "Filename: ";
		getline(cin, filename);

		if (filename == "") {
			cout << endl << "Disconnected." << endl;
			ftp.disconnect();
			connected = false;
			continue;
		}

		size = ftp.getFileSize(filename);
		if (size == 0) { cout << "File does not exist" << endl; continue; }

		cout << "Downloading..." << endl;
		cout << endl << "File size: " << size << " Bytes (" << size / 1024 << "KB, " << size / 1024 / 1024 << "MB)" << endl;

		ftp.downloadAsynced(filename, "", Ftp::Binary, state);

		while (!state.isTransferCompleted()) {
			cout << "\r [" << string(100 * size / state.getTransferedSize(), '*') << string(100 - 100 * size / state.getTransferedSize(), ' ') << "]  " << 100 * size / state.getTransferedSize() << "%";
			sleep(milliseconds(50));
		}

		cout << "\r [" << string(100, '*') << "] 100%" << endl;
		cout << "Done." << endl << endl;

	} while (connected);


	return 0;
}

#endif
