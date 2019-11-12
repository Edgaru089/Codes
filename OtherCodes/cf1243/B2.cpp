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

int k,n;
string s,t;

int cnt[30];




int main(int argc, char* argv[]) {

	ios::sync_with_stdio(false);

	cin>>k;
	while(k--){

		cin>>n;
		cin>>s>>t;

		memset(cnt,0,sizeof(cnt));

		for(char c:s)
			cnt[c-'a']++;
		for(char c:t)
			cnt[c-'a']++;

		bool ok=true;
		for(int i=0;i<26;i++)
			if(cnt[i]&1){
				ok=false;
				break;
			}

		if(!ok)
			cout<<"No"<<endl;
		else{
			vector<pair<int,int> > ops;
			for(int i=n-1;i>=0;i--){
				if(s[i]==t[i])
					continue;
				int j=0;
				while(t[j]!=t[i])
					j++;
				if(j<i){
					swap(s[i],t[j]);
					ops.push_back(make_pair(i,j));
				}else{
					j=0;
					while(s[j]!=t[i])
						j++;
					swap(s[j],t[0]);
					ops.push_back(make_pair(j,0));
					swap(s[i],t[0]);
					ops.push_back(make_pair(i,0));
				}
			}
			cout<<"Yes"<<endl;
			cout<<ops.size()<<endl;
			for(auto[a,b]:ops)
				cout<<a+1<<' '<<b+1<<endl;
			DEBUG("s(%s)\nt(%s)\n",s.c_str(),t.c_str());
		}
	}

	return 0;
}


