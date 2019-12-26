#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <string>
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

#define FOR(i, first, last)               for(int i = (first); i <= (last); ++i)
#define ROF(i, last, first)               for(int i = (last); i >= (first); --i)
#define FORSTEP(i, first, last, step)     for(int i = (first); i <= (last); i += (step))
#define ROFSTEP(i, last, first, stepabs)  for(int i = (last); i >= (first); i -= (step))

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

const int MaxN=50+10;

int n;
string str;
int a[MaxN][MaxN];
int l[MaxN][MaxN],c[MaxN][MaxN];

int dp[MaxN][MaxN][MaxN][MaxN];

int dfs(int xs,int ys,int xt,int yt){
	DEBUG("dfs(s=[%d,%d], t=[%d,%d])\n",xs,ys,xt,yt);
	if(xs>xt||ys>yt)
		return 0;
	if(dp[xs][ys][xt][yt]>=0)
		return dp[xs][ys][xt][yt];

	dp[xs][ys][xt][yt]=max(xt-xs+1,yt-ys+1);

	FOR(i,xs,xt)
		if(l[i][yt]-l[i][ys-1]==0)
			dp[xs][ys][xt][yt]=min(dp[xs][ys][xt][yt],
			                       dfs(xs,ys,i-1,yt)+dfs(i+1,ys,xt,yt));
	FOR(i,ys,yt)
		if(c[xt][i]-c[xs-1][i]==0)
			dp[xs][ys][xt][yt]=min(dp[xs][ys][xt][yt],
			                       dfs(xs,ys,xt,i-1)+dfs(xs,i+1,xt,yt));
	return dp[xs][ys][xt][yt];
}


int main(int argc, char* argv[]) {

	read(n);
	FOR(i,1,n){
		read(str);
		FOR(j,1,n){
			a[i][j]=(str[j-1]=='#');
			l[i][j]=l[i][j-1]+a[i][j];
			c[i][j]=c[i-1][j]+a[i][j];
		}
	}

	PRINTARR2D("%d",l,1,n,1,n);
	PRINTARR2D("%d",c,1,n,1,n);

	memset(dp,-1,sizeof(dp));

	printf("%d\n",dfs(1,1,n,n));




	return 0;
}


// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP

