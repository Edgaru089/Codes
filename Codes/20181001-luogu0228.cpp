/*
 DOCUMENT NAME "20181001-luogu0228.cpp"
 CREATION DATE 2018-10-01
 SIGNATURE CODE_20181001_LUOGU0228
 COMMENT #228. µ¥´Ê½ÓÁú
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181001_LUOGU0228

#include <cstdlib>
#include <iostream>
#include <string>
#include <stack>
#include <algorithm>
using namespace std;

const int MaxN = 1e5 + 10;

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
string strs[MaxN];

stack<string> S;


int main(int argc, char* argv[]) {

	read(n);
	for (int i = 1; i <= n; i++)
		read(strs[i]);


	return 0;
}

#endif

