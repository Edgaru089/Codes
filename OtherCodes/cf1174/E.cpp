#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <cmath>

#ifdef D
#include <custom/Debug.hpp>
#endif

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
#define PRINT(...) dbg(__VA_ARGS__)
#define PRINTVAL(...) dbgv(__VA_ARGS__)
#define PRINTSEQ(...) dbgr(__VA_ARGS__)
#define PRINTSEQVAL(...) dbgm(__VA_ARGS__)
#define PRINTCOMPACT(...) dbgs(__VA_ARGS__)
#else
#define DEBUG(...)
#define PRINTARR(a, b, c, d)
#define PRINTARR2D(a, b, c, d, e, f)
#define PASS
#define ASSERT(expr)
#define PRINT(...)
#define PRINTVAL(...)
#define PRINTSEQ(...)
#define PRINTSEQVAL(...)
#define PRINTCOMPACT(...)
#endif

#define FOR(i, first, last)               for(int i = (first); i <= (last); ++i)
#define ROF(i, last, first)               for(int i = (last); i >= (first); --i)
#define FORSTEP(i, first, last, step)     for(int i = (first); i <= (last); i += (step))
#define ROFSTEP(i, last, first, stepabs)  for(int i = (last); i >= (first); i -= (stepabs))

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

// End of template:edgar:edgar-laptop(LAPTOP-EDGAR-15)

typedef long long ll;
const ll Mod=1e9+7;
const int MaxN=1e6+10,MaxLogN=21;

int n;

int dp[MaxN][MaxLogN][2];

ll f(int j,int k){
	return (k)?(n/((1<<j)*3)):(n/(1<<j));
}


int hlog2(int x){
	int ans=31;
	while(ans>=0&&!(x&(1<<ans)))
		ans--;
	return ans;
}


int main(int argc, char* argv[]) {

	DEBUG("sizeof(dp[][][])=%lldBytes=%.2lfMiB\n",(ll)sizeof(dp),(double)(sizeof(dp))/1024.0/1024.0);

	read(n);

	//int lim=floor(log2(n));
	int lim=hlog2(n);
	DEBUG("lim=%d\n",lim);
	dp[1][lim][0]=1;
	if((1<<lim-1)*3<=n)
		dp[1][lim-1][1]=1;

	FOR(i,1,n){
		FOR(j,0,lim)
			FOR(k,0,1){
				dp[i+1][j][k]=(dp[i+1][j][k]+(ll)dp[i][j][k]*(f(j,k)-i))%Mod;
				dp[i+1][j-1][k]=(dp[i+1][j-1][k]+(ll)dp[i][j][k]*(f(j-1,k)-f(j,k)))%Mod;
				if(k)
					dp[i+1][j][k-1]=(dp[i+1][j][k-1]+(ll)dp[i][j][k]*(f(j,k-1)-f(j,k)))%Mod;
			}
	}

	cout<<dp[n][0][0]<<endl;

	return 0;
}

// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP

