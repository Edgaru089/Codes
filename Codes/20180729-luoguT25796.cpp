/*
DOCUMENT NAME "20180729-luoguT25796.cpp"
CREATION DATE 2018-07-29
SIGNATURE CODE_20180729_LUOGUT25796
COMMENT
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180729_LUOGUT25796

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <queue>
#include <cstring>
#include <exception>
using namespace std;

constexpr double infinity = 1e10;
constexpr int MaxN = 20000 + 10, MaxM = 2 * 20000 + 10;

struct pnt {
	double x, y;
};

struct edge {
	int u, v;
	double len;
};

double sqr(double x) { return x * x; }

double dist(pnt x, pnt y) {
	return sqrt(sqr(x.x - y.x) + sqr(x.y - y.y));
}

int n, m;
int s, t;
pnt p[MaxN];
edge e[MaxM];

bool ok[MaxM];

struct node {
	int v;
	double len;
	node* next;
};

node* h[MaxN];
node mem[2 * MaxM], *memtop = mem;
#define ALLOCATE (++memtop)

void addedge(int u, int v, double len) {
	node* p = ALLOCATE;
	p->v = v;
	p->len = len;
	p->next = h[u];
	h[u] = p;
	p = ALLOCATE;
	p->v = u;
	p->len = len;
	p->next = h[v];
	h[v] = p;
}


double dis[MaxN];
struct st {
	int u;
	double dis;
};
struct stcompare {
	bool operator () (const st& x, const st& y) {
		return x.dis > y.dis;
	}
};
namespace dijstra {
	typedef pair<double, int> pdi;
	priority_queue<pdi, vector<pdi>, greater<pdi>> Q;
	bool been[MaxN];
	void run() {
		for (int i = 1; i <= n; i++)
			dis[i] = infinity;
		Q.push(make_pair(0, s));
		dis[s] = 0;
		while (!Q.empty()) {
			pdi t = Q.top(); Q.pop();
			int u = t.second, d = t.first;
			if (been[u])
				continue;
			been[u] = true;
			for (node* p = h[u]; p != nullptr; p = p->next) {
				int v = p->v;
				double len = p->len;
				if (dis[v] > dis[u] + len) {
					dis[v] = dis[u] + len;
					Q.push(make_pair(d + len, v));
				}
			}
		}
	}
}

int main(int argc, char* argv[]) {

	scanf("%d%d%d%d", &n, &m, &s, &t);
	for (int i = 1; i <= n; i++)
		scanf("%lf%lf", &p[i].x, &p[i].y);
	for (int i = 1; i <= m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[i].u = u;
		e[i].v = v;
		e[i].len = dist(p[u], p[v]);
		ok[i] = true;
	}
	char buf[20];
	int x = -1;
	while (scanf("%s%d", buf, &x) != 0) {
		if (buf[2] == 'X')
			ok[x] = false;
		else if (buf[2] == 'N')
			ok[x] = true;
	}
	for (int i = 1; i <= m; i++) {
		if (ok[i])
			addedge(e[i].u, e[i].v, e[i].len);
	}

	dijstra::run();

	if (dis[t] == infinity)
		printf("-1\n");
	else
		printf("%.4lf\n", dis[t]);

	return 0;
}

#endif

