/*
 DOCUMENT NAME "20180923-bnds0193.cpp"
 CREATION DATE 2018-09-23
 SIGNATURE CODE_20180923_BNDS0193
 COMMENT #193. 2017-7-30模拟测验（二）战线连接
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180923_BNDS0193

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <utility>
#include <algorithm>
#include <set>
using namespace std;

typedef pair<int, int> pii;
const int MaxN = 5e5 + 10, MaxM = 1e5 + 10, MaxQ = 1e5 + 10;

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
template<>
char read<char>() {
	int c;
	while (iscntrl(c = getchar()) || isblank(c));
	return c;
}
template<typename IntType>
void read(IntType& x) { x = read<IntType>(); }
template<typename IntType, typename... Args>
void read(IntType& x, Args&... args) { x = read<IntType>(); read(args...); }

int n, m, q;
set<pii> links;
int k[MaxQ], x[MaxQ], y[MaxQ];
int ans[MaxQ];

int p[MaxN];

int setfind(int x) {
	if (p[x] < 0)
		return x;
	else
		return p[x] = setfind(p[x]);
}

void setunion(int x, int y) {
	x = setfind(x);
	y = setfind(y);
	p[x] += p[y];
	p[y] = x;
}




int main(int argc, char* argv[]) {

	memset(p, -1, sizeof(p));

	read(n, m, q);

	int a, b;
	for (int i = 1; i <= m; i++) {
		read(a, b);
		if (a < b)
			links.insert(make_pair(a, b));
		else
			links.insert(make_pair(b, a));
	}
	for (int i = 1; i <= q; i++) {
		read(k[i]);
		if (k[i] == 1 || k[i] == 2)
			read(x[i], y[i]);
		if (k[i] == 1)
			links.erase(links.find(make_pair(min(x[i], y[i]), max(x[i], y[i]))));
	}

	int cnt = n;
	for (auto i : links) {
		int x = i.first, y = i.second;
		if (setfind(x) != setfind(y)) {
			setunion(x, y);
			cnt--;
		}
	}

	for (int i = q; i >= 1; i--) {
		if (k[i] == 1)
			if (setfind(x[i]) != setfind(y[i])) {
				setunion(x[i], y[i]);
				cnt--;
			}
		if (k[i] == 2)
			ans[i] = (int)(setfind(x[i]) == setfind(y[i]));
		if (k[i] == 3)
			ans[i] = cnt;
	}

	for (int i = 1; i <= q; i++)
		if (k[i] >= 2)
			printf("%d\n", ans[i]);

	return 0;
}

#endif

