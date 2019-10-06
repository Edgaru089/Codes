#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
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

template<>
void read<string>(string& str){
	str.clear();
	int c;
	while(iscntrl(c=getchar())||c==' '||c=='\t');
	do{
		str.push_back(c);
	}while(!(iscntrl(c=getchar())||c==' '||c=='\t'));
}

typedef long double ld;

const int MaxN=100000+10;
const int MaxM=2*MaxN;

int n,m;

struct st{
	st(){}
	st(int v,int len):v(v),len(len){}
	int v,len;
};

vector<st> h[MaxN];

void addedge(int u,int v,int len){
	h[u].push_back(st(v,len));
}


ld ans=0;
void dfs(int u,int len,ld f){
	if(u==n){
		ans+=len*f;
		return;
	}
	for(int i=0;i<h[u].size();i++){
		int v=h[u][i].v,l=h[u][i].len;
		dfs(v,len+l,f/h[u].size());
	}
}




int main(int argc, char* argv[]) {

	read(n);read(m);
	for(int i=1;i<=m;i++){
		int u,v,l;
		read(u);read(v);read(l);
		addedge(u,v,l);
	}

	dfs(1,0,1);


	printf("%.2Lf\n",ans);



	return 0;
}


