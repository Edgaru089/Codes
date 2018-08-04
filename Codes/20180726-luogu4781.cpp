/*
DOCUMENT NAME "20180726-luogu4781.cpp"
CREATION DATE 2018-07-26
SIGNATURE CODE_20180726_LUOGU4781
COMMENT 【模板】拉格朗日插值
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180726_LUOGU4781

#include <cstdlib>
#include <iostream>
using namespace std;

using ull = unsigned long long;

constexpr int MaxN = 2000 + 10;

int n, k, val;
constexpr ull mod = 998244353;
ull x[MaxN], y[MaxN];

ull quickpow(ull base, ull exp, ull mod) {
	ull ans = 1, f = base % mod;
	while (exp != 0) {
		if (exp % 2 == 1)
			ans = (ans * f) % mod;
		f = (f * f) % mod;
		exp /= 2;
	}
	return ans;
}

ull LagrangeBasisPolynomial(int j, ull xval) {
	ull ans1 = 1, ans2 = 1;
	for (int i = 0; i <= k; i++) {
		if (i == j)
			continue;
		ans1 = (ans1 * (xval + mod - x[i])) % mod;
		ans2 = (ans2 * (mod + x[j] - x[i])) % mod;
	}
	return (ans1 * quickpow(ans2, mod - 2, mod)) % mod;
}

ull InterpolationPolynomialInTheLagrangeForm(ull xval) {
	long long val = 0;
	for (int i = 0; i <= k; i++)
		val = (val + (((y[i] % mod) * LagrangeBasisPolynomial(i, xval)) % mod)) % mod;
	return val;
}


int main(int argc, char* argv[]) {

	cin >> n >> val;
	k = n - 1;
	for (int i = 0; i <= k; i++) {
		cin >> x[i] >> y[i];
		x[i] %= mod;
		y[i] %= mod;
	}
	printf("%lld\n", InterpolationPolynomialInTheLagrangeForm(val));
	return 0;
}

#endif

