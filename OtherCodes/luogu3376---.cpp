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
const int MaxN=10000+10,MaxM=100000+10;

int n,m;

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
	pr->v=u;
	pr->flow=0;
	pr->next=h[v];
	h[v]=pr;
	pr->rev=p;
	p->rev=pr;
}

int s,t;

queue<int> Q;
int dep[MaxN];
bool bfs(){
	memset(dep,0,sizeof(dep));
	dep[s]=1;
	Q.push(s);
	while(!Q.empty()){
		int u=Q.front();
		Q.pop();
		for(node* p=h[u];p;p=p->next){
			int v=p->v;
			if(p->flow>0&&dep[v]==0){
				dep[v]=dep[u]+1;
				Q.push(v);
			}
		}
	}
	return dep[t]>0;
}

node* cur[MaxN];
int dfs(int u,int limit){
	if(u==t||limit==0)
		return limit;
	int f,ans=0;
	for(node*& p=cur[u];p;p=p->next){
		int v=p->v;
		if(dep[v]==dep[u]+1&&(f=dfs(v,min(limit,p->flow)))>0){
			limit-=f;
			p->flow-=f;
			p->rev->flow+=f;
			ans+=f;
		}
		if(!limit)
			break;
	}
	return ans;
}

int dinic(){
	int ans=0;
	while(bfs()){
		for(int i=1;i<=n;i++)
			cur[i]=h[i];
		ans+=dfs(s,infinity);
	}
	return ans;
}





int main(int argc, char* argv[]) {

	read(n);read(m);read(s);read(t);
	for(int i=1;i<=m;i++){
		int u,v,f;
		read(u);read(v);read(f);
		addedge(u,v,f);
	}

	printf("%d\n",dinic());




	return 0;
}


