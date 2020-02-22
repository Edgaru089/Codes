#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <queue>

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

typedef long long ll;
const int MaxN=5e5+10,MaxK=2e5+10;
const int MaxE=40;

int n,k;
ll a[MaxN];
ll s[MaxN];

struct node{
	int sum;
	node* son[2];
};

node* root;
node mem[MaxN*MaxE+100],*memtop=mem;
#define ALLOCATE (++memtop)


void insert(ll val){
	node** p=&root;

	ROF(i,MaxE-1,0){
		if(!*p)
			(*p)=ALLOCATE;
		(*p)->sum++;
		if(val&(1ll<<i))
			p=&((*p)->son[1]);
		else
			p=&((*p)->son[0]);
	}

	if(!*p)
		(*p)=ALLOCATE;
	(*p)->sum++;
}

int nodesize(node* p){
	if(!p)
		return 0;
	else
		return p->sum;
}

ll querykth(ll base,int k){
#ifdef D
	int k0=k;
#endif
	node* p=root;
	ll ans=0;
	ROF(i,MaxE-1,0){
		ASSERT(p);
		int exp=(bool)(base&(1ll<<i));
		if(nodesize(p->son[exp^1])>=k){
			p=p->son[exp^1];
			ans|=(((ll)exp^1)<<i);
		}else{
			k-=nodesize(p->son[exp^1]);
			p=p->son[exp];
			ans|=((ll)exp<<i);
		}
	}
	DEBUG("querykth(base=%lld, k=%d) = %lld\n",base,k0,ans^base);
	return ans^base;
}

priority_queue<pair<ll,pair<ll,int>>> Q;







int main(int argc, char* argv[]) {

	read(n);read(k);
	FOR(i,1,n)
		read(a[i]);

	PASS;

	FOR(i,1,n)
		s[i]=s[i-1]^a[i];

	FOR(i,0,n)
		insert(s[i]);

	FOR(i,0,n)
		Q.push(make_pair(querykth(s[i],1),make_pair(s[i],1)));

	PASS;

	ll ans=0;
	FOR(i,1,2*k){
		ll exp=Q.top().first;
		auto[base,t]=Q.top().second;
		Q.pop();
		ans+=exp;
		//if(t<k)
			Q.push(make_pair(querykth(base,t+1),make_pair(base,t+1)));
	}

	printf("%lld\n",ans/2);

	return 0;
}

// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP
