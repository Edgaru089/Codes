#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <queue>
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
		fprintf(stderr,"Debug Assertation Failed on line %d, in function %s:\n  Expression: %s\n",__LINE__,__func__,#expr);\
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

typedef long double ld;
typedef long long ll;
const ld epsilon=1e-7;
const int infinity=1e9+100;
const int MaxN=100+10,MaxM=9900+10,MaxK=1000+10;

int n,m,k;
int b[MaxN][MaxK],s[MaxN][MaxK];
int val[MaxN][MaxN];
int dis[MaxN][MaxN];

struct node{
	int v,len,val;
	node* next;
};

node* h[MaxN];
node mem[MaxM+MaxN*MaxN],*memtop=mem;
#define ALLOCATE (++memtop)

void addedge(int u,int v,int len,int val){
	node* p=ALLOCATE;
	p->v=v;
	p->len=len;
	p->val=val;
	p->next=h[u];
	h[u]=p;
}


queue<int> Q;
ll dis0[MaxN],val0[MaxN];
int sn[MaxN];
bool inq[MaxN];

bool check(ld limit){
	memset(dis0,0,sizeof(dis0));
	memset(val0,0,sizeof(val0));
	memset(sn,0,sizeof(sn));
	while(!Q.empty())
		Q.pop();
	for(int i=1;i<=n;i++){
		inq[n]=true;
		Q.push(i);
	}
	while(!Q.empty()){
		int u=Q.front();
		Q.pop();
		inq[u]=false;
		for(node* p=h[u];p;p=p->next){
			int v=p->v;
			if((ld)(p->val+val0[u])/(ld)(p->len+dis0[u])>=limit&&dis0[v]<dis0[u]+p->len){
				dis0[v]=dis0[u]+p->len;
				val0[v]=val0[u]+p->val;
				sn[v]++;
				if(sn[v]>n)
					return true;
				if(!inq[v]){
					inq[v]=true;
					Q.push(v);
				}
			}
		}
	}
	return false;
}




int main(int argc, char* argv[]) {

	read(n);read(m);read(k);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)
			if(i!=j)
				dis[i][j]=infinity;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=k;j++){
			read(b[i][j]);
			read(s[i][j]);
		}
	}

	for(int i=1;i<=m;i++){
		int u,v,l;
		read(u);read(v);read(l);
		dis[u][v]=min(dis[u][v],l);
		addedge(u,v,l,0);
	}

	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(dis[i][k]+dis[k][j]<dis[i][j])
					dis[i][j]=dis[i][k]+dis[k][j];

	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			if(dis[i][j]<infinity){
				for(int l=1;l<=k;l++){
					if(b[i][l]!=-1&&s[j][l]!=-1)
						val[i][j]=max(val[i][j],s[j][l]-b[i][l]);
				}
				if(val[i][j]>0)
					addedge(i,j,dis[i][j],val[i][j]);
			}
		}

	ld l=0,r=2e9;
	while(r-l>epsilon){
		ld mid=(l+r)/2;
		DEBUG("Checking mid=%.7Lf...",mid);
		if(check(mid)){
			DEBUG("Success\n");
			l=mid;
		}else{
			DEBUG("Failed\n");
			r=mid;
		}
	}

	printf("%d\n",(int)((l+r)/2+1e-6));


	return 0;
}


