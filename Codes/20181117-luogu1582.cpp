/*
 DOCUMENT NAME "20181117-luogu1582.cpp"
 CREATION DATE 2018-11-17
 SIGNATURE CODE_20181117_LUOGU1582
 COMMENT P1582 µ¹Ë®
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181117_LUOGU1582

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
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

template<typename IntType>
IntType lowbit(IntType x) {
	return x & (-x);
}

template<typename IntType>
int popcount(IntType x) {
	int ans = 0;
	while (x) {
		if (x & 1)
			ans++;
		x >>= 1;
	}
	return ans;
}

ll n, k;


int main(int argc, char* argv[]) {

	read(n); read(k);

	ll ans = 0;
	while (popcount(n) > k) {
		ans += lowbit(n);
		n += lowbit(n);
	}

	printf("%lld\n", ans);

	return 0;
}

#endif

