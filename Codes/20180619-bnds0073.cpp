/*
DOCUMENT CODE "20180619-bnds0073.cpp"
CREATION DATE 2018-06-19
SIGNATURE CODE_20180619_BNDS0073
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180619_BNDS0073

#include <cstdlib>
#include <iostream>
#include <string>
#include <cctype>
using namespace std;
string s;
bool flag;
int main(int argc, char* argv[]) {
	cin >> s;
	int count = 0;
	flag = false;
	for (char c : s) {
		if (isdigit(c)) {
			if (!flag)
				count++;
			flag = true;
		}
		else
			flag = false;
	}
	cout << count << endl;
	return 0;
}

#endif

