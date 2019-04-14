// manacher模板

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

const int MaxN=11000000+10;

int n0,n;
char s0[MaxN];
char s[2*MaxN];

int r[2*MaxN],maxp,maxc;



int main(int argc, char* argv[]) {

	scanf("%s",s0);

	n0=strlen(s0);
	for(int i=0;i<n0;i++){
		s[2*i+1]='#';
		s[2*i+2]=s0[i];
	}

	n=2*n0+1;
	s[n]='#';

	r[1]=1;
	maxp=maxc=1;
	int ans=0;
	for(int i=2;i<=n;i++){
		r[i]=1;
		if(i<=maxp)
			r[i]=max(1,min(r[2*maxc-i],maxp-i+1));
		if(i+r[i]-1>=maxp){
			while(i-r[i]+1-1>=1&&i+r[i]-1+1<=n&&s[i-r[i]+1-1]==s[i+r[i]-1+1])
				r[i]++;
		}
		if(i+r[i]-1>maxp){
			maxp=i+r[i]-1;
			maxc=i;
		}
		ans=max(ans,r[i]-1);
	}
//	printf("%s\n",(char*)(s+1));
//	PRINTARR("%d",r,1,n);

	printf("%d\n",ans);

	return 0;
}


