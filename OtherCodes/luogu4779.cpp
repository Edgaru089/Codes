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

const int infinity=1e9;
const int MaxN=100000+10,MaxM=200000+10;

int n,m,s;

struct node{
	int v,len;
	node* next;
};

node* h[MaxN];
node mem[MaxM],*memtop=mem;
#define ALLOCATE (++memtop)

void addedge(int u,int v,int len){
	node* p=ALLOCATE;
	p->v=v;
	p->len=len;
	p->next=h[u];
	h[u]=p;
}

priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > Q;
int dis[MaxN];
bool been[MaxN];
void dijkstra(){
	for(int i=1;i<=n;i++)
		dis[i]=infinity;
	dis[s]=0;
	Q.push(make_pair(0,s));
	while(!Q.empty()){
		int u=Q.top().second;
		Q.pop();
		if(been[u])
			continue;
		DEBUG("%d left the heap\n",u);
		been[u]=true;
		for(node* p=h[u];p;p=p->next){
			if(dis[p->v]>dis[u]+p->len){
				dis[p->v]=dis[u]+p->len;
				Q.push(make_pair(dis[p->v],p->v));
			}
		}
	}
}



int main(int argc, char* argv[]) {
	
	read(n);read(m);read(s);
	for(int i=1;i<=m;i++){
		int u,v,l;
		read(u);read(v);read(l);
		addedge(u,v,l);
	}
	
	dijkstra();
	
	for(int i=1;i<=n;i++){
		if(i!=1)
			printf(" ");
		printf("%d",dis[i]);
	}
	printf("\n");
	
	return 0;
}


