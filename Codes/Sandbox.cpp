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

#include <SFML/Graphics.hpp>

#include "ImGui/imgui-setup.h"

using namespace std;
using namespace sf;


int main(int argc, char* argv[]) {

	//RenderWindow win;

	//win.create(VideoMode(1080, 608), "Title");
	//win.setVerticalSyncEnabled(true);

	//ImGui::SFML::Init(win, true);

	//Clock cl;

	//while (win.isOpen()) {
	//	Event e;
	//	while (win.pollEvent(e)) {
	//		if (e.type == Event::Closed)
	//			win.close();
	//		imgui::SFML::ProcessEvent(e);
	//	}

	//	win.clear();
	//	imgui::SFML::Update(win, cl.restart());

	//	imgui::ShowDemoWindow();

	//	imgui::SFML::Render(win);

	//	win.display();
	//}


	char* ptr = new char;
	int i_ptr;

	i_ptr = ptr;
	i_ptr = "String";

	i_ptr = reinterpret_cast<int>("String");

	cout << i_ptr << endl;
	printf("0x%08x\n", i_ptr);
	printf("%s\n", reinterpret_cast<char*>(i_ptr));

	return 0;
}

#endif
