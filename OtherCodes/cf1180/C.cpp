#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <string>
#include <deque>
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
#define ROFSTEP(i, last, first, stepabs)  for(int i = (last); i >= (first); i -= (step))

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
const ll MaxN=1e5+10,MaxQ=3e5+10;

ll n,q;
ll a[MaxN];
ll mx;

pair<ll,ll> s[MaxQ];
deque<ll> d;
pair<ll,ll> ans[MaxQ];

ll t[MaxN];



int main(int argc, char* argv[]) {

	read(n);read(q);
	FOR(i,1,n){
		read(a[i]);
		mx=max(mx,a[i]);
		d.push_back(a[i]);
	}
	FOR(i,1,q){
		read(s[i].first);
		s[i].second=i;
	}

	sort(s+1,s+q+1);

	ll j=1;
	ll st=0;
	FOR(i,1,n){
		st++;
		ll x=d.front();
		d.pop_front();
		ll y=d.front();
		d.pop_front();
		while(s[j].first==i)
			ans[s[j++].second]=make_pair(x,y);
		
		d.push_front(max(x,y));
		d.push_back(min(x,y));
		if(max(x,y)==mx)
			break;
	}

	d.pop_front();
	//d.push_back(d.front());
	//d.pop_front();
	d.push_front(d.back());
	d.pop_back();

	FOR(i,1,n-1)
		t[i]=d[i-1];

	FOR(i,j,q){
		ans[s[i].second]=make_pair(mx,t[(s[i].first-(st))%(n-1)+1]);
	}

	FOR(i,1,q)
		printf("%lld %lld\n",ans[i].first,ans[i].second);

	return 0;
}


// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP

