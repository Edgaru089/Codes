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

template<>
void read<string>(string& str){
	str.clear();
	int c;
	while(iscntrl(c=getchar())||c==' '||c=='\t');
	do{
		str.push_back(c);
	}while(!(iscntrl(c=getchar())||c==' '||c=='\t'));
}

const int MaxN=1e6+10;

int n,m;

bool flag[MaxN];
int primes[MaxN],pcnt;
int mu[MaxN];

void sieve(){
	int n=max(::n,::m);
	ASSERT(sizeof(char) == sizeof(bool));
	memset(flag,true,sizeof(flag));
	flag[0]=flag[1]=false;
	for(int i=2;i<=n;i++){
		if(flag[i]){
			mu[i]=-1;
			primes[++pcnt]=i;
		}
		for(int j=1;j<=pcnt;j++){
			if(primes[j]*i>n)
				break;
			flag[primes[j]*i]=false;
			if(i%primes[j]==0){
				mu[primes[j]*i]=0;
				break;
			}
			else{
				mu[primes[j]*i]=mu[primes[j]]*mu[i];
			}
		}
	}
}

int ms[MaxN];




int main(int argc, char* argv[]) {

	read(n);read(m);

	sieve();

	PRINTARR("%d",mu,1,n);

	if(n>m)
		swap(n,m);

	for(int i=1;i<=m;i++)
		ms[i]=mu[i]+ms[i-1];

	int ans=0;
	for(int d=1;d<=n;d++)
		ans+=ms[m/d]*n/d;

	printf("%d\n",ans);

	return 0;
}


