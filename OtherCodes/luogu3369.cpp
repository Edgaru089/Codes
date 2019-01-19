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

typedef long long ll;

#define ROOT (overroot->lson)

class treap{
public:
	struct node{
		int val,cnt;
		int key;
		int size;
		node* son[2],*fa;
	};
	static node mem[4*MaxN],*memtop=mem;
#define ALLOCATE (++memtop)
#define lson son[0]
#define rson son[1]

	treap(){
		overroot=ALLOCATE;
		overroot->key=-1e8;
		overroot->val=1e8;
	}

	int tell(node* son){
		return son->fa->lson==son?0:1;
	}
	void connect(node* fa,node* son,int type){
		if(fa)
			fa->son[type]=son;
		if(son)
			son->fa=fa;
	}
	int ssize(node* p){
		return p?p->size:0;
	}
	int scnt(node* p){
		return p?p->cnt:0;
	}

	void update(node* p){
		p->size=ssize(p->lson)+p->cnt+ssize(p->rson);
	}

	void rotate(node* p){
		int t=tell(p);
		node* fa=p->fa,*b=get(p,1-t);
		connect(fa->fa,p,tell(fa));
		connect(p,fa,1-t);
		connect(fa,b,t);
		update(fa);
		update(p);
	}

	void insert(int val,node*& p=ROOT,node* fa=overroot){
		if(!p){
			p=ALLOCATE;
			p->fa=fa;
			p->val=val;
			p->cnt=1;
			p->key=rand();
			adjust(p);
		}else{
			p->ssize++;
			if(val<p->val)
				insert(val,p->lson,p);
			else if(val==p->val)
				p->cnt++;
			else /* val > p->va */
				insert(val,p->rson,p);
		}
	}

	

private:
	node* overroot;
}



int main(int argc, char* argv[]) {
	
	
	
	
	
	
	return 0;
}


