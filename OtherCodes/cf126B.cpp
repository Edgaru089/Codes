#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <string>
#include <cstring>
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
#else
#define DEBUG(...)
#define PRINTARR(a, b, c, d)
#define PRINTARR2D(a, b, c, d, e, f)
#define PASS
#define ASSERT(expr)
#endif

#define FOR(i, first, last)               for(int i = (first); i <= (last); ++i)
#define ROF(i, last, first)               for(int i = (last); i >= (first); --i)
#define FORSTEP(i, first, last, step)     for(int i = (first); i <= (last); i += (step))
#define ROFSTEP(i, last, first, stepabs)  for(int i = (last); i >= (first); i -= (step))

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

const int MaxN=1e6+10;

string s,sr;
int n;

int z[MaxN],zr[MaxN];

template<typename String>
void zfunc(String str,int n,int* z){
	z[0]=0;
	int l,r;
	l=r=0;
	FOR(i,1,n-1){
		if(i<=r)
			z[i]=min(r-i+1,z[i-l]);
		else
			z[i]=0;
		while(str[i+z[i]]==str[z[i]])
			z[i]++;
		if(r<i+z[i]-1){
			l=i;
			r=i+z[i]-1;
		}
	}
}

struct node{
	int left,right;
	node* lson,*rson;
	int max;
	int lazy;
};

node mem[2*MaxN],*memtop=mem;
#define ALLOCATE (++memtop)
node* root;

void build(int l=0,int r=n-1,node*& p=root){
	p=ALLOCATE;
	if(l!=r){
		int mid=(l+r)/2;
		build(l,mid,p->lson);
		build(mid+1,r,p->rson);
	}
}

void pushdown(node* p){
	if(p&&p->lazy){
		p->max=max(p->max,p->lazy);
		if(p->lson){
			p->lson->lazy=max(p->lson->lazy,p->lazy);
			p->rson->lazy=max(p->rson->lazy,p->lazy);
		}
		p->lazy=0;
	}
}

void set(int left,int right,int val,node* p=root){
	pushdown(p);
	if(p->left==left&&p->right==right){
		p->lazy=max(p->lazy,val);
		return;
	}
	pushdown(p);
	pushdown(p->lson);
	pushdown(p->rson);
	if(p->lson->right>=right)
		set(left,right,val,p->lson);
	else if(p->rson->left<=left)
		set(left,right,val,p->rson);
	else{
		set(left,p->lson->right,val,p->lson);
		set(p->rson->left,right,val,p->rson);
	}
	pushdown(p);
	pushdown(p->lson);
	pushdown(p->rson);
	p->max=max(p->lson->max,p->rson->max);
}

int query(int left,int right,node* p=root){
	if(p->left==left&&p->right==right)
		return p->max;
	if(p->lson->right>=right)
		return query(left,right,p->lson);
	else if(p->rson->left<=left)
		return query(left,right,p->rson);
	else
		return max(query(left,p->lson->right,p->lson),
		           query(p->rson->left,right,p->rson));
}

int anslen,anspos;


int main(int argc, char* argv[]) {

	read(s);
	n=s.size();

	sr.resize(n);
	FOR(i,0,n-1)
		sr[n-i-1]=s[i];

	DEBUG("%s\n",sr.c_str());

	zfunc(s,n,z);
	zfunc(sr,n,zr);

	PRINTARR("%d",z,0,n);
	PRINTARR("%d",zr,0,n);

	FOR(i,0,n-1)
		if(zr[i]>0)
			set(n-i-1-zr[i]+1,n-i-1,zr[i]);

	FOR(i,0,n-1){
		if(z[i]>0){
			int cur=min(z[i],)
		}
	}


	return 0;
}


// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP

