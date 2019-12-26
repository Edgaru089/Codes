#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <string>
//#include <map>
#include <unordered_map>
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

const int MaxN=2e5+10;

int n;
pair<int,int> a[MaxN];

unordered_map<int,int> m;


int main(int argc, char* argv[]) {

	read(n);
	FOR(i,1,n){
		read(a[i].first);
		a[i].second=i;
	}

	sort(a+1,a+n+1);

	FOR(i,1,n){
		if(i>1)
			m[a[i].first-a[i-1].first]++;
		if(i<n)
			m[a[i+1].first-a[i].first]++;
		if(m.size()>4){
			printf("-1\n");
			return 0;
		}
	}

	for(auto&[a,b]:m){
		b/=2;
		DEBUG("[%d, %d]\n",a,b);
	}

	FOR(i,1,n){
		if(i>1)
			m[a[i].first-a[i-1].first]--;
		if(i<n)
			m[a[i+1].first-a[i].first]--;
		if(i>1&&i<n)
			m[a[i+1].first-a[i-1].first]++;
		int cnt1=0;
		for(auto[a,b]:m){
			if(b>0)
				cnt1++;
		}
		if(cnt1<=1){
			printf("%d\n",a[i].second);
			return 0;
		}
		if(i>1)
			m[a[i].first-a[i-1].first]++;
		if(i<n)
			m[a[i+1].first-a[i].first]++;
		if(i>1&&i<n)
			m[a[i+1].first-a[i-1].first]--;
	}

	printf("-1\n");
	return 0;
}


// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP

