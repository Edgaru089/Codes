/*
DOCUMENT NAME "20180808-bnds0164.cpp"
CREATION DATE 2018-08-08
SIGNATURE CODE_20180808_BNDS0164
COMMENT ºÚ°×Æå×ÓµÄÒÆ¶¯
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180808_BNDS0164

#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

int n;

int step = 0;
void solve(int n, string& str) {
	if (n > 4) {
		swap(str[n - 1], str[2 * n]);
		swap(str[n], str[2 * n + 1]);
		cout << "step " << ++step << ":" << str << endl;
		swap(str[n - 1], str[2 * n - 1]);
		swap(str[n], str[2 * n - 2]);
		cout << "step " << ++step << ":" << str << endl;
		solve(n - 1, str);
	}
	else {
		cout << "step " << ++step << ":" << "ooo--***o*" << str.substr(2 * n + 2) << endl;
		cout << "step " << ++step << ":" << "ooo*o**--*" << str.substr(2 * n + 2) << endl;
		cout << "step " << ++step << ":" << "o--*o**oo*" << str.substr(2 * n + 2) << endl;
		cout << "step " << ++step << ":" << "o*o*o*--o*" << str.substr(2 * n + 2) << endl;
		cout << "step " << ++step << ":" << "--o*o*o*o*" << str.substr(2 * n + 2) << endl;
	}
}


int main(int argc, char* argv[]) {

	cin >> n;

	string str = string(n, 'o') + string(n, '*') + "--";
	cout << "step 0:" << str << endl;
	solve(n, str);

	return 0;
}

#endif

