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

const int MaxN=1e3+10,MaxM=1e3+10;

int n,m;
int tx[MaxN];
int a[MaxN];

int p[MaxN];

int t[MaxN];
int x[MaxN],y[MaxN];

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
	memset(p,-1,sizeof(p));

	read(n);read(m);

	bool flag=true;
	for(int i=1;i<=m&&flag;i++){
		read(t[i]);read(x[i]);read(y[i]);
		
		if(t[i]==1){
			for(int j=x[i];j<=y[i];j++)
				if(tx[j]!=0)
					setunion(tx[j],i);
			for(int j=x[i];j<=y[i];j++)
				tx[j]=i;
		}
	}

	for(int i=1;i<=m&&flag;i++){
		if(t[i]==0){
			bool ok=false;
			for(int j=x[i];j<=y[i]&&!ok;j++)
				if(tx[j]==0||(setfind(tx[j-1])!=setfind(tx[j])))
					ok=true;
			if(!ok)
				flag=false;
		}
	}

	if(!flag)
		printf("NO\n");
	else{
		printf("YES\n");

		PRINTARR("%d",tx,1,n);

		a[1]=10000;
		for(int i=2;i<=n;i++){
			if(tx[i]==0||(setfind(tx[i-1])!=setfind(tx[i])))
				a[i]=a[i-1]-1;
			else
				a[i]=a[i-1]+1;
		}
		
		printf("%d",a[1]);
		for(int i=2;i<=n;i++)
			printf(" %d",a[i]);
		printf("\n");
	}




	return 0;
}


