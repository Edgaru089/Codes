#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <map>
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
const int MaxN=3e5+10;

ll q,n;
ll a[MaxN];

map<ll,ll> mx[MaxN];
ll nx[MaxN],t[MaxN];




int main(int argc, char* argv[]) {

	read(q);
	while(q--){
		read(n);
		for(ll i=1;i<=n;i++)
			read(a[i]);

		for(ll i=1;i<=n+2;i++){
			mx[i].clear();
			nx[i]=t[i]=0;
		}
		a[n+1]=0;

		nx[n]=n+1;
		for(ll i=n-1;i>=1;i--){

			swap(mx[i],mx[nx[i+1]]);
			mx[i][a[i+1]]=i+1;

			if(auto it=mx[i].find(a[i]); it==mx[i].end())
				nx[i]=n+1;
			else
				nx[i]=it->second;
		}

		ll ans=0;
		for(ll i=n;i>=1;i--){
			if(nx[i]==n+1)
				t[i]=0;
			else
				t[i]=t[nx[i]+1]+1;
			ans+=t[i];
		}

		//printf("%d\n",ans);
		cout<<ans<<endl;
	}

	return 0;
}


