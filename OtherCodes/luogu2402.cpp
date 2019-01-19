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
const ll infinity=1e15;

namespace flow{
	const int MaxN=10000+10,MaxM=100000+10;

	int n,m;
	int s,t;
	struct node{
		int v;
		ll flow;
		node* next,*rev;
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


	queue<int> Q;
	ll dis[MaxN];
	bool bfs(){
		for(int i=1;i<=n;i++)
			dis[i]=infinity;
		dis[s]=1;
		Q.push(s);
		while(!Q.empty()){
			int u=Q.front();
			Q.pop();
			for(node* p=h[u];p;p=p->next){
				if(p->flow>0&&dis[p->v]>dis[u]+1){
					dis[p->v]=dis[u]+1;
					Q.push(p->v);
				}
			}
		}
		return dis[t]<infinity;
	}

	node* cur[MaxN];
	ll dfs(int u,ll limit){
		if(limit==0||u==t)
			return limit;
		ll ans=0;
		for(node*& p=cur[u];p;p=p->next){
			int v=p->v;
			ll &flow=p->flow,f=0;
			if(dis[v]==dis[u]+1&&(f=dfs(v,min(flow,limit)))>0){
				limit-=f;
				flow-=f;
				p->rev->flow+=f;
				ans+=f;
			}
			if(limit==0)
				break;
		}
		return ans;
	}

	ll dinic(){
		ll ans=0;
		while(bfs()){
			for(int i=1;i<=n;i++)
				cur[i]=h[i];
			ans+=dfs(s,infinity);
		}
		return ans;
	}
}

using flow::dinic;
using flow::addedge;
using flow::s;
using flow::t;

const int MaxN=200+10,MaxM=1500+10;
int n,m;

ll dis[MaxN][MaxN];
ll c[MaxN],p[MaxN];
ll stotal;

int idx(int i){
	return i;
}

int idy(int i){
	return i+n;
}

bool check(ll limit){
	if(limit<0)
		return true;
	DEBUG("Checking limit %lld...",limit);
	memset(flow::h,0,sizeof(flow::h));
	flow::memtop=flow::mem;
	for(int i=1;i<=n;i++){
		addedge(s,idx(i),c[i]);
		addedge(idy(i),t,p[i]);
		for(int j=1;j<=n;j++)
			if(dis[i][j]<=limit)
				addedge(idx(i),idy(j),infinity);
	}
	bool flag=dinic()>=stotal;
	DEBUG("%s.\n",flag?"Success":"Failed");
	return flag;
}


int main(int argc, char* argv[]) {
	
	read(n);read(m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(i!=j)
				dis[i][j]=infinity;

	PASS;
	for(int i=1;i<=n;i++){
		read(c[i]);read(p[i]);
		stotal+=c[i];
	}
	PASS;
	for(int i=1;i<=m;i++){
		int u,v;
		ll w;
		read(u);read(v);read(w);
		dis[u][v]=dis[v][u]=min(dis[u][v],w);
	}
	
	PASS;
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);

	flow::s=2*n+1;
	flow::t=flow::n=flow::s+1;

	if(!check(infinity-2)){
		printf("-1\n");
		return 0;
	}

	ll l=-1,r=infinity;
	while(l<r-1){
		ll mid=(l+r)/2;
		if(check(mid))
			r=mid;
		else
			l=mid;
	}
	if(check(l))
		printf("%lld\n",l);
	else
		printf("%lld\n",r);
	
	
	return 0;
}


