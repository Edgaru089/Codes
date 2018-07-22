/*
DOCUMENT NAME "20180715-bnds0326.cpp"
CREATION DATE 2018-07-15
SIGNATURE CODE_20180715_BNDS0326
COMMENT NOIP2010普及组第一题
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180715_BNDS0326

#include <cstdlib>
#include <iostream>
using namespace std;

int x, y;
int cnt;

int main(int argc, char* argv[]) {

	cin >> x >> y;

	for (int i = x; i <= y; i++) {
		int z = i;
		while (z != 0) {
			if (z % 10 == 2)
				cnt++;
			z /= 10;
		}
	}

	cout << cnt << endl;

	return 0;
}

#endif

