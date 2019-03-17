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

typedef long long ll;
const int MaxN=100000+10;

namespace heap{
	struct node{
		int id;
		ll val;
		node* lson,*rson;
		node* fa;
		int dis;
	};

	node* nodes[MaxN];
	node mem[2*MaxN],*memtop=mem;
#define ALLOCATE (++heap::memtop)

	node* findroot(node* p){
		/*
		if(!p)
			return 0;
		while(p->fa)
			p=p->fa;
		return p;
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

		// Place larger node on x
		if(x->val<y->val)
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

	ll top(node* p){
		p=findroot(p);
		return p->val;
	}

	node* pop(node* p){
		p=findroot(p);
		ll ans=p->val;
		if(p->lson)
			p->lson->fa=0;
		if(p->rson)
			p->rson->fa=0;
		p->fa=merge(p->lson,p->rson);
		nodes[p->id]=0;

		return p;
	}
}

int n,m;
int a[MaxN];



int main(int argc, char* argv[]) {

	while(cin>>n){
		for(int i=1;i<=n;i++)
			read(a[i]);
		memset(heap::mem,0,sizeof(heap::mem));
		heap::memtop=heap::mem;
		for(int i=1;i<=n;i++){
			heap::nodes[i]=ALLOCATE;
			heap::nodes[i]->val=a[i];
		}
		read(m);
		for(int i=1;i<=m;i++){
			int x,y;
			read(x);read(y);
			if(heap::findroot(heap::nodes[x])==heap::findroot(heap::nodes[y])){
				printf("-1\n");
				continue;
			}
			heap::node* px=heap::pop(heap::nodes[x]);
			heap::node* pn=ALLOCATE;
			pn->val=px->val/2;
			pn->id=px->id;
			heap::merge(heap::nodes[pn->id]=pn,heap::findroot(heap::nodes[x]));
			px=heap::pop(heap::nodes[y]);

			pn=ALLOCATE;
			pn->val=px->val/2;
			pn->id=px->id;
			heap::merge(heap::nodes[pn->id]=pn,heap::findroot(heap::nodes[x]));
			heap::merge(heap::findroot(heap::nodes[x]),heap::findroot(heap::nodes[y]));
			printf("%lld\n",heap::findroot(heap::nodes[x])->val);
		}
	}

	return 0;
}


