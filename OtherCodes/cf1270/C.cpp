#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
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
#define ASSERT(expr) do{\
	if(!(expr)){\
		fprintf(stderr,"Debug Assertion Failed on line %d, in function %s:\n  Expression: %s\n",__LINE__,__func__,#expr);\
		abort();\
	}\
}while(false)
#define PASS fprintf(stderr,"Passing function \"%s\" on line %d\n", __func__, __LINE__)
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
#define ASSERT(a)
#define PRINTARR(a, b, c, d)
#define PRINTARR2D(a, b, c, d, e, f)
#define PASS
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

typedef long long ll;
const int MaxN=1e5+10;

int t;
int n;
ll a[MaxN];
ll sum,xsum;
vector<ll> ans;




int main(int argc, char* argv[]) {

	read(t);
	while(t--){

		sum=xsum=0;
		ans.clear();

		read(n);
		FOR(i,1,n){
			read(a[i]);
			sum+=a[i];
			xsum^=a[i];
		}

		DEBUG("sum=%d(%x), xsum=%d(%x)\n",sum,sum,xsum,xsum);

		ll sc=1ll<<56;
		if(sum&1)
			sc|=1;
		ans.push_back(sc);
		sum+=sc;
		xsum^=(sc);

		ASSERT(sum<(xsum*2));

		ll d=xsum*2-sum;

		ans.push_back(d/2);
		ans.push_back(d/2);
		sum+=d;
		ASSERT(sum==xsum*2);

		sum=xsum=0;

		FOR(i,1,n){
			sum+=a[i];
			xsum^=a[i];
		}

		sum+=ans[0]+ans[1]+ans[2];
		xsum^=ans[0]^ans[1]^ans[2];
		ASSERT(xsum*2==sum);

//#ifdef ONLINE_JUDGE
		printf("3\n%I64d %I64d %I64d\n",ans[0],ans[1],ans[2]);
//#else
		//printf("3\n%lld %lld %lld\n",ans[0],ans[1],ans[2]);
//#endif

	}

	return 0;
}


// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP

