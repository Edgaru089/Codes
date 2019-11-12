#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
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
const int MaxN=1e5+10;

int n;
ll a[MaxN];
int cnt[70];

vector<int> e[200];
vector<pair<int,int>> es;

void addedge(int u,int v){
	DEBUG("addedge(%d, %d)\n",u,v);
	e[u].push_back(v);
	e[v].push_back(u);
	es.push_back(make_pair(min(u,v),max(u,v)));
}

int step[MaxN];
int ans=10000000;

int ban_s,ban_l;

int bfs_dis(int x,int y){
	int dis[200];
	queue<int> Q;
	memset(dis,-1,sizeof(dis));
	Q.push(x);
	dis[x]=0;
	while(!Q.empty()){
		int u=Q.front();
		Q.pop();
		for(int v:e[u]){
			if(ban_s!=min(u,v)||ban_l!=max(u,v)){
				if(dis[v]==-1){
					dis[v]=dis[u]+1;
					Q.push(v);
				}
			}
		}
	}
	if(dis[y]==-1)
		return 10000000;
	else
		return dis[y];
}



int main(int argc, char* argv[]) {
	memset(step,-1,sizeof(step));

	read(n);
	for(int i=1;i<=n;i++)
		read(a[i]);

	sort(a+1,a+n+1,greater<ll>());
	n=lower_bound(a+1,a+n+1,0,greater<ll>())-a;

	for(int i=1;i<=n;i++){
		int j=0;
		ll x=a[i];
		while(x){
			if(x&1)
				cnt[j]++;
			x>>=1;
			j++;
		}
	}

	for(int i=0;i<70;i++){
		if(cnt[i]>=3){
			printf("3\n");
			return 0;
		}
	}



	for(int i=1;i<n;i++){
		if(!a[i])
			continue;
		for(int j=i+1;j<=n;j++){
			if(a[i]&a[j])
				addedge(i,j);
		}
	}

	for(auto&[x,y]:es){
		ban_s=x;
		ban_l=y;
		ans=min(ans,bfs_dis(x,y)+1);
	}

	if(ans==10000000)
		ans=-1;

	printf("%d\n",ans);


	return 0;
}


