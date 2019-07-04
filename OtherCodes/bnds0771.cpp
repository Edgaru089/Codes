#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
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
		fprintf(stderr,"Debug Assertation Failed on line %d, in function %s:\n  Expression: %s\n",__LINE__,__func__,#expr);\
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

const int MaxN=500000+10;
const int MaxM=200000+10;

int n,m;

int d[MaxN];

struct st{
	int sum,lmax,rmax,max;
};

struct node{
	int left,right;
	node* lson,*rson;
	st s;
};

node* root;
node mem[2*MaxN],*memtop=mem;
#define ALLOCATE (++memtop)


st merge(st l,st r){
	st a;
	a.sum=l.sum+r.sum;
	a.lmax=max(l.lmax,l.sum+r.lmax);
	a.rmax=max(r.rmax,r.sum+l.rmax);
	a.max=max(max(l.max,r.max),l.rmax+r.lmax);
	return a;
}

void build(int left=1,int right=n,node*& p=root){
	p=ALLOCATE;
	p->left=left;
	p->right=right;
	if(left==right){
		p->s.sum=p->s.lmax=p->s.rmax=p->s.max=d[left];
	}else{
		int mid=(left+right)/2;
		build(left,mid,p->lson);
		build(mid+1,right,p->rson);
		p->s=merge(p->lson->s,p->rson->s);
	}
}


st query(int left,int right,node* p=root){
	if(p->left==left&&p->right==right)
		return p->s;
	if(p->lson->right>=right)
		return query(left,right,p->lson);
	else if(p->rson->left<=left)
		return query(left,right,p->rson);
	else{
		st l=query(left,p->lson->right,p->lson);
		st r=query(p->rson->left,right,p->rson);
		return merge(l,r);
	}
}

void change(int pos,int val,node* p=root){
	if(p->left==p->right&&p->left==pos){
		p->s.sum=p->s.lmax=p->s.rmax=p->s.max=val;
		return;
	}
	if(p->lson->right>=pos)
		change(pos,val,p->lson);
	else
		change(pos,val,p->rson);
	p->s=merge(p->lson->s,p->rson->s);
}




int main(int argc, char* argv[]) {

	read(n);read(m);
	for(int i=1;i<=n;i++){
		read(d[i]);
	}

	build();

	for(int i=1;i<=m;i++){
		int k;
		read(k);
		if(k==1){
			int a,b;
			read(a);read(b);
			if(a>b)
				swap(a,b);
			printf("%d\n",query(a,b).max);
		}else if(k==2){
			int p,s;
			read(p);read(s);
			change(p,s);
		}
	}






	return 0;
}


