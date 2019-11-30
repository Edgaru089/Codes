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

typedef long long ll;
const int MaxN=1e6+10,MaxA=1e6+10;

int n;
ll a[MaxN];

int pcnt=0;
bool flag[MaxA];
int p[MaxN];

void sieve(int n=MaxA-6){
	for(int i=2;i<=n;i++){
		if(!flag[i])
			p[++pcnt]=i;
		for(int j=1;j<=pcnt&&i*p[j]<=n;j++){
			flag[i*p[j]]=true;
			if(i%p[j]==0)
				break;
		}
	}
}

bool prime(ll x){
	if(x==1)
		return false;
	ll n=(ll)(ceil(sqrt((long double)(x))));
	for(int i=2;i<=n;i++)
		if(x%i==0)
			return false;
	return true;
}

ll ans=-1;

void check(ll k){
	ll ans=0;
	for(int i=1;i<=n;i++){
		ll l=a[i]/k;
		ll r=l+1;
		l*=k;r*=k;
		if(a[i]-l<=r-a[i])
			ans+=a[i]-l;
		else
			ans+=r-a[i];
	}
	if(::ans==-1)
		::ans=ans;
	else
		::ans=min(::ans,ans);
}


int main(int argc, char* argv[]) {

	read(n);
	for(int i=1;i<=n;i++)
		read(a[i]);

	ll sum=0;
	for(int i=1;i<=n;i++)
		sum+=a[i];
	for(int i=1;i<=n;i++)
		a[i]+=a[i-1];

	sieve();
	PRINTARR("%d",p,1,20);
	for(int i=1;i<=pcnt;i++){
		if(sum%p[i]==0)
			check(p[i]);
	}

	if(prime(sum))
		check(sum);

	cout<<ans<<endl;

	return 0;
}


