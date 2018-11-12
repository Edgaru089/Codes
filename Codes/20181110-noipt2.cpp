/*
 DOCUMENT NAME "20181110-noipt2.cpp"
 CREATION DATE 2018-11-10
 SIGNATURE CODE_20181110_NOIPT2
 COMMENT NOIP2018D1T2 ªı±“œµÕ≥
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181110_NOIPT2

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cctype>
#include <cstring>
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

int n;
int a[1000];
int s[25010];



int main(int argc, char* argv[]) {

	int t;
	read(t);

	while (t--) {
		read(n);
		memset(s, 0, sizeof(s));
		int maxa = 0;
		for (int i = 1; i <= n; i++) {
			read(a[i]);
			s[a[i]]++;
			maxa = max(maxa, a[i]);
		}

		for (int i = 1; i <= n; i++) {
			for (int j = a[i]; j <= maxa; j++) {
				s[j] += s[j - a[i]];
			}
		}

		int ans = 0;
		for (int i = 1; i <= n; i++) {
			if (s[a[i]] == 1)
				ans++;
		}

		printf("%d\n", ans);
	}

	return 0;
}

#endif

