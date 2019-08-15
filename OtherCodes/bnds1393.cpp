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


const int MaxN=1e6+10,MaxM=1e6+10;

int n,m;

struct node{
	int v;
	node* next;
};

node* h[MaxN];
node mem[2*MaxM],*memtop=mem;
#define ALLOCATE (++memtop)

void addedge(int u,int v){
	node* p=ALLOCATE;
	p->v=v;
	p->next=h[u];
	h[u]=p;
	p=ALLOCATE;
	p->v=u;
	p->next=h[v];
	h[v]=p;
}

int dfn[MaxN],fa[MaxN],sstime;
int ssize[MaxN];
void dfs(int u,int from){
	dfn[u]=++sstime;
	fa[u]=from;
	ssize[u]=1;
	for(node* p=h[u];p;p=p->next)
		if(p->v!=from){
			dfs(p->v,u);
			ssize[u]+=ssize[p->v];
		}
}

int a[MaxN];
int d[MaxN];

int lowbit(int x){
	return x&(-x);
}

void add(int pos,int x){
	while(pos<=n){
		d[pos]+=x;
		pos+=lowbit(pos);
	}
}

int prefix(int pos){
	int sum=0;
	while(pos){
		sum+=d[pos];
		pos-=lowbit(pos);
	}
	return sum;
}

int query(int x,int y){
	return prefix(y)-prefix(x-1);
}


void change(int pos,int val){
	add(dfn[pos],val-a[pos]);
	a[pos]=val;
}

int get(int u){
	return query(dfn[u],dfn[u]+ssize[u]-1);
}




int main(int argc, char* argv[]) {

	read(n);
	for(int i=1;i<n;i++){
		int u,v;
		read(u);read(v);
		addedge(u,v);
	}

	dfs(1,0);

	read(m);
	for(int i=1;i<=m;i++){
		int op;
		read(op);
		if(op==1){
			int x;
			read(x);
			printf("%d\n",get(x));
		}else if(op==0){
			int x,y;
			read(x);read(y);
			change(x,y);
		}
	}



	return 0;
}


