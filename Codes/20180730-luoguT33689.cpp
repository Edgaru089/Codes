/*
DOCUMENT NAME "20180730-luoguT33689.cpp"
CREATION DATE 2018-07-30
SIGNATURE CODE_20180730_LUOGUT33689
COMMENT ≤©¿ˆ¡È√Œµƒƒ—Ã‚
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180730_LUOGUT33689

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

using ll = long long;
constexpr int digit = 5, mod = 100000;
constexpr int arrsize = 100;

struct bigint {
	bigint() { memset(digits, 0, sizeof(digits)); }
	bigint(int val) {
		memset(digits, 0, sizeof(digits));
		int id = 0;
		while (val != 0) {
			id++;
			digits[id] = val % mod;
			val /= mod;
		}
	}
	bigint(const bigint& copy) {
		memcpy(digits, copy.digits, sizeof(copy.digits));
	}

	void output() {
		for (int i = 10; i >= 1; i--) {
			for (int j = 10; j >= 1; j--)
				printf("%0*lld", digit, digits[(i - 1) * 10 + j]);
			putchar('\n');
		}
	}

	ll& operator [](const int& index) { return *(digits + index); }
	const ll& operator [](const int& index) const { return *(digits + index); }

	ll digits[500];
};

bigint operator * (const bigint& left, const bigint& right) {
	bigint ans;
	for (int i = 1; i <= arrsize; i++) {
		for (int j = 1; j <= arrsize; j++) {
			ans[i + j - 1] += left[i] * right[j];
			ans[i + j] += ans[i + j - 1] / mod;
			ans[i + j - 1] %= mod;
		}
	}
	return ans;
}


bigint qpow(bigint base, int pow) {
	bigint ans(1);
	while (pow != 0) {
		if (pow % 2 == 1)
			ans = ans * base;
		base = base * base;
		pow /= 2;
	}
	return ans;
}


int main(int argc, char* argv[]) {

	int x, n;
	cin >> x >> n; n++;
	bigint ans = qpow(bigint(x), n);
	ans[1]--;
	ans.output();
	return 0;
}

#endif

