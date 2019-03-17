#include <cstdlib>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <queue>
#include <climits>
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
const int MaxN=10000+10,MaxM=100000+10;

struct node{
	int v;
	ll flow;
	node* next;
	node* rev;
};

node* h[MaxN];
node mem[2*MaxM],*memtop=mem;
#define ALLOCATE (++memtop)

void addedge(int u,int v,ll flow){
	node* p=ALLOCATE;
	p->v=v;
	p->flow=flow;
	p->next=h[u];
	h[u]=p;
	node* pr=ALLOCATE;
	pr->v=u;
	pr->flow=0;
	pr->next=h[v];
	h[v]=pr;
	p->rev=pr;
	pr->rev=p;
}

int n,m;
int s,t;

queue<int> Q;
int dis[MaxN];

bool bfs(){
	memset(dis,0,sizeof(dis));
	dis[s]=1;
	while(!Q.empty())
		Q.pop();
	Q.push(s);
	while(!Q.empty()){
		int u=Q.front();
		Q.pop();
		if(u==t)
			return true;
		for(node* p=h[u];p;p=p->next){
			int v=p->v;
			if(p->flow!=0&&dis[v]==0){
				dis[v]=dis[u]+1;
				Q.push(v);
			}
		}
	}
	if(dis[t]!=0)
		return true;
	else
		return false;
}

node* cur[MaxN];

ll dfs(int u,ll limit){
	if(u==t&&limit!=0)
		return limit;
	ll ans=0;
	for(node*& p=cur[u];p&&limit;p=p->next){
		int v=p->v;
		ll d;
		if(dis[v]==dis[u]+1&&(d=dfs(v,min(limit,p->flow)))!=0){
			p->flow-=d;
			p->rev->flow+=d;
			limit-=d;
			ans+=d;
		}
		if(!limit)
			break;
	}
	return ans;
}

ll dinic(){
	ll ans=0;
	while(bfs()){
		memcpy(cur,h,sizeof(node*)*(n+3));
		ans+=dfs(s,INT_MAX);
	}
	return ans;
}


int main(int argc, char* argv[]) {
	
	read(n);read(m);read(s);read(t);
	for(int i=1;i<=m;i++){
		int u,v;
		ll flow;
		read(u);read(v);read(flow);
		addedge(u,v,flow);
	}
	
	printf("%lld\n",dinic());
	
	
	return 0;
}


