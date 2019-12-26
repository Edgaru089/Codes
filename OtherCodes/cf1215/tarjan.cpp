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

#define FOR(i, first, last)               for(int i = (first); i <= (last); ++i)
#define ROF(i, last, first)               for(int i = (last); i >= (first); --i)
#define FORSTEP(i, first, last, step)     for(int i = (first); i <= (last); i += (step))
#define ROFSTEP(i, last, first, stepabs)  for(int i = (last); i >= (first); i -= (step))

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

const int MaxN=1e4+10,MaxM=1e5+10;

int n,m;
int a[MaxN];

vector<int> h[MaxN],hx[MaxN];

void addedge(int u,int v){
	h[u].push_back(v);
}

int belong[MaxN],bcnt;
vector<int> bs[MaxN];
int dfn[MaxN],low[MaxN],sstime;
stack<int> s;

void dfs(int u){
	dfn[u]=low[u]=++sstime;
	s.push(u);
	for(node* p=h[u];p;p=p->next){
		int v=p->v;
		if(!dfn[v]){
			dfs(v);
			low[u]=min(low[u],low[v]);
		}else if(!belong[v])
			low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u]){
		bcnt++;
		belong[u]=bcnt;
		bs[bcnt].push_back(u);
		while(s.top()!=u){
			int x=s.top();
			s.pop();
			belong[x]=bcnt;
			bs[bcnt].push_back(x);
		}
		s.pop();
	}
}

int d[MaxN];





int main(int argc, char* argv[]) {

	read(n);read(m);
	FOR(i,1,n)
		read(a[i]);
	FOR(i,1,m){
		int x,y;
		read(x);read(y);
		addedge(x,y);
	}

	FOR(i,1,n)
		if(!belong[i])
			dfs(i);

	FOR(i,1,n)
		d[belong[i]]+=a[i];




	return 0;
}


// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP

