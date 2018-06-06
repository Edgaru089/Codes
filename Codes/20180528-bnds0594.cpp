/*
DOCUMENT CODE "20180528-bnds0594.cpp"
CREATION DATE 2018-05-28
SIGNATURE CODE_20180528_BNDS0594
TOPIC Contest 2018-05-28
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180528_BNDS0594

#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

int t, n;
int name;

int a[11][101], delta[11][101];
int s[101];

int main(int argc, char* argv[]) {

	cin >> t >> n >> name;

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= t; j++) {
			cin >> a[i][j];
		}

	for (int i = 1; i <= n; i++) {
		for (int k = t; k >= 0; k--) {
			for (int j = 1; j <= t; j++) {
				int cost = j + name, value = a[i][j];
				if (k - cost >= 0)
					s[k] = max(s[k], s[k - cost] + value);
			}
		}
	}

	int Max = 0;
	for (int i = 1; i <= t; i++)
		Max = max(Max, s[i]);

	cout << Max << endl;

	return 0;
}

#endif

