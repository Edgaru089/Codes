/*
 DOCUMENT NAME "20180916-now173C.cpp"
 CREATION DATE 2018-09-16
 SIGNATURE CODE_20180916_NOW173C
 COMMENT C-集合划分
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180916_NOW173C

#include <cstdlib>
#include <iostream>
using namespace std;

constexpr int MaxN = 18, MaxM = 10000 + 10, MaxK = (1 << MaxN) - 1;

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

int n, m, k;
int a[MaxM];

int ssel;

int bincnt(int x) {
	int cnt = 0;
	while (x != 0) {
		if ((x & 1) == 1)
			cnt++;
		x >>= 1;
	}
	return cnt;
}

int selcnt(int sel) {
	int ans = 0, k = (1 << n) - 1;
	for (int i = 1; i <= k; i++) {
		if ((i&sel) == sel)
			ans++;
	}
	return ans;
}

void printsel(int sel) {
	int k = (1 << n) - 1;
	for (int i = 1; i <= k; i++) {
		if ((i&sel) == i)
			putc('1', stdout);
		else
			putc('0', stdout);
	}
	printf("\n");
}

int main(int argc, char* argv[]) {

	read(n, m, k);
	for (int i = 1; i <= m; i++)
		read(a[i]);

	for (int i = 1; i <= m; i++)
		ssel |= a[i];
	int x = (1 << bincnt(ssel)) - 1;
	if (x > k)
		printf("-1\n");
	else if (x == k)
		printsel(ssel);
	else if (bincnt(k + 1) != 1)
		printf("-1\n");
	else {
		x++;
		k++;
		for (int i = 0; x < k && i < n; i++) {
			if ((ssel&(1 << i)) == 0) {
				ssel |= (1 << i);
				x *= 2;
			}
		}
		printsel(ssel);
	}
	return 0;
}

#endif

