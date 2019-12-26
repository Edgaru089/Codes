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

const int MaxN=1e5+10,MaxM=1e5+10;
const int MaxF=10;

int n,m;
int p[MaxM];
int c[MaxN];

int fcnt[1<<MaxF];
pair<int,int> mx[1<<MaxF],mi[1<<MaxF];
int dp[1<<MaxF];
pair<int,int> dpa[1<<MaxF];


int main(int argc, char* argv[]) {

	FOR(i,0,(1<<9)-1){
		dp[i]=2000000000+100;
		mx[i]=make_pair(-1,-1);
	}

	read(n);
	read(m);

	FOR(i,1,n){
		int k;
		read(k);
		int cf=0;
		FOR(j,1,k){
			int x;
			read(x);
			cf|=(1<<(x-1));
		}
		DEBUG("fMask[i=%d]=%d\n",i,cf);
		fcnt[cf]++;
	}
	FOR(i,1,m){
		int k;
		read(c[i]);
		read(k);
		FOR(j,1,k){
			int x;
			read(x);
			p[i]|=(1<<(x-1));
		}
		int px=p[i];
		DEBUG("pMask[i=%d]=%d\n",i,px);
		if(mx[px].first<0||mx[px].first>c[i]){
			mx[px].second=mx[px].first;
			mi[px].second=mi[px].first;
			mx[px].first=c[i];
			mi[px].first=i;
		}else if(mx[px].second<0||mx[px].second>c[i]){
			mx[px].second=c[i];
			mi[px].second=i;
		}

		if(mx[px].second>0){
			if(dp[px]>mx[px].first+mx[px].second){
				dp[px]=mx[px].first+mx[px].second;
				dpa[px]=mi[px];
			}
		}
	}


	FOR(i,0,(1<<9)-1){
		ASSERT(mx[i].first==-1 || mi[i].first!=mi[i].second);
		FOR(j,0,(1<<9)-1){
			if(mx[i].first>0&&mx[j].first>0&&mi[i].first!=mi[j].first){
				if(dp[i|j]>mx[i].first+mx[j].first){
					dp[i|j]=mx[i].first+mx[j].first;
					dpa[i|j]=make_pair(mi[i].first,mi[j].first);
				}
			}
		}
	}

	fcnt[0]++;

	int acnt=0,acost;
	pair<int,int> ans(-1,-1);
	FOR(i,0,(1<<9)-1){
		if(dp[i]<2000000100){
			int ccnt=0;
			FOR(j,0,(1<<9)-1){
				if((i|j)==i)
					ccnt+=fcnt[j];
			}
			DEBUG("PASS- :[i=%d](dp=%d)(dpa=[%d, %d])(ccnt=%d)\n",i,dp[i],dpa[i].first,dpa[i].second,ccnt);
			if(ccnt>acnt){
				acnt=ccnt;
				acost=dp[i];
				ans=dpa[i];
			}else if(ccnt==acnt&&dp[i]<acost){
				acnt=ccnt;
				acost=dp[i];
				ans=dpa[i];
			}
		}
	}

	printf("%d %d\n",ans.first,ans.second);


	return 0;
}


// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP

