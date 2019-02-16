#include <cstdlib>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <cstdio>
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

const int MaxN=2*1e5+10;

int n,m;

struct node{
	int val;
	int max;
	bool lazy;
	node* son[2];
	node* fa;
};

#define lson son[0]
#define rson son[1]

node* overroot=0;
#define ROOT overroot->lson>>>>>
node mem[MaxN],*memtop=mem;
#define ALLOCATE (++memtop)


void update(node* p){
	p->max=p->val;
	if(p->lson)
		p->max=max(p->max,p->lson->max);
	if(p->rson)
		p->max=max(p->max,p->rson->max);
}

int tell(node* p){
	return p->fa&&p->fa->lson==p?0:1;
}

void connect(node* fa,node* son,int where){
	if(fa)
		fa->son[where]=son;
	if(son)
		son->fa=fa;
}


void rotate(node* p){
	int t=tell(p);
	node* b=p->son[1-t],*fa=p->fa;
	if(fa->fa)
		connect(fa->fa,p,tell(fa));
	connect(p,fa,1-t);
	connect(fa,b,t);
	update(fa);
	update(p);
}

void pushdown(node* p){
	if(p->lazy){
		swap(p->lson,p->rson);
		if(p->lson)
			p->lson->lazy=!p->lson->lazy;
		if(p->rson)
			p->rson->lazy=!p->rson->lazy;
		p->lazy=false;
	}
}

void pushchain(node* p){
	while(p->fa!=overroot)
		pushchain(p->fa);
	pushdown(p);
}

void splay(node* p,node* target){
	pushchain(p);
	while(p->fa!=target){
		if(p->fa->fa!=target)
			if(tell(p)==tell(p->fa))
				rotate(p->fa);
			else
				rotate(p);
		rotate(p);
	}
}

node* seperate(node* x,node* y){
	splay(x,overroot);
	splay(y,x);
	return y->rson;
}

void flip(node* x,node* y){
	node* p=seperate(x,y);
	p->lazy=!p->lazy;
}


int main(int argc, char* argv[]) {
	
	
	
	
	
	
	return 0;
}



