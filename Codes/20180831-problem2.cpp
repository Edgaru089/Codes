/*
DOCUMENT NAME "20180831-problem2.cpp"
CREATION DATE 2018-08-31
SIGNATURE CODE_20180831_PROBLEM2
COMMENT 2.–Ú¡–Œ Ã‚
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180831_PROBLEM2

#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

const int MaxN = 1000 + 10, MaxS = 2048;

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
template<>
string read<string>() {
	string str;
	str.clear();
	int c;
	while (iscntrl(c = getchar()) || isblank(c));
	do {
		str.push_back(c);
	} while (!(iscntrl(c = getchar()) || isblank(c)));
	ungetc(c, stdin);
	return str;
}
template<typename IntType>
void read(IntType& x) { x = read<IntType>(); }
template<typename IntType, typename... Args>
void read(IntType& x, Args&... args) { x = read<IntType>(); read(args...); }

int n;
int a[MaxN];

int flagl[MaxN][MaxS], flagr[MaxN][MaxS];




int main(int argc, char* argv[]) {

	read(n);
	for (int i = 1; i <= n; i++)
		read(a[i]);

	for (int i = 0; i <= n + 1; i++)
		flagl[i][0] = flagr[i][2047] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 0; j < MaxS; j++)
			flagl[i][j^a[i]] += flagl[i - 1][j];
	for (int i = n; i >= 1; i--)
		for (int j = 0; j < MaxS; j++)
			flagr[i][j&a[i]] += flagr[i + 1][j];
	for (int i = n - 1; i >= 1; i--)
		for (int j = 0; j < MaxS; j++)
			flagr[i][j] += flagr[i + 1][j];

	for (int i = 0; i <= n + 1; i++) {
		flagl[i][0]--;
		flagr[i][2047]--;
	}

	int ans = 0;
	for (int i = 2; i <= n; i++)
		for (int j = 0; j < MaxS; j++)
			ans += flagl[i - 1][j] * flagr[i][j];

	printf("%d\n", ans);

	return 0;
}

#endif

