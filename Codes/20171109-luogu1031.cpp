/*
DOCUMENT CODE "luogu1031.cpp"
CREATION DATE 2017-11-09
SIGNATURE CODE_20171109_LUOGU1031
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20171109_LUOGU1031

#include <cstdlib>
#include <iostream>
using namespace std;

int n;
int a[10001];
int ans = 0, sum = 0;

int main(int argc, char* argv[]) {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		sum += a[i];
	}
	for (int i = 1; i <= n; i++)
		a[i] -= sum / n;
	for (int i = 1; i <= n; i++) {
		if (a[i] != 0) {
			ans++;
			a[i + 1] += a[i];
		}
	}
	cout << ans << endl;
	return 0;
}

#endif
