/*
DOCUMENT CODE "20180504-luogu1005.cpp"
CREATION DATE 2018-05-04
SIGNATURE CODE_20180504_LUOGU1005
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180504_LUOGU1005

#include <cstdlib>
#include <iostream>
using namespace std;

int n, m;
int a[81][81];

int main(int argc, char* argv[]) {

	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> a[i][j];
		}
	}

	unsigned long long ans = 0;


	return 0;
}

#endif

