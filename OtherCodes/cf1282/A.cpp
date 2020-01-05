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

int t;
int a,b,c,ra;



int main(int argc, char* argv[]) {

	read(t);
	while(t--){

		read(a);read(b);read(c);read(ra);
		if(a>b)
			swap(a,b);

		int l=c-ra,r=c+ra;
		int ans=0;

		if(a<=l&&b>=r){
			DEBUG("a=%d, b=%d, l=%d, r=%d, ",a,b,l,r);
			DEBUG("Case 1\n");
			ans=b-a-2*ra;
		}else if(a>=l&&a<=r&&b>=l&&b<=r){
			DEBUG("a=%d, b=%d, l=%d, r=%d, ",a,b,l,r);
			DEBUG("Case 2\n");
			ans=0;
		}else if(a>=r||b<=l){
			DEBUG("a=%d, b=%d, l=%d, r=%d, ",a,b,l,r);
			DEBUG("Case 3\n");
			ans=b-a;
		}else if(a<=r||b>=l){
			DEBUG("a=%d, b=%d, l=%d, r=%d, ",a,b,l,r);
			if(a<=l){
				DEBUG("Case 4.a\n");
				ans=l-a;
			}
			if(b>=r){
				DEBUG("Case 4.b\n");
				ans=b-r;
			}
		}else{
			printf("Case failed\n");
			fflush(stdout);
			abort();
		}

		printf("%d\n",ans);

	}

	return 0;
}


// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP

