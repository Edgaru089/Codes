/*
DOCUMENT CODE "20180619-bnds0096.cpp"
CREATION DATE 2018-06-19
SIGNATURE CODE_20180619_BNDS0096
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180619_BNDS0096

#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

bool flag[6][6];
int n = 5;

int cnt = 0;
int p[6] = { 0,1,2,3,4,5 };

int main(int argc, char* argv[]) {

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> flag[i][j];
		}
	}

	do {

		bool flag1 = true;
		for (int i = 1; i <= n; i++) {
			if (!flag[i][p[i]])
				flag1 = false;
		}

		if (flag1) {
			for (int i = 1; i <= n; i++) {
				if (i != 1)
					cout << " ";
				cout << (char)(p[i] + 'A' - 1);
			}
			cout << endl;
		}

	} while (next_permutation(p + 1, p + n + 1));

	return 0;
}

#endif

