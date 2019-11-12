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

const int MaxN=3e5+10;

int q;
int n;

int a[MaxN];
int l[MaxN],r[MaxN];
int dp[MaxN];






int main(int argc, char* argv[]) {

	read(q);
	while(q--){
		read(n);

		//memset(r,0,sizeof(r));
		for(int i=1;i<=n;i++){
			dp[i]=r[i]=0;
			l[i]=n+3;
		}

		for(int i=1;i<=n;i++){
			read(a[i]);
			l[a[i]]=min(l[a[i]],i);
			r[a[i]]=max(r[a[i]],i);
		}

		sort(a+1,a+n+1);
		n=unique(a+1,a+n+1)-a-1;
		//memset(dp,0,sizeof(dp));

		int ans=1;
		dp[n]=1;
		for(int i=n-1;i>=1;i--){
			if(r[a[i]]<l[a[i+1]])
				dp[i]=dp[i+1]+1;
			else
				dp[i]=1;
			ans=max(ans,dp[i]);
		}

		printf("%d\n",n-ans);
	}

	return 0;
}


