/*
DOCUMENT NAME "20180812-bnds0759.cpp"
CREATION DATE 2018-08-12
SIGNATURE CODE_20180812_BNDS0759
COMMENT B. 2018-8-12noip模拟测验（二）-篮球比赛2
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180812_BNDS0759

#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int mod = 1e9 + 7;

int ans[21][21][21];
int fx(int n, int k, int l) {
	if (k < 0)
		return 0;
	else if (n == 0)
		if (k == 0)
			return 1;
		else
			return 0;
	else if (k == 0)
		return 1;
	else if (ans[n][k][l] != 0)
		return ans[n][k][l];
	else {
		int a = 0;
		for (int j = 0; j <= min(k, l); j++) {
			a += fx(n - 1, k - j, l);
			a %= mod;
		}
		return ans[n][k][l] = a % mod;
	}
}

int fact(int n, int mod) {
	int ans = 1;
	for (int i = 2; i <= n; i++) {
		ans = (long long)ans*i%mod;
	}
	return ans;
}

int n, k, l;

int main(int argc, char* argv[]) {

	cin >> n >> k >> l;
	if (l > k)
		l = k;

	cout << (long long)fx(n, k, l)*fact(n, mod) % mod << endl;

	return 0;
}

#endif

