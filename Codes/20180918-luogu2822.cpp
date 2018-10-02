/*
 DOCUMENT NAME "20180918-luogu2822.cpp"
 CREATION DATE 2018-09-18
 SIGNATURE CODE_20180918_LUOGU2822
 COMMENT NOIP2016D2T1 组合数问题
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180918_LUOGU2822

#include <cstdlib>
#include <iostream>
using namespace std;

const int MaxN = 2000 + 10, MaxM = 2000 + 10;

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


int t, n, m, k;
int c[MaxN + 10][MaxM + 10], s[MaxN + 10][MaxM + 10];


int main(int argc, char* argv[]) {

	read(t, k);

	for (int i = 0; i <= MaxN; i++)
		c[i][0] = 1;
	for (int i = 1; i <= MaxN; i++)
		for (int j = 1; j <= i; j++)
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % k;

	for (int i = 1; i <= MaxN; i++)
		for (int j = 1; j <= MaxM; j++) {
			s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
			if (j <= i && c[i][j] == 0)
				s[i][j]++;
		}

	for (int i = 1; i <= t; i++) {
		read(n, m);
		printf("%d\n", s[n][m]);
	}

	return 0;
}

#endif

