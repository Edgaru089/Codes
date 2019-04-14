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

const int MaxN=50000+10;

int n;

struct st{
	int k,b;
	int id;
};

st a[MaxN];

bool cmp(st x,st y){
	return x.k<y.k||(x.k==y.k&&x.b>y.b);
}

bool cmpid(st x,st y){
	return x.id<y.id;
}

st b[MaxN];
int cb;

st s[MaxN];
int t;

void push(st x){s[++t]=x;}
void pop(){t--;}

long double eps=1e-5;

long double intersectX(st x,st y){
	return (long double)(y.b-x.b)/(x.k-y.k);
}


int main(int argc, char* argv[]) {

	read(n);
	for(int i=1;i<=n;i++){
		read(a[i].k);read(a[i].b);
		a[i].id=i;
	}

	sort(a+1,a+n+1,cmp);

	for(int i=1;i<=n;i++)
		if(i==1||a[i-1].k!=a[i].k)
			b[++cb]=a[i];

	for(int i=1;i<=cb;i++){
		if(t==0||t==1)
			push(b[i]);
		else{
			while(t>1&&intersectX(s[t-1],s[t])-intersectX(s[t],b[i])>-eps)
				pop();
			push(b[i]);
		}
	}

	sort(s+1,s+t+1,cmpid);

	for(int i=1;i<=t;i++)
		printf("%d ",s[i].id);



	return 0;
}


