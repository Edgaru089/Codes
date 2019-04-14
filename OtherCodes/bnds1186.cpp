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
const int MaxN=50000+10;

int n,m;

struct node{
	int left,right;
	node* lson,*rson;
	ll val,sum;
};

node* root[MaxN];
node mem[18*MaxN],*memtop=mem;
#define ALLOCATE (++memtop)

void build(int l=1,int r=n,node*& p=root[0]){
	p=ALLOCATE;
	p->left=l;
	p->right=r;
	if(l!=r){
		int mid=(l+r)/2;
		build(l,mid,p->lson);
		build(mid+1,r,p->rson);
	}
}

void addval(int pos,int val,node* prev,node*& np){
	np=ALLOCATE;
	memcpy(np,prev,sizeof(node));
	if(np->left==np->right&&np->left==pos){
		np->val+=val;
		np->sum=np->val*np->val;
		return;
	}
	if(prev->lson->right>=pos)
		addval(pos,val,prev->lson,np->lson);
	else
		addval(pos,val,prev->rson,np->rson);
	np->sum=np->lson->sum+np->rson->sum;
}



int main(int argc, char* argv[]) {

	read(n);read(m);
	build();
	for(int i=1;i<=n;i++){
		int a;
		read(a);
		addval(a,1,root[i-1],root[i]);
	}

	for(int i=1;i<=m;i++){
		int l,r;
		read(l);read(r);
		ll t=-(r-l+1),b=(r-l+1)*(r-l);
		t+=root[r]
	}






	return 0;
}


