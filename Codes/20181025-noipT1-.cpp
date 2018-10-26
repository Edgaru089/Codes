/*
 DOCUMENT NAME "20181025-noipT1-.cpp"
 CREATION DATE 2018-10-25
 SIGNATURE CODE_20181025_NOIPT1_
 COMMENT naive的瓶子 (colour)（回来做的）
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181025_NOIPT1_

#include <cstdlib>
#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

template<typename IntType>
void read(IntType& val) {
	val = 0;
	int c;
	bool inv = false;
	while (!isdigit(c = getchar()))
		if (c == '-')
			inv = true;
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = getchar()));
	if (inv)
		val = -val;
}

typedef long long ll;
const int MaxN = 300 + 10;

int n;
ll a[MaxN];
ll f[MaxN], g[MaxN];
set<ll> S;




int main(int argc, char* argv[]) {

	read(n);
	for (int i = 1; i <= n; i++) {
		read(a[i]);
		S.insert(a[i]);
	}

	for (set<ll>::iterator it = S.begin(); it != S.end(); it++) {
		ll i = *it;

		for (int j = 1; j <= n; j++)
			f[j] = f[j - 1] + i * (a[j] == i ? 0 : a[j]);
		for (int j = 1; j <= n; j++) {
			ll minval = 1e8;
			ll sum = 0;
			for (int k = j; k <= n; k++) {
				minval = min(minval, a[k]);
				sum += a[k];
				f[k] = min(f[k], sum*minval + minval * i*(k - j + 1) + f[j - 1]);
			}
		}

		for (int j = n; j >= 1; j--)
			f[j] = f[j + 1] + i * (a[j] == i ? 0 : a[j]);
		for (int j = n; j >= 1; j--) {
			ll minval = 1e8;
			ll sum = 0;
			for (int k = j; k >= 1; k--) {
				minval = min(minval, a[k]);
				sum += a[k];
				f[k] = min(f[k], sum*minval + minval * i*(k - j + 1) + f[j - 1]);
			}
		}

	}


	return 0;
}

#endif

