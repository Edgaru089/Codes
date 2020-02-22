#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <map>

#ifdef D
#include <custom/Debug.hpp>
#endif

using namespace std;

#if (defined LOCAL) || (defined D)
#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define PRINTARR(formatstr, arr, beginoff, size)				\
do{fprintf(stderr,#arr ":");									\
for (int __i = beginoff; __i <= beginoff + size - 1; __i++)		\
	fprintf(stderr,"\t%d", __i);								\
fprintf(stderr,"\n");											\
for (int __i = beginoff; __i <= beginoff + size - 1; __i++)		\
	fprintf(stderr,"\t" formatstr, arr[__i]);					\
fprintf(stderr,"\n"); }while(false)
#define PASS fprintf(stderr,"Passing function \"%s\" on line %d\n", __func__, __LINE__)
#define ASSERT(expr) do{\
	if(!(expr)){\
		fprintf(stderr,"Debug Assertion Failed on line %d, in function %s:\n  Expression: %s\n",__LINE__,__func__,#expr);\
		abort();\
	}\
}while(false)
#define PRINTARR2D(formatstr, arr, beginoff, size, beginy, sizey)\
do{fprintf(stderr,#arr ":");									\
for (int __i = beginy; __i <= beginy + sizey - 1; __i++)		\
	fprintf(stderr,"\t%d", __i);								\
fprintf(stderr,"\n");											\
for (int __i = beginoff; __i <= beginoff + size - 1; __i++) {	\
	fprintf(stderr, "%d:", __i);								\
	for(int __j = beginy; __j <= beginy + sizey -1; __j++)		\
		fprintf(stderr,"\t" formatstr, arr[__i][__j]);			\
	fprintf(stderr, "\n");										\
}}while(false)
#define PRINT(...) dbg(__VA_ARGS__)
#define PRINTVAL(...) dbgv(__VA_ARGS__)
#define PRINTSEQ(...) dbgr(__VA_ARGS__)
#define PRINTSEQVAL(...) dbgm(__VA_ARGS__)
#define PRINTCOMPACT(...) dbgs(__VA_ARGS__)
#else
#define DEBUG(...)
#define PRINTARR(a, b, c, d)
#define PRINTARR2D(a, b, c, d, e, f)
#define PASS
#define ASSERT(expr)
#define PRINT(...)
#define PRINTVAL(...)
#define PRINTSEQ(...)
#define PRINTSEQVAL(...)
#define PRINTCOMPACT(...)
#endif

#define FOR(i, first, last)               for(int i = (first); i <= (last); ++i)
#define ROF(i, last, first)               for(int i = (last); i >= (first); --i)
#define FORSTEP(i, first, last, step)     for(int i = (first); i <= (last); i += (step))
#define ROFSTEP(i, last, first, stepabs)  for(int i = (last); i >= (first); i -= (stepabs))

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
template<>
void read<string>(string& str){
	str.clear();
	int c;
	while(iscntrl(c=getchar())||c==' '||c=='\t');
	do{
		str.push_back(c);
	}while(!(iscntrl(c=getchar())||c==' '||c=='\t'));
}
#if __cplusplus >= 201103
template<typename IntType,typename... Args>
void read(IntType& val, Args&... args){
	read(val); read(args...);
}
#endif

// End of template:edgar:edgar-laptop(LAPTOP-EDGAR-15)

const int MaxN=1e5+10;

int n,m;

int op[MaxN],x[MaxN];
int xd[MaxN];

int dt[MaxN];
map<int,int> d;
int cnt[MaxN];

struct node{
	int left,right;
	node* lson,*rson;
	int sum;
};

node* root;
node mem[2*MaxN],*memtop=mem;
#define ALLOCATE (++memtop)



void build(int left=1,int right=m,node*& p=root){
	p=ALLOCATE;
	p->left=left;
	p->right=right;
	if(left!=right){
		int mid=(left+right)/2;
		build(left,mid,p->lson);
		build(mid+1,right,p->rson);
	}
}

void update(node* p){
	if(p->lson)
		p->sum=p->lson->sum+p->rson->sum;
}

void add(int pos,int val,node* p=root){
	if(p->left==p->right){
		ASSERT(p->left==pos);
		p->sum+=val;
		return;
	}
	if(p->lson->right>=pos)
		add(pos,val,p->lson);
	else
		add(pos,val,p->rson);
	update(p);
}

int sum(int left,int right,node* p=root){
	if(right<left)
		return 0;
	if(p->left==left&&p->right==right)
		return p->sum;
	if(p->lson->right>=right)
		return sum(left,right,p->lson);
	else if(p->rson->left<=left)
		return sum(left,right,p->rson);
	else
		return (sum(left,p->lson->right,p->lson)+
				sum(p->rson->left,right,p->rson));
}

int kth(int k,node* p=root){
	if(p->left==p->right)
		return p->left;
	if(p->lson->sum>=k)
		return kth(k,p->lson);
	else
		return kth(k-p->lson->sum,p->rson);
}






int main(int argc, char* argv[]) {

	read(n);
	FOR(i,1,n){
		read(op[i],x[i]);
		dt[i]=x[i];
	}

	sort(dt+1,dt+n+1);
	m=unique(dt+1,dt+n+1)-(dt+1);
	FOR(i,1,m)
		d[dt[i]]=i;
	FOR(i,1,n)
		xd[i]=d[x[i]];

	DEBUG("m=%d\n",m);
	PRINTARR("%d",dt,1,m);
	PRINTARR("%d",xd,1,n);

	build();

	FOR(i,1,n){
		switch(op[i]){
			case 1:
				add(xd[i],1);
				cnt[xd[i]]++;
				break;
			case 2:
				add(xd[i],-1);
				cnt[xd[i]]--;
				break;
			case 3:
				printf("%d\n",sum(1,xd[i]-1)+1);
				break;
			case 4:
				printf("%d\n",dt[kth(x[i])]);
				break;
			case 5:
				printf("%d\n",dt[kth(sum(1,xd[i]-1))]);
				break;
			case 6:
				printf("%d\n",dt[kth(sum(1,xd[i]-1)+1+cnt[xd[i]])]);
				break;
		}
	}





	return 0;
}

// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP

