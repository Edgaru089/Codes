#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <string>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

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

typedef long long ll;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> rbtree;
const int MaxN=5e5+10,MaxM=5e5+10,MaxQ=5e5+10;

int n,m,q;
int qxt;
int a0[MaxN];
pair<int,int> a[MaxM];
pair<ll,int> k[MaxQ];
ll scnt[MaxM],bcnt[MaxM];
ll cost[MaxM];

int ans[MaxQ];

rbtree it;


int main(int argc, char* argv[]) {

	read(n);read(m);read(q);
	FOR(i,1,n){
		read(a0[i]);
		a[a0[i]].first++;
	}
	FOR(i,1,q){
		pair<ll,int> qt;
		read(qt.first);
		qt.second=i;
		if(qt.first<=n)
			ans[i]=a0[qt.first];
		else{
			qt.first-=n;
			k[++qxt]=qt;
		}
	}

	FOR(i,1,m)
		a[i].second=i;

	PASS;

	sort(a+1,a+m+1);
#ifdef D
	FOR(i,1,m)
		DEBUG("a[i=%d].first=%d, .second=%d\n",i,a[i].first,a[i].second);
#endif

	scnt[1]=1;
	FOR(i,2,m)
		if(a[i-1].first==a[i].first)
			scnt[i]=scnt[i-1]+1;
		else
			scnt[i]=1;
	bcnt[m]=scnt[m];
	ROF(i,m-1,1)
		if(a[i+1].first==a[i].first)
			bcnt[i]=bcnt[i+1];
		else
			bcnt[i]=scnt[i];

	cost[1]=0;
	FOR(i,2,m){
		if(a[i-1].first==a[i].first)
			cost[i]=cost[i-1];
		else
			cost[i]=cost[i-1]+(ll)(i-1)*(a[i].first-a[i-1].first);
	}

	PRINTARR("%lld",cost,1,m);

	PASS;

	sort(k+1,k+qxt+1);

	int j=0;
	FOR(i,1,qxt){
		while(j+1<=m&&cost[j+1]<k[i].first){
			it.insert(a[j+1].second);
			j++;
		}
		ll qx=k[i].first-cost[j]-1;
		ll idxt;
		//ans[k[i].second]=*it.find_by_order(idxt=qx%(j+bcnt[j]-1));
		ans[k[i].second]=*it.find_by_order(idxt=qx%(j));
		DEBUG("i=%d, q[i]=%lld(rid=%d), j=%d, it.size()=%d, qx=%lld, excnt=%lld, idxt=%lld\n",i,k[i].first,k[i].second,j,(int)it.size(),qx,j+bcnt[j]-1,idxt);
#ifdef D
		DEBUG("    it:");
		for(int x:it)
			DEBUG(" %d",x);
		DEBUG("\n");
#endif
	}

	FOR(i,1,q)
		printf("%d\n",ans[i]);


	return 0;
}


// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP

