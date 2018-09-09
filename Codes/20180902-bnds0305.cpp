/*
DOCUMENT NAME "20180902-bnds0305.cpp"
CREATION DATE 2018-09-02
SIGNATURE CODE_20180902_BNDS0305
COMMENT #305. NOIP2012提高组day2第一题 同余方程
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180902_BNDS0305

#include <cstdlib>
#include <iostream>
using namespace std;

typedef long long ll;

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

void exgcd(ll a, ll b, ll& x, ll& y) {
	if (b == 0) {
		x = 1;
		y = 0;
	}
	else {
		exgcd(b, a % b, y, x);
		y -= (a / b) * x;
	}
}

int main(int argc, char* argv[]) {

	ll a, b, x, y;
	read(a, b);
	exgcd(a, b, x, y);
	printf("%lld\n", (x + b) % b);

	return 0;
}

#endif

