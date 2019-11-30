#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <map>
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
#define PRINTARR2D(formatstr, arr, beginoff, size, beginy, sizey)\
do{fprintf(stderr,#arr ":");									\
for (int __i = beginy; __i <= beginy + sizey - 1; __i++)		\
	fprintf(stderr,"\t%d", __i);								\
fprintf(stderr,"\n");											\
for (int __i = beginoff; __i <= beginoff + size - 1; __i++) {	\
	fprintf(stderr, "%d:", __i);								\
	for(int __j = beginy; __j <= beginy + sizey -1; __j++)		\
		fprintf(stderr,"\t" formatstr, arr[__i][__j]);			\
	fprintf(stderr, "\n");										\
}}while(false)
#else
#define DEBUG(...)
#define PRINTARR(a, b, c, d)
#define PRINTARR2D(a, b, c, d, e, f)
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
const int MaxN=1e5+10,MaxM=3e5+10;
const int MaxK=MaxN,MaxQ=MaxM;

int n,m,k,q;
int a[MaxQ],b[MaxQ];

struct node{
	int v;
	ll len;
	node* next;
};

node* h[MaxN];
node mem[2*MaxM],*memtop=mem;
#define ALLOCATE (++memtop)

void addedge(int u,int v,ll len){
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

ll d[MaxN];
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > Q;
void dijkstra(){
	memset(d,-1,sizeof(d));
	for(int i=1;i<=k;i++){
		Q.push(make_pair(0,i));
		d[i]=0;
	}
	while(!Q.empty()){
		int u=Q.top().second;
		if(d[u]<Q.top().first){
			Q.pop();
			continue;
		}
		Q.pop();

		for(node* p=h[u];p;p=p->next){
			int v=p->v;
			ll len=p->len;
			if(d[v]==-1||d[v]>d[u]+len){
				d[v]=d[u]+len;
				Q.push(make_pair(d[v],v));
			}
		}
	}
}

int p[MaxN];
//set<int> ps[MaxN];
//unordered_set<int> ps[MaxN];
vector<int> ps[MaxN];

ll ans[MaxQ];

int setfind(int x){
	if(p[x]<0)
		return x;
	else
		return p[x]=setfind(p[x]);
}

void setunion(int x,int y,ll anshint){
	x=setfind(x);
	y=setfind(y);
	if(x!=y){
		if(ps[y].size()>ps[x].size())
			swap(x,y);
		for(int yi:ps[y]){
			int oth;
			if(setfind(a[yi])==y)
				oth=b[yi];
			else
				oth=a[yi];
			if(setfind(oth)==x){
				ans[yi]=anshint;
			}else
				ps[x].push_back(yi);
		}
		ps[y].clear();
		ps[y].shrink_to_fit();
		p[x]+=p[y];
		p[y]=x;
	}
}

struct edge{
	int u,v;
	ll len;
};

edge e[MaxM];

//map<pair<int,int>,int> qid;

bool cmp(edge x,edge y){
	return x.len<y.len;
}


int main(int argc, char* argv[]) {

	read(n);read(m);read(k);read(q);
	for(int i=1;i<=m;i++){
		int u,v;
		ll l;
		read(u);read(v);read(l);
		addedge(u,v,l);
		e[i].u=u;
		e[i].v=v;
		e[i].len=l;
	}
	for(int i=1;i<=q;i++){
		read(a[i]);read(b[i]);
		//qid.insert(make_pair(make_pair(min(a,b),max(a,b)),i));
		ps[a[i]].push_back(i);
		ps[b[i]].push_back(i);
	}

	dijkstra();


	for(int i=1;i<=m;i++){
		e[i].len=e[i].len+d[e[i].u]+d[e[i].v];
		DEBUG("%d %d %d\n",e[i].u,e[i].v,e[i].len);
	}
	sort(e+1,e+m+1,cmp);

	memset(p,-1,sizeof(p));
	for(int i=1;i<=m;i++){
		setunion(e[i].u,e[i].v,e[i].len);
	}

	for(int i=1;i<=q;i++){
		printf("%I64d\n",ans[i]);
		//cout<<ans[i]<<endl;
	}


	return 0;
}


