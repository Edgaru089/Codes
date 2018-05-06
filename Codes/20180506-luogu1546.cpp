/*
DOCUMENT CODE "20180506-luogu1546.cpp"
CREATION DATE 2018-05-06
SIGNATURE CODE_20180506_LUOGU1546
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180506_LUOGU1546

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

struct edge {
	int u, v;
	int len;
};

int p[1001];
edge e[10001];
int n;

int Find(int x) {
	if (p[x] < 0)
		return x;
	else
		return p[x] = Find(p[x]);
}

void Union(int x, int y) {
	x = Find(x);
	y = Find(y);
	p[x] += p[y];
	p[y] = x;
}

int main(int argc, char* argv[]) {

	memset(p, -1, sizeof(p));

	cin >> n;
	int k = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			int len;
			cin >> len;
			if (i != j) {
				k++;
				e[k].len = len;
				e[k].u = i;
				e[k].v = j;
			}
		}

	sort(e + 1, e + k + 1, [](edge& x, edge& y) {return x.len < y.len; });

	int sum = 0;
	for (int i = 1; i <= k; i++) {
		if (Find(e[i].u) != Find(e[i].v)) {
			Union(e[i].u, e[i].v);
			sum += e[i].len;
		}
	}

	cout << sum << endl;

	return 0;
}

#endif

