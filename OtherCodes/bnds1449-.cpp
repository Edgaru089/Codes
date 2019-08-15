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

int iabs(int x){
	return (x>0)?x:(-x);
}

const int MaxN=5000+10,MaxA=1000000+10;

int n,a[MaxN];
int ax;
bool flag[2*MaxA];





int main(int argc, char* argv[]) {

	read(n);
	for(int i=1;i<=n;i++){
		read(a[i]);
		ax=max(ax,a[i]);
	}

	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			flag[iabs(a[i]-a[j])]=true;

	for(int i=1;i<=ax;i++){
		bool ok=true;
		for(int j=1;j<=ax/i+1;j++)
			if(flag[i*j]){
				ok=false;
				break;
			}
		if(ok){
			printf("%d\n",i);
			break;
		}
	}



	return 0;
}


