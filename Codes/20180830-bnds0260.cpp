/*
DOCUMENT NAME "20180830-bnds0260.cpp"
CREATION DATE 2018-08-30
SIGNATURE CODE_20180830_BNDS0260
COMMENT #260. ¹ìµÀÅÚ
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180830_BNDS0260

#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

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


const int infinity = 1e8;
const int MaxN = 511 * 501 + 10, MaxM = 2 * 10 * MaxN;

int n, s, t;

struct node {
	int v, len;
	int flow;
	node* next;
	node* rev;
};

node* h[MaxN];
node mem[MaxM], *memtop = mem;
#define ALLOCATE (++memtop)

void addedge(int u, int v, int flow) {
	node* p = ALLOCATE;
	p->v = v;
	p->flow = flow;
	p->next = h[u];
	h[u] = p;
	node* r = ALLOCATE;
	r->v = u;
	r->flow = 0;
	r->next = h[v];
	h[v] = r;
	r->rev = p;
	p->rev = r;
}

template<typename Type, int Size = MaxN>
class queue {
public:
	queue() { clear(); }
	void clear() { left = 1; right = 0; }
	Type front() { return arr[left]; }
	void push(Type x) { arr[++right] = x; }
	void pop() { left++; }
	bool empty() { return !(right >= left); }
private:
	int left, right;
	Type arr[Size];
};

int dis[MaxN];
queue<int> Q;
bool bfs() {
	for (int i = 1; i <= n; i++)
		dis[i] = infinity;
	Q.push(s);
	dis[s] = 0;
	while (!Q.empty()) {
		int u = Q.front(); Q.pop();
		for (node* p = h[u]; p != nullptr; p = p->next) {
			int v = p->v, flow = p->flow;
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
int dfs(int u, int limit) {
	if (u == t || limit == 0)
		return limit;
	int val = 0;
	for (node* p = h[u]; p != nullptr&&limit > 0; p = p->next) {
		int v = p->v, f;
		int& flow = p->flow;
		if (dis[v] == dis[u] + 1 && (f = dfs(v, min(limit, flow))) != 0) {
			flow -= f;
			p->rev->flow += f;
			limit -= f;
			val += f;
		}
	}
	return val;
}
int dinic() {
	int ans = 0;
	while (bfs())
		ans += dfs(s, infinity);
	return ans;
}


int n0, m0;
int x, y;

int xid(int x) { return x; }
int yid(int y) { return n0 + y; }

int main(int argc, char* argv[]) {

	read(n0, m0);
	s = 2 * n0 + 1;
	n = t = s + 1;
	for (int i = 1; i <= n0; i++) {
		addedge(s, xid(i), 1);
		addedge(yid(i), t, 1);
	}
	for (int i = 1; i <= m0; i++) {
		read(x, y);
		addedge(xid(x), yid(y), 1);
	}

	printf("%d\n", dinic());

	return 0;
}

#endif

