#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
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

template<>
void read<string>(string& str){
	str.clear();
	int c;
	while(iscntrl(c=getchar())||c==' '||c=='\t');
	do{
		str.push_back(c);
	}while(!(iscntrl(c=getchar())||c==' '||c=='\t'));
}

typedef long long ll;

ll n,a,b,c,a1;
ll ax,ay;





int main(int argc, char* argv[]) {

	read(n);read(a);read(b);read(c);
	read(a1);

	ay=a1;
	long double ans=0;
	for(int i=2;i<=n;i++){
		ax=ay;
		ay=((long long)ax*a+b)%100000001;
		DEBUG("a[%d]=%d\n",i,ay);
		int axc=ax%c+1,ayc=ay%c+1;
		if(axc>ayc)
			ans+=1.0/axc;
		else
			ans+=1.0/ayc;
	}

	ax=ay;
	ay=a1;
	int axc=ax%c+1,ayc=ay%c+1;
	if(axc>ayc)
		ans+=1.0/axc;
	else
		ans+=1.0/ayc;


	printf("%.3Lf\n",ans);

	return 0;
}


