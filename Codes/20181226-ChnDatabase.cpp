/*
 DOCUMENT NAME "20181226-ChnDatabase.cpp"
 CREATION DATE 2018-12-26
 SIGNATURE CODE_20181226_CHNDATABASE
 COMMENT ≥…”Ô ˝æ›ø‚
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181226_CHNDATABASE

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <fstream>

#include <SFML/Graphics.hpp>
#include <windows.h>

#include "ImGui/imgui-setup.h"

using namespace std;
using namespace sf;
RenderWindow win;

const float getHighDpiScaleFactor() {
	UINT dpi = 96;
	DPI_AWARENESS dpiAwareness = GetAwarenessFromDpiAwarenessContext(GetThreadDpiAwarenessContext());
	switch (dpiAwareness) {
		// Scale the window to the system DPI
		case DPI_AWARENESS_SYSTEM_AWARE:
			dpi = GetDpiForSystem();
			break;

			// Scale the window to the monitor DPI
		case DPI_AWARENESS_PER_MONITOR_AWARE:
			dpi = GetDpiForWindow(win.getSystemHandle());
			break;
	}

	return dpi / 96.0f;
}

vector<string> database;


enum State {
	Empty,
	ChnDisplayExplain,
	ChnDisplayGuess
};

void loadChnDatabase(string filename = "chndb.txt") {
	string str;
	ifstream fin(filename);
	getline(fin, str);
	while (fin) {
		database.push_back(str);
		getline(fin, str);
	}
}


int main(int argc, char* argv[]) {

	imgui::SFML::Init(false);
	imgui::GetIO().IniFilename = nullptr;

	//float factor = getHighDpiScaleFactor();
	static ImFontConfig config;
	config.RasterizerMultiply = 3.0f;
	config.OversampleH = 1;
	imgui::GetIO().Fonts->Clear();
	ImFont* defaultFont = imgui::GetIO().Fonts->AddFontFromFileTTF(R"(C:\Windows\Fonts\simsun.ttc)", 16, &config, imgui::GetIO().Fonts->GetGlyphRangesChineseFull());
	static ImFontConfig config2;
	config2.RasterizerMultiply = 2.0f;
	config2.OversampleH = 1;
	imgui::GetIO().Fonts->Clear();
	ImFont* largeFont = imgui::GetIO().Fonts->AddFontFromFileTTF(R"(C:\Windows\Fonts\simsun.ttc)", 36, &config2, imgui::GetIO().Fonts->GetGlyphRangesChineseSimplifiedCommon());
	imgui::SFML::UpdateFontTexture();
	ImGui::StyleColorsDark();
	auto& style = imgui::GetStyle();
	style.FrameBorderSize = 1.0f;
	style.ScrollbarRounding = 0.0f;
	style.WindowRounding = 0.0f;

	//imgui::GetIO().MouseDrawCursor = true;

	loadChnDatabase();

	win.create(VideoMode(450, 650), "ChnDatabase", Style::Titlebar | Style::Close | Style::Resize);
	win.clear(); win.display();
	win.resetGLStates();
	win.setVerticalSyncEnabled(true);
	//win.setFramerateLimit(30);

	Clock deltaClock;
	while (win.isOpen()) {

		Event e;
		while (win.pollEvent(e)) {
			imgui::SFML::ProcessEvent(e);
			if (e.type == Event::Closed)
				win.close();
		}

		imgui::SFML::Update(win, deltaClock.restart());

		imgui::SetNextWindowSize(win.getSize() + Vector2u(2, 2), ImGuiCond_Always);
		imgui::SetNextWindowPos(ImVec2(-1, -1));
		imgui::SetNextWindowBgAlpha(0.0);
		imgui::Begin("MainFrame", nullptr, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);



		imgui::BeginVertical("AutoTBMargin", ImVec2(win.getSize().x, 0));
		imgui::Spring(.4f);

		imgui::BeginHorizontal("TitleLRMargin", ImVec2(win.getSize().x, 0));
		imgui::Spring(.5f);
		imgui::PushFont(largeFont);
		imgui::TextUnformatted(database[8].c_str());
		imgui::PopFont();
		imgui::Spring(.5f);
		imgui::EndHorizontal();

		imgui::Spring(.6f);
		imgui::EndVertical();


		imgui::End();

		win.clear();
		imgui::SFML::Render(win);
		win.display();
	}

	imgui::SFML::Shutdown();

	return 0;
}

#endif

