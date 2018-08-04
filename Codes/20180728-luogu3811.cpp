/*
DOCUMENT NAME "20180728-luogu3811.cpp"
CREATION DATE 2018-07-28
SIGNATURE CODE_20180728_LUOGU3811
COMMENT ¡¾Ä£°å¡¿³Ë·¨ÄæÔª
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180728_LUOGU3811

#include <cstdlib>
#include <iostream>
using namespace std;

#define GETCHAR getchar()
#define UNGETCHAR(c) ungetc(c, stdin);
template<typename IntType = int>
IntType read() {
	IntType ans = 0;
	int c;
	while (!isdigit(c = GETCHAR));
	do {
		ans = (ans << 3) + (ans << 1) + c - '0';
	} while (isdigit(c = GETCHAR));
	UNGETCHAR(c);
	return ans;
}
template<typename IntType>
void read(IntType& val) { val = read<IntType>(); }
template<typename IntType, typename... Args>
void read(IntType& val, Args&... args) { val = read<IntType>(); read(args...); }

constexpr int MaxN = 3e6 + 10;

int n, p;

long long inv[MaxN];

int main(int argc, char* argv[]) {

	read(n, p);

	inv[1] = 1;
	printf("1\n");
	for (int i = 2; i <= n; i++) {
		inv[i] = (p - p / i)*inv[p%i] % p;
		printf("%lld\n", inv[i]);
	}

	return 0;
}

#endif

