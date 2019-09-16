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
void read<string>(string& str){
	str.clear();
	int c;
	while(iscntrl(c=getchar())||c==' '||c=='\t');
	do{
		str.push_back(c);
	}while(!(iscntrl(c=getchar())||c==' '||c=='\t'));
}

const int infinity=1e6;
const int MaxN=100+10,MaxM=1e6+10;

int n,m;

bool s[MaxN][MaxN];
int dis[MaxN][MaxN];

int p[MaxM];
bool ex[MaxM];






int main(int argc, char* argv[]) {


	read(n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(i!=j)
				dis[i][j]=infinity;
	string str;
	for(int i=1;i<=n;i++){
		read(str);
		for(int j=1;j<=n;j++)
			if(str[j-1]=='1')
				dis[i][j]=1;
	}
	read(m);
	for(int i=1;i<=m;i++)
		read(p[i]);

#ifdef D
//	printf("\t");
	for(int i=1;i<=n;i++)
		printf("\t%d",i);
	printf("\n");
	for(int i=1;i<=n;i++){
		printf("%d",i);
		for(int j=1;j<=n;j++)
			printf("\t%d",dis[i][j]);
		printf("\n");
	}
#endif
	PASS;

	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(dis[i][j]>dis[i][k]+dis[k][j])
					dis[i][j]=dis[i][k]+dis[k][j];

	int l=1,r=2;
	while(r<m){
		int t=r+1;
		if(dis[p[l]][p[t]]==dis[p[l]][p[r]]+dis[p[r]][p[t]]){
			ex[r]=true;
			r++;
		}else{
			l=r;
			r++;
		}
	}

#ifdef D
//	printf("\t");
	for(int i=1;i<=n;i++)
		printf("\t%d",i);
	printf("\n");
	for(int i=1;i<=n;i++){
		printf("%d",i);
		for(int j=1;j<=n;j++)
			printf("\t%d",dis[i][j]);
		printf("\n");
	}
#endif

	int cnt=0;
	for(int i=1;i<=m;i++)
		if(!ex[i])
			cnt++;

	printf("%d\n",cnt);
	bool first=true;
	for(int i=1;i<=m;i++)
		if(!ex[i])
			if(first){
				printf("%d",p[i]);
				first=false;
			}else
				printf(" %d",p[i]);
	if(!first)
		printf("\n");


	return 0;
}


