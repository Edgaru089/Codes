/*
DOCUMENT NAME "20180808-bnds0745.cpp"
CREATION DATE 2018-08-08
SIGNATURE CODE_20180808_BNDS0745
COMMENT 2018-8-8模拟测验（三）-理科男（50分暴力）
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180808_BNDS0745

#include <cstdlib>
#include <iostream>
#include <vector>
#include <cstring>
#include <map>
using namespace std;

using ll = long long;

constexpr ll MaxN = 1000000 + 10;

map<ll, ll> last;
ll a, b, k;

ll gcd(ll n, ll m) {
	if (m == 0)
		return n;
	else
		return gcd(m, n%m);
}

ll phi(ll x) {
	ll cnt = 0;
	for (int i = 1; i <= x; i++) {
		if (gcd(x, i) == 1)
			cnt++;
	}
	return cnt;
}

ll qpow(ll a, ll b, ll p) {
	ll ans = 1;
	while (b != 0) {
		if (b % 2 == 1)
			ans = ans * a%p;
		a = a * a%p;
		b /= 2;
	}
	return ans;
}


int main(int argc, char* argv[]) {

	ll t;
	cin >> t;
	while (t--) {
		last.clear();
		cin >> a >> b >> k;
		a %= b;
		ll cnt = 0;
		ll m = -1, r = 0;
		while (a != 0) {
			cnt++;
			auto i = last.find(a);
			if (i != last.end()) {
				m = last[a] - 1;
				r = cnt - last[a];
				break;
			}
			last[a] = cnt;
			a = a * k%b;
		}
		if (m == -1)
			m = cnt;
		printf("%lld %lld\n", m, r);
	}

	return 0;
}

#endif

