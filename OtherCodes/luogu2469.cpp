#include <cstdlib>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <cstdio>
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

namespace flow{
	int n,m;
	int s,t;

	template<typename Iterator, typename Value>
	void valfill(Iterator begin, Iterator end, Value value) {
		while (begin != end) {
			*begin = value;
			begin++;
		}
	}

	struct node {
		int v, flow, cost;
		node* next, *rev;
	};

	node* h[MaxN];
	node mem[2 * MaxM], *memtop = mem;
#define ALLOCATE (++memtop)

	void addedge(int u, int v, int flow, int cost) {
		node* p = ALLOCATE;
		p->v = v;
		p->flow = flow;
		p->cost = cost;
		p->next = h[u];
		h[u] = p;
		node* pr = ALLOCATE;
		pr->v = u;
		pr->flow = 0;
		pr->cost = -cost;
		pr->next = h[v];
		h[v] = pr;
		pr->rev = p;
		p->rev = pr;
	}

	queue<int> Q;
	bool inQ[MaxN];
	int dis[MaxN], from[MaxN], limit[MaxN];
	node* fromedge[MaxN];
	bool bfs() {
		valfill(dis + 1, dis + n + 1, infinity);
		valfill(from + 1, from + n + 1, 0);
		valfill(limit + 1, limit + n + 1, 0);
		dis[s] = 0;
		limit[s] = infinity;
		from[s] = 0;
		fromedge[s] = 0;
		Q.push(s);
		while (!Q.empty()) {
			int u = Q.front();
			Q.pop(); inQ[u] = false;
			for (node* p = h[u]; p; p = p->next) {
				int v = p->v, cost = p->cost;
				if (p->flow != 0 && dis[v] > dis[u] + cost) {
					dis[v] = dis[u] + cost;
					from[v] = u;
					fromedge[v] = p;
					limit[v] = min(limit[u], p->flow);
					if (!inQ[v]) {
						Q.push(v);
						inQ[v] = true;
					}
				}
			}
		}
		return dis[t] < infinity;
	}

	int maxflow, mincost;
	void update() {
		maxflow += limit[t];
		mincost += limit[t] * dis[t];
		int v = t;
		while (v != s) {
			node* p = fromedge[v];
			p->flow -= limit[t];
			p->rev->flow += limit[t];
			v = from[v];
		}
	}

	void edmondsKarp() {
		while (bfs())
			update();
	}
}




int main(int argc, char* argv[]) {
	
	
	
	
	
	
	return 0;
}


