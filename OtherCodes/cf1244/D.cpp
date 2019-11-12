#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
#include <list>
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
const int MaxN=100000+10;

int n;
int deg[MaxN];

struct st{
	int c[3];
	int dep;
	int id;
};

st s[MaxN];

vector<int> e[MaxN];

void addedge(int u,int v){
	e[u].push_back(v);
	e[v].push_back(u);
}

bool cmp(const st& x,const st& y){
	return x.dep<y.dep;
}

void dfs(int u,int from,int st){
	s[u].dep=st;
	for(int v:e[u])
		if(v!=from)
			dfs(v,u,st+1);
}

ll dp[MaxN][3][3];

int ans0[MaxN],ansa[MaxN];


int main(int argc, char* argv[]) {

	read(n);
	for(int i=1;i<=n;i++)
		read(s[i].c[0]);
	for(int i=1;i<=n;i++)
		read(s[i].c[1]);
	for(int i=1;i<=n;i++)
		read(s[i].c[2]);

	for(int i=1;i<=n-1;i++){
		int u,v;
		read(u);read(v);
		deg[u]++;
		deg[v]++;
		addedge(u,v);
	}

	int root=-1;
	for(int i=1;i<=n;i++){
		if(deg[i]>=3){
			printf("-1\n");
			return 0;
		}
		if(root==-1&&deg[i]==1){
			dfs(i,0,1);
			root=i;
		}
		s[i].id=i;
	}

	sort(s+1,s+n+1,cmp);

#define C(x,y) s[x].c[y]
	for(int i=1;i<=n;i++){
		dp[i][0][1]=dp[i-1][2][0]+C(i,1);
		dp[i][0][2]=dp[i-1][1][0]+C(i,2);
		dp[i][1][0]=dp[i-1][2][1]+C(i,0);
		dp[i][1][2]=dp[i-1][0][1]+C(i,2);
		dp[i][2][0]=dp[i-1][1][2]+C(i,0);
		dp[i][2][1]=dp[i-1][0][2]+C(i,1);
	}

	ll ans=1000000000000000ll;
	int st[3];
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			if(dp[n][i][j]>0){
				if(ans>dp[n][i][j]){
					st[0]=j+1;
					st[1]=i+1;
					st[2]=(3-i-j)+1;
					ans=min(ans,dp[n][i][j]);
				}
			}

	cout<<ans<<endl;


	for(int i=n;i>=1;i--)
		ans0[i]=st[(n-i)%3];

	for(int i=1;i<=n;i++)
		ansa[s[i].id]=ans0[i];

	bool first=true;
	for(int i=1;i<=n;i++)
		if(first){
			first=false;
			printf("%d",ansa[i]);
		}else
			printf(" %d",ansa[i]);
	printf("\n");

	return 0;
}


