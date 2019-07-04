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
const int MaxN=500+10;
const int Mod=1000000007;

int n;
int a[MaxN],b[MaxN];
int t[2*MaxN],tdis[2*MaxN];


int s[2*MaxN];
int cnt;
int dp[2*MaxN];
int c[MaxN];

ll qm(ll base,ll exp){
	ll ans=1;
	while(exp){
		if(exp&1)
			ans=(ans*base)%Mod;
		base=(base*base)%Mod;
		exp>>=1;
	}
	return ans;
}

int inv(int x){
	return qm(x,Mod-2);
}


int main(int argc, char* argv[]) {

	read(n);
	for(int i=1;i<=n;i++){
		read(a[i]);
		read(b[i]);
		s[2*i-1]=a[i];
		s[2*i]=b[i]+1; // [a, b)
	}

	sort(s+1,s+2*n+1);
	cnt=unique(s+1,s+2*n+1)-s-1;
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(s+1,s+cnt+1,a[i])-s;
		b[i]=lower_bound(s+1,s+cnt+1,b[i]+1)-s;
	}

	dp[0]=1;
	for(int i=1;i<=cnt;i++){
		int len=s[i+1]-s[i];
		c[0]=1;
		for(int j=1;j<=n;j++)
			c[j]=(ll)c[j-1]*(len+j-1)%Mod*inv(j)%Mod;
		for(int j=n;j>=1;j--){
			if(a[j]<=i&&b[j]>=i+1){
				int d=0,m=1,cx=len;
				for(int k=j-1;k>=0;k--){
					d=(d+(ll)cx*dp[k])%Mod; // not selected
					if(a[k]<=i&&b[k]>=i+1)  // selected
						cx=c[++m];
				}
				dp[j]=(dp[j]+d)%Mod;
			}
		}
	}

	int ans=0;
	for(int i=1;i<=n;i++)
		ans=(ans+dp[i])%Mod;
	printf("%d\n",ans);


	return 0;
}


