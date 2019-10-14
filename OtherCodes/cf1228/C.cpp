#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <climits>
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

typedef long long ll;
const ll Mod=1e9+7;

ll qm(ll base,ll exp,ll mod){
	ll ans=1;
	while(exp){
		if(exp&1)
			ans=ans*base%mod;
		base=base*base%mod;
		exp>>=1;
	}
	return ans;
}


ll x,n;

ll ps[100010],pcnt=0;


int main(int argc, char* argv[]) {

	read(x);read(n);

	int lim=ceil(sqrt(x));
	for(int i=2;i<=min(x,(ll)lim);i++)
		if(x%i==0){
			ps[++pcnt]=i;
			while(x%i==0)
				x/=i;
		}
	if(x!=1)
		ps[++pcnt]=x;

	ll ans=1;

	DEBUG("pcnt=%d\n",pcnt);

	for(int i=1;i<=pcnt;i++){
		ll px=ps[i],pt=ps[i];
		//long double ptsx=n/pt;
		long double ptsx=LLONG_MAX/pt;
		//int ts=ceil(log10((long double)n)/log10((long double)pt));
		//for(int j=1;j<=ts;j++){
		for(;;){
			ans=ans*qm(pt,n/px,Mod)%Mod;
			if(px>ptsx)
				break;
			ll npx=px*pt;
			if(npx<px||npx>n)
				break;
			px=npx;
		}
	}

	cout<<ans<<endl;

	return 0;
}


