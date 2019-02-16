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

const int MaxN=1000+10,MaxM=1000+10;

int n,m;

struct node{
	int v;
	node* next;
};

node* h[MaxN];
node mem[2*MaxN*MaxN],*memtop=mem;
int incnt[MaxN];
#define ALLOCATE (++memtop)

void addedge(int u,int v){
	node* p=ALLOCATE;
	p->v=v;
	p->next=h[u];
	h[u]=p;
	incnt[v]++;
}

int ansu[MaxN];
int dfs(int u){
	if(ansu[u])
		return ansu[u];
	int ans=0;
	for(node* p=h[u];p;p=p->next)
		ans=max(ans,dfs(p->v));
	return ansu[u]=ans+1;
}

int x[MaxN];
bool flag[MaxN];
bool edge[MaxN][MaxN];


int main(int argc, char* argv[]) {
	
	read(n);read(m);
	for(int i=1;i<=m;i++){
		int a;
		read(a);
		memset(flag,0,sizeof(flag));
		int l=n+1,r=0;
		for(int j=1;j<=a;j++){
			read(x[j]);
			flag[x[j]]=true;
			l=min(l,x[j]);
			r=max(r,x[j]);
		}
		for(int j=l;j<=r;j++)
			if(!flag[j])
				for(int k=1;k<=a;k++)
					edge[x[k]][j]=true;
	}
	
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(edge[i][j])
				addedge(i,j);
	
	int ans=0;
	for(int i=1;i<=n;i++)
		if(incnt[i]==0)
			ans=max(ans,dfs(i));

	printf("%d\n",ans);

	return 0;
}


