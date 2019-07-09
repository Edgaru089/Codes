#include <cstdlib>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cmath>
using namespace std;

#if (defined LOCAL) || (defined D)
#define DEBUG(...) printf(__VA_ARGS__)
#define PRINTARR(formatstr, arr, beginoff, size)				\
do{printf(#arr ":");											\
for (int __i = beginoff; __i <= beginoff + size - 1; __i++)		\
	printf("\t%d", __i);										\
printf("\n");													\
for (int __i = beginoff; __i <= beginoff + size - 1; __i++)		\
	printf("\t" formatstr, arr[__i]);							\
printf("\n"); }while(false)
#define PASS printf("Passing function \"%s\" on line %d\n", __func__, __LINE__)
#define ASSERT(expr) do{\
	if(!(expr)){\
		printf("Debug Assertation Failed on line %d, in function %s:\n  Expression: %s\n",__LINE__,__func__,#expr);\
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

typedef long long ll;
const int MaxN=50000+10,MaxM=50000+10;

int n,m;

struct qu{
	int l,r;
	int id;
	ll ans;
};

qu a[MaxM];
int c[MaxN];

ll ccnt[MaxN],ans;
int l=1,r=0;

int s;


bool cmp(qu x,qu y){
	return x.l/s<y.l/s||
		(x.l/s==y.l/s&&x.r<y.r);
}

bool cmpid(qu x,qu y){
	return x.id<y.id;
}


ll gcd(ll n,ll m){
	if(m==0)
		return n;
	else
		return gcd(m,n%m);
}

void remove(int i){
	ans-=ccnt[c[i]]*ccnt[c[i]];
	ccnt[c[i]]--;
	ans+=ccnt[c[i]]*ccnt[c[i]];
}
void add(int i){
	ans-=ccnt[c[i]]*ccnt[c[i]];
	ccnt[c[i]]++;
	ans+=ccnt[c[i]]*ccnt[c[i]];
}


int main(int argc, char* argv[]) {

	read(n);read(m);

	for(int i=1;i<=n;i++)
		read(c[i]);

	for(int i=1;i<=m;i++){
		read(a[i].l);read(a[i].r);
		a[i].id=i;
	}

	s=floor(sqrt(m));

		if(a[i].l==a[i].r)
			continue;
		while(r<a[i].r){
			r++;
			add(r);
		}
		while(r>a[i].r){
			remove(r);
			r--;
		}
		while(l>a[i].l){
			l--;
			add(l);
		}
		while(l<a[i].l){
			remove(l);
			l++;
		}
		a[i].ans=ans;
	}

	sort(a+1,a+m+1,cmpid);

	for(int i=1;i<=m;i++){
		if(a[i].l==a[i].r){
			printf("0/1\n");
			continue;
		}
		ll t=(ll)a[i].ans-(a[i].r-a[i].l+1),b=(ll)(a[i].r-a[i].l+1)*(a[i].r-a[i].l);
		if(t==0)
			printf("0/1\n");
		else{
			ll g=gcd(t,b);
			printf("%lld/%lld\n",t/g,b/g);
		}
	}


	return 0;
}


