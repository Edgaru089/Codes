/*
DOCUMENT NAME "20180705-luogu1967.cpp"
CREATION DATE 2018-07-05
SIGNATURE CODE_20180705_LUOGU1967
COMMENT 货车运输 / 最大生成树+LCA
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180705_LUOGU1967

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int infinity = 1e8;
const int MaxN = 10000 + 10, MaxM = 50000 + 10;

int read() {
	char c;
	int val = 0;
	while (!isdigit(c = getchar()));
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = getchar()));
	return val;
}

int read(int& x) { return x = read(); }


namespace Set {
	int p[MaxN];

	void initalaize() { memset(p, -1, sizeof(p)); }

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
}

namespace Kruskal {
	struct Edge {
		int u, v;
		int limit;
	};

	vector<Edge> e, ans;

	void work() {
		sort(e.begin(), e.end(), [](const Edge& a, const Edge& b) {
			return a.limit > b.limit;
		});

		for (auto i : e) {
			int u = i.u, v = i.v, limit = i.limit;
			if (Set::Find(u) != Set::Find(v)) {
				ans.push_back(i);
				Union(u, v);
			}
		}
	}
}


int main(int argc, char* argv[]) {

	Set::initalaize();

	return 0;
}

#endif

