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

typedef long long ll;
const int MaxN=1e5+10;

ll n;
ll k;
ll a[MaxN];



int main(int argc, char* argv[]) {

	read(n);read(k);
	for(int i=1;i<=n;i++)
		read(a[i]);

	sort(a+1,a+n+1);
	
	ll max=a[n],min=a[1];
	ll nmax,nmin;
	ll dmax=0,dmin=0;

	int l=1,r=n;
	ll cl=-1,cr=-1;

	ll cost=0;

	while(max>min){
		if(cl==-1){
			while(a[l]==min){
				cl++;
				l++;
			}
			dmin=a[l]-min;
			nmin=a[l];
			cl=(l-1)*(dmin);
		}
		if(cr==-1){
			while(a[r]==max){
				cr--;
				r--;
			}
			dmax=max-a[r];
			nmax=a[r];
			cr=(n-r)*(dmax);
		}
		DEBUG("cost=%d\n",cost);
		DEBUG("l=%d, r=%d, cl=%d, cr=%d\n",l,r,cl,cr);
		DEBUG("dmin=%d, dmax=%d, min=%d, max=%d\n\n",dmin,dmax,min,max);
		if(l<(n-r+1)&&cost+cl<=k){
			if(cost+cl>k)
				break;
			cost+=cl;
			cl=-1;
			min=nmin;
		}else{
			if(cost+cr>k)
				break;
			cost+=cr;
			cr=-1;
			max=nmax;
		}
	}
	DEBUG("cost=%d, min=%d, max=%d\n",cost,min,max);

	if(min<max){
		cl=(l-1);
		cr=(n-r+1);
		DEBUG("l=%d, r=%d, cl=%d, cr=%d\n",l,r,cl,cr);
		DEBUG("dmin=%d, dmax=%d, min=%d, max=%d\n\n",dmin,dmax,min,max);
		if(cl<cr){
			ll d=(k-cost)/cl;
			cost+=d*cl;
			min+=d;
		}else{
			ll d=(k-cost)/cr;
			cost+=d*cr;
			max-=d;
		}
	}

	cout<<max-min<<endl;


	return 0;
}


