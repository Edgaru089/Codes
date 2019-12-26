#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <string>
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

#define FOR(i, first, last)               for(int i = first; i <= last; ++i)
#define ROF(i, last, first)               for(int i = last; i >= first; --i)
#define FORSTEP(i, first, last, step)     for(int i = first; i <= last; i += step)
#define ROFSTEP(i, last, first, stepabs)  for(int i = last; i >= first; i -= step)
#define FORP(p, h_first)                  for(node* p = h_first; p; p = p->next)

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
template<>
void read<string>(string& str){
	str.clear();
	int c;
	while(iscntrl(c=getchar())||c==' '||c=='\t');
	do{
		str.push_back(c);
	}while(!(iscntrl(c=getchar())||c==' '||c=='\t'));
}

typedef long long ll;
const int infinity=1e8;
const int MaxN=5000+10,MaxK=15+2;

int k;
int n[MaxK];
vector<int> a[MaxK];

struct node{
	int v,flow;
	node* next,*rev;
};

node* h[MaxN];
node mem[MaxN*MaxK+2*MaxK+10],*memtop=mem;
#define ALLOCATE (++memtop)

void addedge(int u,int v,int flow){
	node* p=ALLOCATE;
	p->v=v;
	p->next=h[u];
	p->flow=flow;
	h[u]=p;
	node* r=ALLOCATE;
	r->v=u;
	r->next=h[v];
	h[v]=r;
	p->rev=r;
	r->rev=p;
}

int s,t;
int dis[MaxN];
queue<int> Q;

bool bfs(){
	memset(dis,0,sizeof(dis));
	dis[s]=1;
	Q.push(s);
	while(!Q.empty()){
		int u=Q.front();
		Q.pop();
		FORP(p,h[u]){
			int v=p->v;
			if(p->flow!=0&&dis[v]==0){
				dis[v]=dis[u]+1;
				Q.push(v);
			}
		}
	}
	return dis[t]!=0;
}

node* cur[MaxN];

int dfs(int u,int limit){
	int ans=0,l;
	for(node*& p=h[u];p;p=p->next){
		if(dis[p->v]==dis[u]+1&&(l=dfs(p->v,min(limit,p->flow)))){
			limit-=l;
			p->flow-=l;
			p->rev->flow+=l;
			ans+=l;
		}
		if(!limit)
			break;
	}
	return ans;
}

int dinic(){
	int ans=0;
	while(bfs()){
		memcpy(cur,h,sizeof(node)*(n+2));
		ans+=dfs(s,infinity);
	}
	return ans;
}

map<int,int> m;
ll sum;

int main(int argc, char* argv[]) {

	read(k);
	FOR(i,1,k)
		read(n[i]);
	FOR(i,1,k){
		a[i].resize(n[i]);
		FOR(j,0,n[i]-1){
			read(a[i][j]);
			m.insert(make_pair(a[i][j],(int)(m.size()+1)));
			sum+=a[i][j];
		}
	}

	if(sum%k!=0){
		printf("-1\n");
	}else{
		sum/=k;
		FOR(i,1,k)
			FOR(j,0,n[i]-1){
				if()
			}



	}

	return 0;
}


// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP,FORP

