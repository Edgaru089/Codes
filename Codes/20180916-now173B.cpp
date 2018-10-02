/*
 DOCUMENT NAME "20180916-now173B.cpp"
 CREATION DATE 2018-09-16
 SIGNATURE CODE_20180916_NOW173B
 COMMENT B-·ÖÌÇ¹û
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180916_NOW173B

#include <cstdlib>
#include <iostream>
using namespace std;

constexpr int MaxN = 1e6 + 10, MaxA = 1e9 + 10;

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

#ifdef LOCAL
#define DEBUG(...) printf(__VA_ARGS__)
#else
#define DEBUG(...)
#endif

int n, a[MaxN];
int k[MaxN], ans;

void dfs(int u, int c) {
	if (u == n) {
		if (k[1] != c)
			ans++;
	}
	else {
		k[u] = c;
		for (int i = 1; i <= a[i]; i++) {
			if (i != k[u])
				dfs(u + 1, i);
		}
	}
}

int main(int argc, char* argv[]) {

	read(n);
	for (int i = 1; i <= n; i++)
		read(a[i]);

	for (int i = 1; i <= a[1]; i++)
		dfs(1, i);

	printf("%d\n", ans);

	return 0;
}

#endif

