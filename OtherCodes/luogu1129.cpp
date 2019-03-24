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

typedef long long ll;
const int MaxN=10000+10,MaxM=100000+10;

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
    p->rev=pr;
    pr->rev=p;
}

int n,m;
int s,t;

queue<int> Q;
int dis[MaxN];

bool bfs(){
    memset(dis,0,sizeof(dis));
    dis[s]=1;
    while(!Q.empty())
        Q.pop();
    Q.push(s);
    while(!Q.empty()){
        int u=Q.front();
        Q.pop();
        if(u==t)
            return true;
        for(node* p=h[u];p;p=p->next){
            int v=p->v;
            if(p->flow!=0&&dis[v]==0){
                dis[v]=dis[u]+1;
                Q.push(v);
            }
        }
    }
    if(dis[t]!=0)
        return true;
    else
        return false;
}

int dfs(int u,int limit){
    if(u==t&&limit!=0)
        return limit;
    int ans=0;
    for(node* p=h[u];p;p=p->next){
        int v=p->v;
        int d;
        if(dis[v]==dis[u]+1&&(d=dfs(v,min(limit,p->flow)))!=0){
            p->flow-=d;
            p->rev->flow+=d;
            limit-=d;
            ans+=d;
        }
    }
    return ans;
}

int dinic(){
    int ans=0;
    while(bfs())
        ans+=dfs(s,1e8);
    return ans;
}

int n0;



int main(int argc, char* argv[]) {

	int k;
	read(k);
	while(k--){
		read(n0);
		int a;
		memset(h,0,sizeof(h));
		memtop=mem;
		for(int i=1;i<=n0;i++)
			for(int j=1;j<=n0;j++){
				read(a);
				if(a==1)
					addedge(i,n0+j,1);
			}
		s=n0*n0+1;
		t=n=s+1;
		for(int i=1;i<=n0;i++){
			addedge(s,i,1);
			addedge(i+n0,t,1);
		}

		if(dinic()==n0)
			printf("Yes\n");
		else
			printf("No\n");
	}





	return 0;
}


