#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <set>
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

#if __cplusplus >= 201100
template<typename Type, typename... Args>
void read(Type& t, Args&... args){
	read(t);
	read(args...);
}
#endif

const int MaxN=1e5+10;
const int MaxM=3e5+10;

int n,m;

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
	if(x==y)
		return;
	p[x]+=p[y];
	p[y]=x;
}

set<int> e[MaxN];





int main(int argc, char* argv[]) {

	memset(p,-1,sizeof(p));

	read(n);read(m);

	for(int i=1;i<=m;i++){
		int x,y;
		read(x);read(y);
		e[x].insert(y);
		e[y].insert(x);
	}

	for(int i=1;i<=n;i++){
		if(p[i]==-1){
			for(int j=1;j<=n;j++){
				if(e[i].find(j)==e[i].end())
					setunion(i,j);
			}
		}
	}

	int cnt=0;
	vector<int> rs;
	for(int i=1;i<=n;i++){
		if(p[i]<0){
			rs.push_back(i);
			cnt++;
		}
	}

	if(cnt!=3){
		printf("-1\n");
		return 0;
	}

	for(int i=1;i<=n;i++){
		for(int j:e[i]){
			if(setfind(i)==setfind(j)){
				printf("-1\n");
				return 0;
			}
		}
	}

	if(m!=p[rs[0]]*p[rs[1]]+p[rs[1]]*p[rs[2]]+p[rs[2]]*p[rs[0]]){
		printf("-1\n");
		return 0;
	}

	for(int i=1;i<=n;i++){
		int ans=-1;

		if(setfind(i)==rs[0])
			ans=1;
		else if(setfind(i)==rs[1])
			ans=2;
		else if(setfind(i)==rs[2])
			ans=3;
		
		if(i==1)
			printf("%d",ans);
		else
			printf(" %d",ans);
	}

	printf("\n");

	return 0;
}


