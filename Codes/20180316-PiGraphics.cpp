/*
DOCUMENT CODE "20180316-PiGraphics.cpp"
CREATION DATE 2018-03-16
SIGNATURE CODE_20180316_PIGRAPHICS
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180316_PIGRAPHICS

#include <cstdlib>
#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>
#include <random>

#include <SFML/Graphics.hpp>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

using namespace std;
using namespace sf;

const double radius = 1024.0;

typedef Rect<Uint32> UintRect;

RenderWindow win;
Image im;
Texture text;
mutex textlock;

long long total = 0, inrange = 0;
vector<long long> totals, inranges;

void threadPi(int id) {
	minstd_rand0 engine((random_device())());
	uniform_real_distribution<double> distribute(0.0, 1.0);
	while (win.isOpen()) {

		double xc = distribute(engine) * radius;
		double yc = distribute(engine) * radius;

		totals[id]++;
		if (xc * xc + yc * yc <= 1048576.0)
			inranges[id]++;

		//textlock.lock();
		im.setPixel(xc, yc, Color(255, 255, 255, 255));
		//textlock.unlock();

		//this_thread::yield();
	}
}

int main(int argc, char* argv[]) {
	srand(time(nullptr));

	im.create(1025, 1025);
	for (int i = 0; i < 1024; i++)
		for (int j = 0; j < 1024; j++)
			im.setPixel(i, j, Color::Transparent);

	text.create(1024, 1024);

	totals.resize(thread::hardware_concurrency(), 0);
	inranges.resize(thread::hardware_concurrency(), 0);

	sfg::SFGUI sfgui;
	sfg::Desktop desktop;

	sfg::Window::Ptr swin = sfg::Window::Create(sfg::Window::BACKGROUND);
	sfg::Table::Ptr table = sfg::Table::Create();
	sfg::Label::Ptr label1 = sfg::Label::Create(L"Steps"), label2 = sfg::Label::Create(L"InRange"), label3 = sfg::Label::Create(L"Pi");
	table->Attach(label1, UintRect(0, 0, 1, 1));
	table->Attach(label2, UintRect(1, 0, 1, 1));
	table->Attach(label3, UintRect(2, 0, 1, 1));
	table->Attach(sfg::Label::Create(to_string(thread::hardware_concurrency()) + " Threads"),
				  UintRect(3, 0, 1, 1));

	swin->SetRequisition(Vector2f(512.0f, 0.0f));
	swin->Add(table);
	desktop.Add(swin);
	desktop.Update(0.0f);

	win.create(VideoMode(512, 512 + swin->GetAllocation().height), "Random Pi Calculator", Style::Titlebar | Style::Close);
	win.setFramerateLimit(30);

	vector<thread*> threads;
	for (int i = 0; i < thread::hardware_concurrency(); i++)
		threads.push_back(new thread(threadPi, i));

	Sprite sp(text);
	text.setSmooth(true);
	sp.setScale((double)win.getSize().x / (double)text.getSize().x, (double)win.getSize().y / (double)text.getSize().y);
	sp.setPosition(0.0f, swin->GetAllocation().height);
	Clock cl;
	cl.restart();
	win.resetGLStates();
	while (win.isOpen()) {

		total = inrange = 0;
		for (int i = 0; i < thread::hardware_concurrency(); i++) {
			total += totals[i];
			inrange += inranges[i];
		}

		label1->SetText("Steps: "s + to_string(total));
		label2->SetText("InRange: "s + to_string(inrange));
		label3->SetText("PiValue: "s + to_string((double)inrange / (double)total*4.0));

		desktop.Update(cl.restart().asSeconds());

		win.clear();

		sfgui.Display(win);

		//textlock.lock();
		text.loadFromImage(im, IntRect(0, 0, 1024, 1024));
		//textlock.unlock();
		win.draw(sp);

		win.display();

		Event event;
		while (win.pollEvent(event)) {
			desktop.HandleEvent(event);
			if (event.type == Event::Closed)
				win.close();
		}
	}

	for (thread*& i : threads)
		i->join();

	return 0;
}

#endif

