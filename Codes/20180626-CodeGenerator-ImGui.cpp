/*
 DOCUMENT CODE "20180626-CodeGenerator-ImGui.cpp"
 CREATION DATE 2018-06-26
 SIGNATURE CODE_20180626_CODEGENERATOR_IMGUI
 TOPIC CodeGenerator In ImGui Manner
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180626_CODEGENERATOR_IMGUI

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <thread>
#include <Windows.h>
#include "ImGui/imgui-setup.h"
using namespace std;
using namespace sf;

RenderWindow win;

char *codeTemp, fileNameTemp[] = "%04d%02d%02d-%s.cpp", signatureTemp[] = "CODE_%04d%02d%02d_%s";

char fileCode[512], topic[512];
char fileName[1024], signature[1024];
char totalCode[2048];

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

void processFileName(char* buf) {
	for (int i = 0; buf[i] != '\0'; i++) {
		if (buf[i] < 0 || buf[i] > 127 || (!isalnum(buf[i]) && buf[i] != '.')) {
			buf[i] = '-';
		}
	}
}

void processFileCode(char* buf) {
	for (int i = 0; buf[i] != '\0'; i++) {
		if ((buf[i] >= 0 && buf[i] <= 127) && isalnum(buf[i])) {
			if (isalpha(buf[i]))
				buf[i] = toupper(buf[i]);
		} else {
			buf[i] = '_';
		}
	}
}

string convertLFToCRLF(char* from) {
	string s;
	for (int i = 0; from[i] != '\0'; i++) {
		if (from[i] != '\n')
			s.push_back(from[i]);
		else
			s.append("\r\n");
	}
	return s;
}

int main(int argc, char* argv[]) {
	// Load the template file
	ifstream fin("CodeGenTemplate.cpp");
	char* buffer = new char[4096];
	vector<char> vecbuff;
	do {
		fin.read(buffer, 4096);
		size_t oldsize = vecbuff.size();
		vecbuff.resize(oldsize + fin.gcount());
		memcpy(vecbuff.data() + oldsize, buffer, fin.gcount());
	} while (fin);

	delete[] buffer;
	codeTemp = vecbuff.data();

	bool wantFocus = true;
	bool loadedChineseFont = false;
	bool loading = false;

	time_t ttime = time(NULL);
	int dateYear = localtime(&ttime)->tm_year + 1900,
		dateMonth = localtime(&ttime)->tm_mon + 1,
		dateDay = localtime(&ttime)->tm_mday;

	imgui::SFML::Init(win);
	imgui::GetIO().IniFilename = nullptr;

	//float factor = getHighDpiScaleFactor();
	float factor = 1.0f;
	static ImFontConfig configcour;
	configcour.RasterizerMultiply = 2.5f;
	configcour.OversampleH = 1;
	imgui::GetIO().Fonts->Clear();
	imgui::GetIO().Fonts->AddFontFromFileTTF(R"(C:\Windows\Fonts\cour.ttf)", 16, &configcour);
	imgui::SFML::UpdateFontTexture();
	ImGui::StyleColorsDark();
	auto& style = imgui::GetStyle();
	style.ScaleAllSizes(factor);
	style.FrameBorderSize = 1.0f;
	style.ScrollbarRounding = 0.0f;
	style.WindowRounding = 0.0f;

	//imgui::GetIO().MouseDrawCursor = true;

	win.create(VideoMode(450 * factor, 650 * factor), "Code Generator In ImGui", Style::Titlebar | Style::Close | Style::Resize);
	win.clear(); win.display();
	win.resetGLStates();
	win.setVerticalSyncEnabled(true);
	//win.setFramerateLimit(30);

	Clock deltaClock;
	while (win.isOpen()) {
		if (loading) {
			static ImFontConfig config;
			config.RasterizerMultiply = 3.0f;
			config.OversampleH = 1;
			imgui::GetIO().Fonts->Clear();
			imgui::GetIO().Fonts->AddFontFromFileTTF(R"(C:\Windows\Fonts\simsun.ttc)", 16, &config, imgui::GetIO().Fonts->GetGlyphRangesChineseSimplifiedCommon());
			imgui::SFML::UpdateFontTexture();
			loading = false;
		}

		Event e;
		while (win.pollEvent(e)) {
			imgui::SFML::ProcessEvent(e);

			if (e.type == Event::KeyPressed)
				if (e.key.code == Keyboard::Escape)
					win.close();
			if (e.type == Event::KeyReleased) {
				if (e.key.control) {
					if (e.key.code == Keyboard::F)
						imgui::SetClipboardText(fileName);
					else if (e.key.code == Keyboard::S)
						imgui::SetClipboardText(signature);
					else if (e.key.code == Keyboard::C)
						imgui::SetClipboardText(convertLFToCRLF(totalCode).c_str());
				}
			} else if (e.type == Event::Closed)
				win.close();
		}

		imgui::SFML::Update(win, deltaClock.restart());

		imgui::SetNextWindowSize(win.getSize() + Vector2u(2, 2), ImGuiCond_Always);
		imgui::SetNextWindowPos(ImVec2(-1, -1));
		imgui::SetNextWindowBgAlpha(0.0);
		imgui::Begin("MainFrame", nullptr, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
		if (wantFocus) {
			imgui::SetKeyboardFocusHere();
			wantFocus = false;
		}
		if (imgui::InputText("File Code", fileCode, sizeof(fileCode))) {
			if (fileCode[0] == '\0') {
				fileName[0] = '\0';
				signature[0] = '\0';
				totalCode[0] = '\0';
			} else {
				sprintf(fileName, fileNameTemp, dateYear, dateMonth, dateDay, fileCode);
				sprintf(signature, signatureTemp, dateYear, dateMonth, dateDay, fileCode);
				processFileName(fileName);
				processFileCode(signature);
				sprintf(totalCode, codeTemp, fileName, dateYear, dateMonth, dateDay, signature, topic, signature);
			}
		}
		if (!loadedChineseFont) {
			imgui::SameLine();
			if (imgui::Button("Load Chinese Font")) {
				loadedChineseFont = true;
				loading = true;
			}
		}
		if (imgui::InputText("Comment", topic, sizeof(topic)))
			if (fileCode[0] != '\0')
				sprintf(totalCode, codeTemp, fileName, dateYear, dateMonth, dateDay, signature, topic, signature);
		imgui::Separator();
		imgui::InputText("File Name", fileName, sizeof(fileName));
		imgui::SameLine();
		if (imgui::Button("Copy (Ctrl-F)"))
			imgui::SetClipboardText(fileName);
		imgui::InputText("Signature", signature, sizeof(signature));
		imgui::SameLine();
		if (imgui::Button("Copy (Ctrl-S)"))
			imgui::SetClipboardText(signature);
		imgui::Separator();
		imgui::TextUnformatted("Code");
		imgui::SameLine();
		if (imgui::Button("Copy Code To Clipboard (Ctrl-C)"))
			imgui::SetClipboardText(convertLFToCRLF(totalCode).c_str());
		imgui::PushStyleColor(ImGuiCol_FrameBg, Color(0, 0, 0, 0));
		imgui::InputTextMultiline("##CodeInput", totalCode, sizeof(totalCode), ImVec2(-1, -1), ImGuiInputTextFlags_ReadOnly);
		imgui::PopStyleColor();
		//imgui::BeginChild("Child", ImVec2(0, 0), true);
		//imgui::TextUnformatted(totalCode);
		//imgui::EndChild();
		imgui::End();

		win.clear();
		imgui::SFML::Render(win);
		win.display();
	}

	imgui::SFML::Shutdown();

	return 0;
}

#endif

