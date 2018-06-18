/*
DOCUMENT CODE "20180617-luogu1071.cpp"
CREATION DATE 2018-06-17
SIGNATURE CODE_20180617_LUOGU1071
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180617_LUOGU1071

#include <cstdlib>
#include <iostream>
#include <map>
#include <set>
#include <string>
using namespace std;

map<char, char> m;
set<char> used;
string a, b, c;

int main(int argc, char* argv[]) {

	cin >> a >> b >> c;

	bool ok = true;

	for (int i = 0; i < a.length(); i++) {
		auto j = m.find(a[i]);
		if (j == m.end()) {
			if (used.find(b[i]) != used.end()) {
				ok = false;
				break;
			}
			m.insert(pair<char, char>(a[i], b[i]));
			used.insert(b[i]);
		}
		else if (j->second != b[i]) {
			ok = false;
			break;
		}
	}

	if (m.size() < 26)
		ok = false;

	if (!ok)
		cout << "Failed" << endl;
	else {
		for (char i : c) {
			cout << m[i];
		}
		cout << endl;
	}

	return 0;
}

#endif

