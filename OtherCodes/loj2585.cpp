#include <cstdlib>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <map>
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

const int infinity=1e6;
const int MaxN=3e5+10,MaxQ=3e5+10;

int n,k,q;
int x[MaxN],t[MaxN],a[MaxN],b[MaxN];
int l[MaxQ],y[MaxQ];

struct query{
	int time,pos;
};

struct node{
	int left,right;
	int min;
	multiset<int> vals;
	node* lson,*rson;
	node* next;
};

node* root[MaxN];
node mem[2*MaxN],*memtop=mem;
#define ALLOCATE (++memtop)

void build(int left,int right,node*& p){
	p=ALLOCATE;
	p->left=left;
	p->right=right;
	if(left!=right){
		int mid=(left+right)/2;
		build(left,mid,p->lson);
		build(mid+1,right,p->rson);
	}else{
		p->min=infinity;
	}
}


void addval(int pos,int val,node* p){
	if(p->left==p->right&&p->left==pos){
		p->vals.insert(val);
		p->min=*(p->first());
		return;
	}
	if(p->lson->right>=pos)
		addval(pos,val,p->lson);
	else
		addval(pos,val,p->rson);
	p->min=min(p->lson->min,p->rson->min);
}

void eraseval(int pos,int val,node* p){
	if(p->left==p->right){
		auto i=p->vals.find(val);
		if(i!=p->end())
			p->erase(i);
		if(!p->vals.empty())
			p->min=*(p->first());
		else
			p->min=infinity;
		return;
	}
	if(p->lson->right>=pos)
		eraseval(pos,val,p->lson);
	else
		eraseval(pos,val,p->rson);
	p->min=min(p->lson->min,p->rson->min);
}

struct nop{
	bool add; // true->add, false->remove
	int pos,time;
	int type;
};

struct qop{
	int pos,time;
};

nop ns[2*MaxN];
qop qs[2*MaxN];
int nscnt;
multiset<int> colorpos[MaxN];

int poscnt,posq[2*MaxN];
unordered_map<int,int> posdisq;

bool ncmp(nop x,nop y){
	return x.time<y.time;
}

bool qcmp(qop x,qop y){
	return x.time<y.time;
}


/* The Algorithm */

int hascnt=0;

void addshop(int pos,int type){
	if(colorpos[type].empty())
		hascnt++;
	colorpos[type].insert(pos);
}

void removeshop(int pos,int type){
}

int query(int pos){
}




int main(int argc, char* argv[]) {

	read(n);read(k);read(q);
	for(int i=1;i<=n;i++){
		read(x[i]);read(t[i]);read(a[i]);read(b[i]);
		ns[++nscnt].add=true;
		ns[nscnt].pos=x[i];
		ns[nscnt].time=a[i];
		ns[nscnt].type=t[i];
		ns[++nscnt].add=false;
		ns[nscnt].pos=x[i];
		ns[nscnt].time=b[i]+1;
		ns[nscnt].type=t[i];
		posq[++poscnt]=x[i];
	}

	sort(posq+1,posq+poscnt+1);
	posq=unique(posq+1,posq+poscnt+1)-posq-1;

	for(int i=1;i<=q;i++){
		read(l[i]);read(y[i]);
		qs[i].pos=l[i];
		qs[i].time=y[i];
	}
	sort(ns+1,ns+nscnt+1,ncmp);
	sort(qs+1,qs+q+1,qcmp);

	int ni=1;
	for(int i=1;i<=q;i++){
		int time=qs[i].time,pos=qs[i].pos;
		while(ns[ni].time<=time){
			if(ns[ni].add)
				addshop(ns[ni].pos,ns[ni].type);
			else
				removeshop(ns[ni].pos,ns[ni].type);
		}
		
		printf("%d\n",quert())
	}





	return 0;
}


