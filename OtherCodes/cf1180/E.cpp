#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <string>
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

const int MaxN=3e5+10;
const int MaxA=1e6+10;

int n,m,q;
int a[MaxN],b[MaxN];

struct node{
	int left,right;
	node* lson,*rson;
	int max,lazy;
};

node* root;
node mem[2*MaxA],*memtop=mem;
#define ALLOCATE (++memtop)

void build(int left=1,int right=MaxA-7,node*& p=root){
	//DEBUG("build(left=%d, right=%d)\n",left,right);
	p=ALLOCATE;
	p->left=left;
	p->right=right;
	if(left<right){
		int mid=(left+right)/2;
		build(left,mid,p->lson);
		build(mid+1,right,p->rson);
	}
}

void pushdown(node* p){
	if(p&&p->lazy!=0){
		p->max+=p->lazy;
		if(p->lson)
			p->lson->lazy+=p->lazy;
		if(p->rson)
			p->rson->lazy+=p->lazy;
		p->lazy=0;
	}
}

void add(int left,int right,int val,node* p=root){
	if(p->left==left&&p->right==right){
		p->lazy+=val;
		return;
	}
	pushdown(p);
	pushdown(p->lson);
	pushdown(p->rson);
	if(p->lson->right>=right)
		add(left,right,val,p->lson);
	else if(p->rson->left<=left)
		add(left,right,val,p->rson);
	else{
		add(left,p->lson->right,val,p->lson);
		add(p->rson->left,right,val,p->rson);
	}
	pushdown(p->lson);
	pushdown(p->rson);
	p->max=max(p->lson->max,p->rson->max);
}

int querypos(node* p=root){
	pushdown(p);
	pushdown(p->lson);
	pushdown(p->rson);
	if(p->left==p->right)
		if(p->max>0)
			return p->left;
		else
			return -1;
	if(p->rson->max>0)
		return querypos(p->rson);
	else
		return querypos(p->lson);
}




int main(int argc, char* argv[]) {

	read(n);read(m);
	build();
	FOR(i,1,n){
		read(a[i]);
		add(1,a[i],1);
	}
	FOR(i,1,m){
		read(b[i]);
		add(1,b[i],-1);
	}

	read(q);
	FOR(i,1,q){
		int op,id,x;
		read(op);
		read(id);
		read(x);
		DEBUG("op=%d, id=%d, x=%d\n",op,id,x);
		if(op==1){
			add(1,a[id],-1);
			a[id]=x;
			add(1,a[id],1);
		}else if(op==2){
			add(1,b[id],1);
			b[id]=x;
			add(1,b[id],-1);
		}
		printf("%d\n",querypos());
	}






	return 0;
}


// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP

