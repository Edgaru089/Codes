/*
 DOCUMENT NAME "20181003-luogu2312.cpp"
 CREATION DATE 2018-10-03
 SIGNATURE CODE_20181003_LUOGU2312
 COMMENT P2312 解方程
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181003_LUOGU2312

#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

const int MaxN = 100 + 10, MaxM = 1e6 + 10;
const int mod = 1e9 + 7;

constexpr int buffersize = 30 * 1024 * 1024;
char buffer[buffersize], *buffertop = buffer;
#define GETCHAR *(buffertop++)
#define UNGETCHAR(c) (--buffertop)

template<typename IntType = int>   // 模板默认类型需要C++11
IntType read() {
	IntType val = 0;
	int c;
	bool invflag = false;
	while (!isdigit(c = GETCHAR))
		if (c == '-')
			invflag = true;
	do {
		val = (val << 1) + (val << 3) + c - '0';
		if (val > mod)
			val -= mod;
	} while (isdigit(c = GETCHAR));
	UNGETCHAR(c);
	if (invflag)
		return mod - val;
	else
		return val;
}
template<>
string read<string>() {
	string str;
	str.clear();
	int c;
	while (iscntrl(c = GETCHAR) || isblank(c));
	do {
		str.push_back(c);
	} while (!(iscntrl(c = GETCHAR) || isblank(c)));
	UNGETCHAR(c);
	return str;
}
template<typename IntType>
void read(IntType& x) { x = read<IntType>(); }
template<typename IntType, typename... Args>     // 模板参数包需要C++11
void read(IntType& x, Args&... args) { x = read<IntType>(); read(args...); }

char bufferwrite[buffersize], *writetop = bufferwrite;
#define PUTCHAR(c) (*(writetop++) = (c))

template<typename IntType>
void println(IntType val) {
	if (val == 0)
		PUTCHAR('0');
	//if (val < 0) {
	//	PUTCHAR('-');
	//	val = -val;
	//}
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

int n, m;
int a[MaxN];
int ans[MaxN], *anstop = ans;

bool check(int x) {
	long long sum = 0;
	for (int i = n; i >= 0; i--)
		sum = (a[i] + sum)*x%mod;

	if (sum == 0)
		return true;
	else
		return false;
}

int main(int argc, char* argv[]) {
	fread(buffer, 1, buffersize, stdin);

	read(n, m);
	for (int i = 0; i <= n; i++)
		read(a[i]);

	for (int i = 1; i <= m; i++) {
		if (check(i))
			*(anstop++) = i;
	}

	println(anstop - ans);
	for (int* i = ans; i != anstop; i++)
		println(*i);

	fwrite(bufferwrite, 1, writetop - bufferwrite, stdout);
	return 0;
}

#endif

