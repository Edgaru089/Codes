#include <cstdlib>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <deque>
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

const int MaxN=1e6+10;

int n,k,a[MaxN];

struct st{
	st(){}
	st(int a,int id):id(id),a(a){}
	int a,id;
};

deque<st> Q;





int main(int argc, char* argv[]) {

	read(n);read(k);
	for(int i=1;i<=n;i++)
		read(a[i]);

	for(int i=1;i<=k-1;i++){
		while(!Q.empty()&&Q.back().a>a[i])
			Q.pop_back();
		Q.push_back(st(a[i],i));
	}

	for(int i=k;i<=n;i++){
		while(!Q.empty()&&Q.front().id<i-k+1)
			Q.pop_front();
		while(!Q.empty()&&Q.back().a>a[i])
			Q.pop_back();
		Q.push_back(st(a[i],i));
		if(i==k)
			printf("%d",Q.front().a);
		else
			printf(" %d",Q.front().a);
	}
	printf("\n");

	Q.clear();

	for(int i=1;i<=k-1;i++){
		while(!Q.empty()&&Q.back().a<a[i])
			Q.pop_back();
		Q.push_back(st(a[i],i));
	}

	for(int i=k;i<=n;i++){
		while(!Q.empty()&&Q.front().id<i-k+1)
			Q.pop_front();
		while(!Q.empty()&&Q.back().a<a[i])
			Q.pop_back();
		Q.push_back(st(a[i],i));
		if(i==k)
			printf("%d",Q.front().a);
		else
			printf(" %d",Q.front().a);
	}
	printf("\n");


	return 0;
}


