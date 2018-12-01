/*
 DOCUMENT NAME "20181120-luogu4768.cpp"
 CREATION DATE 2018-11-20
 SIGNATURE CODE_20181120_LUOGU4768
 COMMENT P4768 [NOI2018]¹é³Ì
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181120_LUOGU4768

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

#if (defined LOCAL) || (defined D)
#define DEBUG(...) printf(__VA_ARGS__)
#define PRINTARR(formatstr, arr, beginoff, size)				\
do{printf(#arr ":");											\
for (int __i = beginoff; __i <= beginoff + size - 1; __i++)		\
	printf("\t%d", __i);										\
printf("\n");													\
for (int __i = beginoff; __i <= beginoff + size - 1; __i++)		\
	printf("\t" formatstr, arr[__i]);							\
printf("\n"); }while(false)
#define PASS printf("Passing function \"%s\" on line %d\n", __func__, __LINE__)
#define ASSERT(expr) do{\
	if(!(expr)){\
		printf("Debug Assertation Failed on line %d, in function %s:\n  Expression: %s\n",__LINE__,__func__,#expr);\
		abort();\
	}\
}while(false)
#else
#define DEBUG(...)
#define PRINTARR(a, b, c, d)
#define PASS
#define ASSERT(expr)
#endif

template<typename IntType>
void read(IntType& val) {
	val = 0;
	int c;
	bool inv = false;
	while (!isdigit(c = getchar()))
		if (c == '-')
			inv = true;
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = getchar()));
	if (inv)
		val = -val;
}

const int infinity = 1e8;
const int MaxN = 220000 + 10, MaxM = 420000 + 10;
const int MaxLogN = 25;

int n, m;

struct edge {
	int id;
	int u, v;
	int len, alt;
};
edge e[MaxM];

#define ALLOCATE (++memtop)

namespace graph {
	struct node {
		int v, len;
		int alt;
		node* next;
	};

	node* h[MaxN];
	node mem[2 * MaxM], *memtop = mem;

	void addedge(int u, int v, int len, int alt) {
		node* p = ALLOCATE;
		p->v = v;
		p->len = len;
		p->alt = alt;
		p->next = h[u];
		h[u] = p;
		p = ALLOCATE;
		p->v = u;
		p->len = len;
		p->alt = alt;
		p->next = h[v];
		h[v] = p;
	}
}

namespace dijkstra {
	using namespace graph;
	int d[MaxN];

	typedef pair<int, int> pii;
	priority_queue<pii> Q;

	void run() {
		memset(h, 0, sizeof(h));
		memtop = mem;
		for (int i = 1; i <= m; i++)
			addedge(e[i].u, e[i].v, e[i].len, e[i].alt);
		for (int i = 1; i <= n; i++)
			d[i] = infinity;
		Q.push(pii(0, 1));
		d[1] = 0;
		while (!Q.empty()) {
			int u = Q.top().second, dis = Q.top().first;
			Q.pop();
			if (d[u] < dis)
				continue;
			for (node* p = h[u]; p; p = p->next) {
				if (d[p->v] > dis + p->len) {
					d[p->v] = dis + p->len;
					Q.push(make_pair(d[p->v], p->v));
				}
			}
		}
	}
}

namespace kruskal {
	int p[MaxN + MaxM];
	int setfind(int u) {
		return (p[u] > 0) ? (p[u] = setfind(p[u])) : u;
	}
	// set the father of X to Y, with p[y] set to -val
	void setunion(int x, int y, int val) {
		x = setfind(x);
		y = setfind(y);
		p[y] = -val;
		p[x] = y;
	}

	struct node {
		int id;
		int alt;
		int mindis;
		node* lson, *rson;
		node* father;
	};

	// for leaves(nodes on the graph): i
	node *nodes[MaxN + MaxM];
	int nodecnt;
	node mem[MaxN + MaxM], *memtop = mem;

	bool cmp(edge& x, edge& y) {
		return x.alt > y.alt;
	}

	void run() {
		memset(p, 0, sizeof(p));
		memtop = mem;
		for (int i = 1; i <= n; i++) {
			nodes[i] = ALLOCATE;
			nodes[i]->id = i;
			nodes[i]->alt = infinity;
			nodes[i]->mindis = dijkstra::d[i];
			nodes[i]->lson = nodes[i]->rson = nodes[i]->father = 0;
			p[i] = -i;
		}
		nodecnt = n;
		sort(e + 1, e + m + 1, cmp);
		int cnt = 1;
		for (int i = 1; cnt < n&&i <= m; i++) {
			int u = e[i].u, v = e[i].v, alt = e[i].alt;
			if (setfind(u) == setfind(v))
				continue;
			nodes[++nodecnt] = ALLOCATE;
			nodes[nodecnt]->id = nodecnt;
			DEBUG("  %d %d\n  %d %d\n", nodecnt, -p[setfind(u)], nodecnt, -p[setfind(v)]);
			nodes[nodecnt]->lson = nodes[-p[setfind(u)]];
			nodes[nodecnt]->rson = nodes[-p[setfind(v)]];
			nodes[nodecnt]->lson->father = nodes[nodecnt]->rson->father = nodes[nodecnt];
			nodes[nodecnt]->alt = alt;
			nodes[nodecnt]->mindis = min(nodes[nodecnt]->lson->mindis, nodes[nodecnt]->rson->mindis);
			setunion(u, v, nodecnt);
			cnt++;
		}
		if (cnt != n)
			abort();
	}
}

namespace algorithm {
	using namespace kruskal;
	using dijkstra::d;

	int jmp[MaxN + MaxM][MaxLogN];
	int lg[MaxN];

	void prepare() {
		memset(jmp, 0, sizeof(jmp));
		dijkstra::run();
		run();
		for (int i = 1; i <= nodecnt; i++)
			if (nodes[i]->father)
				jmp[i][0] = nodes[i]->father->id;
			else
				jmp[i][0] = 0;
		lg[1] = 0;
		for (int i = 2; i <= n; i++)
			lg[i] = lg[i - 1] + (int)((1 << (lg[i - 1] + 1)) == i);
		PRINTARR("%d", lg, 1, n);
		for (int j = 1; j <= lg[n] + 1; j++)
			for (int i = 1; i <= nodecnt; i++)
				jmp[i][j] = jmp[jmp[i][j - 1]][j - 1];
	}

	int query(int u, int limit) {
		int ux = u;
		for (int i = lg[n]; i >= 0; i--)
			if (jmp[ux][i] && nodes[jmp[ux][i]]->alt > limit)
				ux = jmp[ux][i];
		if (nodes[ux]->father&&nodes[ux]->father->alt > limit)
			abort();
		return nodes[ux]->mindis;
	}
}

int q, k, s;
int v0, p0;

int main(int argc, char* argv[]) {
	int t;
	read(t);

	while (t--) {
		read(n); read(m);
		for (int i = 1; i <= m; i++) {
			read(e[i].u);
			read(e[i].v);
			read(e[i].len);
			read(e[i].alt);
		}

		algorithm::prepare();

		read(q); read(k); read(s);
		long long lastans = 0;
		for (int i = 1; i <= q; i++) {
			read(v0); read(p0);
			int v = (v0 + k * lastans - 1) % n + 1;
			int p = (p0 + k * lastans) % (s + 1);
			printf("%lld\n", lastans = algorithm::query(v, p));
		}
	}

	return 0;
}

#endif

