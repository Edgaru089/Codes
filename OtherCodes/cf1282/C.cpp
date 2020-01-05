#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
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
const ll MaxN=2e5+10;

ll l;
ll n,t,a,b;
ll ac,bc;

struct px{
	ll e,t;
	ll tr;
};

px x[MaxN];

bool cmp(px x,px y){
	return x.t<y.t;
}

vector<ll> ts;

int main(int argc, char* argv[]) {

	read(l);
	while(l--){
		ac=bc=0;

		read(n);read(t);read(a);read(b);
		FOR(i,1,n){
			read(x[i].e);
			if(x[i].e==0){
				x[i].tr=a;
				ac++;
			}else{
				x[i].tr=b;
				bc++;
			}
		}
		FOR(i,1,n)
			read(x[i].t);

		sort(x+1,x+n+1,cmp);

		ts.clear();
		FOR(i,1,n)
			if(i==1||x[i].t!=x[i-1].t)
				ts.push_back(x[i].t);
		ts.push_back(t+1);

		ll ta=0;
		ll j=1;
		ll ans=0;
		FOR(i,0,ts.size()-1){
			ll te=ts[i]-1;
			while(j<=n&&x[j].t<=te){
				ta+=x[j].tr;
				if(x[j].e==0)
					ac--;
				else
					bc--;
				j++;
			}
			ll cur=j-1;
			if(ta>te)
				continue;
			te-=ta;
			ll delta=min(ac,te/a);
			cur+=delta;
			te-=delta*a;
			delta=min(bc,te/b);
			cur+=delta;
			te-=delta*b;
			ans=max(ans,cur);
		}

		printf("%d\n",(int)ans);
	}

	return 0;
}


// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP

