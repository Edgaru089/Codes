/*
 DOCUMENT NAME "20181014-noipT3-Information.cpp"
 CREATION DATE 2018-10-14
 SIGNATURE CODE_20181014_NOIPT3_INFORMATION
 COMMENT information.cpp/in/out
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181014_NOIPT3_INFORMATION

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
using namespace std;

#define FILENAME "information"

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

inline void putstr(const char* str) {
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
const int MaxN = 100000 + 10;
const int Mod = 998244353;

string str;

int ans[MaxN];
int dfs(int i) {
	if (i < 0)
		return 0;
	else if (ans[i] != -1)
		return ans[i];
	else {
		ans[i] = dfs(i - 1);
		if (i > 1 && (str[i - 2] <= '1' || (str[i - 2] == '2' && str[i - 1] <= '6')))
			ans[i] = (ans[i] + dfs(i - 2)) % Mod;
		return ans[i];
	}
}


string getstr(int off = 0) {
	if (off >= str.length())
		return string();
	else if (off < str.length() - 1 && (str[off] <= '1' || (str[off] == '2' && str[off + 1] <= '6')))
		return (char)('a' + (str[off] - '0') * 10 + str[off + 1] - '0' - 1) + getstr(off + 2);
	else
		return (char)('a' + str[off] - '0' - 1) + getstr(off + 1);
}



int main(int argc, char* argv[]) {
#ifndef LOCAL
	FILE* in = fopen(FILENAME ".in", "rb");
	FILE* out = fopen(FILENAME ".out", "wb");
#else
	FILE* in = stdin, *out = stdout;
#endif
	fread(buffer, 1, buffersize, in);

	memset(ans, -1, sizeof(ans));
	ans[0] = 1;

	read(str);

	putstr(getstr().c_str());
	PUTCHAR('\n');
	println(dfs(str.length()));


	fwrite(bufferwrite, 1, writetop - bufferwrite, out);
	return 0;
}

#endif

