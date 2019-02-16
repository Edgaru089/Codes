#include <cstdlib>
#include <queue>
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

typedef long long ll;
const ll infinity=1e15;
const int MaxN=5000+10,MaxM=50000+10;

struct node{
	int v;
	ll flow,cost;
	node* next;
	node* rev;
};

node* h[MaxN];
node mem[2*MaxM],*memtop=mem;
#define ALLOCATE (++memtop)

int n,m;
int s,t;

void addedge(int u,int v,ll flow,ll cost){
	node* p=ALLOCATE;
	p->v=v;
	p->flow=flow;
	p->cost=cost;
	p->next=h[u];
	h[u]=p;
	node* pr=ALLOCATE;
	pr->v=u;
	pr->flow=0;
	pr->cost=-cost;
	pr->next=h[v];
	h[v]=pr;
	p->rev=pr;
	pr->rev=p;
}

ll dis[MaxN],limit[MaxN];
int from[MaxN];
node* fromedge[MaxN];
queue<int> Q;
bool inq[MaxN];
bool spfa(){
	DEBUG("Start SPFA()\n");
	for(int i=1;i<=n;i++){
		dis[i]=infinity;
		limit[i]=0;
		from[i]=0;
	}
	dis[s]=0;
	limit[s]=infinity;
	inq[s]=true;
	Q.push(s);
	while(!Q.empty()){
		int u=Q.front();
		Q.pop();
		inq[u]=false;
		DEBUG("    Poping node %d\n",u);
		for(node* p=h[u];p;p=p->next){
			DEBUG("        Iterating edge %d --> %d, flow=%lld, cost=%lld\n",u,p->v,p->flow,p->cost);
			int v=p->v;
			if(p->flow&&dis[v]>dis[u]+p->cost){
				dis[v]=dis[u]+p->cost;
				from[v]=u;
				fromedge[v]=p;
				limit[v]=min(limit[u],p->flow);
				if(!inq[v]){
					DEBUG("    Pushing node %d\n",v);
					inq[v]=true;
					Q.push(v);
				}
			}
		}
	}
	PRINTARR("%lld",dis,1,n);
	PRINTARR("%lld",limit,1,n);
	PRINTARR("%d",from,1,n);
	DEBUG("End of SPFA(), maxflow=%lld\n",limit[t]);
	return dis[t]<infinity;
}

ll maxflow,mincost;

void update(){
	int deltaflow=limit[t];
	maxflow+=deltaflow;
	mincost+=deltaflow*dis[t];
	for(int i=t;i!=s;i=from[i]){
		node* p=fromedge[i];
		node* pr=p->rev;
		p->flow-=deltaflow;
		pr->flow+=deltaflow;
	}
}

void edmondskarp(){
	maxflow=mincost=0;
	while(spfa())
		update();
}




int main(int argc, char* argv[]) {
	
	read(n);read(m);read(s);read(t);
	for(int i=1;i<=m;i++){
		int u,v;
		ll flow,cost;
		read(u);read(v);read(flow);read(cost);
		addedge(u,v,flow,cost);
	}
	
	edmondskarp();
	
	printf("%lld %lld\n",maxflow,mincost);
	
	return 0;
}


