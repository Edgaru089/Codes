/*
DOCUMENT NAME "20180722-uoj0009.cpp"
CREATION DATE 2018-07-22
SIGNATURE CODE_20180722_UOJ0009
COMMENT ¡¾UTR #1¡¿vfkµÄÊý¾Ý
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180722_UOJ0009

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

struct str {
	string content;
	long double id = 0;
};

int n;
str sdata[10000 + 10];

int main(int argc, char* argv[]) {

	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> sdata[i].content;
		int j = 0;
		while (!isdigit(sdata[i].content[j]))j++;
		while (isdigit(sdata[i].content[j])) {
			sdata[i].id = sdata[i].id * 10 + sdata[i].content[j] - '0';
			j++;
		}
	}

	sort(sdata + 1, sdata + n + 1, [](const str& x, const str& y) {
		return x.id < y.id;
	});

	for (int i = 1; i <= n; i++)
		cout << sdata[i].content << endl;

	return 0;
}

#endif

