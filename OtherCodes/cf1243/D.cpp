#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <map>
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

const int MaxN=1e5+10,MaxM=1e5+10;

struct node{
	int v;
	node* next;
};

node* h[MaxN];
node mem[2*MaxM],*memtop=mem;
#define ALLOCATE (++memtop)

int n,m;

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

int p[MaxN];
map<int,int> roots;

int setfind(int x){
	if(p[x]<0)
		return x;
	else
		return p[x]=setfind(p[x]);
}

void setunion(int x,int y){
	x=setfind(x);
	y=setfind(y);
	if(x!=y){
		p[x]+=p[y];
		p[y]=x;
		roots.erase(roots.find(y));
	}
}




int main(int argc, char* argv[]) {

	read(n);read(m);

	int a,b;
	for(int i=1;i<=m;i++){
		read(a);read(b);
		addedge(a,b);
	}

	memset(p,-1,sizeof(p));
	for(int i=1;i<=n;i++)
		roots.insert(make_pair(i,0));

		vector<int> ops;
	for(int i=2;i<=n;i++){
		DEBUG("i=%d\n",i);
		for(auto& j:roots)
			if(j.first<i)
				j.second=0;
			else
				break;
		int u=i;
		for(node* p=h[i];p;p=p->next){
			int v=p->v;
			if(v<u){
				DEBUG("    Adding edge (%d -- %d)\n",v,u);
				roots[setfind(v)]++;
			}
		}
#ifdef D
		DEBUG("BEGIN DUMP\n");
		PRINTARR("%d",p,1,n);
		for(auto& j:roots){
			fprintf(stderr,"%d %d\n",j.first,j.second);
		}
		DEBUG("END DUMP\n");
#endif
		ops.clear();
		for(auto& j:roots){
			if(j.first<i){
				DEBUG(" Checking: first=%d, second=%d\n",j.first,j.second);
				if(j.second<-p[j.first]){
					ops.push_back(j.first);
					DEBUG("  Merge: %d\n",j);
				}
			}else
				break;
		}
		for(int j:ops){
			setunion(j,i);
		}
	}

	printf("%d\n",(int)roots.size()-1);


	return 0;
}


