/*
DOCUMENT CODE "20180619-bnds0072.cpp"
CREATION DATE 2018-06-19
SIGNATURE CODE_20180619_BNDS0072
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180619_BNDS0072

#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

string s, s1;

int main(int argc, char* argv[]) {

	cin >> s;

	char cur = s[0];
	int cnt = 0;
	s1 += s[0];
	for (char c : s) {
		if (cur != c) {
			if (cnt != 1)
				s1.append(to_string(cnt));
			s1 += c;
			cur = c;
			cnt = 1;
		}
		else {
			cnt++;
		}
	}
	if (cnt != 1)
		s1.append(to_string(cnt));

	cout << s1 << endl;

	return 0;
}

#endif

