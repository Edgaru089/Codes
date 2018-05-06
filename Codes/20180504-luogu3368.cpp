/*
DOCUMENT CODE "20180504-luogu3368.cpp"
CREATION DATE 2018-05-04
SIGNATURE CODE_20180504_LUOGU3368
TOPIC 差分的树状数组
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180504_LUOGU3368

#include <cstdlib>
#include <iostream>
using namespace std;

int n, m;
int a[500001], d[500002];

int lowbit(int x) {
	return x&(-x);
}

void add(int pos, int x) {
	while (pos <= n) {
		d[pos] += x;
		pos += lowbit(pos);
	}
}

int queryPrefixSum(int x) {
	int sum = 0;
	while (x != 0) {
		sum += d[x];
		x -= lowbit(x);
	}
	return sum;
}

int main(int argc, char* argv[]) {
	ios::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		add(i, a[i] - a[i - 1]);
	}

	int t, x, y, k;
	for (int i = 1; i <= m; i++) {
		cin >> t;
		if (t == 1) {
			cin >> x >> y >> k;
			add(x, k);
			add(y + 1, -k);
		}
		else if (t == 2) {
			cin >> x;
			cout << queryPrefixSum(x) << endl;
		}
	}

	return 0;
}

#endif

