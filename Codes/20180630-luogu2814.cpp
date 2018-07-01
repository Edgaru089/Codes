/*
DOCUMENT NAME "20180630-luogu2814.cpp"
CREATION DATE 2018-06-30
SIGNATURE CODE_20180630_LUOGU2814
COMMENT ¼ÒÆ× / STLÏ¹¸ã
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180630_LUOGU2814

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <string>
#include <unordered_map>
using namespace std;

unordered_map<string, string> M;

string Find(string x) {
	if (M[x] != x)
		return Find(M[x]);
	else
		return x;
}

int main(int argc, char* argv[]) {

	char str[100];
	string curfa;

	for (;;) {
		cin >> str;
		if (str[0] == '$')
			break;
		else if (str[0] == '#') {
			curfa = (str + 1);
			if (M[curfa] == "")
				M[curfa] = curfa;
		}
		else if (str[0] == '+') {
			M[string(str + 1)] = curfa;
		}
		else if (str[0] == '?')
			cout << (str + 1) << " " << Find(str + 1) << endl;
	}

	return 0;
}

#endif

