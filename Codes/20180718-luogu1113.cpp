/*
DOCUMENT NAME "20180718-luogu1113.cpp"
CREATION DATE 2018-07-18
SIGNATURE CODE_20180718_LUOGU1113
COMMENT ‘”ŒÔ
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180718_LUOGU1113

#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const string programId = "return";

const int MaxN = 200000 + 10, MaxM = 400000 + 10;
//const int MaxN = 1500 + 10, MaxM = 2000 + 10;

#define GETCHAR (getchar())

template<typename IntType>
IntType read() {
	IntType ans = 0;
	char c;
	while (!isdigit(c = GETCHAR));
	do {
		ans = (ans << 3) + (ans << 1) + c - '0';
	} while (isdigit(c = GETCHAR));
	return ans;
}
template<typename IntType>
void read(IntType& val) { val = read<IntType>(); }

int n, m;
int q, k, s;

namespace graph {
	struct node {
		int v;
		int l, a;
		node* next;
	};

	node* h[MaxN];
	node mem[MaxM * 2], *memtop = mem;
#define ALLOCATE (++memtop)

	void addedge(int u, int v, int len, int at) {
		node* p = ALLOCATE;
		p->v = v;
		p->l = len;
		p->a = at;
		p->next = h[u];
		h[u] = p;
		p = ALLOCATE;
		p->v = u;
		p->l = len;
		p->a = at;
		p->next = h[v];
		h[v] = p;
	}
}

namespace unionfindset {
	int p[MaxN];

	int find(int u) {
		if (p[u] < 0)
			return u;
		else
			return p[u] = find(p[u]);
	}

	void _union(int x, int y) {
		x = find(x);
		y = find(y);
		p[x] += p[y];
		p[y] = x;
	}
}

namespace kruskal {
	struct edge {
		int u, v;
		int l, a;
	};

	edge e[MaxM];

	bool compare(const edge& a, const edge& b) {
		return a.a > b.a;
	}

	void run() {
		sort(e + 1, e + m + 1, compare);

		int cnt = n;
		for (int i = 1; i <= m && cnt > 1; i++) {
			int u = e[i].u, v = e[i].v, l = e[i].l, a = e[i].a;
			if (unionfindset::find(u) != unionfindset::find(v)) {
				unionfindset::_union(u, v);
				graph::addedge(u, v, l, a);
			}
		}
	}
}

int endtime[10000 + 10];
int ans;

int main(int argc, char* argv[]) {

	cin >> n;
	for (int i = 1; i <= n; i++) {
		int k, t;
		int s;
		cin >> k >> t;
		int maxval = 0;
		while (cin >> s && s != 0) {
			maxval = max(maxval, endtime[s]);
		}
		endtime[k] = maxval + t;
		ans = max(ans, endtime[k]);
	}

	for (int i = 1; i <= n; i++) {
		int k = 0, s = 0;
		if (!cin >> k >> s)
			break;
		for (graph::node*p = graph::h[k]; p != NULL; p = p->next) {
			cout << p->v << endl;
		}
	}

	cout << ans << endl;

	return 0;
}

#endif

