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

const int MaxN=40000+10;

int n;
bool flag[MaxN];
int primes[MaxN],pcnt;
int phi[MaxN];

void sieve(){
	for(int i=2;i<=n;i++)
		flag[i]=true;

	flag[1]=false;
	phi[1]=1;

	for(int i=2;i<=n;i++){
		if(flag[i]){
			primes[++pcnt]=i;
			phi[i]=i-1;
		}
		for(int j=1;j<=pcnt;j++){
			int p=primes[j];
			if(p*i>n)
				break;
			flag[p*i]=false;
			if(i%p==0){
				phi[p*i]=p*phi[i];
				break;
			}else{
				phi[p*i]=phi[p]*phi[i]; // =phi[i]*(p-1)
			}
		}
	}
}


int main(int argc, char* argv[]) {

	read(n);

	sieve();

	int ans=1;
	for(int i=1;i<=n-1;i++)
		ans+=2*phi[i];

	printf("%d\n",ans);

	return 0;
}


