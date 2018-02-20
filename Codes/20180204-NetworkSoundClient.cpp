/*
DOCUMENT CODE "20180204-NetworkSoundClient.cpp"
CREATION DATE 2018-02-04
SIGNATURE CODE_20180204_NETWORKSOUNDCLIENT
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180204_NETWORKSOUNDCLIENT

#include <cstdlib>
#include <iostream>
#include <vector>
#include <memory>
#include <thread>
#include <mutex>

#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

using namespace std;
using namespace sfg;
using sf::Clock;
using sf::Time;
using sf::microseconds;
using sf::milliseconds;
using sf::seconds;
using sf::Event;
using sf::RenderWindow;
using sf::VideoMode;
using sf::Socket;
using sf::TcpSocket;
using sf::UdpSocket;
using sf::IpAddress;
using sf::Packet;
using sf::Uint16;
using sf::Int16;
using sf::Uint32;
using sf::Uint64;
using sf::String;
using sf::Vector2f;
using sf::SoundBuffer;
using sf::Sound;

typedef sf::Rect<sf::Uint32> UintRect;

class StringParser {
public:

	//将多个字符串以seperator为分隔符合并为一个
	static const string combineString(vector<string>& strings, char seperator) {
		if (strings.size() == 0)
			return "";
		string buffer = "";
		ostringstream out(buffer);
		out << strings[0];
		for (int i = 1; i < strings.size(); i++)
			out << seperator << strings[i];
		out.flush();
		return buffer;
	}

	//将按上述方法合并为一个字符串的多个字符串分开放到result里面
	static const void seperateString(string source, char seperator, vector<string>& result) {
		int get;
		string buffer;
		istringstream in(source);
		result.clear();
		while (true) {
			buffer.clear();
			while ((get = in.get())) {
				if (in.eof() || get == seperator)
					break;
				else
					buffer += char(get);
			}
			result.push_back(buffer);
			if (in.eof())
				break;
		}
	}

	template<typename... Args>
	static const string generateFormattedString(string source, Args... args) {
		char buffer[4096];
		sprintf_s(buffer, 4096, source.c_str(), args...);
		return string(buffer);
	}

	//把所有pair.first替换成pair.second
	static const string replaceSubString(string source, vector<pair<string, string> > replace) {
		string dest;

		for (pair<string, string> i : replace) {
			dest = ""s;
			for (int j = 0; j < source.size();) {
				if (source.substr(j, i.first.size()) == i.first) {
					j += i.first.size();
					dest += i.second;
				}
				else {
					dest += source[j];
					j++;
				}
			}
			source = dest;
		}
		return source;
	}

	//将各种整数/浮点数转换为字符串
	//或者考虑std::to_string()??? 
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


const bool receive(IpAddress ip, Uint16 port, SoundBuffer& buffer, Uint64& sampleCount, float& progress, bool& done, bool& result, mutex& lock) {
	TcpSocket socket;
	if (socket.connect(ip, port, seconds(10.0f)) != Socket::Done) {
		lock.lock();
		result = false;
		done = true;
		lock.unlock();
		return false;
	}

	shared_ptr<vector<Int16>> samples = make_shared<vector<Int16>>();
	Packet packet;
	Uint64 _sampleCount = 0;
	Uint32 channelCount = 0, sampleRate = 0;

	socket.setBlocking(true);

	if (socket.receive(packet) != Socket::Done) {
		lock.lock();
		result = false;
		done = true;
		lock.unlock();
		return false;
	}

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

	if (!buffer.loadFromSamples(&(*samples)[0], _sampleCount, channelCount, sampleRate)) {
		lock.lock();
		result = false;
		done = true;
		lock.unlock();
		return false;
	}

	lock.lock();
	result = true;
	done = true;
	lock.unlock();

	return true;
}

RenderWindow rwin;

bool isTransfering;
SoundBuffer buffer;
Uint64 sampleCount;
float progress;
bool done, result;
mutex mlock;
Sound sound;

int main(int argc, char* argv[]) {

	SFGUI sfgui;

	Desktop desktop;
	desktop.SetProperty("ProgressBar", "BackgroundColor", sf::Color(230, 230, 230));
	desktop.SetProperty("ProgressBar", "BorderColor", sf::Color(188, 188, 188));
	desktop.SetProperty("ToggleButton", "BackgroundColor", sf::Color(0xe1, 0xe1, 0xe1));
	desktop.SetProperty("ToggleButton", "BorderColor", sf::Color(0xad, 0xad, 0xad));
	desktop.SetProperty("ToggleButton", "Spacing", 5.f);
	desktop.SetProperty("ToggleButton:PRELIGHT", "BackgroundColor", sf::Color(0xe5, 0xf1, 0xfb));
	desktop.SetProperty("ToggleButton:PRELIGHT", "Color", sf::Color::Black);
	desktop.SetProperty("ToggleButton:PRELIGHT", "BorderColor", sf::Color(0, 120, 215));
	desktop.SetProperty("ToggleButton:ACTIVE", "BackgroundColor", sf::Color(204, 228, 247));
	desktop.SetProperty("ToggleButton:ACTIVE", "Color", sf::Color::Black);
	desktop.SetProperty("ToggleButton:ACTIVE", "BorderColor", sf::Color(0, 84, 153));
	desktop.SetProperty("AToggleButton", "BackgroundColor", sf::Color(129, 187, 235));
	Window::Ptr win;
	win = Window::Create(Window::BACKGROUND);

	Table::Ptr mainTable = Table::Create();
	mainTable->SetRequisition(Vector2f(500.0f, 0.0f));
	mainTable->SetRowSpacings(5.0f);

	Table::Ptr targetInputTable = Table::Create();
	Entry::Ptr ipAddressEntry = Entry::Create(), portEntry = Entry::Create();

	Table::Ptr targetTransferTable = Table::Create();
	Button::Ptr transferButton = Button::Create(L"Transfer");
	ProgressBar::Ptr transferProgress = ProgressBar::Create();

	Table::Ptr playControlTable = Table::Create();
	Scale::Ptr playTimeScale = Scale::Create();
	Label::Ptr playTimeLabel = Label::Create(L"0:00 / 0:00");
	Button::Ptr playButton = Button::Create("Play"), pauseButton = Button::Create(L"Pause"), stopButton = Button::Create(L"Stop");
	ToggleButton::Ptr repeatToggle = ToggleButton::Create(L"Repeat");

	Label::Ptr hintLabel = Label::Create(L"Ready");

	auto updateScalePosLoop = [&]() {
		while (result) {
			playTimeScale->GetAdjustment()->SetValue((sound.getPlayingOffset() / sound.getBuffer()->getDuration())*10000.0f);
			playTimeLabel->SetText(StringParser::generateFormattedString("%d:%02d / %d:%02d",
				(int)(sound.getPlayingOffset().asSeconds()) / 60, (int)(sound.getPlayingOffset().asSeconds()) % 60,
				(int)(sound.getBuffer()->getDuration().asSeconds()) / 60, (int)(sound.getBuffer()->getDuration().asSeconds()) % 60));
			sleep(milliseconds(50));
		}
	};


	targetInputTable->Attach(Label::Create(L"Address"), UintRect(0, 0, 1, 1), 0);
	targetInputTable->Attach(ipAddressEntry, UintRect(1, 0, 3, 1));
	targetInputTable->Attach(Separator::Create(Separator::Orientation::VERTICAL), UintRect(4, 0, 1, 1), 0);
	targetInputTable->Attach(Label::Create(L"Port"), UintRect(5, 0, 1, 1), 0);
	targetInputTable->Attach(portEntry, UintRect(6, 0, 1, 1));
	targetInputTable->SetColumnSpacings(8.0f);
	mainTable->Attach(targetInputTable, UintRect(0, 0, 1, 1));


	transferButton->GetSignal(Button::OnLeftClick).Connect([&]() {
		if (isTransfering)
			return;
		thread([&]() {
			isTransfering = true;
			done = false;

			sound.stop();
			playTimeLabel->SetText(L"0:00 / 0:00");
			result = false;

			hintLabel->SetText(L"Transfering...");

			thread(receive, IpAddress(ipAddressEntry->GetText().toAnsiString()), (Uint16)(StringParser::toInt(portEntry->GetText().toAnsiString())),
				ref(buffer), ref(sampleCount), ref(progress), ref(done), ref(result), ref(mlock)).detach();

			while (true) {
				float _prog;
				bool _done;
				Uint64 _size;
				mlock.lock();
				_prog = progress;
				_done = done;
				_size = sampleCount;
				mlock.unlock();

				hintLabel->SetText(StringParser::generateFormattedString("Transfering... %d/%d samples, %d%%",
					(int)(_size*_prog), _size, (int)(_prog * 100.0f)));

				transferProgress->SetFraction(_prog);

				if (_done)
					break;

				sleep(milliseconds(50));
			}

			if (result) {
				sound.setBuffer(buffer);
				thread(updateScalePosLoop).detach();
				hintLabel->SetText(L"Transfer Done.");
			}
			else
				hintLabel->SetText(L"Transfer Failed.");

			isTransfering = false;
		}).detach();
	});
	targetTransferTable->SetColumnSpacings(8.0f);
	targetTransferTable->Attach(transferButton, UintRect(0, 0, 1, 1));
	targetTransferTable->Attach(transferProgress, UintRect(1, 0, 9, 1));
	mainTable->Attach(targetTransferTable, UintRect(0, 1, 1, 1));


	mainTable->Attach(Separator::Create(), UintRect(0, 2, 1, 1));


	playTimeScale->SetRequisition(Vector2f(0.0f, 15.0f));
	playTimeScale->GetAdjustment()->Configure(0.0f, 0.0f, 10008.0f, 0.1f, 0.0f, 8.0f);
	playTimeScale->GetSignal(Adjustment::OnChange).Connect([&]() {

	});
	repeatToggle->GetSignal(ToggleButton::OnToggle).Connect([&]() {
		if (repeatToggle->IsActive()) {
			sound.setLoop(true);
			repeatToggle->SetId("AToggleButton");
			repeatToggle->Refresh();
		}
		else {
			sound.setLoop(false);
			repeatToggle->SetId("ToggleButton");
			repeatToggle->Refresh();
		}
	});
	playButton->GetSignal(Button::OnLeftClick).Connect([&]() {
		if (result)
			if (sound.getStatus() != Sound::Playing)
				sound.play();
	});
	pauseButton->GetSignal(Button::OnLeftClick).Connect([&]() {
		if (result)
			sound.pause();
	});
	stopButton->GetSignal(Button::OnLeftClick).Connect([&]() {
		if (result)
			sound.stop();
	});
	playControlTable->SetColumnSpacings(5.0f);
	playControlTable->SetRowSpacings(5.0f);
	playControlTable->Attach(playTimeScale, UintRect(0, 0, 11, 1));
	playControlTable->Attach(playButton, UintRect(0, 1, 1, 1));
	playControlTable->Attach(pauseButton, UintRect(1, 1, 1, 1));
	playControlTable->Attach(stopButton, UintRect(2, 1, 1, 1));
	playControlTable->Attach(playTimeLabel, UintRect(3, 1, 1, 1), Table::FILL);
	playControlTable->Attach(repeatToggle, UintRect(10, 1, 1, 1));
	mainTable->Attach(playControlTable, UintRect(0, 3, 1, 1));



	// Label HintLabel
	mainTable->Attach(Separator::Create(), UintRect(0, 4, 1, 1));
	mainTable->Attach(hintLabel, UintRect(0, 5, 1, 1), 0);

	win->Add(mainTable);

	desktop.Add(win);

	desktop.Update(0.0f);

	rwin.create(VideoMode(win->GetAllocation().width, win->GetAllocation().height), L"Network Sound Client", sf::Style::Titlebar | sf::Style::Close);
	rwin.setFramerateLimit(120);
	rwin.resetGLStates();

	Clock clock;
	while (rwin.isOpen()) {
		Event event;
		while (rwin.pollEvent(event)) {
			if (event.type == Event::Closed)
				rwin.close();
			desktop.HandleEvent(event);
		}

		desktop.Update(clock.restart().asSeconds());

		rwin.clear();
		sfgui.Display(rwin);
		rwin.display();
	}

	return 0;
}

#endif

