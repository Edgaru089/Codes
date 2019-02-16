#include <cstdlib>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <cstdio>
using namespace std;

#if (defined LOCAL) || (defined D)
#define DEBUG(...) printf(__VA_ARGS__)
#define PRINTARR(formatstr, arr, beginoff, size)				\
do{printf(#arr ":");											\
for (int __i = beginoff; __i <= beginoff + size - 1; __i++)		\
	printf("\t%d", __i);										\
printf("\n");													\
for (int __i = beginoff; __i <= beginoff + size - 1; __i++)		\
	printf("\t" formatstr, arr[__i]);							\
printf("\n"); }while(false)
#define PASS printf("Passing function \"%s\" on line %d\n", __func__, __LINE__)
#define ASSERT(expr) do{\
	if(!(expr)){\
		printf("Debug Assertation Failed on line %d, in function %s:\n  Expression: %s\n",__LINE__,__func__,#expr);\
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
const int MaxN=2000000+10;
const ll Mod=20100403;

ll n,m;
ll f[MaxN];

ll qpow(ll base,ll exp,ll mod){
	ll ans=1;
	while(exp){
		if(exp&1)
			ans=(ans*base)%mod;
		base=base*base%mod;
		exp>>=1;
	}
	return ans;
}

ll inv(ll x,ll mod=Mod){
	return qpow(x,mod-2,mod);
}

ll C(int n,int m){
	return f[n]*inv(f[m])%Mod*inv(f[n-m])%Mod;
}

int main(int argc, char* argv[]) {
	
	read(n);read(m);
	
	f[0]=f[1]=1;
	for(int i=2;i<MaxN;i++)
		f[i]=f[i-1]*i%Mod;
	
	printf("%lld\n",(C(n+m,m)-C(n+m,m-1)+Mod)%Mod);
	
	return 0;
}


