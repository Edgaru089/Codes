#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <string>
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
const int MaxN=4e5+10;
const int MaxC=20+2;
const ll infinity=1e16;

int n;
int a[MaxN];
vector<int> pos[MaxC];
ll cnt[MaxC][MaxC];

ll dp[1<<MaxC];


int main(int argc, char* argv[]) {

	read(n);
	FOR(i,1,n){
		read(a[i]);
		pos[a[i]].push_back(i);
	}

	FOR(i,1,20){
		FOR(j,1,20){
			if(i==j||pos[i].empty()||pos[j].empty())
				continue;
			int pi=0,pj=0;
			while(pi<pos[i].size()){
				while(pj<pos[j].size()-1){
					if(pos[j][pj+1]>pos[i][pi])
						break;
					pj++;
				}
				if(pos[i][pi]>pos[j][pj])
					cnt[i][j]+=pj+1;
				pi++;
			}
		}
	}

	PASS;

	FOR(i,1,1<<20)
		dp[i]=infinity;

	vector<int> mk;
	FOR(i,0,(1<<20)-1){
		mk.clear();
		FOR(j,0,19)
			if(i&(1<<j))
				mk.push_back(j+1);
		FOR(j,0,19){
			if(!(i&(1<<j))){
				ll sum=0;
				for(int k:mk)
					sum+=cnt[k][j+1];
				dp[i|(1<<j)]=min(dp[i|(1<<j)],dp[i]+sum);
			}
		}
	}

	cout<<dp[(1<<20)-1]<<endl;

	return 0;
}


// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP

