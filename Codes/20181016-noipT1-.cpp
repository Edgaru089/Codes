/*
 DOCUMENT NAME "20181016-noipT1-.cpp"
 CREATION DATE 2018-10-16
 SIGNATURE CODE_20181016_NOIPT1_
 COMMENT Çá¹¦£¨¿¼ÍêÐ´µÄ£©
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181016_NOIPT1_

#include <cstdlib>
#include <iostream>
#include <cctype>
#include <cstdio>
#include <algorithm>
using namespace std;

#define FILENAME "qinggong"

#ifdef LOCAL
#define DEBUG(...) printf(__VA_ARGS__)
#else
#define DEBUG(...)
#endif

const int bufferreadsize = 30 * 1024 * 1024;
const int bufferwritesize = 5 * 1024 * 1024;
char buffer[bufferreadsize], *buffertop = buffer;
#define GETCHAR *(buffertop++)
#define UNGETCHAR(c) (--buffertop)

template<typename IntType>
inline IntType read() {
	IntType val = 0;
	int c;
	bool invflag = false;
	while (!isdigit(c = GETCHAR))
		if (c == '-')
			invflag = true;
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = GETCHAR));
	UNGETCHAR(c);
	if (invflag)
		return -val;
	else
		return val;
}
template<>
inline string read<string>() {
	string str;
	str.clear();
	int c;
	while (iscntrl(c = GETCHAR) || c == ' ' || c == '\t');
	do {
		str.push_back(c);
	} while (!(iscntrl(c = GETCHAR) || c == ' ' || c == '\t'));
	UNGETCHAR(c);
	return str;
}
template<typename IntType>
inline void read(IntType& x) { x = read<IntType>(); }

char bufferwrite[bufferwritesize], *writetop = bufferwrite;
#define PUTCHAR(c) (*(writetop++) = (c))

inline void putstr(char* str) {
	while ((*str) != '\0') {
		PUTCHAR(*str);
		str++;
	}
}

template<typename IntType>
inline void println(IntType val) {
	if (val == 0)
		PUTCHAR('0');
	if (val < 0) {
		PUTCHAR('-');
		val = -val;
	}
	char buf[16], *buftop = buf + 15;
	while (val > 0) {
		*buftop = (val % 10 + '0');
		buftop--;
		val /= 10;
	}
	for (buftop++; buftop <= buf + 15; buftop++)
		PUTCHAR(*buftop);
	PUTCHAR('\n');
}

/******************** End of quickread template ********************/

const long long infinity = 1e16;
const int MaxN = 1000 + 10, MaxK = 500 + 10;

int n, k, w;
int q;

int flag[MaxN][MaxK];
long long a[MaxK], v[MaxK];
long long dp[MaxN][MaxK];
int x, y;

// [left, right]
bool check(int left, int right, int type) {
	if (left > 0)
		return !(flag[type][right] - flag[type][left - 1]);
	else
		return !flag[type][right];
}


int main(int argc, char* argv[]) {
#ifndef LOCAL
	FILE* in = fopen(FILENAME ".in", "rb");
	FILE* out = fopen(FILENAME ".out", "wb");
#else
	FILE* in = stdin, *out = stdout;
#endif
	fread(buffer, 1, bufferreadsize, in);
	fclose(in);

	read(n); read(k); read(w);
	for (int i = 1; i <= k; i++) {
		read(a[i]); read(v[i]);
	}
	read(q);
	for (int i = 1; i <= q; i++) {
		read(x); read(y);
		flag[y][x] = 1;
	}

	for (int i = 1; i <= k; i++)
		for (int j = 1; j <= n + 1; j++)
			flag[i][j] += flag[i][j - 1];

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= k; j++)
			dp[i][j] = infinity;


	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= k; j++) {
			for (int l = 1; l <= k; l++) {
				if (i - a[j] >= 0 && check(i - a[j] + 1, i, j)) {
					dp[i][j] = min(dp[i][j], dp[i - a[j]][l] + v[j] + ((j != l) ? w : 0));
				}
			}
		}
	}

	long long ans = infinity;
	for (int i = 1; i <= k; i++) {
		ans = min(ans, dp[n][i]);
	}

	if (ans < infinity)
		println(ans);
	else
		println(-1);


	fwrite(bufferwrite, 1, writetop - bufferwrite, out);
	fflush(out);
	fclose(out);
	return 0;
}

#endif

