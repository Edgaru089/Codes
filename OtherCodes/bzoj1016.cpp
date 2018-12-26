#include <cstdlib>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <cstdio>
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

const int MaxN=100+10,MaxM=1000+10;
const int Mod=31011;

int n,m;
struct edge{
	int u,v;
	int len;
};

edge e[MaxM],ec[MaxN],el[MaxN];

int p[MaxN];

int setfind(int x,bool compress=true){
	if(p[x]<0)
		return x;
	else{
		if(compress)
			return p[x]=setfind(p[x]);
		else
			return setfind(p[x]);
	}
}

void setunion(int x,int y){
	x=setfind(x);
	y=setfind(y);
	if(x!=y){
		p[x]+=p[y];
		p[y]=x;
	}
}

bool cmp(const edge& x,const edge& y){
	return x.len<y.len;
}

int sum;
int len,lcnt;
void dfs(int i,int bcnt){
	if(i>=lcnt+1||bcnt<=1){
		if(bcnt==1)
			sum++;
		return;
	}
	int u=el[i].u,v=el[i].v;
	if(setfind(u,false)!=setfind(v,false)){
		int ru=setfind(u,false),rv=setfind(v,false);
		int pu=p[ru],pv=p[rv];
		setunion(ru,rv);
		dfs(i+1,bcnt-1);
		p[ru]=pu;
		p[rv]=pv;
	}
	dfs(i+1,bcnt);
}


int main(int argc, char* argv[]) {
	
	read(n);read(m);
	for(int i=1;i<=m;i++){
		read(e[i].u);read(e[i].v);read(e[i].len);
	}

	memset(p,-1,sizeof(p));
	sort(e+1,e+m+1,cmp);
	int cnt=0;
	for(int i=1;i<=m;i++){
		int u=e[i].u,v=e[i].v,len=e[i].len;
		if(setfind(u)!=setfind(v)){
			setunion(u,v);
			ec[++cnt]=e[i];
		}
	}
	PRINTARR("%d",p,1,n);
#ifdef DEBUG
	for(int i=1;i<=cnt;i++)
		printf("%d %d %d\n",ec[i].u,ec[i].v,ec[i].len);
#endif
	PASS;
	if(cnt<n-1)
		printf("0\n");
	else{
		PASS;
		DEBUG("Begin of algorithm\n");
		int ans=1;
		ec[cnt+1].len=ec[0].len=-1;
		int j=1;
		for(int i=1;i<=n&&j<=cnt;){
			PASS;

			len=ec[j++].len;
			lcnt=0;
			DEBUG("Loop starting, i=%d, j=%d, len=%d",i,j,len);

			while(e[i].len!=len)
				i++;
			while(e[i].len==len)
				el[++lcnt]=e[i++];
			DEBUG(", lcnt=%d",lcnt);
			
			memset(p,-1,sizeof(int)*(n+3));
			for(int i=1;i<=cnt;i++)
				if(ec[i].len!=len)
					setunion(ec[i].u,ec[i].v);
			
			int bcnt=0;
			for(int i=1;i<=n;i++)
				if(p[i]<0)
					bcnt++;
			DEBUG(", bcnt=%d",bcnt);
			
			sum=0;
			dfs(1,bcnt);
			DEBUG(", sum=%d\n",sum);
			ans=(ans*sum)%Mod;
#ifdef DEBUG
			for(int i=1;i<=lcnt;i++)
				printf("%d %d %d\n",el[i].u,el[i].v,el[i].len);
#endif

			while(ec[j].len==ec[j-1].len)
				j++;
		}
		printf("%d\n",ans);
	}
	
	
	return 0;
}


