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

const int infinity=1e7;
const int MaxN=50+10,MaxK=50+10,MaxM=1000+10;

int n,m,k;

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

int dis[MaxN][MaxK];
priority_queue<pair<int,pair<int,int> >,vector<pair<int,pair<int,int> > >,greater<pair<int,pair<int,int> > > > Q;

void dijkstra(){
	for(int i=1;i<=n;i++)
		for(int j=0;j<=k;j++)
			dis[i][j]=infinity;
	Q.push(make_pair(0,make_pair(1,0)));
	dis[1][0]=0;
	while(!Q.empty()){
		int l=Q.top().first,u=Q.top().second.first,j=Q.top().second.second;
		Q.pop();
		if(dis[u][j]<l)
			continue;
		for(node* p=h[u];p;p=p->next){
			int v=p->v,len=p->len;
			if(dis[v][j]>dis[u][j]+len){
				dis[v][j]=dis[u][j]+len;
				Q.push(make_pair(dis[v][j],make_pair(v,j)));
			}
			if(j<k&&dis[v][j+1]>dis[u][j]+len/2){
				dis[v][j+1]=dis[u][j]+len/2;
				Q.push(make_pair(dis[v][j+1],make_pair(v,j+1)));
			}
		}
	}
}



int main(int argc, char* argv[]) {
	
	read(n);read(m);read(k);
	for(int i=1;i<=m;i++){
		int u,v,l;
		read(u);read(v);read(l);
		addedge(u,v,l);
	}
	
	dijkstra();

	int ans=infinity;
	for(int i=0;i<=k;i++)
		ans=min(ans,dis[n][i]);
	
	printf("%d\n",ans);
	
	return 0;
}


