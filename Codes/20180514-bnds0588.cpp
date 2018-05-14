/*
DOCUMENT CODE "20180514-bnds0588.cpp"
CREATION DATE 2018-05-14
SIGNATURE CODE_20180514_BNDS0588
TOPIC test 20150514
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180514_BNDS0588

#include <cstdlib>
#include <iostream>
using namespace std;

int a[1000000];
int n;

int main(int argc, char* argv[]) {

	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}

	if (n < 3) {
		cout << 0 << endl;
		return 0;
	}

	int sum = 0;
	for (int i = 1; i <= n - 2; i++) {
		for (int j = i + 1; j <= n - 1; j++) {
			for (int k = j + 1; k <= n; k++) {
				if (a[i] > a[j] && a[j] > a[k])
					sum++;
			}
		}
	}

	cout << sum << endl;

	return 0;
}

#endif

