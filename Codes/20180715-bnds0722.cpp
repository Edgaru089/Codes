/*
DOCUMENT NAME "20180715-bnds0722.cpp"
CREATION DATE 2018-07-15
SIGNATURE CODE_20180715_BNDS0722
COMMENT 2018-7-15»ù´¡²âÑé£¨Èý£©-ÃÜÂë
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180715_BNDS0722

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int MaxS = 100000 + 10;

char str[MaxS];
int len;
int m;

int getminchar(char str[], int len, int offset, int minidmax) {
	char minchar = (char)126;
	int minid = 0;
	for (int i = offset; i < min(len, minidmax); i++) {
		if (minchar > str[i]) {
			minchar = str[i];
			minid = i;
		}
	}
	return minid;
}

int main(int argc, char* argv[]) {

	ios::sync_with_stdio(false);

	cin >> m >> str;
	len = strlen(str);

	for (int i = 0; i < len - 1 && m > 0; i++) {
		int minid = getminchar(str, len, i, m + i + 1);
		m -= (minid - i);
		for (int j = minid; j > i; j--)
			swap(str[j], str[j - 1]);
	}

	if (m > 0) {
		if (m % 2 == 1)
			swap(str[len - 1], str[len - 2]);
	}

	cout << str << endl;


	return 0;
}

#endif

