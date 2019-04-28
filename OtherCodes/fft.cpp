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

const int MaxN=1e6+10;
const int MaxC=1<<20;

int n,m;
int a[MaxN],b[MaxN];

int lg[MaxN],r[MaxC];


class cmpx{
public:
	long double r,i;
	cmpx(){}
	cmpx(double alpha):r(cos(alpha)),i(sin(alpha)){}
	cmpx(double real,double imag):r(real),i(imag){}

	cmpx operator +(cmpx right)const{return cmpx(r+right.r,i+right.i);}
	cmpx operator -(cmpx right)const{return cmpx(r-right.r,i-right.i);}
	cmpx operator -()const{return cmpx(-r,-i);}
	cmpx operator *(cmpx right)const{return cmpx(r*right.r-i*right.i,r*right.i+i*right.r);}
};




int main(int argc, char* argv[]) {

	for(int i=2;i<=n;i++){
		lg[i]=lg[i-1];
		if(!(i&(1<<lg[i-1])))
			lg[i]++;
	}

	for(int i=1;i<MaxC;i++)
		r[i]=(r[i>>1])|((i&1)<<lg[i]);





	return 0;
}


