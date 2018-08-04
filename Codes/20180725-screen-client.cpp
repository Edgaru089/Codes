/*
DOCUMENT NAME "20180725-screen-client.cpp"
CREATION DATE 2018-07-25
SIGNATURE CODE_20180725_SCREEN_CLIENT
COMMENT screen client
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180725_SCREEN_CLIENT

#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <queue>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
using namespace std;
using namespace sf;

#include "ImGui/imgui-setup.h"

String u8ToSfString(const char* u8string) { return String::fromUtf8(u8string, u8string + strlen(u8string)); }
String u8ToSfString(const string& str) { return String::fromUtf8(str.begin(), str.end()); }
//把所有pair.first替换成pair.second
string replaceSubString(string source, initializer_list<pair<string, string>> replace) {
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

string totalBuffer;
mutex totalBufferLock;
char inputBuffer[4096 + 1];
bool showConnectWindow, wantLoadFont, chnFontLoaded;
char connectIpBuffer[256 + 1];
int connectPort = 22344;

RenderWindow win;
const string compileTime = string(__DATE__) + " " + string(__TIME__);

class Connection {
public:
	bool connect(IpAddress target, Uint16 port, Time timeout = seconds(8.0f)) {
		totalBuffer += "Connecting to " + target.toString() + "...";
		win.setTitle("Screen Client [Connecting], Compile Time: " + compileTime);
		socket.disconnect();
		connected = false;
		Socket::Status stat = socket.connect(target, port, timeout);
		if (stat != Socket::Disconnected&&stat != Socket::Error) {
			totalBuffer += " Connected.\n";
			win.setTitle("Screen Client [Connected], Compile Time: " + compileTime);
			connected = true;
			handlerThread = new thread(&Connection::handler, this);
			return true;
		}
		else {
			totalBuffer += " Connection Failed.\n";
			win.setTitle("Screen Client [Disconnected], Compile Time: " + compileTime);
			return false;
		}
	}

	void pushInput() {
		Packet p;
		p << "INPUTLN" << inputBuffer;
		inputBuffer[0] = '\0';
		queueLock.lock();
		sendQueue.push(p);
		queueLock.unlock();
	}

	void disconnect() {
		socket.disconnect();
		connected = false;
	}

	atomic_bool connected;
private:
	void handler() {
		Packet pack;
		Socket::Status status;
		socket.setBlocking(false);
		while ((status = socket.receive(pack)) != Socket::Disconnected) {
			if (status == Socket::Partial)
				continue;
			string command;
			if (pack >> command) {
				if (command == "OUTPUT") {
					string str;
					pack >> str;
					totalBufferLock.lock();
					totalBuffer += replaceSubString(str, {{"\r\n","\n"}});
					totalBufferLock.unlock();
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
		totalBuffer += "Disconnected from server.\n";
		win.setTitle("Screen Client [Disconnected], Compile Time: " + compileTime);
	}

	thread* handlerThread;

	TcpSocket socket;
	queue<Packet> sendQueue;
	mutex queueLock;
};

Connection connection;

int main(int argc, char* argv[]) {
	win.create(VideoMode(960, 640),
			   "Screen Client [Disconnected], Compile Time: " + compileTime,
			   Style::Titlebar | Style::Resize | Style::Close);
	win.clear(); win.display();
	win.setVerticalSyncEnabled(true);
	win.resetGLStates();

	imgui::SFML::Init(win);
	imgui::GetIO().IniFilename = nullptr;
	ImGui::StyleColorsClassic();
	auto& style = imgui::GetStyle();
	style.FrameBorderSize = 1.0f;
	style.ScrollbarRounding = 0.0f;
	style.WindowRounding = 0.0f;
	style.ChildBorderSize = 0.0f;

	Clock deltaClock;
	while (win.isOpen()) {
		Event e;
		while (win.pollEvent(e)) {
			imgui::SFML::ProcessEvent(e);
			if (e.type == Event::Closed)
				win.close();
		}

		if (wantLoadFont) {
			imgui::GetIO().Fonts->AddFontFromFileTTF("C:/Windows/Fonts/Dengb.ttf",
													 13, nullptr, imgui::GetIO().Fonts->GetGlyphRangesChinese());
			imgui::SFML::UpdateFontTexture();
			wantLoadFont = false;
			chnFontLoaded = true;
		}

		imgui::SFML::Update(win, deltaClock.restart());

		if (showConnectWindow)
			imgui::OpenPopup("Connect to Server");
		imgui::SetNextWindowPos(imgui::GetIO().DisplaySize / 2, ImGuiCond_Always, ImVec2(0.5, 1.0));
		if (imgui::BeginPopupModal("Connect to Server", &showConnectWindow, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings)) {
			imgui::InputText("IP Address", connectIpBuffer, 256);
			imgui::InputInt("Port", &connectPort);
			if (imgui::Button("Connect")) {
				connection.connect(IpAddress(connectIpBuffer), connectPort);
				showConnectWindow = false;
			}
			imgui::EndPopup();
		}

		imgui::SetNextWindowSize(imgui::GetIO().DisplaySize + ImVec2(2, 2), ImGuiCond_Always);
		imgui::SetNextWindowPos(ImVec2(-1, -1), ImGuiCond_Always);
		imgui::Begin("MainWindow", nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoSavedSettings);

		if (imgui::BeginMenuBar()) {
			if (imgui::BeginMenu("Menu")) {
				if (imgui::MenuItem("Connect...")) {
					showConnectWindow = true;
				}
				imgui::Separator();
				if (imgui::BeginMenu("Fonts")) {
					if (!chnFontLoaded) {
						if (imgui::MenuItem("Load Chinese Font")) {
							wantLoadFont = true;
						}
						imgui::Separator();
					}
					imgui::ShowFontSelector("Fonts");
					imgui::Text(u8"Innovation In China 中国智造，惠及全球 1234567890");
					imgui::EndMenu();
				}
				imgui::EndMenu();
			}
			imgui::EndMenuBar();
		}

		imgui::Text("Input");
		imgui::SameLine();
		imgui::PushItemWidth(-1);
		static bool wantSetActive = false;
		if (wantSetActive) {
			imgui::SetKeyboardFocusHere();
			wantSetActive = false;
		}
		if (imgui::InputText("##Input", inputBuffer, 2096, ImGuiInputTextFlags_EnterReturnsTrue)) {
			//totalBuffer += string(inputBuffer) + "\n";
			if (connection.connected)
				connection.pushInput();
			wantSetActive = true;
		}
		imgui::PopItemWidth();
		imgui::Separator();
		imgui::BeginChild("OutputChild", ImVec2(0, 0), true);
		static float size;
		totalBufferLock.lock();
		imgui::TextUnformatted(totalBuffer.c_str(), totalBuffer.c_str() + totalBuffer.size());
		totalBufferLock.unlock();
		if (size != imgui::GetScrollMaxY())
			imgui::SetScrollY(imgui::GetScrollMaxY());
		size = imgui::GetScrollMaxY();
		imgui::EndChild();

		imgui::End();

		win.clear();

		imgui::SFML::Render(win);

		win.display();
	}

	return 0;
}
#endif

