#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>

#ifdef D
#include <custom/Debug.hpp>
#endif

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
#define PRINT(...) dbg(__VA_ARGS__)
#define PRINTVAL(...) dbgv(__VA_ARGS__)
#define PRINTSEQ(...) dbgr(__VA_ARGS__)
#define PRINTSEQVAL(...) dbgm(__VA_ARGS__)
#define PRINTCOMPACT(...) dbgs(__VA_ARGS__)
#else
#define DEBUG(...)
#define PRINTARR(a, b, c, d)
#define PRINTARR2D(a, b, c, d, e, f)
#define PASS
#define ASSERT(expr)
#define PRINT(...)
#define PRINTVAL(...)
#define PRINTSEQ(...)
#define PRINTSEQVAL(...)
#define PRINTCOMPACT(...)
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
#if __cplusplus >= 201103
template<typename IntType,typename... Args>
void read(IntType& val, Args&... args){
	read(val); read(args...);
}
#endif

// End of template:edgar:edgar-laptop(LAPTOP-EDGAR-15)

const int MaxN=250000+10;

int n;
int m;

vector<int> h[MaxN];

void addedge(int u,int v){
	h[u].push_back(v);
	h[v].push_back(u);
}

int fa[MaxN],ssize[MaxN],dep[MaxN];
int hson[MaxN];
void dfs1(int u,int from,int step){
	fa[u]=from;
	dep[u]=step;
	ssize[u]=1;
	int mi=0,mv=0;

	for(int v:h[u]){
		if(v!=from){
			dfs1(v,u,step+1);
			ssize[u]+=ssize[v];
			if(ssize[v]>mv){
				mv=ssize[v];
				mi=v;
			}
		}
	}

	hson[u]=mi;
}

int top[MaxN];
int sstime,dfn[MaxN];
void dfs2(int u,int t){
	top[u]=t;
	dfn[u]=++sstime;
	if(hson[u])
		dfs2(hson[u],t);

	for(int v:h[u])
		if(v!=fa[u]&&v!=hson[u]){
			dfs2(v,v);
		}
}


struct node{
	int left,right;
	node* lson,*rson;
	int sum;
};

node* root;
node mem[2*MaxN],*memtop=mem;
#define ALLOCATE (++memtop)

void build(int left=1,int right=n,node*& p=root){
	p=ALLOCATE;
	p->left=left;
	p->right=right;
	if(left==right)
		p->sum=1;
	else{
		int mid=(left+right)/2;
		build(left,mid,p->lson);
		build(mid+1,right,p->rson);
		p->sum=p->lson->sum+p->rson->sum;
	}
}

void change(int pos,int val,node* p=root){
	if(p->left==pos&&p->right==pos){
		p->sum=val;
		return;
	}
	if(p->lson->right>=pos)
		change(pos,val,p->lson);
	else
		change(pos,val,p->rson);
	p->sum=p->lson->sum+p->rson->sum;
}

int query(int left,int right,node* p=root){
	if(p->left==left&&p->right==right)
		return p->sum;
	if(p->lson->right>=right)
		return query(left,right,p->lson);
	else if(p->rson->left<=left)
		return query(left,right,p->rson);
	else
		return (query(left,p->lson->right,p->lson)+
				query(p->rson->left,right,p->rson));
}


int opquery(int x){
	int ans=0;

	while(x!=0){
		ans+=query(dfn[top[x]],dfn[x]);
		x=fa[top[x]];
	}

	return ans;
}



int main(int argc, char* argv[]) {

	read(n);
	FOR(i,1,n-1){
		int u,v;
		//read(u,v);
		read(u);
		read(v);
		addedge(u,v);
	}

	dfs1(1,0,1);
	dfs2(1,1);

	build();
	change(dfn[1],0);

	read(m);
	string op;
	FOR(i,1,n+m-1){
		int x;
		read(op,x);
		if(op=="W")
			printf("%d\n",opquery(x));
		else if(op=="A"){
			int y;
			read(y);
			if(dfn[x]>dfn[y])
				swap(x,y);
			change(dfn[y],0);
		}
	}






	return 0;
}

// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP

