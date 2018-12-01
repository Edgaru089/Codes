/*
 DOCUMENT NAME "20181116-luogu1029.cpp"
 CREATION DATE 2018-11-16
 SIGNATURE CODE_20181116_LUOGU1029
 COMMENT P1029 最大公约数和最小公倍数问题
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181116_LUOGU1029

#include <cstdlib>
#include <iostream>
#include <cmath>
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
int x, y;

ll gcd(ll n, ll m) {
	if (m == 0)
		return n;
	else
		return gcd(m, n%m);
}


int main(int argc, char* argv[]) {

	read(x); read(y);
	ll k = (ll)x*y;

	int n = sqrt((double)k) + 1;
	int ans = 0;

	for (int i = 1; i <= n; i++) {
		if (k%i == 0 && gcd(i, k / i) == x)
			ans++;
	}

	printf("%d\n", 2 * ans);

	return 0;
}

#endif

