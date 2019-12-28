#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <string>
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

#define FOR(i, first, last)               for(int i = (first); i <= (last); ++i)
#define ROF(i, last, first)               for(int i = (last); i >= (first); --i)
#define FORSTEP(i, first, last, step)     for(int i = (first); i <= (last); i += (step))
#define ROFSTEP(i, last, first, stepabs)  for(int i = (last); i >= (first); i -= (step))

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
template<>
void read<string>(string& str){
	str.clear();
	int c;
	while(iscntrl(c=getchar())||c==' '||c=='\t');
	do{
		str.push_back(c);
	}while(!(iscntrl(c=getchar())||c==' '||c=='\t'));
}

const int MaxN=1e5+10;

int n,m;
string a,b;
string tx;

int z[2*MaxN];

template<typename String>
void zfunc(String str,int n,int* z){
	z[0]=0;
	int l,r;
	l=r=0;
	FOR(i,1,n-1){
		if(i<=r)
			z[i]=min(r-i+1,z[i-l]);
		else
			z[i]=0;
		while(str[i+z[i]]==str[z[i]])
			z[i]++;
		if(r<i+z[i]-1){
			l=i;
			r=i+z[i]-1;
		}
	}
}




int main(int argc, char* argv[]) {

	read(a);read(b);
	n=a.size();
	m=b.size();

	tx=b+'$'+a;
	zfunc(tx,tx.size(),z);

	DEBUG("%s\n",tx.c_str());
	PRINTARR("%d",z,0,tx.size());

	z[0]=m;

	printf("%d",z[0]);
	FOR(i,1,m-1)
		printf(" %d",z[i]);
	printf("\n");
	printf("%d",z[m+1]);
	FOR(i,m+2,m+n)
		printf(" %d",z[i]);
	printf("\n");


	return 0;
}


// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP

