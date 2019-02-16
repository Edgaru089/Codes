#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <deque>
using namespace std;

#if (defined LOCAL) || (defined D)
#define DEBUG(...) printf(__VA_ARGS__)
#define PRINTARR(formatstr, arr, beginoff, size, suffix)				\
do{printf(":");											\
for (int __i = beginoff; __i <= beginoff + size - 1; __i++)		\
	printf("\t%d", __i);										\
printf("\n");													\
for (int __i = beginoff; __i <= beginoff + size - 1; __i++)		\
	printf("\t" formatstr, arr[__i] suffix);							\
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
#define PRINTARR(a, b, c, d, e)
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


const int MaxN=1e6+10;

int n,k;
int a;


deque<pair<int,int> > Qmax,Qmin;

int ansmax[MaxN],ansmin[MaxN];


int main(int argc, char* argv[]) {

	read(n);read(k);

	for(int i=1;i<=n;i++){
		read(a);
		while(!Qmax.empty()&&Qmax.front().second<i-k+1)
			Qmax.pop_front();
		while(!Qmax.empty()&&Qmax.back().first<a)
			Qmax.pop_back();
		Qmax.push_back(make_pair(a,i));
		while(!Qmin.empty()&&Qmin.front().second<i-k+1)
			Qmin.pop_front();
		while(!Qmin.empty()&&Qmin.back().first>a)
			Qmin.pop_back();
		Qmin.push_back(make_pair(a,i));

		if(i>=k){
			ansmax[i]=Qmax.front().first;
			ansmin[i]=Qmin.front().first;
		}
	}

	for(int i=k;i<=n;i++){
		if(i!=k)
			printf(" %d",ansmin[i]);
		else
			printf("%d",ansmin[i]);
	}
	printf("\n");
	for(int i=k;i<=n;i++){
		if(i!=k)
			printf(" %d",ansmax[i]);
		else
			printf("%d",ansmax[i]);
	}
	printf("\n");


	return 0;
}


