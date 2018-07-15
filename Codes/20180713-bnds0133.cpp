/*
DOCUMENT NAME "20180713-bnds0133.cpp"
CREATION DATE 2018-07-13
SIGNATURE CODE_20180713_BNDS0133
COMMENT 整数区间
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180713_BNDS0133

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int infinity = 1e8;
const int MaxN = 10000 + 10;

template<typename IntType = int>
IntType read() {
	IntType ans = 0;
	char c;
	while (!isdigit(c = getchar()));
	do {
		ans = (ans << 1) + (ans << 3) + c - '0';
	} while (isdigit(c = getchar()));
	return ans;
}

template<typename IntType>
void read(IntType& x) { x = read(); }
template<typename IntType, typename... Args>
void read(IntType& x, Args&... args) { read(x); read(args...); }

int n;
int s[MaxN], t[MaxN];

int cnt[MaxN];

int main(int argc, char* argv[]) {

	int left = infinity, right = 0;
	read(n);
	for (int i = 1; i <= n; i++) {
		read(s[i], t[i]);
		s[i]++; t[i]++;
		left = min(left, s[i]);
		right = max(right, t[i]);
		for (int j = s[i]; j <= t[i]; j++)
			cnt[j]++;
	}

	int cntt = n;
	int ans = 0;
	while (cntt > 0) {
		int maxcnt = 0, maxid = 0;
		for (int i = left; i <= right; i++) {
			if (maxcnt < cnt[i]) {
				maxcnt = cnt[i];
				maxid = i;
			}
		}
		ans++;
		for (int i = 1; i <= n; i++) {
			if (s[i] <= maxid && t[i] >= maxid) {
				for (int j = s[i]; j <= t[i]; j++)
					cnt[j]--;
				cntt--;
			}
		}
	}

	printf("%d\n", ans);

	return 0;
}

#endif

