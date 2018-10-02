/*
 DOCUMENT NAME "20180916-now173A.cpp"
 CREATION DATE 2018-09-16
 SIGNATURE CODE_20180916_NOW173A
 COMMENT A-·½²î
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180916_NOW173A

#include <cstdlib>
#include <iostream>
using namespace std;

using ll = long long;

constexpr int MaxN = 1e5 + 10, MaxA = 1e4 + 10;

template<typename IntType = int>
IntType read() {
	IntType val = 0;
	int c;
	bool invflag = false;
	while (!isdigit(c = getchar()))
		if (c == '-')
			invflag = true;
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = getchar()));
	ungetc(c, stdin);
	if (invflag)
		return -val;
	else
		return val;
}
template<>
string read<string>() {
	string str;
	str.clear();
	int c;
	while (iscntrl(c = getchar()) || isblank(c));
	do {
		str.push_back(c);
	} while (!(iscntrl(c = getchar()) || isblank(c)));
	ungetc(c, stdin);
	return str;
}
template<typename IntType>
void read(IntType& x) { x = read<IntType>(); }
template<typename IntType, typename... Args>
void read(IntType& x, Args&... args) { x = read<IntType>(); read(args...); }

int n;
ll a[MaxN], sum, sumsqr;



int main(int argc, char* argv[]) {

	read(n);
	for (int i = 1; i <= n; i++) {
		read(a[i]);
		sum += a[i];
		sumsqr += a[i] * a[i];
	}

	for (int i = 1; i <= n; i++) {
		if (i != 1)
			putc(' ', stdout);
		printf("%lld", (n - 1)*(sumsqr - a[i] * a[i]) - (sum - a[i])*(sum - a[i]));
	}

	printf("\n");

	return 0;
}

#endif

