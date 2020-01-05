#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <string>
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

#define FOR(i, first, last)               for(int i = (first); i <= (last); ++i)
#define ROF(i, last, first)               for(int i = (last); i >= (first); --i)
#define FORSTEP(i, first, last, step)     for(int i = (first); i <= (last); i += (step))
#define ROFSTEP(i, last, first, stepabs)  for(int i = (last); i >= (first); i -= (stepabs))

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
const int MaxN=2e5+10,MaxM=5e5+10;

int t;
int n,m;
int a,b;

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

int acnt,bcnt;
int ap[MaxN],bp[MaxN];
ll apc[MaxN],bpc[MaxN];

void dfsa(int u,int id){
	if(u!=b){
		ap[u]=id;
		apc[id]++;
	}
	for(node* p=h[u];p;p=p->next){
		int v=p->v;
		if(v!=a&&ap[v]==0)
			dfsa(v,id);
	}
}

void dfsb(int u,int id){
	if(u!=a){
		bp[u]=id;
		bpc[id]++;
	}
	for(node* p=h[u];p;p=p->next){
		int v=p->v;
		if(v!=b&&bp[v]==0)
			dfsb(v,id);
	}
}





int main(int argc, char* argv[]) {

	read(t);
	while(t--){

		read(n);read(m);
		read(a);read(b);

		memset(h,0,sizeof(node*)*(n+6));
		memtop=mem;
		FOR(i,1,m){
			int u,v;
			read(u);read(v);
			addedge(u,v);
		}

		memset(ap,0,sizeof(int)*(n+6));
		memset(apc,0,sizeof(ll)*(n+6));
		acnt=0;
		for(node* p=h[a];p;p=p->next){
			int u=p->v;
			if(ap[u]==0)
				dfsa(u,++acnt);
		}

		memset(bp,0,sizeof(int)*(n+6));
		memset(bpc,0,sizeof(ll)*(n+6));
		bcnt=0;
		for(node* p=h[b];p;p=p->next){
			int u=p->v;
			if(bp[u]==0)
				dfsb(u,++bcnt);
		}

		PRINTARR("%d",ap,1,n);
		PRINTARR("%d",bp,1,n);
		PRINTARR("%lld",apc,1,acnt);
		PRINTARR("%lld",bpc,1,bcnt);

		long long ans=(long long)(n-2)*(n-3)/2;
		DEBUG("ans0=%lld\n",ans);
		FOR(i,1,acnt)
			ans-=apc[i]*(apc[i]-1)/2;
		FOR(i,1,bcnt)
			ans-=bpc[i]*(bpc[i]-1)/2;
		DEBUG("ans1=%lld\n",ans);

		map<pair<int,int>,int> mp;
		FOR(i,1,n)
			if(i!=a&&i!=b)
				mp[make_pair(ap[i],bp[i])]++;
		for(auto& i:mp)
			ans+=(ll)i.second*(i.second-1)/2;

		cout<<max(ans,0ll)<<endl;
	}

	return 0;
}


// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP

