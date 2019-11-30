#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>

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

typedef pair<int,int> pii;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> rbtree;
const int MaxN=2e5+10,MaxM=2e5+10;

int n,m;
int a0[MaxN];
pii a[MaxN];
int ans[MaxN];

struct Q{
	int k,pos;
	int i;
};

Q q[MaxM];
rbtree t;



int main(int argc, char* argv[]) {

	read(n);
	FOR(i,1,n){
		read(a0[i]);
		a[i].first=a0[i];
		a[i].second=i;
	}
	read(m);
	FOR(i,1,m){
		read(q[i].k);
		read(q[i].pos);
		q[i].i=i;
	}

	sort(a+1,a+n+1,[](pii a,pii b){
		if(a.first>b.first)
			return true;
		else if(a.first==b.first&&a.second<b.second)
			return true;
		else
			return false;
	});
	sort(q+1,q+m+1,[](Q a,Q b){
		return a.k<b.k;
	});

	int j=1;
	FOR(i,1,m){
		DEBUG("i=%d, q[i]=[k=%d, pos=%d, i=%d]\n",i,q[i].k,q[i].pos,q[i].i);
		while(t.size()<q[i].k){
			DEBUG("------ Insert- j=%d, a[j]=%d, a[j].id0=%d\n",j,a[j].first,a[j].second);
			t.insert(a[j++].second);
		}
		ans[q[i].i]=a0[*t.find_by_order(q[i].pos-1)];
		DEBUG("    ans[q[i].i]=%d\n",ans[q[i].i]);
	}

	FOR(i,1,m)
		printf("%d\n",ans[i]);

	return 0;
}


// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP

