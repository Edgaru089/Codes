/*
DOCUMENT CODE "20180619-bnds0080.cpp"
CREATION DATE 2018-06-19
SIGNATURE CODE_20180619_BNDS0080
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180619_BNDS0080

#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

int n;
int a[100];

int main(int argc, char* argv[]) {

	int Min = INT_MAX;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		Min = min(Min, a[i]);
	}

	int flag = -1;
	for (int i = Min; flag == -1 && i >= 1; i--) {
		bool flag0 = true;
		for (int j = 1; j <= n; j++) {
			if (a[j] % i != 0)
				flag0 = false;
		}
		if (flag0) {
			flag = i;
			break;
		}
	}

	cout << flag << endl;

	return 0;
}

#endif

