/*
DOCUMENT CODE "20180430-luogu1739.cpp"
CREATION DATE 2018-04-30
SIGNATURE CODE_20180430_LUOGU1739
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180430_LUOGU1739

#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

string str;
int level;

int main(int argc, char* argv[]) {

	cin >> str;

	str.resize(str.find('@'));

	for (char& i : str) {
		if (i == '(')
			level++;
		if (i == ')')
			level--;
		if (level < 0)
			break;
	}

	if (level == 0)
		cout << "YES" << endl;
	else
		cout << "NO" << endl;

	return 0;
}

#endif

