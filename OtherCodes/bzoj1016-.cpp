#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <map>
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

edge e0[MaxM];

bool cmp(edge x,edge y){
	return x.len<y.len;
}

map<int,int> lenid;
edge e[MaxM][MaxM];
int tc,ec[MaxM];
edge idce[MaxM][MaxM];
int idcnt[MaxM];

int p[MaxN];
int p0;

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



int main(int argc, char* argv[]) {

	read(n);read(m);
	for(int i=1;i<=m;i++){
		read(e0[i].u);read(e0[i].v);read(e0[i].len);
	}

	sort(e0+1,e0+m+1,cmp);

	tc=1;
	for(int i=1;i<=m;i++){
		if(i==1||e0[i-1].len==e0[i].len)
			e[tc][++ec[tc]]=e0[i];
		else{
			tc++;
			e[tc][++ec[tc]]=e0[i];
		}
	}
	for(int i=1;i<=tc;i++)
		lenid[e[i][1].len]=i;

	int kcnt=n;
	memset(p,-1,sizeof(p));
	for(int i=1;i<=m&&kcnt>1;i++){
		int u=e0[i].u,v=e0[i].v;
		int len=e0[i].len;
		if(setfind(u)!=setfind(v)){
			setunion(u,v);
			idcnt[lenid[len]]++;
			kcnt--;
		}
	}

	int ans=1;

	for(int i=1;i<=tc;i++){
		memset(p,-1,sizeof(p));
		for(int j=1;j<=tc;j++){
			if(j!=i){
				for(int k=1;k<=ec[j];k++)
					setunion()
			}
		}
	}


	return 0;
}


