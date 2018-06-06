/*
DOCUMENT CODE "20180605-luogu1091.cpp"
CREATION DATE 2018-06-05
SIGNATURE CODE_20180605_LUOGU1091
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180605_LUOGU1091

#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

int n, a[200];
int countL[200], countR[200];

int main(int argc, char* argv[]) {

	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}

	for (int i = 1; i <= n; i++) {
		countL[i] = 1;
		for (int j = i - 1; j >= 1; j--) {
			if (a[j] < a[i])
				countL[i] = max(countL[j] + 1, countL[i]);
		}
	}

	for (int i = n; i >= 1; i--) {
		countR[i] = 1;
		for (int j = i + 1; j <= n; j++) {
			if (a[j] < a[i])
				countR[i] = max(countR[j] + 1, countR[i]);
		}
	}

	int ans = n;
	for (int i = 1; i <= n; i++)
		ans = min(ans, (i - countL[i]) + ((n - i + 1) - countR[i]));

	cout << ans << endl;

	return 0;
}

#endif

