/*
DOCUMENT NAME "20180731-luogu3171.cpp"
CREATION DATE 2018-07-31
SIGNATURE CODE_20180731_LUOGU3171
COMMENT [CQOI2015]ÍøÂçÍÌÍÂÁ¿
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180731_LUOGU3171

#include <cstdlib>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

using ll = long long;

#define ALLOCATE (++memtop)
constexpr ll infinity = 1e14;
constexpr ll MaxN = 10000 + 10, MaxM = 100000 + 10;

template<typename IntType = ll>
IntType read() {
	IntType val = 0;
	ll c;
	while (!isdigit(c = getchar()));
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = getchar()));
	ungetc(c, stdin);
	return val;
}

template<typename IntType>
void read(IntType& x) { x = read<IntType>(); }
template<typename IntType, typename... Args>
void read(IntType& x, Args&... args) { x = read<IntType>(); read(args...); }


namespace graph {
	ll n, m;
	ll s;

	struct node {
		ll v, len;
		node* next;
	};

	node* h[MaxN];
	node mem[2 * MaxM], *memtop = mem;

	void addedge(ll u, ll v, ll len) {
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

	queue<ll> Q;
	bool inQ[MaxN];
	ll dis[MaxN];
	void spfa() {
		for (ll i = 1; i < MaxN; i++)
			dis[i] = infinity;
		Q.push(s);
		inQ[s] = true;
		dis[s] = 0;
		while (!Q.empty()) {
			ll u = Q.front();
			Q.pop(); inQ[u] = false;
			for (node* p = h[u]; p != nullptr; p = p->next) {
				ll v = p->v, len = p->len;
				if (dis[v] > dis[u] + len) {
					dis[v] = dis[u] + len;
					if (!inQ[v]) {
						inQ[v] = true;
						Q.push(v);
					}
				}
			}
		}
	}
}


namespace flow {
	ll n, m;
	ll s, t;

	struct node {
		ll v, flow;
		node* next;
		node* rev;
	};

	node* h[MaxN];
	node mem[2 * MaxM], *memtop = mem;

	void addedge(ll u, ll v, ll flow) {
		node* p1 = ALLOCATE;
		p1->v = v;
		p1->flow = flow;
		p1->next = h[u];
		h[u] = p1;
		node* p2 = ALLOCATE;
		p2->v = u;
		p2->flow = 0;
		p2->next = h[v];
		h[v] = p2;
		p1->rev = p2;
		p2->rev = p1;
	}

	ll dis[MaxN];

	queue<ll> Q;
	bool bfs() {
		for (ll i = 1; i <= n; i++)
			dis[i] = infinity;
		Q.push(s);
		dis[s] = 0;
		while (!Q.empty()) {
			ll u = Q.front(); Q.pop();
			for (node* p = h[u]; p != nullptr; p = p->next) {
				ll v = p->v, flow = p->flow;
				if (flow > 0)
					if (dis[v] == infinity) {
						dis[v] = dis[u] + 1;
						Q.push(v);
					}
			}
		}
		if (dis[t] == infinity)
			return false;
		else
			return true;
	}

	ll dfs(ll u, ll limit) {
		if (u == t || limit == 0)
			return limit;
		ll val = 0;
		for (node* p = h[u]; p != nullptr&&limit > 0; p = p->next) {
			ll v = p->v, f;
			ll& flow = p->flow;
			if (dis[v] == dis[u] + 1 && (f = dfs(v, min(limit, flow))) != 0) {
				flow -= f;
				p->rev->flow += f;
				limit -= f;
				val += f;
			}
		}
		return val;
	}

	ll dinic() {
		ll ans = 0;
		while (bfs())
			ans += dfs(s, infinity);
		return ans;
	}
}


ll n, m;
ll u, v, l;
ll throughput[MaxN];

ll inid(ll id) { return id; }
ll outid(ll id) { return id + n; }

void buildflow() {
	using graph::dis;
	using graph::node;
	using graph::h;
	using flow::addedge;
	using flow::s;
	using flow::t;

	s = 2 * n + 1;
	t = 2 * n + 2;
	flow::n = t;
	addedge(s, outid(1), infinity);
	addedge(inid(n), t, infinity);
	for (ll u = 1; u <= n; u++) {
		addedge(inid(u), outid(u), throughput[u]);
		for (node* p = h[u]; p != nullptr; p = p->next) {
			ll v = p->v, len = p->len;
			if (dis[v] == dis[u] + len) {
				addedge(outid(u), inid(v), infinity);
			}
		}
	}
}


int main(int argc, char* argv[]) {
	using graph::addedge;

	read(n, m);
	graph::n = flow::n = n;
	graph::s = flow::s = 1;
	flow::t = n;
	for (ll i = 1; i <= m; i++) {
		read(u, v, l);
		addedge(u, v, l);
	}
	for (ll i = 1; i <= n; i++)
		read(throughput[i]);

	graph::spfa();
	buildflow();
	printf("%lld\n", flow::dinic());

	return 0;
}

#endif

