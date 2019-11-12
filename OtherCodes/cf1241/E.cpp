#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
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
const ll MaxN=5e5+10;

ll q;
ll n,k;

struct st{
	st(){}
	st(ll v,ll w):v(v),w(w){}
	ll v,w;
};

vector<st> e[MaxN];

void addedge(ll u,ll v,ll w){
	e[u].push_back(st(v,w));
	e[v].push_back(st(u,w));
}

ll fa[MaxN];
void dfs0(ll u,ll from=0){
	DEBUG("dfs0(u=%d, from=%d)\n",u,from);
	fa[u]=from;
	for(auto s:e[u]){
		ll v=s.v,w=s.w;
		if(v!=from)
			dfs0(v,u);
	}
}

ll dp[MaxN][2];
void dfs(ll u){
	DEBUG("dfs(u=%d)\n",u);
	vector<ll> vec;
	ll ans=0;
	for(auto s:e[u]){
		ll v=s.v,w=s.w;
		if(v!=fa[u]){
			dfs(v);
			ans+=dp[v][0];
			vec.push_back(dp[v][1]+w-dp[v][0]);
		}
	}
	sort(vec.begin(),vec.end(),greater<ll>());
	for(ll i=0;i<min(k-1,(ll)vec.size());i++)
		if(vec[i]>0)
			ans+=vec[i];
		else
			break;
	dp[u][0]=dp[u][1]=ans;
	if(vec.size()>=k&&vec[k-1]>0)
		dp[u][0]+=vec[k-1];
}




int main(int argc, char* argv[]) {

	read(q);
	while(q--){

		read(n);read(k);
		
		for(ll i=1;i<=n;i++){
			e[i].clear();
			e[i].shrink_to_fit();
		}

		for(ll i=1;i<=n-1;i++){
			ll u,v,w;
			read(u);read(v);read(w);
			addedge(u,v,w);
		}

		dfs0(1);
		dfs(1);

		PRINTARR2D("%d",dp,1,n,0,2);

		printf("%I64d\n",dp[1][0]);

	}

	return 0;
}


