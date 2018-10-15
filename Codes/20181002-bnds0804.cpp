/*
 DOCUMENT NAME "20181002-bnds0804.cpp"
 CREATION DATE 2018-10-02
 SIGNATURE CODE_20181002_BNDS0804
 COMMENT
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181002_BNDS0804

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int MaxN = 50000 + 10, MaxM = 100000 + 10;

template<typename IntType>
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

template<typename IntType>
void read(IntType& val) { val = read<IntType>(); }

int n, m, need;

const int black = 1, white = 0;

struct edge {
	int u, v;
	int len, extlen;
	int color;
};

edge e[MaxM];

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

int lastcheckans;
int check(int val) {
	int whitecount = 0;
	memset(p, -1, sizeof(p));
	for (int i = 1; i <= m; i++) {
		if (e[i].color == white)
			e[i].extlen = val;
		else
			e[i].extlen = 0;
	}
	sort(e + 1, e + m + 1, [](const edge& x, const edge& y) {
		return x.len + x.extlen < y.len + y.extlen || (x.len + x.extlen == y.len + y.extlen && x.color == white);
	});
	int cnt = n;
	lastcheckans = 0;
	for (int i = 1; i <= m && cnt > 1; i++) {
		if (setfind(e[i].u) != setfind(e[i].v)) {
			setunion(e[i].u, e[i].v);
			lastcheckans += e[i].len;
			if (e[i].color == white)
				whitecount++;
		}
	}
	return whitecount;
}



int main(int argc, char* argv[]) {

	read(n); read(m); read(need);
	for (int i = 1; i <= m; i++) {
		read(e[i].u); read(e[i].v); read(e[i].len); read(e[i].color);
	}

	int l = -120, r = 120;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		int cnt = check(mid);
		if (cnt == need) {
			printf("%d\n", lastcheckans);
			return 0;
		}
		else if (cnt < need)
			r = mid;
		else
			l = mid;
	}

	if (check(l) < need)
		check(r);

	printf("%d\n", lastcheckans);

	return 0;
}

#endif

