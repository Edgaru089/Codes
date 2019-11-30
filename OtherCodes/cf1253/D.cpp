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

const int MaxN=200000+10,MaxM=200000+10;

int n,m;

vector<int> h[MaxN];
int bcnt,bid[MaxN];
pair<int,int> blr[MaxN];

void addedge(int u,int v){
	h[u].push_back(v);
	h[v].push_back(u);
}


void dfs(int u,int id){
	bid[u]=id;
	blr[id].first=min(blr[id].first,u);
	blr[id].second=max(blr[id].second,u);
	for(int v:h[u]){
		if(bid[v]==0)
			dfs(v,id);
	}
}



int main(int argc, char* argv[]) {

	read(n);read(m);
	for(int i=1;i<=m;i++){
		int u,v;
		read(u);read(v);
		addedge(u,v);
	}

	for(int i=1;i<=n;i++){
		if(bid[i]==0){
			bcnt++;
			blr[bcnt].first=n+1;
			dfs(i,bcnt);
			DEBUG("Block id=%d, startI=%d, (l=%d,r=%d)\n",bcnt,i,blr[bcnt].first,blr[bcnt].second);
		}
	}

	sort(blr+1,blr+bcnt+1);

	int ans=0;
	int i=1;
	while(i<=bcnt){
		int l=blr[i].first,r=blr[i].second;
		DEBUG("Starting- block i=%d(l=%d, r=%d)\n",i,l,r);
		i++;
		while(i<=bcnt&&blr[i].first<=r){
			DEBUG("   Merging- block i=%d(l=%d, r=%d)\n",i,blr[i].first,blr[i].second);
			r=max(r,blr[i].second);
			ans++;
			i++;
		}
	}

	printf("%d\n",ans);

	return 0;
}


