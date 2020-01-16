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

// End of template:edgar:edgar-laptop(LAPTOP-EDGAR-15)

const int MaxN=2e5+10;

int n;

vector<int> h[MaxN];

void addedge(int u,int v){
	h[u].push_back(v);
	h[v].push_back(u);
}

int dep[MaxN],fa[MaxN];
int ssize[MaxN];
void dfs1(int u,int step,int from){
	ssize[u]=1;
	fa[u]=from;
	dep[u]=step;
	for(int v:h[u]){
		if(v!=from){
			dfs1(v,step+1,u);
			ssize[u]+=ssize[v];
		}
	}
}

int top[MaxN],tail[MaxN];
vector<int> chain[MaxN];
int hson[MaxN];
int dfn[MaxN],sstime;
void dfs2(int u,int t){
	int maxv,maxsize=0;
	dfn[u]=++sstime;
	top[u]=t;
	chain[t].push_back(u);
	for(int v:h[u]){
		if(v!=fa[u]){
			DEBUG("AHHHHH u=%d, v=%d\n",u,v);
			if(maxsize<ssize[v]){
				maxsize=ssize[v];
				maxv=v;
			}
		}
	}
	if(maxsize==0){ // leaf
		ASSERT(tail[t]==0);
		DEBUG("leaf %d\n",u);
		tail[t]=u;
	}else{
		hson[u]=maxv;
		dfs2(maxv,t);
		for(int v:h[u]){
			if(v!=fa[u]&&v!=maxv)
				dfs2(v,v);
		}
	}
}

int tdis;

int askdis(int u){
	int ans;
	printf("d %d\n",u);
	fflush(stdout);
	read(ans);
	if(ans==-1)
		exit(0);
	else if(ans==0){
		ASSERT(tdis==0 || dep[u]==tdis+1);
		printf("! %d\n",u);
		exit(0);
	}
	return ans;
}

int asknext(int u){
	int ans;
	printf("s %d\n",u);
	fflush(stdout);
	read(ans);
	if(ans==-1)
		exit(0);
	return ans;
}


void solve(int u,int lastdis){
	ASSERT(top[u]==u);

	DEBUG("solve(u=%d, lastdis=%d), chain:\n",u,lastdis);
	PRINT(chain[u]);

	int ndis=askdis(tail[u]);
	ASSERT(lastdis+ndis >= chain[u].size()-1);
	if(lastdis+ndis==chain[u].size()-1){
		// found
		DEBUG("FOUND\n");
		askdis(chain[u][lastdis]);
		abort(); // shouldn't reach here
	}else{ // lastdis+ndis > chain[u].size()-1
		int nextdis=(lastdis+ndis-chain[u].size()+1)/2-1;
		int off=lastdis-nextdis-1;
		DEBUG("not found, nextdis=%d, offid=%d\n",nextdis,off);
		solve(asknext(chain[u][off]),nextdis);
	}
}

int main(int argc, char* argv[]) {

	read(n);
	FOR(i,1,n-1){
		int u,v;
		read(u);
		read(v);
		addedge(u,v);
	}

	dfs1(1,1,0);
	PRINTARR("%d",dep,1,n);
	PRINTARR("%d",fa,1,n);
	PRINTARR("%d",ssize,1,n);

	dfs2(1,1);
	PRINTARR("%d",top,1,n);
	PRINTARR("%d",tail,1,n);

	tdis=askdis(1);

	solve(1,tdis);

	return 0;
}

// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP

