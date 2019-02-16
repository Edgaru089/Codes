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


const int MaxN=100000+10;

struct node{
	int val,id;
	int dis;
	node* lson,*rson;
	node* fa;
};

node mem[MaxN],*memtop=mem;
#define ALLOCATE ++memtop;
node* nodes[MaxN];


int disof(node* p){
	return p?p->dis:0;
}

void update(node* p){
	p->dis=disof(p->rson)+1;
}

node* merge(node* x,node* y){
	PASS;
	DEBUG("merging nodes ( [x:%d=%d] [y:%d=%d] )\n",x?x->id:-1,x?x->val:-1,y?y->id:-1,y?y->val:-1);
	if(!x||!y)
		return x?x:y;
	if(x->val>y->val||(x->val==y->val&&x->id>y->id))
		swap(x,y);
	x->rson=merge(x->rson,y);
	x->rson->fa=x;
	update(x);
	if(disof(x->lson)<disof(x->rson)){
		swap(x->lson,x->rson);
		update(x);
	}
	return x;
}

node* top(node* x){
	if(x->fa)
		return top(x->fa);
	else
		return x;
}

void pop(node* p){
	if(!p)
		return;
	if(p->fa)
		pop(p->fa);
	else{
		if(p->lson)
			p->lson->fa=0;
		if(p->rson)
			p->rson->fa=0;
		merge(p->lson,p->rson);
		p->lson=p->rson=0;
		update(p);
		
		// Delete the node
		nodes[p->id]=0;
	}
}

int n,m;
int k,x,y;


int main(int argc, char* argv[]) {

	read(n);read(m);
	for(int i=1;i<=n;i++){
		nodes[i]=ALLOCATE;
		read(nodes[i]->val);
		nodes[i]->id=i;
	}

	for(int i=1;i<=m;i++){
		read(k);
		switch(k){
			case 1:
				read(x);read(y);
				if(top(nodes[x])==top(nodes[y])||!nodes[x]||!nodes[y])
					break;
				merge(nodes[x],nodes[y]);
				break;
			case 2:{
				read(x);
				if(nodes[x]){
					node* p=top(nodes[x]);
					printf("%d\n",p->val);
					pop(p);
				}else
					printf("-1\n");
				break;
			}
		}
	}

	return 0;
}


