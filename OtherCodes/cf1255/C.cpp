#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
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

const int MaxN=1e5+10;

class triple{
public:
	int a,b,c;
	int id;
	bool operator == (triple right){
		return a==right.a&&b==right.b&&c==right.c;
	}
};

int n;
triple a[MaxN];
vector<triple> ax[MaxN];
bool used[MaxN];

int cnt[MaxN];

vector<int> ans;

bool contain(triple tri,int x){
	return tri.a==x||tri.b==x||tri.c==x;
}


int main(int argc, char* argv[]) {

	read(n);
	for(int i=1;i<=n-2;i++){
		read(a[i].a);read(a[i].b);read(a[i].c);
		a[i].id=i;
		cnt[a[i].a]++;
		cnt[a[i].b]++;
		cnt[a[i].c]++;
		ax[a[i].a].push_back(a[i]);
		ax[a[i].b].push_back(a[i]);
		ax[a[i].c].push_back(a[i]);
	}

	int s;
	for(int i=1;i<=n;i++)
		if(cnt[i]==1){
			s=i;
			break;
		}

	ans.push_back(s);
	int cnt0=0;
	triple prev=ax[s][0];
	int x,y;
	if(ax[s][0].a==s){
		x=prev.b;
		y=prev.c;
	}
	if(ax[s][0].b==s){
		x=prev.a;
		y=prev.c;
	}
	if(ax[s][0].c==s){
		x=prev.a;
		y=prev.b;
	}
	if(ax[x].size()>2)
		swap(x,y);
	ans={s,x,y};

	used[ax[s][0].id]=true;

	DEBUG("Begin- s=%d, x=%d, y=%d\n",s,x,y);

	for(int i=1;i<=n-3;i++){
		int z=-1;
		for(auto j:ax[x]){
			if(contain(j,y)&&!used[j.id]){
				z=j.a+j.b+j.c-x-y;
				used[j.id]=true;
				break;
			}
		}
		DEBUG("Loop%d- x=%d, y=%d, z=%d\n",i,x,y,z);
		ans.push_back(z);
		x=y;
		y=z;
	}

	printf("%d",ans[0]);
	for(int i=1;i<ans.size();i++)
		printf(" %d",ans[i]);
	printf("\n");

	return 0;
}


