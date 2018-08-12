/*
DOCUMENT NAME "20180811-bnds0756.cpp"
CREATION DATE 2018-08-11
SIGNATURE CODE_20180811_BNDS0756
COMMENT 银河英雄传说-NOI2002
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180811_BNDS0756

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

const int MaxT = 500000 + 10, MaxN = 30000 + 10;

int t;

int p[MaxN], len[MaxN];

int Find(int x) {
	if (p[x] < 0)
		return x;
	else {
		int t = p[x];
		p[x] = Find(p[x]);
		if (t != p[x])
			len[x] = len[t] + len[x] + 1;
		return p[x];
	}
}

void Union(int x, int y) {
	x = Find(x);
	y = Find(y);
	int size = p[x];
	p[x] = y;
	len[x] = -p[y] - 1;
	p[y] += size;
}

int query(int x, int y) {
	int x1 = Find(x);
	int y1 = Find(y);
	if (x1 != y1)
		return -1;
	else
		return abs(len[x] - len[y]);
}



int main(int argc, char* argv[]) {

	memset(p, -1, sizeof(p));

	string str;
	cin >> t;
	for (int i = 1; i <= t; i++) {
		int x, y;
		cin >> str >> x >> y;
		if (str == "M") {
			Union(x, y);
		}
		else if (str == "C") {
			cout << query(x, y) << endl;
		}
	}

	return 0;
}

#endif

