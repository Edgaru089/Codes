/*
DOCUMENT NAME "20180904-bnds0805.cpp"
CREATION DATE 2018-09-04
SIGNATURE CODE_20180904_BNDS0805
COMMENT #805. 口袋的天空 / kruskal
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180904_BNDS0805

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int MaxN = 1000 + 10, MaxM = 10000 + 10;

template<typename IntType = int>   // 模板默认类型需要C++11
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
template<typename IntType, typename... Args>     // 模板参数包需要C++11
void read(IntType& x, Args&... args) { x = read<IntType>(); read(args...); }

int n, m, k;

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


struct edge {
	int u, v, len;
};

edge e[MaxM];

int kruskal() {
	if (n < k)
		return -1;

	sort(e + 1, e + m + 1, [](const edge& x, const edge& y) {
		return x.len < y.len;
	});

	memset(p, -1, sizeof(p));

	int ans = 0;
	int cnt = n;
	for (int i = 1; i <= m&&cnt > k; i++) {
		int u = e[i].u, v = e[i].v, len = e[i].len;
		if (setfind(u) != setfind(v)) {
			setunion(u, v);
			ans += len;
			cnt--;
		}
	}
	if (cnt > k)
		return -1;
	else
		return ans;
}



int main(int argc, char* argv[]) {

	read(n, m, k);
	for (int i = 1; i <= m; i++)
		read(e[i].u, e[i].v, e[i].len);

	int ans = kruskal();
	if (ans == -1)
		printf("No Answer\n");
	else
		printf("%d\n", ans);

	return 0;
}

#endif

