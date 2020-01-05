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
#define ROFSTEP(i, last, first, stepabs)  for(int i = (last); i >= (first); i -= (stepabs))

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

const int MaxN=100;

int r,c;
int a[MaxN][MaxN];
int xs[MaxN],ys[MaxN];
int ts;


bool check2(){
	if(a[1][1]==1||a[r][1]==1||a[1][c]==1||a[r][c]==1)
		return true;
	FOR(i,2,r-1)
		if(xs[i]==c)
			return true;
	FOR(i,2,c-1)
		if(ys[i]==r)
			return true;
	return false;
}

bool check3(){
	FOR(i,1,c)
		if(a[1][i]==1||a[r][i]==1)
			return true;
	FOR(i,1,r)
		if(a[i][1]==1||a[i][c]==1)
			return true;
	return false;
}


int main(int argc, char* argv[]) {

	int t;
	read(t);
	string str;
	while(t--){
		read(r);read(c);
		FOR(i,1,r){
			read(str);
			FOR(j,1,c)
				a[i][j]=(int)(str[j-1]=='A');
		}

		FOR(i,1,r)
			xs[i]=0;
		FOR(j,1,c)
			ys[j]=0;
		ts=0;

		FOR(i,1,r)
			FOR(j,1,c){
				xs[i]+=a[i][j];
				ys[j]+=a[i][j];
				ts+=a[i][j];
			}

		if(ts==0)
			printf("MORTAL\n");
		else if(ts==r*c)
			printf("0\n");
		else if(xs[1]==c||xs[r]==c||ys[1]==r||ys[c]==r)
			printf("1\n");
		else if(check2())
			printf("2\n");
		else if(check3())
			printf("3\n");
		else
			printf("4\n");

	}

	return 0;
}


// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP

