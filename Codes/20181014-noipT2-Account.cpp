/*
 DOCUMENT NAME "20181014-noipT2-Account.cpp"
 CREATION DATE 2018-10-14
 SIGNATURE CODE_20181014_NOIPT2_ACCOUNT
 COMMENT account.cpp/in/out
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181014_NOIPT2_ACCOUNT

#include <cstdlib>
#include <iostream>
#include <cctype>
#include <cstdio>
#include <map>
using namespace std;

#define FILENAME "account"
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

typedef long long ll;
typedef unsigned long long ull;
const int MaxN = 100000 + 10, MaxM = 100000 + 10, MaxQ = 100000 + 10;

int n, m, q;
string str1, str2;
int val;
map<string, ll> container;
map<ull, ll> hashc;




int main(int argc, char* argv[]) {
#ifndef LOCAL
	FILE* in = fopen(FILENAME ".in", "rb");
	FILE* out = fopen(FILENAME ".out", "wb");
#else
	FILE* in = stdin, *out = stdout;
#endif
	fread(buffer, 1, buffersize, in);

	read(n);
	read(m);
	read(q);

	if (n <= 20000) {
		for (int i = 1; i <= n + m; i++)
			read(str1);

		for (int i = 1; i <= q; i++) {
			read(str1); read(str2); read(val);
			long long& x = container[str1 + '#' + str2];
			x += val;
			println(x);
		}

	} else {

	}


	fwrite(bufferwrite, 1, writetop - bufferwrite, out);
	return 0;
}

#endif

