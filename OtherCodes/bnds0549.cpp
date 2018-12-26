#include <cstdlib>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <queue>
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

typedef long long ll;
const ll infinity=2e16;
const int MaxN=2e5+10, MaxM=2e5+10;
int n,m;

struct node{
	int v;
	ll len;
	node* next;
};

node* h[MaxN];
node mem[2*MaxM+2*MaxN],*memtop=mem;
#define ALLOCATE ++memtop

void addedgem(int u,int v,ll len){
	node* p=ALLOCATE;
	p->v=v;
	p->len=len;
	p->next=h[u];
	h[u]=p;
}

void addedge(int u,int v,ll len){
	addedgem(u,v,len);
	addedgem(v,u,len);
}

int s;

ll dis[MaxN];

typedef pair<long long, int> pii;
priority_queue<pii, vector<pii>, greater<pii> > Q;
bool been[MaxN];
void run() {
	for (int i = 1; i <= n; i++)
		dis[i] = infinity;
	Q.push(make_pair(0, s));
	dis[s] = 0;
	while (!Q.empty()) {
		pii t = Q.top(); Q.pop();
		int u = t.second;
		ll d = t.first;
		if (been[u])
			continue;
		been[u] = true;
		for (node* p = h[u]; p; p = p->next) {
			int v = p->v;
			ll len = p->len;
			if (dis[v] > dis[u] + len) {
				dis[v] = dis[u] + len;
				Q.push(make_pair(d + len, v));
			}
		}
	}
}


int main(int argc, char* argv[]) {

	read(n);read(m);
	for(int i=1;i<=m;i++){
		int u,v;
		ll len;
		read(u);read(v);read(len);
		addedge(u,v,2*len);
	}

	for(int i=1;i<=n;i++){
		ll len;
		read(len);
		addedgem(n+1,i,len);
	}
	s=n+1;
	n++;

	run();

	for(int i=1;i<=n-1;i++){
		if(i>1)
			printf(" ");
		printf("%lld",dis[i]);
	}

	printf("\n");

	return 0;
}


