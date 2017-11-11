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
#include <thread>
#include <functional>

#include <SFML/System.hpp>

using namespace std;
using namespace sf;

class Foo {
public:
	Foo(int x, int y) :
		x(x), y(y) {}
	Foo(int x) :
		x(x), y(0) {}

	void print() {
		printf("X: %d, Y: %d\n", x, y);
	}

private:
	int x, y;
};


template<class First, class Second, class Third>
class triple {
public:

	First first;
	Second second;
	Third third;

	const bool operator < (triple<First, Second, Third> x) {
		return first < x.first;
	}

	const bool operator > (triple<First, Second, Third> x) {
		return first > x.first;
	}

	const bool operator == (triple<First, Second, Third> x) {
		return first == x.first;
	}

};


const string compileTime = string(__DATE__) + " " + string(__TIME__);

template<typename Type>
inline void safeDelete(Type*& pointer) {
	Type* tmp = pointer;
	pointer = NULL;
	delete tmp;
}

template<class Type, class... Args>
inline Type* allocate(Type*& pointer, Args... args) {
	return pointer = new Type(args...);
}

template<class Object, class Compare>
const bool compare(const Object obj1, const Object obj2, Compare compare) {
	bool result = compare(obj1, obj2);
	return result;
}


pair<char*, Int64> loadFile(string filename) {
	FILE* file = fopen(filename.c_str(), "rb");
	if (file == NULL)
		return pair<char*, Int64>(NULL, 0);

	fseek(file, 0, SEEK_END);
	Int64 size = ftell(file);
	fseek(file, 0, SEEK_SET);

	char* data = new char[size];

	fread(data, 1, size, file);

	return pair<char*, Int64>(data, size);
}


int main(int argc, char* argv[]) {

	auto lam = []() {cout << "Auto Lambda Object" << endl; };

	cout << "Compile Time: " << compileTime << endl;
	cout << "C++ Standard: " << __cplusplus << endl;
	system("PAUSE");

	string filename;
	cout << "Filename: ";
	cin >> filename;

	cout << "Loading...";

	pair<char*, Int64> res = loadFile(filename);

	if (res.first == NULL)
		cout << "Failed." << endl;
	else
		cout << "Complete." << endl;

	system("PAUSE");

	sf::sleep(sf::seconds(0.5f));

	Foo* foo, *bar;
	int ref = 13;

	function<int(int)> func = [&ref](int a)->int {
		cout << "Lambda: " << a << endl;
		ref += a;
		return ref;
	};


	cout << "Constructing thread object" << endl;
	thread th([]() {
		cout << "Calling lambda from thread" << endl;
		for (int i = 1; i <= 5; i++) {
			sf::sleep(sf::seconds(1.0f));
			cout << "\tLoop " << i << endl;
		}
		cout << "Lambda terminating" << endl;
	});

	sf::sleep(sf::seconds(0.5f));

	allocate(foo, 1, 2);
	allocate(bar, 5);

	cout << "Ref: " << ref << endl;
	cout << "Lambda Launcher: " << func(5) << endl;
	cout << "Ref: " << ref << endl;

	foo->print();
	bar->print();

	safeDelete(foo);
	safeDelete(bar);

	th.join();

	thread([]() {cout << "HEllo!" << endl; }).detach();

	return 0;
}

#endif
