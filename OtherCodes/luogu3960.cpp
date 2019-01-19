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
	node* lson,*rson;
	node* fa;
}

bool notroot(node* p){
	return p->fa&&(p->fa->lson==p||p->fa->rson==p);
}

typedef unsigned char sontype;
const sontype lson=0,rson=1;
node*& get(node* fa,sontype type){
	return type==lson?fa->lson:fa->rson;
}
sontype tell(node* son){
	return son->fa&&son->fa->lson==son?lson:rson;
}
void connect(node* fa,node* son,sontype t){
	if(fa)
		get(fa,t)=son;
	if(son)
		son->fa=fa;
}

void rotate(node* p){
	int t=tell(p);
	node* fa=p->fa,*b=get(p,1^t);
	if(notroot(fa))
		connect(fa->fa,p,tell(fa));
	else
		p->fa=fa->fa;
	connect(p,fa,)
}


int main(int argc, char* argv[]) {
	
	
	
	
	
	
	return 0;
}


