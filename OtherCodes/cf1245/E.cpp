#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <cmath>
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
		fprintf(stderr,"Debug Assertion Failed on line %d, in function %s:\n  Expression: %s\n",__LINE__,__func__,#expr);\
		abort();\
	}\
}while(false)
#define PRINTARR2D(formatstr, arr, beginoff, size, beginy, sizey)\
do{fprintf(stderr,#arr ":");									\
for (int __i = beginy; __i <= beginy + sizey - 1; __i++)		\
	fprintf(stderr,"\t%d", __i);								\
fprintf(stderr,"\n");											\
for (int __i = beginoff; __i <= beginoff + size - 1; __i++) {	\
	fprintf(stderr, "%d:", __i);								\
	for(int __j = beginy; __j <= beginy + sizey -1; __j++)		\
		fprintf(stderr,"\t" formatstr, arr[__i][__j]);			\
	fprintf(stderr, "\n");										\
}}while(false)
#else
#define DEBUG(...)
#define PRINTARR(a, b, c, d)
#define PRINTARR2D(a, b, c, d, e, f)
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

typedef long double ld;
const int n=10;

int h[n+5][n+5];
ld dp0[n+5][n+5],dp1[n+5][n+5];


void advance(int& x,int& y){
	if(x&1)
		y--;
	else
		y++;
	if(y<=0){
		y=1;
		x--;
	}
	if(y>=n+1){
		y=n;
		x--;
	}
}

void fallback(int& x,int& y){
	if(x&1)
		y++;
	else
		y--;
	if(y<=0){
		y=1;
		x--;
	}
	if(y>=n+1){
		y=n;
		x--;
	}
}

int id[n+10][n+10];
int f[100+10];
ld expt[100+10];

int g(int i,int r){
	if(i+r<=100)
		return i+r;
	else
		return i;
}


int main(int argc, char* argv[]) {

	{
		int x=10,y=1;
		for(int i=1;i<=100;i++){
			id[x][y]=i;
			advance(x,y);
		}
	}

	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			read(h[i][j]);
			if(h[i][j]==0)
				f[id[i][j]]=id[i][j];
			else
				f[id[i][j]]=id[i-h[i][j]][j];
		}

	ld prev=0;
	for(int t=1;t<=2000;t++){
		for(int i=99;i>=1;i--){
			ld sum=1;
			for(int r=1;r<=6;r++)
				sum+=min(expt[g(i,r)],expt[f[g(i,r)]])/6.0;
			expt[i]=sum;
		}
	}

	printf("%.12Lf\n",expt[1]);



	return 0;
}


