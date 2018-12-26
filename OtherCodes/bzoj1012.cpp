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

char getnextchar(){
	int c;
	while(iscntrl(c=getchar())||c==' '||c=='\t');
	return c;
}

typedef long long ll;
const int MaxN=200000+10;

int m;
ll p;

struct node{
	int left,right;
	ll max;
	node* lson,*rson;
};

node* root;
node mem[2*MaxN],*memtop=mem;
#define ALLOCATE (++memtop)

void build(int left=1,int right=m,node*& p=root){
	p=ALLOCATE;
	p->left=left;
	p->right=right;
	if(left==right){
		//p->max=0;
	}else{
		int mid=(left+right)/2;
		build(left,mid,p->lson);
		build(mid+1,right,p->rson);
		//p->max=max(p->lson->max,p->rson->max);
	}
}

void setpnt(int pos,int val,node* p=root){
	if(p->left==p->right){
		ASSERT(p->left==pos);
		p->max=val;
		return;
	}
	if(p->lson->right>=pos)
		setpnt(pos,val,p->lson);
	else
		setpnt(pos,val,p->rson);
	p->max=max(p->lson->max,p->rson->max);
}

int querymax(int left,int right,node* p=root){
	if(p->left==left&&p->right==right)
		return p->max;
	if(p->lson->right>=right)
		return querymax(left,right,p->lson);
	else if(p->rson->left<=left)
		return querymax(left,right,p->rson);
	else
		return max(querymax(left,p->lson->right,p->lson),
				   querymax(p->rson->left,right,p->rson));
}


int main(int argc, char* argv[]) {
	
	read(m);read(p);
	build();

	int len=0,t=0;
	for(int i=1;i<=m;i++){
		int c,x;
		c=getnextchar();
		read(x);
		if(c=='A')
			setpnt(++len,(x+t)%p);
		else if(c=='Q')
			printf("%d\n",t=querymax(len-x+1,len));
	}
	
	return 0;
}


