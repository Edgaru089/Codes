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

const int MaxN=100000+10;

char s[2*MaxN];
int n;
int r[2*MaxN];
int maxpos,maxc;

int lx[MaxN],rx[MaxN];


int main(int argc, char* argv[]) {

	scanf("%s",s+1);
	n=strlen(s+1);
	
	for(int i=n;i>=1;i--){
		s[2*i+1]='#';
		s[2*i]=s[i];
	}
	s[1]='#';
	n=2*n+1;

	for(int i=1;i<=n;i++){
		r[i]=1;
		if(i<maxpos)
			r[i]=min(maxpos-i+1,r[2*maxc-i]);
		if(r[i]+i-1>=maxpos)
			while(i+r[i]<=n&&i-r[i]>=1&&s[i+r[i]]==s[i-r[i]])
				r[i]++;
		if(r[i]+i-1>maxpos){
			maxpos=i+r[i]-1;
			maxc=i;
		}
	}

	DEBUG("%s\n",s+1);
	PRINTARR("%d",r,1,n);




	return 0;
}


