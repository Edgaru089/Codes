#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <set>
#include <vector>
#include <map>
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

int n;
int a[MaxN];


bool ok=true;
map<int,int> cur;
set<int> whole;
vector<int> ans;





int main(int argc, char* argv[]) {

	read(n);
	for(int i=1;i<=n;i++)
		read(a[i]);

	ans.push_back(0);

	for(int i=1;i<=n;i++){
		int x=a[i];
		DEBUG("x=%d\n",x);
		if(x>0){
			auto it=cur.find(x);
			if(cur.end()!=it){
				DEBUG("Abort: cur.end()!=it\n");
				ok=false;
				break;
			}
			if(!whole.insert(x).second){
				DEBUG("Abort: !whole.insert(x).second\n");
				ok=false;
				break;
			}
		}else if(x<0){
			set<int>::iterator it=whole.find(-x);
			if(it==whole.end()){
				DEBUG("Abort: it==whole.end()\n");
				ok=false;
				break;
			}else{
				whole.erase(it);
				cur[-x]=i;
			}
		}
		if(whole.size()==0){
			cur.clear();
			ans.push_back(i);
		}
	}

	//ans.push_back(n);
	if(!whole.empty()){
		DEBUG("Abort: (Post) !whole.empty()\n");
		ok=false;
	}

	if(ok){
		printf("%d\n",(int)ans.size()-1);
		for(int i=1;i<=ans.size()-1;i++)
			if(i==1)
				printf("%d",ans[i]-ans[i-1]);
			else
				printf(" %d",ans[i]-ans[i-1]);
		printf("\n");
	}else{
		printf("-1\n");
	}


	return 0;
}


