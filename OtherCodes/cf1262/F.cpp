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

typedef long long ll;
const ll Mod=998244353;
const int MaxN=2e5+10;

int n,k;
ll h[MaxN];
ll fact[MaxN],_inv[MaxN];

ll qm(ll base,ll exp,ll mod=Mod){
	ll ans=1;
	while(exp){
		if(exp&1)
			ans=ans*base%mod;
		base=base*base%mod;
		exp>>=1;
	}
	return ans;
}

ll inv(ll x){
	return qm(x,Mod-2,Mod);
}

ll C(ll n,ll m){
	return fact[n]*inv(fact[m])%Mod*inv(fact[n-m])%Mod;
}



int main(int argc, char* argv[]) {

	read(n);read(k);
	FOR(i,1,n)
		read(h[i]);

	if(k==1){
		printf("0\n");
		return 0;
	}

	fact[0]=1;
	FOR(i,1,n)
		fact[i]=fact[i-1]*i%Mod;

	int t=0;
	FOR(i,1,n)
		if(h[i]!=h[i%n+1])
			t++;

	ll ans=0;
	ll inv2=inv(2);
	FOR(i,0,t-1){
		ll delta=qm(k-2,i,Mod)*C(t,i)%Mod;
		if((t-i)&1)
			delta=delta*qm(2,t-i-1,Mod);
		else
			delta=delta*(qm(2,t-i)+Mod-C(t-i,(t-i)/2))%Mod*inv2%Mod;
		ans+=delta;
		ans%=Mod;
	}

	ans=ans*qm(k,n-t)%Mod;

	cout<<ans<<endl;


	return 0;
}


// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP

