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

typedef __int128 ll;
const ll Mod=1000000007;

ll f[100];
ll s[100];

ll decompose(ll n){
	ll ans=0;
	for(int i=80;i>=0;i--){
		while(f[i]<=n){
			n-=f[i];
			ans|=(1<<i);
		}
	}
	return ans;
}

ll solve0(ll x){
	if(x==-1)
		return 0;
	if(x==0)
		return 1;
	if(x==1)
		return 3;

	int i=80;
	while(f[i]>x)
		i--;

	ll ans=s[i]^solve0(x-f[i]);
	if((x-f[i]+1)&1)
		ans|=(1<<(i));

	return ans;
}

ll solve(ll l,ll r,int i=80){
	if(r<l||(l==r&&r==0))
		return 0;
	while(f[i]>r)
		i--;
	ll lx=r-f[i];

	ll l1=0,r1=lx;
	ll l2=l,r2=f[i]-1;
	ll ans;

//	if(l2<=r1){
//		if(r2>r1)
//			ans=solve(l1,l2-1)^solve(r1+1,r2);
//		else if(r2==r1)
//			ans=solve(l1,l2-1);
//		else
//			ans=solve(l1,l2-1)^solve(r2+1,r1);
//	}else
//		ans=solve(l,f[i]-1,i)^solve(0,lx);
	ans=solve(l,f[i]-1,i)^solve0(lx);

	if((lx+1)&1)
		ans|=(1<<i);

	return ans;
}




int main(int argc, char* argv[]) {

	f[0]=1;
	f[1]=2;
	for(int i=2;i<=80;i++)
		f[i]=f[i-1]+f[i-2];
	s[0]=1;
	s[1]=3;
	for(int i=2;i<=80;i++){
		s[i]=s[i-1]^s[i-2];
		if(f[i-2]&1)
			s[i]|=(1<<(i-1));
	}

	ll a,b;
	read(a);read(b);

//#ifndef T
//	if(a<=1000000&&b<=1000000){
//		ll ans=0;
//		for(ll i=a;i<=b;i++){
//			ans^=decompose(i);
//		}
//		printf("%lld\n",(long long)(ans%Mod));
//	}else{
//#endif
	printf("%lld\n",(long long)(solve(a,b)%Mod));
//#ifndef T
//	}
//#endif



	return 0;
}


