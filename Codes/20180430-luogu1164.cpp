/*
DOCUMENT CODE "20180430-luogu1164.cpp"
CREATION DATE 2018-04-30
SIGNATURE CODE_20180430_LUOGU1164
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180430_LUOGU1164

#include <cstdlib>
#include <iostream>
using namespace std;

int n, m;
int a[10001], s[10001];

int main(int argc, char* argv[]) {

	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}

	s[0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = m - a[i]; j >= 0; j--) {
			s[j + a[i]] += s[j];
		}
	}
	
	cout << s[m] << endl;

	return 0;
}

#endif

