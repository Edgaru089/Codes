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

const int MaxN=1e7+10;

bool flag[MaxN];
int primes[MaxN],pcnt;

int n,m;



int main(int argc, char* argv[]) {

	read(n);read(m);

	for(int i=2;i<=n;i++)
		flag[i]=true;

	// sieve
	for(int i=2;i<=n;i++){
		if(flag[i])
			primes[++pcnt]=i;
		for(int j=1;j<=pcnt;j++){
			int p=primes[j];
			if(p*i>n)
				break;
			flag[p*i]=false;
			if(i%p==0)
				break;
		}
	}


	for(int i=1;i<=m;i++){
		int a;
		read(a);
		if(flag[a])
			printf("Yes\n");
		else
			printf("No\n");
	}



	return 0;
}


