// 字符串哈希
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
const int MaxN=1e6+10;
const int Charset=26;

int n,m;
char x[MaxN],y[MaxN];
ll a[MaxN],b[MaxN];

ll qm(ll base,ll exp,ll mod){
	ll ans=1;
	while(exp){
		if(exp&1)
			ans=ans*base%mod;
		base=(ll)base*base%mod;
		exp>>=1;
	}
	return ans;
}

ll push(ll val,ll push,ll mod){
	return (val*Charset+push)%mod;
}

ll trans(ll val,ll push,ll pop,ll len,ll mod){
	return ((val+mod-pop*qm(Charset,len-1,mod)%mod)%mod*Charset+push)%mod;
}

const ll mod1=998244353,mod2=1000000007,mod3=1000000009;

ll xm,ym;

bool check(){
	return xm==ym;
}

int main(int argc, char* argv[]) {

	scanf("%s%s",x+1,y+1);
	n=strlen(x+1);
	m=strlen(y+1);
	for(int i=1;i<=n;i++)
		a[i]=x[i]-'a';
	for(int i=1;i<=m;i++)
		b[i]=y[i]-'a';

	for(int i=1;i<=m;i++){
		ym=push(ym,b[i],mod1);
	}

	DEBUG("ym=%d\n",ym);

	if(n<m){
		printf("0\n");
	}else{
		int ans=0;
		for(int i=1;i<=m;i++)
			xm=push(xm,a[i],mod1);
		DEBUG("xm0=%d\n",xm);
		if(check())
			ans++;
		DEBUG("n=%d, m=%d\n",n,m);
		for(int i=m+1;i<=n;i++){
			xm=trans(xm,a[i],a[i-m],m,mod1);
			DEBUG("i=%d, xm=%d\n",i,xm);
			if(check())
				ans++;
		}
		printf("%d\n",ans);
	}


	return 0;
}


