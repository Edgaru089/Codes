/*
 DOCUMENT NAME "20181103-luogu1313.cpp"
 CREATION DATE 2018-11-03
 SIGNATURE CODE_20181103_LUOGU1313
 COMMENT P1313 ¼ÆËãÏµÊý
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181103_LUOGU1313

#include <cstdlib>
#include <iostream>
using namespace std;

template<typename IntType = int>
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
template<typename IntType, typename... Args>
void read(IntType& val, Args&... args) { read(val); read(args...); }

const int Mod = 10007;
const int MaxK = 1000 + 10;

int a, b, k, n, m;
int pas[MaxK][MaxK];

// C_n^k
int C(int n, int k) {
	return pas[n][k];
}

int qpow(int base, int exp, int mod) {
	long long ans = 1;
	while (exp) {
		if (exp & 1)
			ans = (ans*base) % mod;
		base = base * base%mod;
		exp >>= 1;
	}
	return ans;
}



int main(int argc, char* argv[]) {

	read(a, b, k, n, m);
	a %= Mod;
	b %= Mod;

	for (int i = 0; i <= k; i++)
		pas[i][0] = 1;
	for (int i = 1; i <= k; i++)
		for (int j = 1; j <= i; j++)
			pas[i][j] = (pas[i - 1][j] + pas[i - 1][j - 1]) % Mod;

	printf("%lld\n", ((long long)(qpow(a, n, Mod)*qpow(b, m, Mod)) % Mod)*C(k, n) % Mod);

	return 0;
}

#endif

