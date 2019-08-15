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

const int MaxN=500+10,MaxD=500+10;

int n,d;

struct node{
	int v,len;
	node* next;
};

node mem[2*MaxN],*memtop=mem;
node* h[MaxN];
#define ALLOCATE (++memtop)

int icnt[MaxN];

int root=1;

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

int dis[MaxN];

void dfs1(int u,int from){
	for(node* p=h[u];p;p=p->next){
		int v=p->v;
		if(v!=from){
			dis[v]=dis[u]+p->len;
			dfs1(v,u);
		}
	}
}




int main(int argc, char* argv[]) {

	bool strflag=true;

	read(n);read(d);
	for(int i=1;i<n;i++){
		int u,v,l;
		read(u);read(v);read(l);
		addedge(u,v,l);
		icnt[u]++;
		icnt[v]++;
	}

	for(int i=1;i<=n;i++)
		if(icnt[i]>2)
			strflag=false;

	if(strflag){

		for(int i=1;i<=n;i++)
			if(icnt[i]==1){
				root=i;
				break;
			}

		dfs1(root,0);
		sort(dis+1,dis+n+1);

		int ans=1,sum=0;
		for(int i=2;i<=n;i++){
			sum+=(dis[i]-dis[i-1]);
			if(sum>d){
				ans++;
				sum=0;
			}
		}

		printf("%d\n",ans);
	}else{


	}

	return 0;
}


