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

const int infinity=0x0f7f7f7f;
const int MaxN=3000+10,MaxM=3000+10;

int n,m;

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

int val[MaxN];
int dp[MaxN][MaxM];

int dfs(int u,int from){
	if(u>=(n-m+1)){
		dp[u][1]=val[u];
		return 1;
	}
	dp[u][0]=val[u];
	int cnt=0;
	for(node* p=h[u];p;p=p->next){
		int v=p->v;
		if(v==from)
			continue;
		int t=dfs(v,u);
		for(int k=cnt;k>=0;k--)
			for(int j=1;j<=t;j++)
				dp[u][k+j]=max(dp[u][k+j],dp[u][k]+dp[v][j]);
		cnt+=t;
	}
	return cnt;
}


int main(int argc, char* argv[]) {
	
	read(n);read(m);
	for(int i=1;i<=n-m;i++){
		int k;
		read(k);
		for(int j=1;j<=k;j++){
			int v,len;
			read(v);read(len);
			addedge(i,v);
			val[v]-=len;
		}
	}
	for(int i=n-m+1;i<=n;i++){
		int x;
		read(x);
		val[i]+=x;
	}
	
	for(int i=1;i<=n;i++)
		for(int j=0;j<=n;j++)
			dp[i][j]=-infinity;
	
	int k=dfs(1,0);
	ASSERT(k==m);

	int ans=0;
	for(int i=0;i<=m;i++)
		if(dp[1][i]>=0)
			ans=max(ans,i);
	
	printf("%d\n",ans);

	return 0;
}


