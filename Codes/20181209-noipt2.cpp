/*
 DOCUMENT NAME "20181209-noipt2.cpp"
 CREATION DATE 2018-12-09
 SIGNATURE CODE_20181209_NOIPT2
 COMMENT 小奇的数列 (seq)
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181209_NOIPT2

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cctype>
#include <cstdio>
#include <bitset>
using namespace std;

#define FILENAME "seq"

#define ASSERT_NODEBUG(expr) do{\
	if(!(expr)){\
		printf("Debug Assertation Failed on line %d, in function %s:\n  Expression: %s\n",__LINE__,__func__,#expr);\
		abort();\
	}\
}while(false)

#if (defined LOCAL) || (defined D)
#define DEBUG(...) printf(__VA_ARGS__)
#define PRINTARR(formatstr, arr, beginoff, size)				\
do{printf(#arr ":");											\
for (int __i = beginoff; __i <= beginoff + size - 1; __i++)		\
	printf("\t%d", __i);										\
printf("\n");													\
for (int __i = beginoff; __i <= beginoff + size - 1; __i++)		\
	printf("\t" formatstr, arr[__i]);							\
printf("\n"); }while(false)
#define PASS printf("Passing function \"%s\" on line %d\n", __func__, __LINE__)
#define ASSERT(expr) ASSERT_NODEBUG(expr)
#else
#define DEBUG(...)
#define PRINTARR(a, b, c, d)
#define PASS
#define ASSERT(expr)
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

const int MaxN = 200 + 10, MaxP = 500 + 10;

int n, m;
int a[MaxN];
int l, r, p;
bitset<2 * MaxP> s[MaxN][MaxN];





int main(int argc, char* argv[]) {
#if (defined LOCAL) || (defined ONLINE_JUDGE)
	FILE* in = stdin, *out = stdout;
#else
	FILE* in = fopen(FILENAME ".in", "rb");
	FILE* out = fopen(FILENAME ".out", "wb");
#endif
	fread(buffer, 1, bufferreadsize, in);
	fclose(in);

	read(n); read(m);
	ASSERT_NODEBUG(n <= MaxN);
	for (int i = 1; i <= n; i++)
		read(a[i]);
	for (int i = 1; i <= m; i++) {
		read(l); read(r); read(p);
		ASSERT_NODEBUG(l < r);
		ASSERT_NODEBUG(p <= MaxP);

		for (int i = l; i <= r; i++) {
			for (int j = 0; j + i - 1 <= r; j++) {
				s[i][j].reset();
				s[i][j].set(0, true);
			}
			//s[i][1].set(a[i] % p, true);
		}
		for (int i = 1; i <= r - l + 1; i++) {
			for (int j = l; j + i - 1 <= r; j++) {
				s[j][i] |= s[j][i - 1] << (a[j + i - 1] % p);
				s[j][i] |= s[j][i - 1] >> (p - a[j + i - 1] % p);
				s[j][i] |= s[j + 1][i - 1] << (a[j] % p);
				s[j][i] |= s[j + 1][i - 1] >> (p - a[j] % p);
			}
		}
		for (int i = 1; i < p; i++) {
			if (s[l][r - l + 1][i]) {
				println(i);
				break;
			}
		}
	}




	fwrite(bufferwrite, 1, writetop - bufferwrite, out);
	fclose(out);
	return 0;
}

#endif

