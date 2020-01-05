#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
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

typedef pair<int,int> pii;
const int MaxN=5000+10;

int n,m,k;
int a[MaxN],b[MaxN],c[MaxN];


priority_queue<int,vector<int>,greater<int>> q;
int front[MaxN];
vector<int> back[MaxN];






int main(int argc, char* argv[]) {

	read(n);read(m);read(k);
	FOR(i,1,n){
		read(a[i]);
		read(b[i]);
		read(c[i]);
	}
	FOR(i,1,m){
		int u,v;
		read(u);read(v);
		front[v]=max(front[v],u);
	}

	FOR(i,1,n){
		if(front[i]!=0)
			back[front[i]].push_back(i);
	}

	int ans=0;
	FOR(i,1,n){
		while((k<0||k<a[i])&&!q.empty()){
			int t=q.top();
			q.pop();
			k++;
			ans-=t;
		}
		if(k<a[i]){
			ans=-1;
			break;
		}
		k+=b[i];
		if(front[i]==0){
			k--;
			ans+=c[i];
			q.push(c[i]);
		}
		FOR(j,0,(int)back[i].size()-1){
			int l=back[i][j];
			k--;
			ans+=c[l];
			q.push(c[l]);
		}
	}
	while((k<0)&&!q.empty()){
		int t=q.top();
		q.pop();
		k++;
		ans-=t;
	}

	printf("%d\n",ans);

	return 0;
}


// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP

