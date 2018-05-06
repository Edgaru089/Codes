/*
DOCUMENT CODE "20180504-luogu1048.cpp"
CREATION DATE 2018-05-04
SIGNATURE CODE_20180504_LUOGU1048
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180504_LUOGU1048

#include <cstdlib>
#include <iostream>
#include <climits>
using namespace std;

int n, m;
int v[101], w[101];
int s[30001];

int max(const int& a, const int& b) {
	if (a >= b)
		return a;
	else
		return b;
}

int main(int argc, char* argv[]) {

	cin >> m >> n;
	for (int i = 1; i <= n; i++)
		cin >> w[i] >> v[i];

	for (int i = 1; i <= m; i++)
		s[i] = INT_MIN;

	for (int i = 1; i <= n; i++) {
		for (int j = m - w[i]; j >= 0; j--) {
			s[j + w[i]] = max(s[j + w[i]], s[j] + v[i]);
		}
	}

	int Max = 0;
	for (int i = 0; i <= m; i++)
		Max = max(Max, s[i]);

	cout << Max << endl;

	return 0;
}

#endif

