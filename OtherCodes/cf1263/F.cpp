#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
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

const int MaxN=1000+10,MaxM=2000+10;

int n;
int a,b;
int da[MaxM],db[MaxM];

struct node{
	int v;
	node* next;
};

node* ha[MaxM],*hb[MaxM];
node mem[2*2*MaxM],*memtop=mem;
#define ALLOCATE (++memtop)

int la[MaxM],ra[MaxM];
int sa[MaxM];
int lb[MaxM],rb[MaxM];
int sb[MaxM];

void addedgea(int u,int v){
	node* p=ALLOCATE;
	p->v=v;
	p->next=ha[u];
	ha[u]=p;
	p=ALLOCATE;
	p->v=u;
	p->next=ha[v];
	ha[v]=p;
}

void addedgeb(int u,int v){
	node* p=ALLOCATE;
	p->v=v;
	p->next=hb[u];
	hb[u]=p;
	p=ALLOCATE;
	p->v=u;
	p->next=hb[v];
	hb[v]=p;
}

void dfsa(int u,int from){
	sa[u]=1;
	if(da[u]!=0){
		la[u]=ra[u]=da[u];
		return;
	}
	la[u]=MaxN;
	for(node* p=ha[u];p;p=p->next){
		int v=p->v;
		if(v!=from){
			dfsa(v,u);
			sa[u]+=sa[v];
			la[u]=min(la[u],la[v]);
			ra[u]=max(ra[u],ra[v]);
		}
	}
}

void dfsb(int u,int from){
	sb[u]=1;
	if(db[u]!=0){
		lb[u]=rb[u]=db[u];
		return;
	}
	lb[u]=MaxN;
	for(node* p=hb[u];p;p=p->next){
		int v=p->v;
		if(v!=from){
			dfsb(v,u);
			sb[u]+=sb[v];
			lb[u]=min(lb[u],lb[v]);
			rb[u]=max(rb[u],rb[v]);
		}
	}
}

vector<int> lx[MaxN],wx[MaxN];
int dp[MaxN];

void addseg(int l,int r,int w){
	DEBUG("addseg([l,r]=[%d, %d], w=%d)\n",l,r,w);
	lx[r].push_back(l);
	wx[r].push_back(w);
}


int main(int argc, char* argv[]) {

	read(n);
	read(a);
	FOR(i,2,a){
		int x;
		read(x);
		addedgea(i,x);
	}
	FOR(i,1,n){
		int x;
		read(x);
		da[x]=i;
	}
	read(b);
	FOR(i,2,b){
		int x;
		read(x);
		addedgeb(i,x);
	}
	FOR(i,1,n){
		int x;
		read(x);
		db[x]=i;
	}

	dfsa(1,0);
	dfsb(1,0);

	PRINTARR("%d",sa,1,a);
	PRINTARR("%d",la,1,a);
	PRINTARR("%d",ra,1,a);

	FOR(i,1,a){
		if(i==1)
			addseg(la[i],ra[i],sa[i]-1);
		else
			addseg(la[i],ra[i],sa[i]);
	}
	PRINTARR("%d",sb,1,b);
	PRINTARR("%d",lb,1,b);
	PRINTARR("%d",rb,1,b);
	FOR(i,1,b){
		if(i==1)
			addseg(lb[i],rb[i],sb[i]-1);
		else
			addseg(lb[i],rb[i],sb[i]);
	}

	FOR(i,1,n)
		FOR(j,0,lx[i].size()-1)
			dp[i]=max(dp[i],dp[lx[i][j]-1]+wx[i][j]);

	printf("%d\n",dp[n]);


	return 0;
}


// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP

