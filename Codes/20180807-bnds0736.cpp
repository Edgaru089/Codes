/*
DOCUMENT NAME "20180807-bnds0736.cpp"
CREATION DATE 2018-08-07
SIGNATURE CODE_20180807_BNDS0736
COMMENT Drying / 二分答案
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180807_BNDS0736

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;

constexpr int MaxN = 100000 + 10;

template<typename IntType = int>   // 模板默认类型需要C++11
IntType read() {
	IntType val = 0;
	int c;
	while (!isdigit(c = getchar()));
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = getchar()));
	ungetc(c, stdin);
	return val;
}

template<typename IntType>
void read(IntType& x) { x = read<IntType>(); }
template<typename IntType, typename... Args>     // 模板参数包需要C++11
void read(IntType& x, Args&... args) { x = read<IntType>(); read(args...); }

int n;
int a[MaxN], ax[MaxN], k;

bool check(int time) {
	int kt = k - 1;
	memcpy(ax + 1, a + 1, sizeof(int)*n);
	int t0 = 0;
	for (int i = 1; i <= n; i++) {
		ax[i] -= time;
		t0 += ceil((double)ax[i] / kt);
	}
	if (t0 <= time)
		return true;
	else
		return false;
}

int main(int argc, char* argv[]) {

	read(n);
	int maxa = 0;
	for (int i = 1; i <= n; i++) {
		read(a[i]);
		maxa = max(maxa, a[i]);
	}
	read(k);

	int l = 1, r = maxa;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(mid))
			r = mid;
		else
			l = mid;
	}

	if (check(l))
		cout << l << endl;
	else
		cout << r << endl;

	return 0;
}

#endif

