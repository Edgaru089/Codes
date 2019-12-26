#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <string>
#include <set>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#ifdef D
#include <custom/Debug.hpp>
#endif

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

typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> rbtree;

typedef long long ll;
const int MaxN=2e5+10;
const ll Mod=998244353;

int n;
struct pnt{
	int x,y;
};
pnt p[MaxN];




int main(int argc, char* argv[]) {

	read(n);
	FOR(i,1,n){
		read(p[i].x);
		read(p[i].y);
	}

	sort(p+1,p+n+1,[](pnt x,pnt y){
		if(x.y>y.y)
			return true;
		else if(x.y==y.y&&x.x<y.x)
			return true;
		else
			return false;
	});

#ifdef D
	FOR(i,1,n)
		DEBUG("p[%d]=[x=%d, y=%d]\n",i,p[i].x,p[i].y);
#endif

	int j=0;
	rbtree xi;
	vector<int> dx;
	ll ans=0;
	FOR(i,1,n){
		DEBUG("i=%d, p[i].y=%d\n",i,p[i].y);
		bool first=true;
		dx.clear();
		while(first||(i<=n&&p[i-1].y==p[i].y)){
			xi.insert(p[i].x);
			dx.push_back(p[i].x);
			i++;
			first=false;
		}
		int prev=-1;
		for(int x:dx){
			int np=xi.order_of_key(x);
#ifdef D
			int dbg_delta;
			ans+=dbg_delta=(np-prev)*(xi.size()-np);
			DEBUG("   p[i].x=%d, prev=%d, factL=%d, factR=%d, np=%d, delta=%d\n",x,prev,np-prev,(int)xi.size()-np,np,dbg_delta);
#else
			ans+=(ll)(np-prev)*(xi.size()-np);
#endif
			prev=np;
		}
		i--;
		PRINT(xi);
		//ans=(ans+(ll)xi.size()*(xi.size()+1)/2%Mod)%Mod;
	}

	cout<<ans<<endl;


	return 0;
}


// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP

