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

typedef long long ll;
const int MaxN=1000+10;

int n,m;
int a[2][MaxN][MaxN];
int s[2][MaxN][MaxN];

int popcount(int x){
	int ans=0;
	while(x){
		if(x&1)
			ans++;
		x>>=1;
	}
	return ans;
}

ll xsum(int x,int y){
	if(x<=0||y<=0)
		return 0;
	ll cx=(ll)x*y;
	ll ans=cx/2*(s[0][n][m]+s[1][n][m]);
	if(cx&1)
		if((popcount(x-1)+popcount(y-1))&1)
			ans+=s[1][n][m];
		else
			ans+=s[0][n][m];
	DEBUG("xsum(%d,%d) = %lld\n",x,y,ans);
	return ans;
}


ll psum(int x,int y){
	if(x<=0||y<=0)
		return 0;
	ll ans=xsum(x/n,y/m);
	if(x%n)
		if((y/m)&1)
			ans+=(ll)(y/m/2)*(s[0][x%n][m]+s[1][x%n][m])+s[(popcount(x/n)+popcount(y/m-1))&1][x%n][m];
		else
			ans+=(ll)(y/m/2)*(s[0][x%n][m]+s[1][x%n][m]);
	if(y%m)
		if((x/n)&1)
			ans+=(ll)(x/n/2)*(s[0][n][y%m]+s[1][n][y%m])+(s[(popcount(y/m)+popcount(x/n-1))&1][n][y%m]);
		else
			ans+=(ll)(x/n/2)*(s[0][n][y%m]+s[1][n][y%m]);

	if((x%n)&&(y%m))
		ans+=s[(popcount(x/n)+popcount(y/m))&1][x%n][y%m];

	DEBUG("psum(%d,%d) = %lld\n",x,y,ans);
	return ans;
}

ll ans(int a,int b,int x,int y){
	return psum(x,y)-psum(x,b-1)-psum(a-1,y)+psum(a-1,b-1);
}


int q;


int main(int argc, char* argv[]) {

	read(n);read(m);read(q);
	string str;
	FOR(i,1,n){
		read(str);
		FOR(j,1,m){
			a[0][i][j]=str[j-1]-'0';
			a[1][i][j]=1-a[0][i][j];
			s[0][i][j]=s[0][i-1][j]+s[0][i][j-1]-s[0][i-1][j-1]+a[0][i][j];
			s[1][i][j]=s[1][i-1][j]+s[1][i][j-1]-s[1][i-1][j-1]+a[1][i][j];
			ASSERT(s[1][i][j]==i*j-s[0][i][j]);
		}
	}

	FOR(i,1,q){
		int a,b,x,y;
		read(a);read(b);read(x);read(y);
		printf("%lld\n",ans(a,b,x,y));
	}





	return 0;
}


// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP

