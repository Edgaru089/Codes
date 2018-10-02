/*
 DOCUMENT NAME "20180918-luogu2827.cpp"
 CREATION DATE 2018-09-18
 SIGNATURE CODE_20180918_LUOGU2827
 COMMENT NOIP2016D1T2 òÇò¾
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180918_LUOGU2827

#include <cstdlib>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

const int MaxN = 1e5 + 10, MaxM = 7e6 + 10;

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

int n, m, q, u, v, t;
double p;
int a[MaxN];

typedef pair<int, int> pii;
queue<pii> Q0, Ql, Qr;
vector<int> ans, pans;


int main(int argc, char* argv[]) {

	read(n, m, q, u, v, t);
	p = (double)u / (double)v;
	ans.reserve(m / t + 1);
	pans.reserve((n + m) / t + 1);
	for (int i = 1; i <= n; i++)
		read(a[i]);

	sort(a + 1, a + n + 1, greater<int>());
	for (int i = 1; i <= n; i++)
		Q0.push(pii(a[i], 1));

	bool flag = true;
	int tq0, tql, tqr, k;
	for (int i = 1; i <= m; i++) {
		tq0 = Q0.empty() ? -1 : (Q0.front().first + (i - Q0.front().second)*q);
		tql = Ql.empty() ? -1 : (Ql.front().first + (i - Ql.front().second)*q);
		tqr = Qr.empty() ? -1 : (Qr.front().first + (i - Qr.front().second)*q);
		int mx = max({ tq0, tql, tqr });
		if (mx == tq0) {
			Q0.pop();
			k = tq0;
		}
		else if (mx == tql) {
			Ql.pop();
			k = tql;
		}
		else {
			Qr.pop();
			k = tqr;
		}
		int l = k * p;
		int r = k - l;
		Ql.push(pii(l, i + 1));
		Qr.push(pii(r, i + 1));
		if (i%t == 0) {
			if (flag)
				flag = false;
			else
				printf(" ");
			printf("%d", k);
		}
	}
	printf("\n");

	while (!Q0.empty()) {
		pans.push_back(Q0.front().first + (m + 1 - Q0.front().second)*q);
		Q0.pop();
	}
	while (!Ql.empty()) {
		pans.push_back(Ql.front().first + (m + 1 - Ql.front().second)*q);
		Ql.pop();
	}
	while (!Qr.empty()) {
		pans.push_back(Qr.front().first + (m + 1 - Qr.front().second)*q);
		Qr.pop();
	}
	sort(pans.begin(), pans.end(), greater<int>());

	flag = true;
	for (int i = t; i <= pans.size(); i += t) {
		if (flag)
			flag = false;
		else
			printf(" ");
		printf("%d", pans[i - 1]);
	}
	printf("\n");

	return 0;
}

#endif

