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

#define FOR(i, first, last)               for(int i = first; i <= last; ++i)
#define ROF(i, last, first)               for(int i = last; i >= first; --i)
#define FORSTEP(i, first, last, step)     for(int i = first; i <= last; i += step)
#define ROFSTEP(i, last, first, stepabs)  for(int i = last; i >= first; i -= step)

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

const int MaxN=100+10,MaxK=62+5;

int r,c;
int k;
bool a[MaxN][MaxN];
int s[MaxN][MaxN];
int scnt;

bool advance(int& i,int& j){
	if(i&1){
		j++;
		if(j>c){
			j=c;
			i++;
			if(i>r)
				return false;
		}
	}else{
		j--;
		if(j<1){
			j=1;
			i++;
			if(i>r)
				return false;
		}
	}
	return true;
}

int getcnt(int i){
	int mod=scnt%k;
	if(i<=mod)
		return scnt/k+1;
	else
		return scnt/k;
}

char ithchar(int i){
	if(i<=26)
		return i+'A'-1;
	else if(i<=2*26)
		return i-26+'a'-1;
	else
		return i-26-26+'0'-1;
}



int main(int argc, char* argv[]) {

	int t;
	read(t);
	while(t--){

		read(r);read(c);read(k);
		string str;
		scnt=0;
		FOR(i,1,r){
			read(str);
			FOR(j,1,c){
				if(str[j-1]=='R'){
					scnt++;
					a[i][j]=true;
				}else
					a[i][j]=false;
			}
		}

		int i=1,j=1;
		int cur=1,tot=0;
		do{
			s[i][j]=cur;
			if(a[i][j]){
				tot++;
				if(tot==getcnt(cur)&&cur<k){
					cur++;
					tot=0;
				}
			}
		}while(advance(i,j));

		FOR(i,1,r){
			FOR(j,1,c)
				putchar(ithchar(s[i][j]));
			putchar('\n');
		}

		fflush(stdout);

	}

	return 0;
}


// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP

