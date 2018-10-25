/*
 DOCUMENT NAME "20181017-noip1015T1-AC.cpp"
 CREATION DATE 2018-10-17
 SIGNATURE CODE_20181017_NOIP1015T1_AC
 COMMENT 10月15日模拟赛T1 刺客信条 AC.cpp/in/out
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181017_NOIP1015T1_AC

#include <cstdlib>
#include <iostream>
#include <cctype>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;

#define FILENAME "AC"

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

const int MaxN = 3000 + 10;

int x, y, n;
int a[MaxN], b[MaxN];

int p[MaxN];

int setfind(int x) {
	if (p[x] < 0)
		return x;
	else
		return p[x] = setfind(p[x]);
}

void setunion(int x, int y) {
	x = setfind(x);
	y = setfind(y);
	if (x != y) {
		p[x] += p[y];
		p[y] = x;
	}
}



bool check(double c) {
	memset(p, -1, sizeof(p));

	int top = n + 1, right = n + 2, bottom = n + 3, left = n + 4;
	double sqr = 4 * c * c;

	for (int i = 1; i <= n; i++) {
		if (x - a[i] <= c)
			setunion(i, right);
		if (y - b[i] <= c)
			setunion(i, top);
		if (a[i] <= c)
			setunion(i, left);
		if (b[i] <= c)
			setunion(i, bottom);
		for (int j = 1; j < i; j++) {
			int disx = a[i] - a[j];
			int disy = b[i] - b[j];
			if (disx*disx + disy * disy <= sqr)
				setunion(i, j);
		}
	}

	int t = setfind(top), b = setfind(bottom), r = setfind(right), l = setfind(left);
	return r != t && l != b && l != r && t != b;
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

	read(x); read(y); read(n);
	for (int i = 1; i <= n; i++) {
		read(a[i]); read(b[i]);
	}

	double l = 0, r = 1e6 + 10;
	while (fabs(l - r) > 1e-3) {
		double mid = (l + r) / 2.0;
		if (check(mid)) {
			l = mid;
		} else
			r = mid;
	}

	fprintf(out, "%.2lf\n", l);


	//fwrite(bufferwrite, 1, writetop - bufferwrite, out);
	fflush(out);
	fclose(out);
	return 0;
}

#endif

