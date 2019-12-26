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

template<typename Int>
Int iabs(Int x){
	return ((x)>0)?(x):(-x);
}

int a,b,c,d;
vector<int> ans;

int main(int argc, char* argv[]) {

	read(a);
	read(b);
	read(c);
	read(d);

	bool front1=false;
	if(a==0&&b==0){
		if(iabs(c-d)<=1){
			if(c<d)
				ans.push_back(3);
			FOR(i,1,min(c,d)){
				ans.push_back(2);
				ans.push_back(3);
			}
			if(c>d)
				ans.push_back(2);
		}else{
			printf("NO\n");
			return 0;
		}
	}else if(c==0&&d==0){
		if(iabs(a-b)<=1){
			if(a<b)
				ans.push_back(1);
			FOR(i,1,min(a,b)){
				ans.push_back(0);
				ans.push_back(1);
			}
			if(a>b)
				ans.push_back(0);
		}else{
			printf("NO\n");
			return 0;
		}

	}else if(a>b||c<d){
		printf("NO\n");
		return 0;
	}else{
		FOR(i,1,a){
			ans.push_back(0);
			ans.push_back(1);
		}
		b-=a;
		a=0;
		FOR(i,1,d){
			ans.push_back(2);
			ans.push_back(3);
		}
		c-=d;
		d=0;
		if(c==0){
			if(b==1)
				front1=true;
			else if(b>1){
				printf("NO\n");
				return 0;
			}
		}else{
			int dt=min(b,c);
			FOR(i,1,dt){
				ans.push_back(2);
				ans.push_back(1);
			}
			b-=dt;
			c-=dt;
			if(b>1||c>1){
				printf("NO\n");
				return 0;
			}
			if(b==1)
				front1=true;
			if(c==1)
				ans.push_back(2);
		}
	}

	printf("YES\n");
	if(front1){
		printf("1");
		for(int i:ans)
			printf(" %d",i);
		printf("\n");
	}else{
		printf("%d",ans[0]);
		FOR(i,1,ans.size()-1)
			printf(" %d",ans[i]);
		printf("\n");
	}

	return 0;
}


// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP

