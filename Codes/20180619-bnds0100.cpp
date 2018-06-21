/*
DOCUMENT CODE "20180619-bnds0100.cpp"
CREATION DATE 2018-06-19
SIGNATURE CODE_20180619_BNDS0100
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180619_BNDS0100

#include <cstdlib>
#include <iostream>
#include <stack>
#include <string>
using namespace std;

string str;
stack<char> s;

int main(int argc, char* argv[]) {

	cin >> str;
	for (char c : str) {
		if (c == '(' || c == ')' || c == '[' || c == ']') {
			if (c == '(' || c == '[')
				s.push(c);
			else {
				if (c == ')') {
					if (s.empty()) {
						cout << "NO" << endl;
						return 0;
					}
					char a = s.top(); s.pop();
					if (a != '(') {
						cout << "NO" << endl;
						return 0;
					}
				}
				else if (c == ']') {
					if (s.empty()) {
						cout << "NO" << endl;
						return 0;
					}
					char a = s.top(); s.pop();
					if (a != '[') {
						cout << "NO" << endl;
						return 0;
					}
				}
			}
		}
	}

	if (!s.empty())
		cout << "NO" << endl;
	else
		cout << "YES" << endl;

	return 0;
}

#endif

