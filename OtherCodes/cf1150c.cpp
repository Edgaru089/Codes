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
		fprintf(stderr,"Debug Assertation Failed on line %d, in function %s:\n  Expression: %s\n",__LINE__,__func__,#expr);\
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

const int MaxN=200000+10;

int n;
int a;
int cnt[3];





int main(int argc, char* argv[]) {

	read(n);
	for(int i=1;i<=n;i++){
		read(a);
		cnt[a]++;
	}

	if(cnt[2]==0){
		for(int i=1;i<=n;i++){
			if(i==1)
				printf("1");
			else
				printf(" 1");
		}
		printf("\n");
	}else{
		if(cnt[1]==0){
			for(int i=1;i<=n;i++){
				if(i==1)
					printf("2");
				else
					printf(" 2");
			}
			printf("\n");
		}else{
			printf("2 1");
			cnt[2]--;
			cnt[1]--;
			for(int i=1;i<=cnt[2];i++)
				printf(" 2");
			for(int i=1;i<=cnt[1];i++)
				printf(" 1");
		}
	}

	return 0;
}


