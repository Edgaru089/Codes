/*
DOCUMENT CODE "Metadata.cpp"
CREATION DATE 2017-10-08
SIGNATURE CODE_20171008_METADATA
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20171008_METADATA

#include <cstdlib>
#include <iostream>

#include <SFML/Graphics.hpp>

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

using namespace std;
using namespace sfg;

using sf::Vector2f;
using sf::RenderWindow;
using sf::VideoMode;
using sf::Event;
using sf::Clock;


#define WINDOW_WIDTH   800
#define WINDOW_HEIGHT  600
#define WINDOW_SIZE    WINDOW_WIDTH, WINDOW_HEIGHT


int main(int argc, char* argv[]) {

	////////////////////////////////////////////////////////////
	//                 GUI Initalaization                     //
	////////////////////////////////////////////////////////////

	SFGUI sfgui;
	//sfgui.AddCharacterSet(0x4E00, 0x9FEA); // CJK Unified Ideographs Range: 4E00¨C9FEA

	Desktop desktop;

	Window::Ptr loginWindow = Window::Create(Window::TITLEBAR | Window::BACKGROUND);
	loginWindow->SetTitle("Login Window");


	Window::Ptr loginProgressWindow = Window::Create(Window::TITLEBAR | Window::BACKGROUND | Window::SHADOW);
	loginProgressWindow->SetTitle("Please Wait...");
	loginProgressWindow->Show(false);

	Box::Ptr loginProgressBox = Box::Create(Box::Orientation::VERTICAL, 15.0f);
	Button::Ptr loginCancelButton = Button::Create("Cancel");
	loginCancelButton->GetSignal(Button::OnLeftClick).Connect([&loginWindow, &loginProgressWindow]() {
		loginProgressWindow->Show(false);
	});

	loginProgressBox->Pack(Label::Create("Logging in..."), true);
	loginProgressBox->Pack(loginCancelButton, false);
	loginProgressWindow->Add(loginProgressBox);
	

	Box::Ptr loginWindowBox = Box::Create(Box::Orientation::VERTICAL, 15.0f);

	Entry::Ptr usernameEntry = Entry::Create();
	Entry::Ptr passwordEntry = Entry::Create();
	usernameEntry->SetRequisition(Vector2f(250, 25));
	passwordEntry->SetRequisition(Vector2f(250, 25));
	passwordEntry->HideText('*');

	Label::Ptr usernameLabel = Label::Create("Username");
	Label::Ptr passwordLabel = Label::Create("Password");

	Box::Ptr usernameBox = Box::Create(Box::Orientation::HORIZONTAL, 8.0f), passwordBox = Box::Create(Box::Orientation::HORIZONTAL, 8.0f);

	Button::Ptr loginButton = Button::Create("Login");
	loginButton->GetSignal(Button::OnLeftClick).Connect([&usernameEntry, &passwordEntry, &loginProgressWindow, &desktop]() {
		cout << "Logging in..." << endl;
		cout << "  Username: " << usernameEntry->GetText().toAnsiString() << endl;
		cout << "  Password: " << passwordEntry->GetText().toAnsiString() << endl;
		loginProgressWindow->SetPosition(Vector2f((WINDOW_WIDTH - loginProgressWindow->GetRequisition().x) / 2,
			(WINDOW_HEIGHT - loginProgressWindow->GetRequisition().y) / 2 - 100));
		loginProgressWindow->Show(true);
		loginProgressWindow->GrabFocus();
		desktop.BringToFront(loginProgressWindow);
	});

	usernameBox->Pack(usernameLabel, false);
	usernameBox->Pack(usernameEntry);
	passwordBox->Pack(passwordLabel, false);
	passwordBox->Pack(passwordEntry);

	loginWindowBox->Pack(usernameBox);
	loginWindowBox->Pack(passwordBox);
	loginWindowBox->Pack(loginButton);

	loginWindow->Add(loginWindowBox);

	desktop.Add(loginWindow);
	desktop.Add(loginProgressWindow);
	desktop.Update(0.0f);
	loginWindow->SetPosition(Vector2f((WINDOW_WIDTH - loginWindow->GetRequisition().x) / 2,
		(WINDOW_HEIGHT - loginWindow->GetRequisition().y) / 2 - 100));
	loginProgressWindow->SetPosition(Vector2f((WINDOW_WIDTH - loginProgressWindow->GetRequisition().x) / 2,
		(WINDOW_HEIGHT - loginProgressWindow->GetRequisition().y) / 2 - 100));


	////////////////////////////////////////////////////////////
	//                      Game Loop                         //
	////////////////////////////////////////////////////////////

	Clock clock;
	Event event;
	RenderWindow win(VideoMode(WINDOW_SIZE), "Window", sf::Style::Titlebar | sf::Style::Close);
	win.setFramerateLimit(120);
	win.resetGLStates();
	while(win.isOpen()) {

		desktop.Update(clock.restart().asSeconds());

		win.clear();
		sfgui.Display(win);
		win.display();

		while(win.pollEvent(event)) {
			desktop.HandleEvent(event);

			if(event.type == Event::Closed)
				win.close();
		}
	}

	return 0;
}

#endif
