/*
 DOCUMENT NAME "20181026-noipT1-.cpp"
 CREATION DATE 2018-10-26
 SIGNATURE CODE_20181026_NOIPT1_
 COMMENT inverse
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181026_NOIPT1_

#include <cstdlib>
#include <iostream>
#include <cctype>
#include <cstdio>
#include <algorithm>
using namespace std;

#define FILENAME "inverse"

#if (defined LOCAL || defined D)
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

typedef long long ll;
const int Mod = 998244353;
const int MaxT = 1e5 + 10,MaxN=1e7+10;

int t;
int n[MaxT];
int maxval = 0;
int f[MaxN];

ll qpow(ll base, ll exp, ll mod = Mod) {
	ll ans = 1;
	while (exp) {
		if (exp & 1)
			ans = (ans*base) % mod;
		base = (base*base) % mod;
		exp >>= 1;
	}
	return ans;
}


int main(int argc, char* argv[]) {
#if (defined LOCAL) || (defined ONLINE_JUDGE)
	FILE* in = stdin, *out = stdout;
#else
	FILE* in = fopen(FILENAME ".in", "rb");
	FILE* out = fopen(FILENAME ".out", "wb");
#endif
	fread(buffer, 1, bufferreadsize, in);
	fclose(in);

	read(t);
	for (int i = 1; i <= t; i++) {
		read(n[i]);
		maxval = max(maxval, n[i]);
	}

	for (int i = 2; i <= maxval; i++) {
		f[i] = (f[i - 1] * qpow(i, Mod - 2, Mod) % Mod) + ((f[i - 1] + 1)*qpow(i, Mod - 2, Mod) % Mod*(i - 1));
	}

	for (int i = 1; i <= t; i++)
		println(f[n[i]]);


	fwrite(bufferwrite, 1, writetop - bufferwrite, out);
	fclose(out);
	return 0;
}

#endif
