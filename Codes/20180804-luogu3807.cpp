/*
DOCUMENT NAME "20180804-luogu3807.cpp"
CREATION DATE 2018-08-04
SIGNATURE CODE_20180804_LUOGU3807
COMMENT 【模板】卢卡斯定理
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180804_LUOGU3807

#include <cstdlib>
#include <iostream>
using namespace std;

using ll = long long;

int t;
ll n, m, p;

ll qpow(ll base, ll exp, ll mod) {
	ll ans = 1;
	while (exp != 0) {
		if (exp % 2 == 1)
			ans = ans * base%mod;
		base = base * base%mod;
		exp /= 2;
	}
	return ans;
}

ll fact[8000001];
void prepfact(int cnt) {
	fact[0] = 1;
	for (int i = 1; i <= cnt; i++)
		fact[i] = fact[i - 1] * i % p;
}

// C_n^m = frac{n!}{m!\left(n-m\right)!}
ll smallc(int n, int m, int mod) {
	if (n == 0 || m == 0)
		return 0;
	if (n < m)
		return 0;
	return fact[n] * qpow(fact[m], mod - 2, mod) % mod*qpow(fact[n - m], mod - 2, mod) % mod;
}

ll c(int n, int m, int mod) {
	int ans = 1;
	while (n != 0 && m != 0 && ans != 0) {
		ans = ans * smallc(n%mod, m%mod, mod) % mod;
		n /= mod;
		m /= mod;
	}
	return ans;
}


int main(int argc, char* argv[]) {
	cin >> t;
	while (t--) {
		cin >> n >> m >> p;
		prepfact(n + m);
		cout << c(n + m, m, p) << endl;
	}

	return 0;
}

#endif

