#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
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
int q[MaxN][MaxN];

ll qm(ll base,ll exp,ll mod){
	ll ans=1;
	while(exp){
		if(exp&1)
			ans=(ans*base)%mod;
		base=base*base%mod;
		exp>>=1;
	}
	return ans;
}



int main(int argc, char* argv[]) {

	memset(q,-1,sizeof(q));

	bool ok=true;

	read(n);read(m);
	for(int i=1;i<=n&&ok;i++){
		int x;
		read(x);
		for(int j=1;j<=x;j++)
			if(q[i][j]==0)
				ok=false;
			else
				q[i][j]=1;
		if(q[i][x+1]==1)
			ok=false;
		else
			q[i][x+1]=0;
	}

	for(int i=1;i<=m&&ok;i++){
		int x;
		read(x);
		for(int j=1;j<=x;j++)
			if(q[j][i]==0)
				ok=false;
			else
				q[j][i]=1;
		if(q[x+1][i]==1)
			ok=false;
		else
			q[x+1][i]=0;
	}

	if(!ok)
		printf("0\n");
	else{
		int cnt=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				if(q[i][j]==-1)
					cnt++;
		printf("%d\n",(int)qm(2,cnt,1000000007));
	}






	return 0;
}


