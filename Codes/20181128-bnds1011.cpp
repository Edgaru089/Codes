/*
 DOCUMENT NAME "20181128-bnds1011.cpp"
 CREATION DATE 2018-11-28
 SIGNATURE CODE_20181128_BNDS1011
 COMMENT [HNOI2008]Ò£Ô¶µÄÐÐÐÇ
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181128_BNDS1011

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
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
const int MaxN = 1e5 + 10;

int n;
double a;
int m[MaxN];
ll sum[MaxN];


int main(int argc, char* argv[]) {

	read(n);
	scanf("%lf", &a);

	for (int i = 1; i <= n; i++) {
		read(m[i]);
		sum[i] = sum[i - 1] + m[i];
	}

	for (int i = 1; i <= n; i++) {
		int fl = i * a + 1e-7;
		if (i <= 1000) {
			double ans = 0;
			for (int j = 1; j <= fl; j++)
				ans += (double)m[j] * m[i] / (i - j);
			printf("%lf\n", ans);
		} else
			printf("%lf\n", (double)sum[fl] * m[i] / (i - .5*fl));
	}

	return 0;
}

#endif

