/*
DOCUMENT NAME "20180901-bnds0829.cpp"
CREATION DATE 2018-09-01
SIGNATURE CODE_20180901_BNDS0829
COMMENT #829. [Ä£°å]³Ë·¨ÄæÔª
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180901_BNDS0829

#include <cstdlib>
#include <iostream>
#include <SFML/System.hpp>
using namespace std;
using namespace sf;

typedef long long ll;
const int MaxN = 1.5e6 + 10;

ll n, p;
ll ans[MaxN];

inline ll qpow(ll base, ll exp, const ll& mod) {
	ll ans = 1;
	while (exp != 0) {
		if (exp % 2 == 1)
			ans = ans*base%mod;
		base = base*base%mod;
		exp /= 2;
	}
	return ans;
}



int main(int argc, char* argv[]) {

	freopen("out.txt", "w", stdout);

	Clock c;

	scanf("%lld%lld", &n, &p);

	for (int i = 1; i <= n; i++)
		printf("%lld\n", qpow(i, p - 2, p));

	Time t = c.getElapsedTime();
	fprintf(stderr, "Exit in %.4f sec, (%d millisec)", t.asSeconds(), t.asMilliseconds());

	return 0;
}

#endif

