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

const int MaxN=3e5+10;

int n,m;
int a[MaxN];

// lim\in[l,r]
inline bool contain(int l,int r,int lim){
	return l<=lim&&r>=lim;
}

int getmin(int a,int d,int lim){
	DEBUG("      getmin(a=%d, d=%d, lim=%d)\n",a,d,lim);
	if(a+d>=m){
		int l=0,r=(a+d)%m;
		DEBUG("         Type 0+ : +l=%d, +r=%d\n",l,r);
		if(contain(l,r,lim))
			return lim;
		else{
			l=a;
			r=m-1;
			DEBUG("            Type 0X : -l=%d, -r=%d\n",l,r);
			if(contain(l,r,lim))
				return lim;
			else if(lim>r)
				return -1;
			else // lim < a-d
				return l;
		}
	}else{
		int l=a,r=a+d;
		DEBUG("         Type 0- : l=%d, r=%d\n",l,r);
		if(contain(l,r,lim))
			return lim;
		else if(lim>r)
			return -1;
		else // lim < a-d
			return l;
	}
}


int p[MaxN];
bool check(int d){
	DEBUG("check(d=%d)\n",d);
	FOR(i,1,n){
		p[i]=getmin(a[i],d,p[i-1]);
		DEBUG("   p[i=%d]=%d\n",i,p[i]);
		if(p[i]==-1)
			return false;
	}
	return true;
}



int main(int argc, char* argv[]) {

	read(n,m);
	FOR(i,1,n)
		read(a[i]);

	int l=0,r=2*(max(n,m));
	while(l<r-1){
		int mid=(l+r)/2;
		if(check(mid))
			r=mid;
		else
			l=mid;
	}

	if(check(l))
		printf("%d\n",l);
	else
		printf("%d\n",r);

	return 0;
}

// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP

