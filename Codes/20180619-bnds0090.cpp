/*
DOCUMENT CODE "20180619-bnds0090.cpp"
CREATION DATE 2018-06-19
SIGNATURE CODE_20180619_BNDS0090
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180619_BNDS0090

#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

int n;
int a[100];

int main(int argc, char* argv[]) {

	cin >> n;
	for (int i = 1; i <= n; i++) {
		a[i] = i;
	}

	do {
		for (int i = 1; i <= n; i++)
			cout << a[i];
		cout << endl;
	} while (next_permutation(a + 1, a + n + 1));

	return 0;
}

#endif

