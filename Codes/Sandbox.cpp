/*
DOCUMENT CODE "Sandbox.cpp"
CREATION DATE 2017-05-18
SIGNATURE CODE_SANDBOX
TOPIC 沙箱 用来写一些没用的测试性东西
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_SANDBOX

//#include <cstdlib>
//#include <iostream>
//#include <fstream>
//
//#include <SFML/Graphics.hpp>
//
//#include "ImGui/imgui-setup.h"
//
//using namespace std;
//using namespace sf;
//
//String u8ToSfString(string u8string) { return String::fromUtf8(u8string.begin(), u8string.end()); }
//String u8ToSfString(char* u8string) { return String::fromUtf8(u8string, u8string + strlen(u8string)); }
//
//string wideToMultibyte(wstring wstr) {
//	string buf(MB_CUR_MAX, 0);
//	string ans;
//	for (wchar_t c : wstr) {
//		int ret = wctomb(&buf[0], c);
//		cout << "multibyte char " << buf << " is " << ret << " bytes\n";
//		ans.append(buf);
//	}
//	cout << "return: " << ans << endl;
//	return ans;
//}
//
//int main(int argc, char* argv[]) {
//
//	setlocale(LC_CTYPE, "zh-CN");
//
//	//RenderWindow win;
//
//	//win.create(VideoMode(1080, 608), u8ToSfString(u8"Dear ImGui WIP|β"));
//	//win.setVerticalSyncEnabled(true);
//
//	//ImGui::SFML::Init(win, true);
//
//	//Clock cl;
//
//	//while (win.isOpen()) {
//	//	Event e;
//	//	while (win.pollEvent(e)) {
//	//		if (e.type == Event::Closed)
//	//			win.close();
//	//		imgui::SFML::ProcessEvent(e);
//	//	}
//
//	//	win.clear();
//	//	imgui::SFML::Update(win, cl.restart());
//
//	//	imgui::ShowDemoWindow();
//
//	//	imgui::SFML::Render(win);
//
//	//	win.display();
//	//}
//
//
//	//char* ptr = new char;
//	//int i_ptr;
//
//	//i_ptr = ptr;
//	//i_ptr = "String";
//
//	//i_ptr = reinterpret_cast<int>("String");
//
//	//cout << i_ptr << endl;
//	//printf("0x%08x\n", i_ptr);
//	//printf("%s\n", reinterpret_cast<char*>(i_ptr));
//
//	cout << "αβγσπ 一二三四五" << endl;
//	cout << wideToMultibyte(u8ToSfString(u8"αβγσπ 一二三四五").toWideString()) << endl;
//	wcout << u8ToSfString(u8"αβγσπ 一二三四五").toWideString() << endl;
//
//	ifstream fin("utf8.txt");
//	string str;
//	char sign[4];
//	if (fin.get() == 0xEF)
//		fin.ignore(2);
//	else
//		fin.unget();
//	while (!getline(fin, str).eof())
//		wcout << u8ToSfString(str).toWideString() << endl;
//
//	return 0;
//}

#define LOCAL
#define DEBUG

#include <cstdlib>
#include <fstream>

#include <set>
#include <stack>
#include <string>
#include <climits>
#include <vector>
#include <algorithm>

#ifdef LOCAL
#include <iostream>
#else
std::ifstream cin("complexity.in");
std::ofstream cout("complexity.out");
#endif

using namespace std;

int t;
int p;
int nP, nPcur, nPMax;

stack<bool> didNPIncrease;
stack<string> loops;
multiset<string> used;


bool isOk;

bool isLoopTerminated;
string terminateVar;


int state;
const int Increase = 1, Decrease = 2;
int peakCount = 0;

const int toInt(string str) {
	int a = 0;
	if (sscanf(str.c_str(), "%d", &a) <= 0)
		return INT_MIN;
	else
		return a;
}

const string toStr(int x) {
	char buffer[24];
	sprintf(buffer, "%d", x);
	return string(buffer);
}

const int getFactor(string str) {
	string sub = str.substr(2, str.size() - 2);
	if (sub[0] == '1')
		return 0;
	else {
		sub = sub.substr(2, sub.size() - 2);
		return toInt(sub);
	}
}

/*
template<typename... Args>
const string sprintf(string& format,Args... args){
char* buffer=new char[8192]; // 8KB
sprintf(buffer,format.c_str(),args...);
return string(buffer);
}*/

void debug(string str, bool noEndl = false) {
#ifdef DEBUG
	cout << "DEBUG: " << str;
	if (!noEndl)
		cout << endl;
#endif
}

void local(string str, bool noEndl = false) {
#ifdef LOCAL
	cout << "LOCAL: " << str;
	if (!noEndl)
		cout << endl;
#endif
}

void onIncrease() {
	if (state != Increase)
		state = Increase;
}

void onDecrease() {
	if (state != Decrease) {
		state = Decrease;
		peakCount++;
	}
}

int main() {

	cin >> t;

	//per program
	for (int l = 1; l <= t; l++) {
		debug("Loop #" + toStr(l) + " Starting");

		while (!loops.empty())
			loops.pop();
		used.clear();
		isLoopTerminated = false;

		string str;
		cin >> p >> str;

		nP = getFactor(str);
		nPcur = 0;
		nPMax = 0;
		isOk = true;

		//per instruction
		for (int i = 1; i <= p; i++) {
			char c;
			string var, a, end;
			bool didIncrease = false;

			while ((true, cin >> c) && !isalpha(c));

			if (c == 'F') {

				cin >> var >> a >> end;

				debug(string("F Loop Starts: ") + var);

				//variable redefined
				if (used.find(var) != used.end()) {
					debug("ERROR: variable redefined");
					isOk = false;
				}

				//add variable
				used.insert(var);
				loops.push(var);

				//parse loop params
				if (a == "n"&&end != "n") {
					//loop cannot enter; loop terminates
					debug(string("Loop ") + var + " cannot enter; loop terminates");

					if (!isLoopTerminated)
						terminateVar = var;
					isLoopTerminated = true;
				}
				else if (a == "n"&&end == "n") {
					debug(string("Loop ") + var + " cannot enter; a == b == n");
					//do nothing
				}
				else {

					int loopstart = toInt(a);

					//O(n) loop
					if (end == "n") {
						//if not terminated
						if (!isLoopTerminated) {
							nPcur++;
							didIncrease = true;
							onIncrease();
						}
					}
					else {
						int loopend = toInt(end);
						if (loopstart <= loopend) {
							//do nothing; O(1) loop
						}
						else {
							//loop cannot enter; loop terminates
							debug(string("Loop ") + var + " cannot enter; loop terminates");

							if (!isLoopTerminated)
								terminateVar = var;
							isLoopTerminated = true;
						}
					}
				}
				didNPIncrease.push(didIncrease);
			}
			else if (c == 'E') {

				//stack empty; F/E mismatch (missing F; extra E)
				if (loops.empty()) {
					debug("ERROR: stack empty; F/E mismatch (missing F; extra E)");
					isOk = false;
				}
				else {
					//a loop ends here
					string var = loops.top();
					loops.pop();
					bool didIncrease = didNPIncrease.top();
					didNPIncrease.pop();
					used.erase(used.find(var));

					debug(string("E Loop Ends: ") + var);

					//nPcur--; 
					nPMax = max(nPMax, nPcur);
					if (didIncrease) {
						nPcur--;
						onDecrease();
					}

					if (isLoopTerminated&&terminateVar == var) {
						isLoopTerminated = false;
					}

					//if stack empty now -> recursive loop ends
					if (loops.empty()) {
						debug(string("Stack empty, recursive loops end, var: ") + var);
						nPcur = 0;
						isLoopTerminated = false;
					}
				}
			}
		}

		//if stack not empty -> F/E mismatch (missing E)
		if (!loops.empty()) {
			debug("ERROR: stack not empty -> F/E mismatch (missing E)");
			isOk = false;
		}


		debug(string("Loop #") + toStr(l) + ": nPans = " + toStr(nPMax) + ", Peaks: " + toStr(peakCount) + ", result: ", true);

		//if(peakCount>1)
		//	nPMax=-1;

		if (!isOk)
			cout << "ERR" << endl;
		else if (nPMax == nP)
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
	}

	return 0;
}



#endif
