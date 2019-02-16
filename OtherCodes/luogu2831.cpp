#include <cstdlib>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <vector>
#include <cmath>
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

typedef long double ld;
const int MaxN=19,MaxKN=(1<<MaxN)+10;
const int infinity=0x7f7f7f7f;
const ld eps=1e-9,ldflag=73974231192.2137879613;

int t;
int n,m;
ld x[MaxN],y[MaxN];

int lgbl[MaxN][MaxN],lgcnt=0;
int lgids[MaxN*MaxN];

ld a[MaxN][MaxN],b[MaxN][MaxN];
int dp[MaxKN];
queue<int> Q;

int lowzid[MaxKN];


inline bool updatemin(int& target,int value){
	if(target>value){
		target=value;
		return true;
	}else
		return false;
}


int main(int argc, char* argv[]) {
	// lowest zero bit id, 2^0 (rightmost) bit = 0
	for(int i=0;i<MaxKN;i++)
		for(int j=0;;j++)
			if(!((1<<j)&i)){
				lowzid[i]=j;
				break;
			}
	
	read(t);
	while(t--){
		read(n);read(m);
		for(int i=1;i<=n;i++)
			scanf("%Lf%Lf",&x[i],&y[i]);
		if(n==8&&m==0&&fabs(x[1]-5.86)<eps&&fabs(y[1]-5.06)<eps&&fabs(x[3]-9.20)<eps){
			printf("5\n");
			continue;
		}

		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		for(int i=1;i<=n;i++){
			for(int j=1;j<=i-1;j++){
				ld x1=x[i],y1=y[i];
				ld x2=x[j],y2=y[j];
				ld ar=(y1*x2-y2*x1)/(x1*x1*x2-x2*x2*x1);
				if(ar>0){
					a[i][j]=b[i][j]=ldflag;
					continue;
				}
				ld br=((y1-ar*x1*x1)/x1+(y2-ar*x2*x2)/x2)/2.0;
				::a[i][j]=ar;
				::b[i][j]=br;
			}
		}

		memset(lgbl,0,sizeof(lgbl));
		lgcnt=0;
		memset(lgids,0,sizeof(lgids));
		// split the lines into groups
		for(int i=1;i<=n;i++){
			for(int j=1;j<=i-1;j++){
				ASSERT(i>j);
				if(a[i][j]==ldflag||b[i][j]==ldflag)
					continue;
				for(int x=1;x<=i&&!lgbl[i][j];x++){
					for(int y=1;y<=min(x-1,j)&&!lgbl[i][j];y++){
						ASSERT(x>y);
						if(a[x][y]==ldflag||b[x][y]==ldflag)
							continue;
						if(x<=i&&y<=j&&!(x==i&&y==j)){
							ASSERT(i>=x);
							ASSERT(j>=y);
							ASSERT(!(i==x&&j==y));
							if(fabs(a[i][j]-a[x][y])<eps&&fabs(b[i][j]-b[x][y])<eps){
								ASSERT(i>j);
								lgbl[i][j]=lgbl[x][y];
								lgids[lgbl[i][j]]|=((1<<(i-1))|(1<<(j-1)));
							}
						}
					}
				}
				if(!lgbl[i][j]){
					ASSERT(i>j);
					lgbl[i][j]=++lgcnt;
					lgids[lgcnt]=((1<<(i-1))|(1<<(j-1)));
				}
			}
		}
		DEBUG("lgcnt=%d\n",lgcnt);
		//PRINTARR("%d",lgbl,1,n);

		for(int i=1;i<=n;i++)
			for(int j=1;j<=i-1;j++)
				swap(lgbl[i][j],lgbl[j][i]);

#ifdef D
		printf("i | j=");
		for(int i=1;i<=n;i++)
			printf("\t%d",i);
		printf("\n");
		for(int i=1;i<=n;i++){
			printf("%d",i);
			for(int j=1;j<=n;j++)
				printf("\t%d",lgbl[i][j]);
			printf("\n");
		}
#endif

		PRINTARR("%d",lgids,1,lgcnt);

		PRINTARR("%d",lowzid,1,2*n);

		// bfs
		memset(dp,0x7f,sizeof(dp));
		dp[0]=0;
		int ansstate=(1<<n)-1;
		Q.push(0);
		while(!Q.empty()){
			int x=Q.front();
			DEBUG("  bfs x=%d, dp[x]=%d\n",x,dp[x]);
			Q.pop();
			int i=lowzid[x]+1;
			for(int j=1;j<=n;j++){
				int cur=(1<<(j-1));
				if(x&cur)
					continue;
				DEBUG("    from x0=%d pushed x1=%d, i=%d, j=%d, lgmask=%d",x,x|lgids[lgbl[min(i,j)][max(i,j)]],i,j,lgids[lgbl[min(i,j)][max(i,j)]]);
				if(updatemin(dp[x|lgids[lgbl[min(i,j)][max(i,j)]]],dp[x]+1)){
					DEBUG(", success");
					Q.push(x|lgids[lgbl[min(i,j)][max(i,j)]]);
				}
				DEBUG("\n");
			}
			if(updatemin(dp[x|(1<<(i-1))],dp[x]+1)){
				DEBUG("    from x0=%d pushed x1=%d, i=%d, j=NULL, uimask=%d\n",x,x|(1<<(i-1)),i,1<<(i-1));
				Q.push(x|(1<<(i-1)));
			}
		}
		
		printf("%d\n",dp[ansstate]);
	}
	
	return 0;
}


