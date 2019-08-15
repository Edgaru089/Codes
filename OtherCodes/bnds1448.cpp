#include <cstdlib>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <queue>
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

int iabs(int x){
	return (x>0)?x:(-x);
}

const int MaxN=20+5;

int n,m,k;

struct st{
	st(){}
	st(int x,int y,int a):x(x),y(y),a(a){}
	int x,y;
	int a;
};

struct stcmp{
	bool operator () (const st& l,const st& r)const{
		return l.a<r.a;
	}
};

priority_queue<st,vector<st>,stcmp> Q;




int main(int argc, char* argv[]) {

	read(n);read(m);read(k);

	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int a;
			read(a);
			if(a==0)
				continue;
			Q.push(st(i,j,a));
		}
	}

	int x=Q.top().x,y=Q.top().y,a=Q.top().a;
	int ans=0;
	Q.pop();
	if(k<2*x+1){
		printf("0\n");
		return 0;
	}
	ans+=a;
	k-=x+1;

	DEBUG("Init: k=%d, ans=%d\n",k,ans);

	while(!Q.empty()){
		int nx=Q.top().x,ny=Q.top().y;
		a=Q.top().a;
		Q.pop();
		int dis=(iabs(x-nx)+iabs(y-ny));
		if(k<dis+nx+1)
			break;
		k-=dis+1;
		ans+=a;
		x=nx;y=ny;
		DEBUG("Round: nx=%d, ny=%d, Na=%d, dis=%d, Nk=%d, Nans=%d\n",nx,ny,a,dis,k,ans);
	}

	printf("%d\n",ans);



	return 0;
}

/*
6 7 21
0 0 0 0 0 0 0
0 0 0 0 13 0 0
0 0 0 0 0 0 7
0 15 0 0 0 0 0
0 0 0 9 0 0 0
0 0 0 0 0 0 0
--------------
37
*/

/*
6 7 20
0 0 0 0 0 0 0
0 0 0 0 13 0 0
0 0 0 0 0 0 7
0 15 0 0 0 0 0
0 0 0 9 0 0 0
0 0 0 0 0 0 0
--------------
28
*/


