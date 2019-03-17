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

const int MaxN=2e3+10,MaxM=MaxN*MaxN/4;

int n,m;
int a[MaxN];

struct node{
	int v;
	bool useable;
	node* next;
	node* rev;
};

node* h[MaxN];
node mem[2*MaxM],*memtop=mem;
#define ALLOCATE (++memtop)

// u is on the left
void addedge(int u,int v){
	node* p=ALLOCATE;
	p->v=v;
	p->useable=true;
	p->next=h[u];
	h[u]=p;
	node* pr=ALLOCATE;
	pr->v=u;
	pr->useable=false;
	pr->next=h[v];
	h[v]=pr;
	pr->rev=p;
	p->rev=pr;
}

#define LEFT 0
#define RIGHT 1

bool used[MaxN];
int side[MaxN];

int u[MaxN],v[MaxN];

void bfs(){
	queue<int> Q;
	memset(side,-1,sizeof(side));
	Q.push(1);
	side[1]=LEFT;
	while(!Q.empty()){
		int u=Q.front();
		Q.pop();
		for(node* p=h[u];p;p=p->next){
			int v=p->v;
			if(side[v]<0){
				side[v]=side[u]^1;
				Q.push(v);
			}
		}
	}
}

bool dfs(int u){
	if(side[u]==RIGHT&&!used[u]){
		used[u]=true;
		return true;
	}
	for(node* p=h[u];p;p=p->next){
		if(p->useable){
			bool ok=dfs(p->v);
			if(ok){
				p->useable=false;
				p->rev->useable=true;
				return true;
			}
		}
	}
	return false;
}

int n0,m0,k0;

int main(int argc, char* argv[]) {
	
	read(n0);read(m0);read(k0);
	/*
	for(int i=1;i<=n;i++){
		int u,v;
		read(u[i]);read(v[i]);
		if()
		addedge(u[i],v[i]);
	}*/
	
	for(int i=1;i<=k0;i++){
		int u,v;
		read(u);read(v);
		if(u>n0||v>m0)
			continue;
		addedge(u,v+n0);
	}

	for(int i=1;i<=n0;i++)
		side[i]=LEFT;
	for(int i=n0+1;i<=n0+m0;i++)
		side[i]=RIGHT;
	n=n0+m0;
	
	int ans=0;
	for(int i=1;i<=n0;i++)
		ans+=(int)dfs(i);

	printf("%d\n",ans);
	
	return 0;
}


