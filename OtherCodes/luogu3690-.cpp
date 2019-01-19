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

const int MaxN=3e5+10,MaxM=3e5+10;

int n,m;

struct node{
	int val,sum;
	node* lson,*rson;
	node* fa;
	bool lazy;
};

node* nodes[MaxN];
node mem[MaxN],*memtop=mem;
#define ALLOCATE (++memtop)

const int lson=0,rson=1;
int tell(node* son){
	return son->fa&&son->fa->lson==son?lson:rson;
}
node*& get(node* fa,int type){
	return type==lson?fa->lson:fa->rson;
}
void connect(node* son,node* fa,int type){
	if(fa)
		get(fa,type)=son;
	if(son)
		son->fa=fa;
}

bool nroot(node* p){
	return p->fa&&(p->fa->lson==p||p->fa->rson==p);
}

void update(node* p){
	p->sum=p->val;
	if(p->lson)
		p->sum^=p->lson->sum;
	if(p->rson)
		p->sum^=p->rson->sum;
}

void rotate(node* p){
	int t=tell(p);
	node* fa=p->fa,*b=get(p,1-t);
	if(nroot(fa))
		connect(p,fa->fa,tell(fa));
	else
		p->fa=fa->fa;
	connect(fa,p,1-t);
	connect(b,fa,t);
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
	if(nroot(p))
		pushchain(p->fa);
	pushdown(p);
}

void splay(node* p){
	pushchain(p);
	while(nroot(p)){
		if(nroot(p->fa))
			if(tell(p)==tell(p->fa))
				rotate(p->fa);
			else
				rotate(p);
		rotate(p);
	}
}

void access(node* p){
	node* prev=0;
	while(p){
		splay(p);
		p->rson=prev;
		update(p);
		prev=p;
		p=p->fa;
	}
}

node* findroot(node* p){
	access(p);
	splay(p);
	pushdown(p);
	while(p->lson){
		p=p->lson;
		pushdown(p);
	}
	return p;
}

void makeroot(node* p){
	access(p);
	splay(p);
	p->lazy=!p->lazy;
}

void link(node* x,node* y){
	makeroot(x);
	if(findroot(y)!=x)
		x->fa=y;
}

void cut(node* x,node* y){
	makeroot(x);
	if(findroot(y)!=x||y->lson!=x||x->rson)
		return;
	y->lson=x->fa=0;
	update(y);
}

void changeval(node* p,int x){
	access(p);
	splay(p);
	p->val=x;
	update(p);
}

node* split(node* x,node* y){
	makeroot(x);
	access(y);
	splay(y);
	return y;
}




int main(int argc, char* argv[]) {
	
	read(n);
	read(m);
	
	for(int i=1;i<=n;i++){
		nodes[i]=ALLOCATE;
		read(nodes[i]->val);
		update(nodes[i]);
	}

	int k;
	int x,y;
	for(int i=1;i<=m;i++){
		read(k);read(x);read(y);
		switch(k){
			case 0:
				printf("%d\n",split(nodes[x],nodes[y])->sum);
				break;
			case 1:
				link(nodes[x],nodes[y]);
				break;
			case 2:
				cut(nodes[x],nodes[y]);
				break;
			case 3:
				changeval(nodes[x],y);
				break;
		}
	}
	
	
	return 0;
}


