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
string str[MaxN];
ll s[MaxN][MaxN];





int main(int argc, char* argv[]) {

	read(n);read(m);
	FOR(i,0,n-1)
		read(str[i]);

	FOR(i,1,n-1){
		FOR(j,0,m-1){
			if(str[i-1][j]!=str[i][j]){
				int t=1;
				while(i+t<=n-1&&str[i+t][j]==str[i][j])
					t++;
				if(t>i||i+2*t-1>=n||str[i+2*t-1][j]==str[i][j]){
					DEBUG("    Failed: pre\n");
					continue;
				}
				DEBUG("[i,j]=[%d,%d], t=%d\n",i,j,t);
				bool ok=true;
				int k=i-2;
				while(ok){
					if(k<i-t)
						break;
					if(str[k][j]!=str[i-1][j])
						ok=false;
					k--;
				}
				if(!ok){
					DEBUG("    Failed: top\n");
					continue;
				}
				k=i+t+1;
				while(ok){
					if(k>i+2*t-1)
						break;
					if(str[k][j]!=str[i+t][j])
						ok=false;
					k++;
				}
				if(!ok){
					DEBUG("    Failed: bot\n");
					continue;
				}else
					s[i][j]=t;
			}
		}
	}

	PRINTARR2D("%lld",s,0,n,0,m);

	ll ans=0;
	FOR(i,0,n-1){
		ll cur=-1;
		int cnt=0;
		FOR(j,0,m-1){
			DEBUG("[i,j]=[%d,%d], ",i,j);
			if(s[i][j]>0){
				DEBUG("Case 1.");
				ll tid=(((ll)s[i][j]<<24)|((ll)str[i-1][j]<<16)|((ll)str[i][j]<<8)|((ll)str[i+s[i][j]][j]));
				if(cur==-1){
					cur=tid;
					cnt=1;
					DEBUG("1, cnt=%d\n",cnt);
				}else if(cur==tid){
					cnt++;
					DEBUG("2, cnt=%d\n",cnt);
				}else /* cur != s[i][j] */{
					cur=tid;
					cnt=1;
					DEBUG("3, cnt=%d\n",cnt);
				}
				ans+=cnt;
			}else{
				DEBUG("Case 2\n");
				cur=-1;
			}
		}
		DEBUG("\n");
	}

	printf("%lld\n",ans);

	return 0;
}


// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP

