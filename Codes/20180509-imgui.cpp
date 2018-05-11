/*
DOCUMENT CODE "20180509-imgui.cpp"
CREATION DATE 2018-05-09
SIGNATURE CODE_20180509_IMGUI
TOPIC Test out some Dear ImGui features
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180509_IMGUI

#include <cstdlib>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "ImGui\imgui-setup.h"

using namespace std;
using namespace sf;


#include <iostream>
#include <string>
#include <ctime>
#include <cstring>
#include <cstdio>
#include <mutex>


using namespace std;

class StringParser {
public:

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


class Log {
public:

	const string logLevelName[5] = { "DEBUG", " INFO", " WARN", "ERROR", "FATAL ERROR" };

	enum LogLevel {
		Debug,
		Info,
		Warning,
		Error,
		FatalError
	};

	Log() :ignoreLevel(-1) {}
	Log(ostream& output) :out({ &output }), ignoreLevel(-1) {}
	Log(ostream* output) :out({ output }), ignoreLevel(-1) {}

	void log(string content, LogLevel level = Info) {
		if (level <= ignoreLevel) return;
		time_t curtime = time(NULL);
		char buffer[64];
		strftime(buffer, 63, "[%T", localtime(&curtime));
		string final = string(buffer) + " " + logLevelName[level] + "]: " + content;
		lock.lock();
		this->buffer += final + '\n';
		for (ostream* i : out) {
			(*i) << final << '\n';
			i->flush();
		}
		for (const auto& i : outf)
			i(final);
		lock.unlock();
	}

	template<typename... Args>
	void logf(LogLevel level, string format, Args... args) {
		char buf[2560];
		sprintf_s(buf, 2560, format.c_str(), args...);
		log(string(buf), level);
	}

	void operator() (string content, LogLevel level = Info) {
		log(content, level);
	}

	void addOutputStream(ostream& output) { out.push_back(&output); }
	void addOutputStream(ostream* output) { out.push_back(output); }
	void addOutputHandler(function<void(const string&)> output) { outf.push_back(output); }

	// Lower and equal; use -1 to ignore nothing
	void ignore(int level) { ignoreLevel = level; }

	const string& getBuffer() { return buffer; }

private:
	vector<ostream*> out;
	vector<function<void(const string&)>> outf;
	recursive_mutex lock;
	int ignoreLevel;

	string buffer;
};

Log dlog;

class LogMessage {
public:

	LogMessage() :level(Log::Info) {}
	LogMessage(Log::LogLevel level) :level(level) {}

	LogMessage& operator <<(bool                data) { buffer += StringParser::toString(data); return *this; }
	LogMessage& operator <<(char                data) { buffer += (data); return *this; }
	LogMessage& operator <<(unsigned char       data) { buffer += StringParser::toString(data); return *this; }
	LogMessage& operator <<(short               data) { buffer += StringParser::toString(data); return *this; }
	LogMessage& operator <<(unsigned short      data) { buffer += StringParser::toString(data); return *this; }
	LogMessage& operator <<(int                 data) { buffer += StringParser::toString(data); return *this; }
	LogMessage& operator <<(unsigned int        data) { buffer += StringParser::toString(data); return *this; }
	LogMessage& operator <<(long long           data) { buffer += StringParser::toString(data); return *this; }
	LogMessage& operator <<(unsigned long long  data) { buffer += StringParser::toString(data); return *this; }
	LogMessage& operator <<(float               data) { buffer += StringParser::toString(data); return *this; }
	LogMessage& operator <<(double              data) { buffer += StringParser::toString(data); return *this; }
	LogMessage& operator <<(const char*         data) { buffer += string(data); return *this; }
	LogMessage& operator <<(const std::string&  data) { buffer += data; return *this; }

	LogMessage& operator <<(Log::LogLevel      level) { this->level = level;  return *this; }
	LogMessage& operator <<(Log&                 log) { flush(log);  return *this; }

public:

	void setLevel(Log::LogLevel level) { this->level = level; }
	void flush(Log& log) { logout(log); clear(); }
	void logout(Log& log) { log(buffer, level); }
	void clear() { buffer = ""; }

private:
	string buffer;
	Log::LogLevel level;
};

#define mlog LogMessage()
#define mlogd LogMessage(Log::Debug)


void showMyLogWindow() {
	static bool open = true;

	imgui::Begin("Log", &open);

	imgui::BeginChild(324359, Vector2i(0, 0), true);

	imgui::Text((dlog.getBuffer() + '\n').c_str(), "");
	imgui::SetScrollY(imgui::GetScrollMaxY());
	imgui::EndChild();

	imgui::End();
}


int main(int argc, char* argv[]) {
	sf::RenderWindow window(sf::VideoMode(1600, 900), "ImGui + SFML = <3");
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);

	float color[3] = { 0.95f, 0.95f, 0.95f };

	dlog.addOutputStream(cout);

	ImGui::StyleColorsClassic();
	
	/*
	if (ImGui::BeginMainMenuBar()) {

		if (ImGui::BeginMenu("Files")) {

			if (ImGui::MenuItem("Open File")) {
				mlog << "[Menu] OpenFile clicked" << dlog;
			}

			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}*/

	sf::Clock deltaClock;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		ImGui::SFML::Update(window, deltaClock.restart());

		ImGui::ShowDemoWindow();

		ImGui::Begin("Hello, world!");

		ImGui::ColorEdit3("Background", color);

		ImGui::ShowStyleEditor();

		ImGui::End();

		showMyLogWindow();

		window.clear(Color(255 * color[0], 255 * color[1], 255 * color[2]));
		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();
	return 0;
}

#endif

