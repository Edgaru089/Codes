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
		fprintf(stderr,"Debug Assertation Failed on line %d, in function %s:\n  Expression: %s\n",__LINE__,__func__,#expr);\
		abort();\
	}\
}while(false)
#else
#define DEBUG(...)
#define PRINTARR(a, b, c, d)
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

const int MaxN=500000+10;

int d[MaxN];
int n,m;

int lowbit(int x){
	return x&(-x);
}

void add(int pos,int x){
	while(pos<=n){
		d[pos]+=x;
		pos+=lowbit(pos);
	}
}

int prefix(int pos){
	int sum=0;
	while(pos){
		sum+=d[pos];
		pos-=lowbit(pos);
	}
	return sum;
}

int query(int x,int y){
	return prefix(y)-prefix(x-1);
}




int main(int argc, char* argv[]) {

	read(n);read(m);
	for(int i=1;i<=n;i++){
		int x;
		read(x);
		add(i,x);
	}

	for(int i=1;i<=m;i++){
		int k,x,y;
		read(k);read(x);read(y);
		if(k==1)
			add(x,y);
		else if(k==2)
			printf("%d\n",query(x,y));
	}





	return 0;
}


