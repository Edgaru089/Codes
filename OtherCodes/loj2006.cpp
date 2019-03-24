// loj#2006. 「SCOI2015」小凸玩矩阵
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

const int MaxN=1000+10,MaxM=2000+10;

struct node{
	int v,flow;
	node* next;
	node* rev;
};

node* h[MaxN];
node mem[2*MaxM],*memtop=mem;
#define ALLOCATE (++memtop)

void addedge(int u,int v,int flow){
	node* p=ALLOCATE;
	p->v=v;
	p->flow=flow;
	p->next=h[u];
	h[u]=p;
	node* pr=ALLOCATE;
	pr->v=v;
	pr->flow=0;
	pr->next=h[v];
	h[v]=pr;
	pr->rev=p;
	p->rev=pr;
}

int s,t;
int dis[MaxN];
queue<int> Q;
bool bfs(){
	memset(dis,-1,sizeof(dis));
	Q.push(s);
	dis[s]=1;
	while(!Q.empty()){
		int u=Q.front();
		DEBUG("u=%d\n",u);
		Q.pop();
		for(node* p=h[u];p;p=p->next){
			int v=p->v;
			if(p->flow&&dis[v]<0){
				dis[v]=dis[u]+1;
				Q.push(v);
				DEBUG("push v=%d\n",v);
			}
		}
	}
#ifdef D
	if(dis[t]>=0)
		DEBUG("bfs success\n");
	else
		DEBUG("bfs failure\n");
#endif
	return dis[t]>=0;
}

node* cur[MaxN];
int dfs(int u,int limit){
	if(u==t||!limit)
		return limit;
	int ans=0;
	int f;
	for(node*& p=cur[u];p;p=p->next){
		int v=p->v,&flow=p->flow;
		if(dis[v]==dis[u]+1&&flow&&(f=dfs(v,min(flow,limit)))){
			ans+=f;
			flow-=f;
			p->rev->flow+=f;
			limit-=f;
		}
		if(!limit)
			break;
	}
	return ans;
}

int dinic(){
	int ans=0;
	while(bfs()){
		memcpy(cur,h,sizeof(cur));
		ans+=dfs(s,10000000);
	}
	DEBUG("dinic()=%d\n",ans);
	return ans;
}

int n,m,k;
int a[MaxN][MaxN];

bool check(int limit){
	memset(h,0,sizeof(h));
	memtop=mem;
	s=n+m+1;
	t=n+m+2;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(a[i][j]>=limit)
				addedge(i,n+j,1);
	for(int i=1;i<=n;i++)
		addedge(s,i,1);
	for(int i=1;i<=m;i++)
		addedge(i+n,t,1);
	return dinic()>=k;
}


int main(int argc, char* argv[]) {

	read(n);read(m);read(k);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			read(a[i][j]);

	int l=1,r=1000000000;
	while(l<r-1){
		int mid=(l+r)/2;
		if(check(mid))
			r=mid;
		else
			l=mid;
	}

	if(check(l))
		printf("%d\n",l);
	else
		printf("%d\n",r);

	return 0;
}


