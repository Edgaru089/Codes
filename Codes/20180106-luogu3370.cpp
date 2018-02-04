/*
DOCUMENT CODE "20180106-luogu3370.cpp"
CREATION DATE 2018-01-06
SIGNATURE CODE_20180106_LUOGU3370
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180106_LUOGU3370

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <string>
#include <algorithm>
using namespace std;

int Hash(string str, unsigned long long base) {
	unsigned long long val = 0;
	for (char i : str)
		val = val * base + i;
	return val;
}

int val[10001];

int main(int argc, char* argv[]) {

	unsigned long long p1 = 171;

	int n;
	string str;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> str;
		val[i] = Hash(str, p1);
	}

	sort(val + 1, val + n + 1);
	int count = 1;
	for (int i = 2; i <= n; i++) {
		if (val[i - 1] != val[i])
			count++;
	}

	cout << count << endl;

	return 0;
}

#endif

