#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
#include <deque>

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

const int MaxN=2*1e6+10;

int n;
int a[MaxN],d[MaxN];
int as[MaxN],ds[MaxN];

int ab[MaxN],db[MaxN];

bool ans[MaxN];

struct st{
	st(){}
	st(int pos,int val):pos(pos),val(val){}
	int pos;
	int val;
};

// maintaining a minimum value
deque<st> q;
int sum=0;

void maintain(int pos,int len){
	while(q.front().pos<pos-len+1){
		//DEBUG("      Maintain(): POP_FRONT(pos=%d, val=%d)\n",q.front().pos,q.front().val);
		q.pop_front();
	}
}

void insert(int pos,int val,int len){
	DEBUG("    INSERT: pos=%d, val=%d\n",pos,val);
	while(!q.empty()&&q.back().val>val){
		//DEBUG("      Insert(): POP_BACK(pos=%d, val=%d)\n",q.back().pos,q.back().val);
		q.pop_back();
	}
	q.push_back(st(pos,val));
	maintain(pos,len);
}

int minimum(int pos,int len){
	maintain(pos,len);
	//DEBUG("  MINIMUM(pos=%d, len=%d) = (pos=%d, val=%d)\n",pos,len,q.front().pos,q.front().val);
	return q.front().val;
}


int main(int argc, char* argv[]) {

	read(n);
	FOR(i,1,n){
		read(a[i]);
		read(d[i]);
		a[i+n]=a[i];
		d[i+n]=d[i];
	}

	FOR(i,1,2*n){
		as[i]=as[i-1]+a[i];
		ds[i]=ds[i-1]+d[i];
	}
	DEBUG("LINEAR\n");

	PRINTARR("%d",a,1,n);
	PRINTARR("%d",d,1,n);

	PRINTARR("%d",as,1,2*n);
	PRINTARR("%d",ds,1,2*n);

	FOR(i,1,n){
		insert(i,as[i]-ds[i],n);
	}
	FOR(i,1,n){
		DEBUG("  i=%d, min=%d, min-ds+as=%d, a[i]=%d, %s\n",
			i,minimum(i+n-1,n),minimum(i+n-1,n)+ds[i-1]-as[i-1],a[i],
			(minimum(i+n-1,n)+ds[i-1]-as[i-1]>=0)?"TRUE":"FALSE");

		ans[i]|=(minimum(i+n-1,n)+ds[i-1]-as[i-1]>=0);
		insert(i+n,as[i+n]-ds[i+n],n);
	}

	DEBUG("COUTERLINEAR\n");

	FOR(i,1,n)
		ab[n-i+1]=a[i];
	FOR(i,1,n-1)
		db[i]=d[n-i];
	db[n]=d[n];

	memcpy(a+1,ab+1,sizeof(int)*n);
	memcpy(d+1,db+1,sizeof(int)*n);

	PRINTARR("%d",a,1,n);
	PRINTARR("%d",d,1,n);
	FOR(i,1,n){
		a[i+n]=a[i];
		d[i+n]=d[i];
	}

	q.clear();

	FOR(i,1,2*n){
		as[i]=as[i-1]+a[i];
		ds[i]=ds[i-1]+d[i];
	}

	PRINTARR("%d",as,1,2*n);
	PRINTARR("%d",ds,1,2*n);

	FOR(i,1,n){
		insert(i,as[i]-ds[i],n);
	}
	FOR(i,1,n){
		DEBUG("  i=%d, min=%d, min-ds+as=%d, a[i]=%d, %s\n",
			i,minimum(i+n-1,n),minimum(i+n-1,n)+ds[i-1]-as[i-1],a[i],
			(minimum(i+n-1,n)+ds[i-1]-as[i-1]>=0)?"TRUE":"FALSE");

		ans[n-i+1]|=(minimum(i+n-1,n)+ds[i-1]-as[i-1]>=0);
		insert(i+n,as[i+n]-ds[i+n],n);
	}



	FOR(i,1,n)
		if(ans[i])
			printf("TAK\n");
		else
			printf("NIE\n");


	return 0;
}

// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP

