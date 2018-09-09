/*
DOCUMENT NAME "20180907-FileClient.cpp"
CREATION DATE 2018-09-07
SIGNATURE CODE_20180907_FILECLIENT
COMMENT Network file transfer client
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180907_FILECLIENT

#include <cstdlib>
#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <fstream>
#include <SFML/Network.hpp>
using namespace std;
using namespace sf;

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

#pragma region Client Connecter

class FileClient {
public:
	class TransferStatus {
	public:
		friend class FileClient;
		Uint64 totalFileSize() { return totalSize; }
		Uint64 receivedFileSize() { return receivedSize; }
		double receivedFraction() { return (double)((unsigned long long)receivedSize) / totalSize; }
		bool isDone() { return receivedSize < totalSize; }
	private:
		Uint64 totalSize;
		atomic_ullong receivedSize;
	};

	bool connect(IpAddress target, Uint16 port) {
		connected = false;
		sock.disconnect();
		Socket::Status stat = sock.connect(target, port);
		if (stat == Socket::Done)
			connected = true;
		else
			sock.disconnect();
		return connected;
	}

	bool downloadFileToLocalFileBlocking(String remoteFilename, String localFilename) {
		wcout << "Downloading file from remote \"" << remoteFilename.toWideString() << "\" to local \"" << localFilename.toWideString() << "\"" << endl;
		ofstream fout(localFilename.toWideString(), ofstream::binary);
		if (!fout)
			return false;
		Packet pack, ret;
		Uint64 fileSize;
		ResponseType responseByte;
		// Send the command
		pack << CommandType(DownloadFile) << remoteFilename;
		sock.send(pack);
		// Receive the file size
		sock.receive(ret);
		ret >> responseByte >> fileSize;
		if (responseByte != SendingFileData) {
			cout << "[Error] File Download: Opening Response Failed: " << (int)responseByte << ", Size: " << fileSize << endl;
			return false;
		}
		cout << "The file has a size of " << fileSize << endl;
		cout << "Receiving data..." << endl;
		// Receive raw data
		constexpr size_t bufferSize = 16 * 1024 * 1024;
		char* buffer = new char[bufferSize];
		size_t receivedSize = 0, receivedAll = 0;
		while (receivedAll < fileSize&&connected) {
			Socket::Status stat;
			stat = sock.receive(buffer, min(bufferSize, size_t(fileSize) - receivedAll), receivedSize);
			fout.write(buffer, receivedSize);
			receivedAll += receivedSize;
			if (stat == Socket::Disconnected || stat == Socket::Error)
				connected = false;
		}
		// Receive the stopping package
		sock.receive(ret);
		ret >> responseByte;
		if (responseByte != FileDataSent)
			cout << "[Warning] File Download: Ending Response Failed: " << (int)responseByte << endl;
		delete[] buffer;
	}

	void disconnect() {
		connected = false;
		sock.disconnect();
	}

	atomic_bool connected;
private:
	TcpSocket sock;
};

#pragma endregion

FileClient client;


int main(int argc, char* argv[]) {
	string serverip;
	Uint16 port;
	string rfilename, lfilename;
	cout << "Server Ip:";
	cin >> serverip;
	cout << "Port: ";
	cin >> port;
	cout << "Remote Filename: ";
	cin >> rfilename;
	cout << "Local Filename:";
	cin >> lfilename;

	cout << endl << "Connecting...";
	if (!client.connect(IpAddress(serverip), port)) {
		cout << "Error." << endl;
		return EXIT_FAILURE;
	}

	cout << "Done." << endl;
	cout << "Downloading File..." << endl;
	client.downloadFileToLocalFileBlocking(rfilename, lfilename);

	return 0;
}

#endif

