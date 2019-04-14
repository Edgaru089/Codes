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

const int MaxN=100000+10,Charset=30;

struct node{
	node* pre;
	node* ch[Charset];
	int step;
};

node* root;
node* last;
node mem[2*MaxN],*memtop=mem;
#define ALLOCATE (++memtop)

void insert(int c){
	node* u=ALLOCATE;
	u->step=last->step+1;
	node* p=last->prev;
	while(p&&!p->ch[c])
		p=p->prev;
	if(!p){
		u->prev=root;
	}else{
		node* q=p->ch[c];
		if(q->step==p->step+1)
			u->prev=q;
		else{
			node* v=ALLOCATE;
			memcpy(v->ch,q->ch,sizeof(v->ch));
			v->prev=q->prev;
			u->prev=q->prev=v;
			for(;p&&p->ch[c]==q;p=p->prev)
				p->ch[c]=q;
		}
	}
}




int main(int argc, char* argv[]) {

	root=ALLOCATE;
	last=root;







	return 0;
}


