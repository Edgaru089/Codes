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

const int MaxN=1e5+10;

string str;
int n;
int z[MaxN],a[MaxN];

template<typename String>
void zfunc(String str,int n,int* z){
	z[0]=0;
	int l,r;
	l=r=0;
	FOR(i,1,n-1){
		if(i<=r)
			z[i]=min(r-i+1,z[i-l]);
		else
			z[i]=0;
		while(i+z[i]<n&&str[i+z[i]]==str[z[i]])
			z[i]++;
		if(r<i+z[i]-1){
			l=i;
			r=i+z[i]-1;
		}
	}
}

vector<pair<int,int> > ans;


int main(int argc, char* argv[]) {

	read(str);
	n=str.size();

	zfunc(str,n,z);

	PRINTARR("%d",z,0,n);

	z[0]=n;
	memcpy(a+1,z,sizeof(int)*n);
	sort(a+1,a+n+1,greater<int>());
	PRINTARR("%d",a,1,n);

	int k=n;
	FOR(i,1,n){
		if(z[n-i]==i){
			while(a[k]<z[n-i])
				k--;
			ans.push_back(make_pair(i,k));
		}
	}

	printf("%d\n",(int)ans.size());
	FOR(i,0,ans.size()-1)
		printf("%d %d\n",ans[i].first,ans[i].second);

	return 0;
}


// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP

