/*
DOCUMENT NAME "20180812-bnds0758.cpp"
CREATION DATE 2018-08-12
SIGNATURE CODE_20180812_BNDS0758
COMMENT A. 2018-8-12noip模拟测验（一）-篮球比赛1
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180812_BNDS0758

#include <cstdlib>
#include <iostream>
using namespace std;

constexpr int MaxN = 1000 + 10, MaxState = 1024;
constexpr int Mod = 1000000007;

template<typename IntType = int>
IntType read() {
	IntType val = 0;
	int c;
	bool invflag = false;
	while (!isdigit(c = getchar()))
		if (c == '-')
			invflag = true;
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = getchar()));
	ungetc(c, stdin);
	if (invflag)
		return -val;
	else
		return val;
}

template<typename IntType>
void read(IntType& x) { x = read<IntType>(); }
template<typename IntType, typename... Args>
void read(IntType& x, Args&... args) { x = read<IntType>(); read(args...); }

int n;
int a[MaxN];
int cntfront[MaxN][MaxState], cntback[MaxN][MaxState];


int main(int argc, char* argv[]) {

	read(n);
	for (int i = 1; i <= n; i++)
		read(a[i]);

	cntfront[1][a[1]] = 1;
	cntback[n][a[n]] = 1;
	for (int i = 2; i <= n; i++) {
		for (int j = 0; j < MaxState; j++) {
			cntfront[i][j] += cntfront[i - 1][j];
			cntback[n - i + 1][j] += cntback[n - i + 2][j];
			cntfront[i][j^a[i]] += cntfront[i - 1][j];
			cntback[n - i + 1][j&a[n - i + 1]] += cntback[n - i + 2][j];
		}
	}

	int ans = 0;
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < MaxState; j++) {
			ans = (ans + (long long)cntfront[i][j] * cntback[i + 1][j] % Mod) % Mod;
		}
	}

	printf("%d\n", ans);

	return 0;
}

#endif

