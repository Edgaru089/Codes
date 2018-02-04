/*
DOCUMENT CODE "20180116-NetworkSoundStream.cpp"
CREATION DATE 2018-01-16
SIGNATURE CODE_20180116_NETWORKSOUNDSTREAM
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180116_NETWORKSOUNDSTREAM

#include <cstdlib>
#include <iostream>
#include <mutex>
#include <thread>
#include <memory>
#include <iomanip>

#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace std;
using namespace sf;


const bool receive(IpAddress ip, Uint16 port, SoundBuffer& buffer, Uint64& sampleCount, float& progress, bool& done, mutex& lock) {
	TcpSocket socket;
	if (socket.connect(ip, port, seconds(10.0f)) != Socket::Done)
		return false;

	shared_ptr<vector<Int16>> samples = make_shared<vector<Int16>>();
	Packet packet;
	Uint64 _sampleCount = 0;
	Uint32 channelCount = 0, sampleRate = 0;

	socket.setBlocking(true);

	if (socket.receive(packet) != Socket::Done)
		return false;

	packet >> _sampleCount >> channelCount >> sampleRate;

	lock.lock();
	sampleCount = _sampleCount;
	progress = 0.0f;
	done = false;
	lock.unlock();

	samples->resize(_sampleCount);
	Uint64 curpos = 0;
	socket.setBlocking(false);
	while (curpos < _sampleCount) {
		size_t received;
		if (socket.receive(reinterpret_cast<void*>(&(*samples)[curpos]), (size_t)(samples->size() - curpos) * sizeof(Int16), received) >= Socket::Disconnected) // Disconnected or error
			break;
		received /= sizeof(Int16);
		curpos += received;

		lock.lock();
		progress = (float)curpos / (float)_sampleCount;
		lock.unlock();

		sleep(milliseconds(100));
	}

	if (curpos < _sampleCount)
		return false;

	lock.lock();
	progress = 1.0f;
	lock.unlock();

	socket.setBlocking(false);

	packet.clear();
	packet << "TRANSFER OK";
	socket.send(packet);

	packet.clear();
	socket.receive(packet);
	string str;
	packet >> str;
	if (str == "DISCONNECT")
		socket.disconnect();

	if (!buffer.loadFromSamples(&(*samples)[0], _sampleCount, channelCount, sampleRate))
		return false;

	lock.lock();
	done = true;
	lock.unlock();

	return true;
}


void listen(Uint16 port, SoundBuffer& buffer, bool& stop, mutex& lock) {
	stop = false;
	TcpListener listener;
	shared_ptr<TcpSocket> socket;

	listener.setBlocking(false);

	listener.listen(port);

	while (!stop) {
		socket = make_shared<TcpSocket>();
		while (!stop&&listener.accept(*socket) != Socket::Done)
			sleep(milliseconds(50));
		thread([&](shared_ptr<TcpSocket> socket, const SoundBuffer* buffer) {
			cout << "Connected" << endl;
			Packet packet;
			packet << (Uint64)buffer->getSampleCount() << (Uint32)buffer->getChannelCount() << (Uint32)buffer->getSampleRate();

			socket->send(packet);
			socket->send(reinterpret_cast<const void*>(buffer->getSamples()), buffer->getSampleCount() * sizeof(Int16));

			packet.clear();
			string str;
			socket->receive(packet);
			packet >> str;
			if (str == "TRANSFER OK") {
				packet.clear();
				packet << "DISCONNECT";
				socket->send(packet);
				socket->disconnect();
			}

			cout << "Disconnected" << endl;
		}, socket, &buffer).detach();
	}
}

SoundBuffer buffer;

int main(int argc, char* argv[]) {

	char choice;

	cout << "Server(s) or client(c)? ";
	cin >> choice;

	if (choice == 's') {
		Uint16 port;
		string filename;
		cout << "  Port: ";
		cin >> port;
		cout << "  Filename: ";
		cin >> filename;

		cout << "Loading...";
		buffer.loadFromFile(filename);
		cout << " Done." << endl;

		bool stop = false;
		mutex lock;

		thread(listen, port, ref(buffer), ref(stop), ref(lock)).detach();
		cout << "  Press Enter to stop listening";
		cin.ignore(); cin.ignore();
		lock.lock();
		stop = true;
		lock.unlock();
	}
	else if (choice == 'c') {
		string ip;
		Uint16 port;
		cout << "  Server Ip: ";
		cin >> ip;
		cout << "  Server port: ";
		cin >> port;
		cout << "Receiving..." << endl;

		mutex lock;
		bool done = false;
		float prog = 0.0f;
		Uint64 size = 0;

		thread(receive, IpAddress(ip), ref(port), ref(buffer), ref(size), ref(prog), ref(done), ref(lock)).detach();

		while (true) {

			float _prog;
			bool _done;
			Uint64 _size;
			lock.lock();
			_prog = prog;
			_done = done;
			_size = size;
			lock.unlock();
			cout << "\r    [ " << string(60 * _prog, '=') << string(60 - 60 * _prog, ' ') << " ] " <<
				_size*_prog << "/" << _size << " samples, " << (int)(_prog * 100) << "%";
			if (_done)
				break;
		}

		cout << "Done. " << endl;
		std::cout << " " << buffer.getDuration().asSeconds() << " seconds" << std::endl;
		std::cout << " " << buffer.getSampleRate() << " samples / sec" << std::endl;
		std::cout << " " << buffer.getChannelCount() << " channels" << std::endl;
		cout << "Press Enter to play...";
		cin.ignore(); cin.ignore();
		Sound sound(buffer);
		sound.play();
		while (sound.getStatus() == sf::Sound::Playing) {
			// Leave some CPU time for other processes
			sf::sleep(sf::milliseconds(100));

			// Display the playing position
			std::cout << "\rPlaying... " << sound.getPlayingOffset().asSeconds() << " sec        ";
			std::cout << std::flush;
		}
	}

	cout << "Press Enter to close...";
	cin.ignore();

	return 0;
}

#endif

