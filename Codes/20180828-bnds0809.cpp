/*
DOCUMENT NAME "20180828-bnds0809.cpp"
CREATION DATE 2018-08-28
SIGNATURE CODE_20180828_BNDS0809
COMMENT A. 2018-8-28noip模拟测验（一）-某种密码
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180828_BNDS0809

#include <cstdlib>
#include <iostream>
using namespace std;

const int MaxN = 40 + 10, MaxKeyStore = 245 * 1024 * 1024 / 4;
const int MaxKey = MaxKeyStore / 2;

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

long long n, key;
long long a[MaxN];
int ans[MaxKeyStore];



int main(int argc, char* argv[]) {

	read(n, key);
	key += MaxKey;
	for (int i = 1; i <= n; i++)
		read(a[i]);
	ans[MaxKey] = 1;
	for (register int i = 1; i <= n; i++) {
		if (a[i] > 0)
			for (register int j = key; j >= a[i]; j--)
				ans[j] += ans[j - a[i]];
		else
			for (register int j = 0; j <= key + a[i]; j++)
				ans[j] += ans[j - a[i]];
	}

	printf("%d\n", ans[key]);

	return 0;
}

#endif

