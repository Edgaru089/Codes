/*
DOCUMENT CODE "20180504-luogu3374.cpp"
CREATION DATE 2018-05-04
SIGNATURE CODE_20180504_LUOGU3374
TOPIC Ê÷×´Êý×é
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180504_LUOGU3374

#include <cstdlib>
#include <iostream>
using namespace std;

int d[500001];
int n, m;

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

int querySection(int x, int y) {
	return queryPrefixSum(y) - queryPrefixSum(x - 1);
}

int main(int argc, char* argv[]) {
	
	cin >> n >> m;
	int t, x, y;
	for (int i = 1; i <= n; i++) {
		cin >> t;
		add(i, t);
	}
	for (int i = 1; i <= m; i++) {
		cin >> t >> x >> y;
		if (t == 1)
			add(x, y);
		else if (t == 2)
			cout << querySection(x, y) << endl;
	}

	return 0;
}

#endif

