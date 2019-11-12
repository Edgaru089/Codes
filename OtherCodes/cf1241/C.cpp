#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
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
const int MaxN=2e5+10;

ll q;
ll n;
ll p[MaxN];
//a >= b
ll a,x,b,y;
ll k;

ll gcd(ll m,ll n){
	if(n==0)
		return m;
	else
		return gcd(n,m%n);
}

ll lcm(ll x,ll y){
	return x*y/gcd(x,y);
}

bool check(ll l){
	ll acnt=l/a,bcnt=l/b;
	ll xcnt=l/lcm(a,b);
	acnt-=xcnt;
	bcnt-=xcnt;

	ll ans=0;
	ll i=1;
	DEBUG("check(%d), acnt=%d, bcnt=%d, xcnt=%d, ",l,acnt,bcnt,xcnt);
	while(xcnt--)
		ans+=p[i++]/100*(x+y);
	while(acnt--)
		ans+=p[i++]/100*x;
	while(bcnt--)
		ans+=p[i++]/100*y;

	DEBUG("ans=%d, k=%d, ",ans,k);
	DEBUG((ans>=k)?"true\n":"false\n");
	return ans>=k;
}



int main(int argc, char* argv[]) {

	read(q);
	while(q--){

		read(n);
		for(int i=1;i<=n;i++)
			read(p[i]);
		read(x);read(a);
		read(y);read(b);
		if(x<y){
			swap(a,b);
			swap(x,y);
		}
		read(k);

		sort(p+1,p+n+1,greater<ll>());

		if(!check(n)){
			printf("-1\n");
			continue;
		}

		ll l=1,r=n;
		while(l<r-1){
			ll mid=(l+r)/2;
			if(check(mid))
				r=mid;
			else
				l=mid;
		}

		if(check(l))
			printf("%d\n",(int)l);
		else
			printf("%d\n",(int)r);
	}

	return 0;
}


