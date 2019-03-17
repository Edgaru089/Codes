#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
using namespace std;

#if (defined LOCAL) || (defined D)
#define DEBUG(...) printf(__VA_ARGS__)
#define PRINTARR(formatstr, arr, beginoff, size)				\
do{printf(#arr ":");											\
for (int __i = beginoff; __i <= beginoff + size - 1; __i++)		\
	printf("\t%d", __i);										\
printf("\n");													\
for (int __i = beginoff; __i <= beginoff + size - 1; __i++)		\
	printf("\t" formatstr, arr[__i]);							\
printf("\n"); }while(false)
#define PASS printf("Passing function \"%s\" on line %d\n", __func__, __LINE__)
#define ASSERT(expr) do{\
	if(!(expr)){\
		printf("Debug Assertation Failed on line %d, in function %s:\n  Expression: %s\n",__LINE__,__func__,#expr);\
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
inline void read(IntType& val) {
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

const int MaxN=100000+10;

int n,m;

struct node{
	int id,val;
	node* lson,*rson;
	node* fa;
	int dis;
};

node* nodes[MaxN];
node mem[MaxN],*memtop=mem;
#define ALLOCATE (++memtop)


node* findroot(node* p){
	/*
	node* p0=p;
	if(!p)
		return 0;
	while(p->fa)
		p=p->fa;
	return p0->fa=p;
	*/
	if(!p)
		return 0;
	if(p->fa)
		return p->fa=findroot(p->fa);
	else
		return p;
}

node* merge(node* x,node* y){
	DEBUG("mergeing nodes x=%d|%d, y=%d|%d\n",x?x->id:-1,x?x->val:-1,y?y->id:1,y?y->val:1);
	if(!x||!y||x==y)
		return x?x:y;

	// Place smaller node on x
	if(x->val>y->val||(x->val==y->val&&x->id>y->id))
		swap(x,y);

	x->rson=merge(x->rson,y);
	if(x->rson)
		x->rson->fa=x;

	// Maintain
	if(!x->rson||(x->lson&&x->lson->dis<x->rson->dis))
		swap(x->lson,x->rson);

	if(!x->rson)
		x->dis=0;
	else
		x->dis=x->rson->dis+1;

	return x;
}

int pop(node* p){
	p=findroot(p);
	int ans=p->val;
	if(p->lson)
		p->lson->fa=0;
	if(p->rson)
		p->rson->fa=0;
	p->fa=merge(p->lson,p->rson);
	nodes[p->id]=0;
	return ans;
}



int main(int argc, char* argv[]) {
	
	read(n);read(m);
	int a;
	for(int i=1;i<=n;i++){
		read(a);
		node* p=nodes[i]=ALLOCATE;
		p->val=a;
		p->id=i;
	}
	
	int x,y;
	for(int i=1;i<=m;i++){
		read(a);
		if(a==1){
			read(x);read(y);
			if(!nodes[x]||!nodes[y]||x==y)
				continue;
			merge(findroot(nodes[x]),findroot(nodes[y]));
		}else{
			read(x);
			if(!nodes[x])
				printf("-1\n");
			else
				printf("%d\n",pop(nodes[x]));
		}
		DEBUG("Action %d complete\n",i);
	}
	
	return 0;
}


