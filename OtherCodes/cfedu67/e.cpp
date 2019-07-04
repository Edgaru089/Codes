#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
using namespace std;

#if (defined LOCAL) || (defined D)
#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define PRINTARR(formatstr, arr, beginoff, size)				\
do{fprintf(stderr,#arr ":");									\
for (int __i = beginoff; __i <= beginoff + size - 1; __i++)		\
	fprintf(stderr,"\t%d", __i);								\
fprintf(stderr,"\n");											\
for (int __i = beginoff; __i <= beginoff + size - 1; __i++)		\
	fprintf(stderr,"\t" formatstr, arr[__i]);					\
fprintf(stderr,"\n"); }while(false)
#define PASS fprintf(stderr,"Passing function \"%s\" on line %d\n", __func__, __LINE__)
#define ASSERT(expr) do{\
	if(!(expr)){\
		fprintf(stderr,"Debug Assertion Failed on line %d, in function %s:\n  Expression: %s\n",__LINE__,__func__,#expr);\
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

const int MaxN=2e5+10;

int n;

struct node{
	int v;
	node* next;
};

node* h[MaxN];
node mem[2*MaxN],*memtop=mem;
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

int ssize[MaxN],msize[MaxN];

void dfs0(int u,int from){
	ssize[u]=1;
	for(node* p=h[u];p;p=p->next){
		int v=p->v;
		if(v!=from){
			dfs0(v,u);
			ssize[u]+=ssize[v];
			if(ssize[v]>msize[u])
				msize[u]=ssize[v];
		}
	}
}

int ans[MaxN];
void dfs1(int u,int from){
	ans[u]=ssize[u];
	for(node* p=h[u];p;p=p->next){
		if(p->v!=from){
			dfs1(p->v,u);
			ans[u]+=ans[p->v];
		}
	}
}



int main(int argc, char* argv[]) {

	read(n);
	for(int i=1;i<=n-1;i++){
		int u,v;
		read(u);read(v);
		addedge(u,v);
	}

	dfs0(1,0);
	for(int u=2;u<=n;u++){
		if(ssize[1]-ssize[u]>msize[u])
			msize[u]=ssize[1]-ssize[u];
	}

	int mins=1000000,id=1;
	for(int i=1;i<=n;i++){
		if(msize[i]!=0&&mins>msize[i]){
			mins=msize[i];
			id=i;
		}
	}

	PRINTARR("%d",ssize,1,n);
	PRINTARR("%d",msize,1,n);
	DEBUG("id=%d\n",id);

	dfs0(id,0);

	PRINTARR("%d",ssize,1,n);

	dfs1(id,0);

	PRINTARR("%d",ans,1,n);

	printf("%d\n",ans[id]);



	return 0;
}


