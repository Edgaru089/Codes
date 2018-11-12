/*
 DOCUMENT NAME "20181103-luogu1134.cpp"
 CREATION DATE 2018-11-03
 SIGNATURE CODE_20181103_LUOGU1134
 COMMENT P1134 Ω◊≥ÀŒ Ã‚
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181103_LUOGU1134

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

typedef long long ll;

int n;
ll ans;



int main(int argc, char* argv[]) {

	read(n);
	ans = 1;
	for (int i = 1; i <= n; i++) {
		ans *= i;
		while (ans % 10 == 0)
			ans /= 10;
		ans %= 100000000;
	}

	printf("%lld\n", ans % 10);

	return 0;
}

#endif

