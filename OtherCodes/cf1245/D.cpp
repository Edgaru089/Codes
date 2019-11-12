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
const int MaxN=2000+10;

int n;
ll x[MaxN],y[MaxN];
ll c[MaxN],k[MaxN];


struct edge{
	edge()=default;
	edge(int u,int v,ll len):u(u),v(v),len(len){}
	int u,v;
	ll len;
};

vector<edge> e;
vector<edge> ea;
ll ans;
int cnt;

int p[MaxN];

int setfind(int x){
	if(p[x]<0)
		return x;
	else
		return p[x]=setfind(p[x]);
}

void setunion(int x,int y){
	x=setfind(x);
	y=setfind(y);
	if(x!=y){
		p[x]+=p[y];
		p[y]=x;
	}
}

template<typename Int>
Int iabs(Int x){
	return x>0?x:-x;
}



int main(int argc, char* argv[]) {

	read(n);
	for(int i=1;i<=n;i++){
		read(x[i]);
		read(y[i]);
	}
	for(int i=1;i<=n;i++)
		read(c[i]);
	for(int i=1;i<=n;i++)
		read(k[i]);

	for(int i=1;i<=n;i++){
		e.push_back(edge(0,i,c[i]));
		for(int j=1;j<i;j++)
			e.push_back(edge(i,j,(iabs(x[i]-x[j])+iabs(y[i]-y[j]))*(k[i]+k[j])));
	}

	sort(e.begin(),e.end(),[](edge x,edge y)->bool{
		return x.len<y.len;
	});

	memset(p,-1,sizeof(p));

	int pcnt=0;
	for(auto i:e){
		int u=i.u,v=i.v;
		int len=i.len;
		if(setfind(u)!=setfind(v)){
			setunion(u,v);
			ea.push_back(i);
			ans+=len;
			if(u==0)
				cnt++;
			pcnt++;
			if(pcnt==n)
				break;
		}
	}

	cout<<ans<<endl;
	cout<<cnt<<endl;
	bool first=true;
	for(auto i:ea){
		if(i.u==0)
			if(first){
				first=false;
				cout<<i.v;
			}
			else
				cout<<' '<<i.v;
	}
	if(!first)
		cout<<endl;
	cout<<ea.size()-cnt<<endl;
	first=true;
	for(auto i:ea)
		if(i.u!=0){
			first=false;
			cout<<i.u<<' '<<i.v<<endl;
		}
	if(!first)
		cout<<endl;

	return 0;
}


