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

typedef long long ll;

ll k,n;

ll getcnt(ll x){
	ll ans=0;
	FOR(i,0,62){
		ll l=x<<i,r;
		if(x&1)
			r=l+(1ll<<i)-1;
		else
			r=l+(1ll<<(i+1))-1;
		if(l>n)
			break;
		else if(r<=n)
			ans+=(r-l+1);
		else
			ans+=n-l+1;
	}
	return ans;
}

bool check(ll x){
	return getcnt(x)>=k;
}

ll ans=0;

void odd(){
	ll l=1,r;
	if(n&1)
		r=n/2+1;
	else
		r=n/2;
	while(l<r-1){
		ll mid=(l+r)/2;
		if(check(mid*2-1))
			l=mid;
		else
			r=mid;
	}
	if(check(r*2-1))
		ans=max(ans,r*2-1);
	else if(check(l*2-1))
		ans=max(ans,l*2-1);
}

void even(){
	ll l=1,r=n/2;
	while(l<r-1){
		ll mid=(l+r)/2;
		if(check(mid*2))
			l=mid;
		else
			r=mid;
	}
	if(check(r*2))
		ans=max(ans,r*2);
	else if(check(l*2))
		ans=max(ans,l*2);
}



int main(int argc, char* argv[]) {

	read(n);read(k);


	even();
	odd();


	cout<<ans<<endl;



	return 0;
}


// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP

