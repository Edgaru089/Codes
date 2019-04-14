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

const int MaxN=1000000+10;

int n;

char s1[MaxN],s2[MaxN];
int i1,j1,i2,j2;



int main(int argc, char* argv[]) {

	scanf("%s%s",(char*)(s1+1),(char*)(s2+1));
	n=strlen(s1+1);

	int ans1=0,ans2=0;
	i1=1;j1=2;
	while(i1<=n&&j1<=n){
		int k=1;
	while(k<=n&&s1[(i1+k-1)%k]==s1[(j1+k-1)%k])
			k++;
		if(k>n){
			ans1=i1;
			break;
		}else{
			if(s1[(i1+k-1)%k]<s1[(j1+k-1)%k])
				j1=(j1+k-1)%k;
			else
				i1=(i1+k-1)%k;
		}
	}
	if(j1>n)
		ans1=i1;
	else if(i1>n)
		ans1=j1;
	else
		ASSERT(ans1!=0);

	DEBUG("%d\n",ans1);



	return 0;
}


