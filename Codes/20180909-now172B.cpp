/*
 DOCUMENT NAME "20180909-now172B.cpp"
 CREATION DATE 2018-09-09
 SIGNATURE CODE_20180909_NOW172B
 COMMENT B-ÊýÊý×Ö
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180909_NOW172B

#include <cstdlib>
#include <iostream>
#include <set>
using namespace std;

using ll = long long;
constexpr ll MaxN = 1e18;

template<typename IntType = int>
IntType read() {
	IntType ans = 0;
	int c;
	while (!isdigit(c = getchar()));
	do { ans = (ans << 1) + (ans << 3) + c - '0'; } while (isdigit(c = getchar()));
	ungetc(c, stdin);
	return ans;
}
template<typename IntType>
void read(IntType& x) { x = read<IntType>(); }
template<typename IntType, typename... Args>
void read(IntType& x, Args&... args) { x = read<IntType>(); read(args...); }

ll l, r, l1, r1;
struct defactored {
	defactored() :valid(false) { cnt2 = cnt3 = cnt5 = cnt7 = 0; }
	defactored(bool valid) :valid(valid) { cnt2 = cnt3 = cnt5 = cnt7 = 0; }
	ll cnt2, cnt3, cnt5, cnt7;
	bool valid;

	const defactored& operator +=(const defactored& right) {
		if (right.valid) {
			cnt2 += right.cnt2;
			cnt3 += right.cnt3;
			cnt5 += right.cnt5;
			cnt7 += right.cnt7;
		}
		return *this;
	}
};

struct decmp {
	constexpr bool operator()(const defactored& x, const defactored& y) const {
		return (x.cnt2 < y.cnt2) ||
			(x.cnt2 == y.cnt2&&x.cnt3 < y.cnt3) ||
			(x.cnt2 == y.cnt2&&x.cnt3 == y.cnt3&&x.cnt5 < y.cnt5) ||
			(x.cnt2 == y.cnt2&&x.cnt3 == y.cnt3&&x.cnt5 == y.cnt5&&x.cnt7 < y.cnt7);
	}
};

set<defactored, decmp> S;

defactored defactor(ll val) {
	defactored d;
	d.valid = true;
	while (val % 2 == 0) {
		val /= 2;
		d.cnt2++;
	}
	while (val % 3 == 0) {
		val /= 3;
		d.cnt3++;
	}
	while (val % 5 == 0) {
		val /= 5;
		d.cnt5++;
	}
	while (val % 7 == 0) {
		val /= 7;
		d.cnt7++;
	}
	if (val != 1)
		return defactored();
	else
		return d;
}

defactored breakdown(ll val) {
	defactored ans;
	ans.valid = true;
	while (val != 0) {
		int digit = val % 10;
		if (digit == 0)
			return defactored(true);
		auto d = defactor(digit);
		if (d.valid)
			ans += d;
		else
			return defactored();
		val /= 10;
	}
	return ans;
}

int main(int argc, char* argv[]) {

	read(l, r, l1, r1);

	if (r1 - l1 <= 200000) {
		for (int i = l1; i <= r1; i++) {
			auto d = defactor(i);
			if (d.valid)
				S.insert(d);
		}
		ll ans = 0;
		for (ll i = l; i <= r; i++) {
			if (S.find(breakdown(i)) != S.end())
				ans++;
		}
		printf("%lld\n", ans);
	}
	else {
		ll ans = 0;
		for (ll i = l; i <= r; i++) {
			ll val = 1;
			ll x = i;
			while (x != 0) {
				val *= x % 10;
				if (val == 0)
					break;
				x /= 10;
			}
			if (val >= l1 && val <= r1)
				ans++;
		}
		printf("%lld\n", ans);
	}

	return 0;
}

#endif

