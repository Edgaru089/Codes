/*
DOCUMENT NAME "20180901-bnds0823.cpp"
CREATION DATE 2018-09-01
SIGNATURE CODE_20180901_BNDS0823
COMMENT #823. [HAOI2012]ÈÝÒ×Ìâ (luogu2220)
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180901_BNDS0823

#include <cstdlib>
#include <iostream>
#include <map>
#include <set>
#include <cassert>
using namespace std;

typedef long long ll;

const int MaxN = 1e9 + 10, MaxM = 1e9 + 10, MaxK = 1e5 + 10;
const int Mod = 1000000007;

template<typename IntType = int>
IntType read() {
	IntType val = 0;
	int c;
	bool invflag = false;
	while (!isdigit(c = getchar()))
		if (c == '-')
			invflag = true;
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = getchar()));
	ungetc(c, stdin);
	if (invflag)
		return -val;
	else
		return val;
}
template<>
string read<string>() {
	string str;
	str.clear();
	int c;
	while (iscntrl(c = getchar()) || isblank(c));
	do {
		str.push_back(c);
	} while (!(iscntrl(c = getchar()) || isblank(c)));
	ungetc(c, stdin);
	return str;
}
template<typename IntType>
void read(IntType& x) { x = read<IntType>(); }
template<typename IntType, typename... Args>
void read(IntType& x, Args&... args) { x = read<IntType>(); read(args...); }

ll n, m, k;
ll x, y;

map<ll, set<ll>> M;

ll qpow(ll base, ll exp, ll mod) {
	long long ans = 1;
	while (exp != 0) {
		if (exp % 2 == 1)
			ans = ans*base%mod;
		base = base*base%mod;
		exp /= 2;
	}
	assert(ans >= 0);
	return ans;
}




int main(int argc, char* argv[]) {

	read(n, m, k);
	for (ll i = 1; i <= k; i++) {
		read(x, y);
		M[x].insert(y);
	}

	ll ans = qpow((n*(n + 1) / 2) % Mod, m - M.size(), Mod);
	for (auto& i : M) {
		ll ans0 = n*(n + 1) / 2 % Mod;
		for (auto& j : i.second)
			ans0 = (ans0 + Mod - j) % Mod;
		ans = (ans*ans0 + Mod) % Mod;
		assert(ans >= 0);
	}

	printf("%lld\n", ans);

	return 0;
}

#endif

