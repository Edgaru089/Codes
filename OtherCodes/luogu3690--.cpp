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

const int MaxN=3e5+10;

int n,m;

struct node{
	int val,sum;
	bool lazy;
	node* son[2],*fa;
};

node* nodes[MaxN];
node mem[MaxN],*memtop=mem;
#define ALLOCATE (++memtop)
#define lson son[0]
#define rson son[1]

int tell(node* p){
	return p->fa&&p->fa->lson==p?0:1;
}

void connect(node* father,node* son,int type){
	if(father)
		father->son[type]=son;
	if(son)
		son->fa=father;
}

bool notroot(node* p){
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
	node* fa=p->fa,*b=p->son[1-t];
	if(notroot(fa))
		connect(p,fa->fa,tell(fa));
	else
		p->fa=fa->fa;
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
	if(notroot(p))
		pushchain(p->fa);
	pushdown(p);
}

void splay(node* p){
	pushchain(p);
	while(notroot(p)){
		if(notroot(p->fa))
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

void makeroot(node* p){
	access(p);
	splay(p);
	p->lazy=!p->lazy;
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

node* split(node* x,node* y){
	makeroot(x);
	access(y);
	splay(y);
	return y;
}

void changeval(node* p,int val){
	access(p);
	splay(p);
	p->val=val;
	update(p);
}


int main(int argc, char* argv[]) {
	
	read(n);read(m);
	for(int i=1;i<=n;i++){
		nodes[i]=ALLOCATE;
		read(nodes[i]->val);
		update(nodes[i]);
	}
	
	int k,x,y;
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


