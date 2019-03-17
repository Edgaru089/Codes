// hdu2966 / K-D Tree

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

typedef long long ll;
const int MaxN=1e5+10;
const int MaxK=5;

const int k=2;

int n;

struct pnt{
	ll d[MaxK];
};

struct pntcmp{
	pntcmp(int normal):normal(normal){}

	bool operator ()(const pnt& x,const pnt& y){
		return x.d[normal]<y.d[normal];
	}
	
	int normal;
};

pnt a[MaxN];
ll curans=0;

struct node{
	ll d[MaxK];
	int id;
	int curnorm;
	ll lx,ly;
	ll rx,ry;
	node* lson,*rson;
};

node* root;
node mem[MaxK*MaxN],*memtop=mem;
#define ALLOCATE (++memtop)

void build(node*& p,int larr,int rarr,ll lx,ll rx,ll ly,ll ry,int normal){
	if(lx>ly||rx>ry)
		return;

	p=ALLOCATE;
	p->lx=lx;
	p->ly=ly;
	p->rx=rx;
	p->ry=ry;
	p->curnorm=normal;

	int mx=(lx+ly)/2,my=(ly+ry)/2;
	if(normal==1){ // x axis
		int marr=(larr+rarr)/2,mx=(lx+rx)/2;
		nth_element(a+larr,a+marr,a+rarr,pntcmp(1));
		memcpy(p->d,a[marr].d,sizeof(p->d));
		p->id=marr;
		build(p->lson,larr,marr-1,lx,mx-1,ly,ry,(normal-1)%k+1);
		build(p->rson,marr+1,rarr,mx+1,rx,ly,ry,(normal-1)%k+1);
	}else{ // y axis
		int marr=(larr+rarr)/2,my=(ly+ry)/2;
		nth_element(a+larr,a+marr,a+rarr,pntcmp(1));
		memcpy(p->d,a[marr].d,sizeof(p->d));
		p->id=marr;
		build(p->lson,larr,marr-1,lx,rx,ly,my-1,(normal-1)%k+1);
		build(p->rson,marr+1,rarr,lx,rx,my+1,ry,(normal-1)%k+1);
	}
}



int main(int argc, char* argv[]) {

	int t;
	read(t);
	while(t--){
		read(n);
		for(int i=1;i<=n;i++){
			read(node[i].d[1],node[i].d[2]);
		}
	}








	return 0;
}


