/*
DOCUMENT NAME "20180728-luogu4722.cpp"
CREATION DATE 2018-07-28
SIGNATURE CODE_20180728_LUOGU4722
COMMENT 【模板】最大流 加强版 / 预流推进
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180728_LUOGU4722

#ifdef LOCAL
//#define DEBUG
#endif
#define USE_FREAD_INPUT_OPTIMIZATION

#include <cstdlib>
#include <iostream>
#include <queue>
#include <cstring>
#include <climits>
#include <exception>
#include <string>
#include <cassert>
using namespace std;

#ifdef DEBUG
#define debug(...) printf(__VA_ARGS__)
#else
#define debug(...)
#endif

typedef long long ll;

constexpr ll infinity = 1e12;
constexpr int MaxN = 12000 + 10, MaxM = 200000 + 10;

#ifdef USE_FREAD_INPUT_OPTIMIZATION
constexpr int buffersize = 80 * 1024 * 1024;
char buffer[buffersize], *buffertop = buffer;
#define GETCHAR *(buffertop++)
#define UNGETCHAR(c) (--buffertop)
#else
#define GETCHAR getchar()
#define UNGETCHAR(c) ungetc(c, stdin);
#endif

template<typename IntType = int>
IntType read() {
	IntType ans = 0;
	int c;
	while (!isdigit(c = GETCHAR));
	do {
		ans = (ans << 3) + (ans << 1) + c - '0';
	} while (isdigit(c = GETCHAR));
	UNGETCHAR(c);
	return ans;
}

template<typename IntType>
void read(IntType& val) { val = read<IntType>(); }
template<typename IntType, typename... Args>
void read(IntType& val, Args&... args) { val = read<IntType>(); read(args...); }

int n, m;
int s, t;

struct node {
	int v;
	ll flow;
	node* next;
	node* rev;
};

node* h[MaxN];
node mem[4 * MaxM], *memtop = mem;
#define ALLOCATE (++memtop)

void addedge(int u, int v, ll flow) {
	node* p = ALLOCATE;
	p->v = v;
	p->flow = flow;
	p->next = h[u];
	h[u] = p;
	node* prev = ALLOCATE;
	prev->v = u;
	prev->flow = 0;
	prev->next = h[v];
	h[v] = prev;
	p->rev = prev;
	prev->rev = p;
}




struct st {
	int u;
	int height;
};

struct stcompare {
	bool operator () (const st& x, const st& y) const {
		return x.height < y.height;
	}
};

priority_queue<st, vector<st>, stcompare> Q;
ll e[MaxN];
int height[MaxN];

queue<int> Q0;
void bfs() {
	memset(height, -1, sizeof(height));
	Q0.push(t);
	height[t] = 0;
	while (!Q0.empty()) {
		int u = Q0.front();
		Q0.pop();
		for (node* p = h[u]; p != nullptr; p = p->next) {
			int v = p->v;
			if (p->rev->flow != 0) {
				if (height[v] == -1) {
					height[v] = height[u] + 1;
					Q0.push(v);
				}
			}
		}
	}
}

void prepare() {
	int& u = s;
	for (node* p = h[s]; p != nullptr; p = p->next) {
		if (p->flow != 0) {
			int v = p->v;
			ll flow = p->flow;
			p->flow = 0;
			p->rev->flow += flow;
			e[v] += flow;
			e[u] -= flow;
			if (v != t)
				Q.push(st{v, height[v]});
			debug("Source prepushed--> %d flow: %lld\n", v, flow);
		}
	}
}

void reheight(int u) {
	int minheight = INT_MAX;
	for (node* p = h[u]; p != nullptr; p = p->next) {
		assert(p->flow >= 0);
		if (p->flow != 0)
			minheight = min(minheight, height[p->v]);
	}
	if (minheight != INT_MAX)
		height[u] = minheight + 1;
	//height[u]++;
}

void push() {
	st a = Q.top();
	Q.pop();
	int u = a.u;
	if (height[u] < a.height)
		return;
	assert(e[u] >= 0);
	debug("%d (height %d) pushing\n", u, height[u]);
	for (node* p = h[u]; p != nullptr&&e[u] != 0; p = p->next) {
		assert(p->flow >= 0);
		if (p->flow == 0)
			continue;
		int v = p->v;
		if (height[v] == height[u] - 1) {
			ll flow = min(e[u], p->flow);
			assert(p->flow >= 0);
			assert(flow >= 0);
			e[v] += flow;
			e[u] -= flow;
			p->flow -= flow;
			p->rev->flow += flow;
			if (e[v] > 0 && v != t && v != s)
					Q.push(st{v, height[v]});
			debug("%d(height %d) -->pushed--> %d(height %d) flow: %lld\n", u, height[u], v, height[v], flow);
		}
	}
	if (e[u] > 0 && u != t && u != s) {
		reheight(u);
		Q.push(st{u, height[u]});
		debug("%d reheighted to %d\n", u, height[u]);
	}
}

bool checkrepush() {
	debug("checking excessive flow...");
	bool done = true;
	for (int i = 1; i <= n; i++) {
		if (i != s && i != t && e[i] != 0) {
			done = false;
			Q.push(st{i,height[i]});
		}
	}
	debug("checked. %s.\n", done ? "done" : "undone");
	return done;
}

ll preflowpush() {
	bfs();
	height[s] = n;
	prepare();
	do {
		while (!Q.empty())
			push();
	} while (!checkrepush());
	assert(e[s] == -e[t]);
	return e[t];
}



int main(int argc, char* argv[]) {
#ifdef USE_FREAD_INPUT_OPTIMIZATION
	fread(buffer, 1, buffersize, stdin);
#endif
	read(n, m, s, t);
	int u, v;
	int c;
	for (int i = 1; i <= m; i++) {
		read(u, v, c);
		addedge(u, v, c);
	}

	printf("%lld\n", preflowpush());

	return 0;
}

#endif

