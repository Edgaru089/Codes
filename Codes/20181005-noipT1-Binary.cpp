/*
 DOCUMENT NAME "20181005-noipT1-Binary.cpp"
 CREATION DATE 2018-10-05
 SIGNATURE CODE_20181005_NOIPT1_BINARY
 COMMENT binary.cpp/in/out
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181005_NOIPT1_BINARY

#include <cstdlib>
#include <iostream>
#include <cctype>
using namespace std;

#define FILENAME "binary"
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
void readstr(string& str) {
	str.clear();
	int c;
	while (iscntrl(c = GETCHAR) || c == ' ' || c == '\t');
	do {
		str.push_back(c);
	} while (!(iscntrl(c = GETCHAR) || c == ' ' || c == '\t'));
	UNGETCHAR(c);
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

int n, m, p;
int a[MaxN], pre[MaxN];
string str;

int count(int val) {
	int cnt = 0;
	while (val > 0) {
		if ((val & 1) != 0)
			cnt++;
		val >>= 1;
	}
	return cnt;
}


int main(int argc, char* argv[]) {
//#ifndef LOCAL
	FILE* in = fopen(FILENAME ".in", "rb");
	FILE* out = fopen(FILENAME ".out", "wb");
//#else
//	FILE* in = stdin, *out = stdout;
//#endif
	fread(buffer, 1, buffersize, in);

	read(n); read(p);
	str.reserve(n);
	readstr(str);

	for (int i = 1; i <= n; i++) {
		a[i] = str[i - 1] - '0';
		pre[i] = pre[i - 1] + a[i];
	}

	read(m);
	for (int i = 1; i <= m; i++) {
		int l, r, re;
		int ans = 0;
		read(l); read(r); read(re);
		int cnt = pre[r] - pre[l - 1];
		int maxval = (((1 << cnt) - 1) << (r - l + 1 - cnt));
		DEBUG("Left: %d, Right: %d, Remainer: %d, Count: %d, MaxVal: %d", l, r, re, cnt, maxval);
		int j = re;
		DEBUG(", Start: %d\n", j);
		for (; j <= maxval; j += p) {
			DEBUG("%d, Count: %d\n", j, count(j));
			if (count(j) == cnt)
				ans++;
		}
		println(ans);
	}




	fwrite(bufferwrite, 1, writetop - bufferwrite, out);
	return 0;
}


#endif

