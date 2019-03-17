#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
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
const int MaxN=100+10,Mod=9999973;

int n,m;

ll dp[MaxN][MaxN][MaxN];


template<typename Int>
void addmod(Int& val,Int add){
	if(val>Mod)
		val%=Mod;
	if(add>Mod)
		add%=Mod;
	val+=add;
	if(val>Mod)
		val-=Mod;
	if(val>Mod)
		val%=Mod;
}

// C{I, 2}
ll C(ll i){
	return i*(i-1)/2%Mod;
}

int main(int argc, char* argv[]) {

	read(n);read(m);

	dp[0][0][0]=1;
	for(int i=0;i<=n;i++){
		for(int j=0;j<=m;j++){
			for(int k=0;k<=m;k++){
				if(!dp[i][j][k]||j+k>m)
					continue;
				// 不放棋子
				addmod(dp[i+1][j][k],dp[i][j][k]);
				// 放一个棋子
				if(j+k<=m-1) // 放在空的列
					addmod(dp[i+1][j+1][k],dp[i][j][k]*(m-j-k));
				if(j>=1) // 放在有一个棋子的列
					addmod(dp[i+1][j-1][k+1],dp[i][j][k]*j);
				// 放两个棋子
				if(j+k<=m-2) // 放在两个空的列
					addmod(dp[i+1][j+2][k],dp[i][j][k]*C(m-j-k));
				if(j+k<=m-1) // 放在一个空的列和一个有一个棋子的列
					addmod(dp[i+1][j][k+1],dp[i][j][k]*(m-j-k)%Mod*j);
				if(j>=2) // 放在两个有一个棋子的列
					addmod(dp[i+1][j-2][k+2],dp[i][j][k]*C(j));
			}
		}
	}

	ll ans=0;
	for(int i=0;i<=m;i++)
		for(int j=0;j<=m;j++)
			if(i+j<=m)
				addmod(ans,dp[n][i][j]);

	printf("%lld\n",ans);


	return 0;
}


