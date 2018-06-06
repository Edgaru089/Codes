/*
DOCUMENT CODE "20180528-bnds0592.cpp"
CREATION DATE 2018-05-28
SIGNATURE CODE_20180528_BNDS0592
TOPIC Contest 2018-05-28
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180528_BNDS0592

#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int bits[300001][31];
int sums[31];

void breakDown(int val, int id) {
	int *bit = bits[id];
	int i = 0, x = 2;
	while (val > 0) {
		bit[i] = val % x;
		val /= 2;
		i++;
	}
}

int n, a[300001];
vector<int> indexs;

int main(int argc, char* argv[]) {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		breakDown(a[i], i);
	}

	int Max = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j < i; j++)
			Max = max(Max, a[i] & a[j]);

	cout << Max << endl;

	return 0;
}

#endif

