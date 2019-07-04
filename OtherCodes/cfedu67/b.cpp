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

template<>
void read<string>(string& val){
	val.clear();
	int c;
	while(iscntrl(c=getchar())||c==' '||c=='\t');
	do{
		val.push_back(c);
	}while(!(iscntrl(c=getchar())||c==' '||c=='\t'));
}

const int MaxN=2e5+10,MaxM=5e4+10;

int n,m;
string s;
string t;

int cnts[MaxN][30];
int cntt[30];


bool check(int i){
	for(int j=0;j<26;j++)
		if(cntt[j]>cnts[i][j])
			return false;
	return true;
}


int main(int argc, char* argv[]) {

	read(n);
	read(s);

	cnts[0][s[0]-'a']++;
	for(int i=1;i<n;i++){
		for(int j=0;j<26;j++)
			cnts[i][j]+=cnts[i-1][j];
		cnts[i][s[i]-'a']++;
	}

	read(m);
	for(int i=1;i<=m;i++){
		read(t);
		memset(cntt,0,sizeof(cntt));
		for(char c:t)
			cntt[c-'a']++;
		int l=0,r=n-1;
		while(l<r-1){
			int mid=(l+r)/2;
			if(check(mid))
				r=mid;
			else
				l=mid;
		}
		if(check(l))
			printf("%d\n",l+1);
		else
			printf("%d\n",r+1);
	}


	return 0;
}


