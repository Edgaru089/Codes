#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>

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
#if __cplusplus >= 201103
template<typename IntType,typename... Args>
void read(IntType& val, Args&... args){
	read(val); read(args...);
}
#endif

// End of template:edgar:edgar-laptop(LAPTOP-EDGAR-15)

const int MaxN=1000+10;

int n,m;
int h[MaxN][MaxN];

struct st{
	int x,y;
	int h;
	int id;
	bool city;
};

st a[MaxN*MaxN];

bool pump[MaxN*MaxN];

int p[MaxN*MaxN];
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

	pump[y]|=pump[x];

	p[y]+=p[x];
	p[x]=y;
}

bool cmp(st x,st y){
	return x.h<y.h;
}


int bindid(int i,int j){
	return (i-1)*m+j;
}


int main(int argc, char* argv[]) {

	read(n,m);
	int t=0;
	FOR(i,1,n){
		FOR(j,1,m){
			int h;
			read(h);
			a[++t].x=i;
			a[t].y=j;
			a[t].id=t;
			ASSERT(bindid(i,j)==t);
			a[t].city=(h>0);
			a[t].h=abs(h);

			::h[i][j]=abs(h);
		}
	}

	memset(p,-1,sizeof(p));
	sort(a+1,a+n*m+1,cmp);

	int ans=0;
	FOR(i,1,n*m){
		int last=i;
		while(i<n*m&&a[i+1].h==a[i].h)
			i++;
		FOR(j,last,i){
			int x=a[j].x,y=a[j].y;
			if(x<=n-1&&h[x+1][y]<=h[x][y])
				setunion(bindid(x+1,y),a[j].id);
			if(x>=2&&h[x-1][y]<=h[x][y])
				setunion(bindid(x-1,y),a[j].id);
			if(y<=m-1&&h[x][y+1]<=h[x][y])
				setunion(bindid(x,y+1),a[j].id);
			if(y>=2&&h[x][y-1]<=h[x][y])
				setunion(bindid(x,y-1),a[j].id);
		}
		FOR(j,last,i)
			if(a[j].city&&!pump[setfind(a[j].id)]){
				ans++;
				pump[setfind(a[j].id)]=true;
			}
	}

	printf("%d\n",ans);

	return 0;
}

// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP

