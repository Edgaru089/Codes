#include <cstdlib>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cmath>
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

const int MaxN=300+10;

int n;
int x[MaxN],y[MaxN];


bool check(int i,long double h){
	DEBUG("  check on %d with h=%.5Lf...",i,h);
	long double prev=-1e15;
	for(int j=1;j<i;j++){
		long double cur=(long double)((long double)y[i]+h-y[j])/((long double)x[i]-x[j]);
		if(cur<prev){
			DEBUG("failed on j=%d, cur=%.3Lf, prev=%.3Lf,x[i]=%d, x[j]=%d.\n",j,cur,prev,x[i],x[j]);
			return false;
		}
		prev=cur;
	}
	prev=-1e15;
	for(int j=i+1;j<=n;j++){
		long double cur=(long double)((long double)y[i]+h-y[j])/((long double)x[i]-x[j]);
		if(cur<prev){
			DEBUG("failed on j=%d, cur=%.3Lf, prev=%.3Lf,x[i]=%d, x[j]=%d.\n",j,cur,prev,x[i],x[j]);
			return false;
		}
		prev=cur;
	}
	DEBUG("success.\n");
	return true;
}


long double getans(int i){
	long double l=3e10,r=0;
	while(fabs(l-r)>1e-7){
		long double mid=(l+r)/2;
		if(check(i,mid))
			l=mid;
		else
			r=mid;
	}
	DEBUG("ans of i=%d is %.3Lf\n",i,(l+r)/2);
	return (l+r)/2;
}


int main(int argc, char* argv[]) {
	
	read(n);
	for(int i=1;i<=n;i++)
		read(x[i]);
	for(int i=1;i<=n;i++)
		read(y[i]);
	
	long double ans=3e8;
	for(int i=1;i<=n;i++)
		ans=min(ans,getans(i));
	
	printf("%.3Lf\n",ans);
	
	return 0;
}


