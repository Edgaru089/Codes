/*
 DOCUMENT NAME "20181006-noipT1-Game.cpp"
 CREATION DATE 2018-10-06
 SIGNATURE CODE_20181006_NOIPT1_GAME
 COMMENT game.cpp/in/out
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181006_NOIPT1_GAME

#include <cstdlib>
#include <iostream>
#include <cctype>
using namespace std;

#define FILENAME "game"
#define ENDLINE "\r\n"

#ifdef LOCAL
#define DEBUG(...) printf(__VA_ARGS__)
#else
#define DEBUG(...)
#endif

const int buffersize = 30 * 1024 * 1024;
char buffer[buffersize], *buffertop = buffer;
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

char bufferwrite[buffersize], *writetop = bufferwrite;
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
	putstr(ENDLINE);
}

/******************** End of quickread template ********************/

const int MaxN = 100000 + 10;
int q;
int n, k;
int s[MaxN], t[MaxN], x[MaxN], xdiff[MaxN];



int main(int argc, char* argv[]) {
#ifndef LOCAL
	FILE* in = fopen(FILENAME ".in", "rb");
	FILE* out = fopen(FILENAME ".out", "wb");
#else
	FILE* in = stdin, *out = stdout;
#endif
	fread(buffer, 1, buffersize, in);

	read(q);
	while (q--) {
		read(n); read(k);
		for (int i = 1; i <= n; i++)
			read(s[i]);
		for (int i = 1; i <= n; i++)
			read(t[i]);
		for (int i = 1; i <= n; i++)
			if (s[i] < t[i])
				x[i] = t[i] - s[i];
			else if (s[i] > t[i])
				x[i] = t[i] + k - s[i];
		for (int i = n; i >= 1; i--)
			if (s[i] == t[i])
				if (x[i + 1] <= k / 2)
					x[i] = 0;
				else
					x[i] = k;
		int ans = 0;
		for (int i = 1; i <= n; i++) {
			xdiff[i] = x[i] - x[i - 1];
			if (xdiff[i] > 0)
				ans += xdiff[i];
		}
		DEBUG("    S:");
		for (int i = 1; i <= n; i++)
			DEBUG(" %3d ", s[i]);
		DEBUG("\n    T:");
		for (int i = 1; i <= n; i++)
			DEBUG(" %3d ", t[i]);
		DEBUG("\n    X:");
		for (int i = 1; i <= n; i++)
			DEBUG(" %3d ", x[i]);
		DEBUG("\nXDiff:");
		for (int i = 1; i <= n; i++)
			DEBUG(" %3d ", xdiff[i]);
		DEBUG("\n");

		println(ans);
	}

	fwrite(bufferwrite, 1, writetop - bufferwrite, out);
	return 0;
}

#endif

