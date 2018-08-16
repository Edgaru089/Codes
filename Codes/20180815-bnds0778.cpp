/*
DOCUMENT NAME "20180815-bnds0778.cpp"
CREATION DATE 2018-08-15
SIGNATURE CODE_20180815_BNDS0778
COMMENT A. 2018-8-15noip模拟测验（一）-过去的姬君
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180815_BNDS0778

#include <cstdlib>
#include <iostream>
using namespace std;

using ll = __int128;

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
template<typename IntType>
void read(IntType& x) { x = read<IntType>(); }
template<typename IntType, typename... Args>
void read(IntType& x, Args&... args) { x = read<IntType>(); read(args...); }

#ifdef LOCAL
#define DEBUG(...) (printf(__VA_ARGS__))
#else
#define DEBUG(...)
#endif


// m <= 2
ll C(ll n, ll m) {
	if (n < m)
		return 0;
	else if (m == 0 || n == m)
		return 1;
	else if (m == 1)
		return n;
	else if (m == 2) {
		//if (n <= 6000000)
		//	if (ans[n] != 0)
		//		return ans[n];
		//	else
		//		return ans[n] = C(n - 1, m) + C(n - 1, m - 1);
		//else
		//	return C(n - 1, m) + C(n - 1, m - 1);
		return n * (n - 1) / 2;
	}
	else if (m == 3)
		return n * (n - 1) / 2 * (n - 2) / 3;
	else
		throw;
}

ll fx(ll x) {
	ll a = 0;
	for (int j = 4; j <= x; j++) {
		a += C(j - 1, 2);
	}
	return a + 1;
}

ll getans(ll n, ll k) {
	ll ans = 0;
	ll y = n % k;
	ll x = k - y;
	ll d = n / k;
	ans += C(d, 3) * x;
	ans += C(d + 1, 3)*y;
	DEBUG("Ans(%lld, %lld) = %lld*C(%lld, 3) + %lld*C(%lld+1, 3) = %lld+%lld = %lld\n", n, k, x, d, y, d, C(d, 3) * x, C(d + 1, 3)*y, ans);
	return ans;
}



int main(int argc, char* argv[]) {

	ll n, k;
	read(n, k);
	ll ans = getans(n, k);

	string str;
	while (ans != 0) {
		str.push_back(ans % 10 + '0');
		ans /= 10;
	}

	for (int i = 0; i < str.size() / 2; i++) {
		swap(str[i], str[str.size() - i - 1]);
	}
	printf("%s\n", str.c_str());

	return 0;
}

#endif

