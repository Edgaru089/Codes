#include <cstdlib>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <vector>
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

int t;

int n;
int l,r;




int main(int argc, char* argv[]) {

	read(t);

	vector<int> x,y;

	while(t--){
		read(n);
		int ans=0;


		for(int i=0;i<7;i++){
			if((1<<i)>n)
				break;
			x.clear();
			y.clear();
			for(int j=1;j<=n;j++){
				if((j&(1<<i)))
					x.push_back(j);
				else
					y.push_back(j);
			}
			printf("%d %d",x.size(),y.size());
			for(int j=0;j<x.size();j++)
				printf(" %d",x[j]);
			for(int j=0;j<y.size();j++)
				printf(" %d",y[j]);
			printf("\n");
			fflush(stdout);
			int r;
			read(r);
			if(r==-1)
				return 0;
			ans=max(ans,r);
		}

		printf("-1 %d\n",ans);

	}




	return 0;
}


