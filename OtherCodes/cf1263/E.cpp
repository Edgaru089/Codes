#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <string>
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

#define FOR(i, first, last)               for(int i = first; i <= last; ++i)
#define ROF(i, last, first)               for(int i = last; i >= first; --i)
#define FORSTEP(i, first, last, step)     for(int i = first; i <= last; i += step)
#define ROFSTEP(i, last, first, stepabs)  for(int i = last; i >= first; i -= step)

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

int n;
string str;

struct node{
	int left,right;
	node* lson,*rson;
	int max,min,lazy;
};

node* root;
node mem[2*MaxN],*memtop=mem;
#define ALLOCATE (++memtop)

void build(int l=1,int r=n,node*& p=root){
	p=ALLOCATE;
	p->left=l;
	p->right=r;
	if(l!=r){
		int mid=(l+r)/2;
		build(l,mid,p->lson);
		build(mid+1,r,p->rson);
	}
}

void pushdown(node* p){
	if(p&&p->lazy){
		p->max+=p->lazy;
		p->min+=p->lazy;
		if(p->lson)
			p->lson->lazy+=p->lazy;
		if(p->rson)
			p->rson->lazy+=p->lazy;
		p->lazy=0;
	}
}

void add(int l,int r,int val,node* p=root){
	pushdown(p);
	if(p->left==l&&p->right==r){
		p->lazy+=val;
		return;
	}
	pushdown(p->lson);
	pushdown(p->rson);
	if(p->lson->right>=r)
		add(l,r,val,p->lson);
	if(p->rson->left<=l)
		add(l,r,val,p->rson);
	else{
		add(l,p->lson->right,val,p->lson);
		add(p->rson->left,r,val,p->rson);
	}
	pushdown(p->lson);
	pushdown(p->rson);
	p->max=max(p->lson->max,p->rson->max);
	p->min=min(p->lson->min,p->rson->min);
}

int querymax(int left,int right,node* p=root){
	pushdown(p);
	if(p->left==left&&p->right==right)
		return p->max;
	pushdown(p->lson);
	pushdown(p->rson);
	if(p->lson->right>=right)
		return querymax(left,right,p->lson);
	else if(p->rson->left<=left)
		return querymax(left,right,p->rson);
	else
		return max(querymax(left,p->lson->right,p->lson),
		           querymax(p->rson->left,right,p->rson));
}

int querymin(int left,int right,node* p=root){
	pushdown(p);
	if(p->left==left&&p->right==right)
		return p->min;
	pushdown(p->lson);
	pushdown(p->rson);
	if(p->lson->right>=right)
		return querymin(left,right,p->lson);
	else if(p->rson->left<=left)
		return querymin(left,right,p->rson);
	else
		return min(querymin(left,p->lson->right,p->lson),
		           querymin(p->rson->left,right,p->rson));
}

int ans[MaxN];
char buf[MaxN];
int cur;



int main(int argc, char* argv[]) {

	read(n);
	read(str);

	int nr=1;
	for(char c:str)
		if(c=='R')
			nr++;

	build(1,nr);

	memset(buf,'#',sizeof(buf)-1);

	cur=1;
	FOR(i,1,n){
		int ans=0;
		char c;
		int ndelta=0;
		switch(c=str[i-1]){
			case 'L':
				if(cur>1)
					cur--;
				break;
			case 'R':
				cur++;
				break;
			case '(':
				if(buf[cur]==')')
					ndelta++;
				if(buf[cur]!='(')
					ndelta++;
				buf[cur]='(';
				break;
			case ')':
				if(buf[cur]=='(')
					ndelta--;
				if(buf[cur]!=')')
					ndelta--;
				buf[cur]=')';
				break;
			default:
				if(buf[cur]=='(')
					ndelta--;
				else if(buf[cur]==')')
					ndelta++;
				buf[cur]=c;
		}
		if(ndelta)
			add(cur,nr,ndelta);
		if(querymin(1,nr)>=0&&querymax(nr,nr)==0)
			::ans[i]=querymax(1,nr);
		else
			::ans[i]=-1;
	}

	buf[n+1]=0;
	DEBUG("buf[]=\"%s\"\n",buf+1);

	printf("%d",ans[1]);
	FOR(i,2,n)
		printf(" %d",ans[i]);
	printf("\n");

	return 0;
}


// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP

