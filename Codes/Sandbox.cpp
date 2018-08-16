/*
DOCUMENT CODE "Sandbox.cpp"
CREATION DATE 2017-05-18
SIGNATURE CODE_SANDBOX
TOPIC 沙箱 用来写一些没用的测试性东西
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_SANDBOX

#include <cstdlib>
#include <iostream>
#include <Windows.h>
#include <SFML/Graphics.hpp>
#include "ImGui/imgui-setup.h"
using namespace std;
using namespace sf;

RenderWindow win;

String u8ToSfString(const char* u8string) { return String::fromUtf8(u8string, u8string + strlen(u8string)); }
String u8ToSfString(const string& str) { return String::fromUtf8(str.begin(), str.end()); }
wchar_t convertBufferWStr[32 * 1024];
char convertBufferStr[32 * 1024];
const UINT codepage = 54936; // GB18030-2005 for Vista+ versions of windows
void convert936ToUtf8(string& str) {
	convertBufferWStr[MultiByteToWideChar(codepage, 0, str.c_str(), str.size(), convertBufferWStr, 32 * 1024)] = '\0';
	auto u8result = sf::String(convertBufferWStr).toUtf8();
	str.clear();
	str.reserve(u8result.size());
	for (auto i : u8result)
		str.push_back((char)i);
}
void convertUtf8To936(string& str) {
	wstring wstr = String::fromUtf8(str.begin(), str.end()).toWideString();
	convertBufferStr[WideCharToMultiByte(codepage, 0, wstr.c_str(), wstr.size(), convertBufferStr, 32 * 1024, NULL, NULL)] = '\0';
	str = string(convertBufferStr);
}

int main(int argc, char* argv[]) {

	string str;
	string str0;
	int cnt = 0;
	while (!getline(cin, str).eof()) {
		if (atoi(str.c_str()) >= 3)
			cnt++;
		if (cnt == 287) {
			str0 = str;
			break;
		}
	}

	cout << endl << str0 << endl;


	int dis[MaxN][MaxN];
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				if (dis[i][j] > dis[i][k] + dis[k][j])
					dis[i][j] = dis[i][k] + dis[k][j];



	win.create(VideoMode(1080, 608), "ImGui Snippet");
	win.setVerticalSyncEnabled(true);
	win.resetGLStates();

	imgui::SFML::Init(win, true);

	Clock deltaClock;
	while (win.isOpen()) {
		Event e;
		while (win.pollEvent(e)) {
			imgui::SFML::ProcessEvent(e);
			if (e.type == Event::Closed)
				win.close();
		}

		imgui::SFML::Update(win, deltaClock.restart());

		imgui::ShowDemoWindow();
		imgui::ShowMetricsWindow();

		win.clear(Color(240, 240, 240));
		imgui::SFML::Render(win);
		win.display();
	}

	return 0;
}


#endif
