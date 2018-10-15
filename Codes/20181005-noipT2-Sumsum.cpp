/*
 DOCUMENT NAME "20181005-noipT2-Sumsum.cpp"
 CREATION DATE 2018-10-05
 SIGNATURE CODE_20181005_NOIPT2_SUMSUM
 COMMENT sumsum.cpp/in/out
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181005_NOIPT2_SUMSUM

#include <cstdlib>
#include <iostream>
#include <cctype>
using namespace std;

#define FILENAME "filecodehere"
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

const int infinity = 1e8;
const long long infinintyll = 1e16;
const long long mod = 998244353;
const int MaxN = 8000000 + 10;
int n, a[MaxN];
long long sum;


int main(int argc, char* argv[]) {
#ifndef LOCAL
	FILE* in = fopen(FILENAME ".in", "rb");
	FILE* out = fopen(FILENAME ".out", "wb");
#else
	FILE* in = stdin, *out = stdout;
#endif
	fread(buffer, 1, buffersize, in);

	bool allpositive = true;

	read(n);
	for (int i = 1; i <= n; i++) {
		read(a[i]);
		if (a[i] < 0)
			allpositive = false;
	}

	if (allpositive) {
		long long sum = 0;
		for (int i = 1; i <= n; i++)
			sum = (sum + ((long long)i*(n - i + 1) % mod)*a[i]) % mod;
		println(sum);
	}
	else {
		for (int i = 1; i <= n; i++) {
			long long maxval = -infinity, sum = 0, cnt = 0;
			DEBUG("Start: i=%d\n", i);
			for (int j = i; j <= n; j++) {
				sum += a[j];
				DEBUG("    j=%d, Value: %d, Sum: %lld, MaxVal: %lld", j, a[j], sum, maxval);
				if (maxval < sum) {
					DEBUG(", Added, Count: %d\n", cnt);
					::sum += maxval * cnt;
					maxval = sum;
					cnt = 1;
				}
				else {
					cnt++;
					DEBUG(", CntAdded, Cnt: %lld\n", cnt);
				}
			}
			DEBUG("Final: MaxVal: %lld, Count: %lld\n", maxval, cnt);
			::sum += maxval * cnt;
		}

		if (sum < 0)
			println((sum + mod * (-sum / mod + 1)) % mod);
		else
			println(sum%mod);
	}

	fwrite(bufferwrite, 1, writetop - bufferwrite, out);
	return 0;
}

#endif

