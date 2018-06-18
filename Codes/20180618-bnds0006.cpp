/*
DOCUMENT CODE "20180618-bnds0006.cpp"
CREATION DATE 2018-06-18
SIGNATURE CODE_20180618_BNDS0006
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180618_BNDS0006

#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {

	int n, cnt2 = 0, cnt5 = 0;
	cin >> n;

	for (int i = 2; i <= n; i++) {
		int x = i;
		while (x % 2 == 0) {
			cnt2++;
			x /= 2;
		}
		while (x % 5 == 0) {
			cnt5++;
			x /= 5;
		}
	}

	cout << min(cnt2, cnt5) << endl;

	return 0;
}

#endif

