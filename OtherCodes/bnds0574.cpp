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

template<typename IntType>
inline void println(IntType val) {
	if (val == 0)
		putchar('0');
	if (val < 0) {
		putchar('-');
		val = -val;
	}
	char buf[16], *buftop = buf + 15;
	while (val > 0) {
		*buftop = (val % 10 + '0');
		buftop--;
		val /= 10;
	}
	for (buftop++; buftop <= buf + 15; buftop++)
		putchar(*buftop);
	putchar('\n');
}

typedef __int128 ll;

const int MaxN=10000+10;

int t;
int n;

bool flag[MaxN];
int p[MaxN],pcnt;

void sieve(){
	const int n=10000+3;
	for(int i=2;i<=n;i++)
		flag[i]=true;
	for(int i=2;i<=n;i++){
		if(flag[i])
			p[++pcnt]=i;
		for(int j=1;j<=pcnt;j++){
			if(i%p[j]==0||i*p[j]>n)
				break;
			flag[i*p[j]]=false;
		}
	}
}

int cnt[MaxN];

int ans[MaxN];
int alen;

void multiply(int x){
	for(int i=1;i<=alen;i++)
		ans[i]*=x;
	for(int i=1;i<=alen;i++){
		ans[i+1]+=ans[i]/10;
		ans[i]%=10;
	}
	while(ans[alen+1]){
		alen++;
		ans[alen+1]+=ans[alen]/10;
		ans[alen]%=10;
	}
}

void printans(){
	for(int i=alen;i>=1;i--)
		printf("%d",ans[i]);
	printf("\n");
}



int main(int argc, char* argv[]) {

	sieve();

	read(t);
	while(t--){
		read(n);

		memset(cnt,0,sizeof(cnt));
		for(int x=1;x<=n;x++){
			int xi=x;
			for(int i=1;i<=pcnt;i++){
				if(xi==1)
					break;
				while(xi%p[i]==0){
					cnt[i]++;
					xi/=p[i];
				}
			}
		}

		memset(ans,0,sizeof(ans));
		ans[1]=1;
		alen=1;
		for(int i=1;i<=pcnt;i++){
			if(cnt[i]==0)
				continue;
			multiply(cnt[i]*2+1);
			PRINTARR("%d",cnt,1,alen);
		}

		printans();
	}





	return 0;
}


