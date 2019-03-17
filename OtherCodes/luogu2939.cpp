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

const int MaxN=10000+10,MaxM=50000+10,MaxK=20+10;

int n,m,k;
int s,t;

struct node{
	int v,len;
	node* next;
};

node* h[MaxN];
node mem[2*MaxM],*memtop=mem;
#define ALLOCATE (++memtop)

void addedge(int u,int v,int len){
	node* p=ALLOCATE;
	p->v=v;
	p->len=len;
	p->next=h[u];
	h[u]=p;
	p=ALLOCATE;
	p->v=u;
	p->len=len;
	p->next=h[v];
	h[v]=p;
}

struct st{
	int u,j;
	int dis;
};

struct stcmp{
	bool operator ()(st x,st y)const{
		return x.dis>y.dis;
	}
};


int dis[MaxN][MaxK];
priority_queue<st,vector<st>,stcmp> Q;
void dijkstra(){
	PASS;
	memset(dis,0x7f,sizeof(dis));
	Q.push(st{s,0,0});
	dis[s][0]=0;
	while(!Q.empty()){
		PASS;
		int u=Q.top().u,j=Q.top().j,d=Q.top().dis;
		Q.pop();
		if(dis[u][j]<d)
			continue;
		for(node* p=h[u];p;p=p->next){
			int v=p->v,len=p->len;
			if(dis[v][j]>dis[u][j]+len){
				dis[v][j]=dis[u][j]+len;
				Q.push(st{v,j,dis[v][j]});
			}
			if(j<=k-1&&dis[v][j+1]>dis[u][j]){
				dis[v][j+1]=dis[u][j];
				Q.push(st{v,j+1,dis[v][j+1]});
			}
		}
	}
}


int main(int argc, char* argv[]) {
	
	read(n);read(m);read(k);
	s=1;t=n;
	for(int i=1;i<=m;i++){
		int u,v,t;
		read(u);read(v);read(t);
		addedge(u,v,t);
	}
	
	dijkstra();
	
	int ans=0x7f7f7f7f;
	for(int i=0;i<=k;i++)
		ans=min(ans,dis[t][i]);
	printf("%d\n",ans);
	
	return 0;
}


