#include <cstdlib>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <cstdio>
using namespace std;

#if (defined LOCAL) || (defined D)
#define DEBUG(...) printf(__VA_ARGS__)
#define PRINTARR(formatstr, arr, beginoff, size)				\
do{printf(#arr ":");											\
for (int __i = beginoff; __i <= beginoff + size - 1; __i++)		\
	printf("\t%d", __i);										\
printf("\n");													\
for (int __i = beginoff; __i <= beginoff + size - 1; __i++)		\
	printf("\t" formatstr, arr[__i]);							\
printf("\n"); }while(false)
#define PASS printf("Passing function \"%s\" on line %d\n", __func__, __LINE__)
#define ASSERT(expr) do{\
	if(!(expr)){\
		printf("Debug Assertation Failed on line %d, in function %s:\n  Expression: %s\n",__LINE__,__func__,#expr);\
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

const int MaxN=10000+10;

struct node{
	bool ch;
	node* next[10];
};

node* root;
node mem[100000+10],*memtop=mem;
#define ALLOCATE (++memtop)

bool insert(const string& str){
	node** p=&root;
	bool cr=false;
	for(int i=0;i<str.size();i++){
		char c=str[i];
		p=&((*p)->next[c-'0']);
		if(!*p){
			cr=true;
			*p=ALLOCATE;
		}else
			cr=false;
	}
	(*p)->ch=true;
	return cr;
}

int t;
int n;
string str[MaxN];

bool cmp(const string& x,const string& y){
	return x.size()>y.size();
}

int main(int argc, char* argv[]) {

	read(t);
	while(t--){
		read(n);
		bool ans=true;
		memset(mem,0,sizeof(mem));
		memtop=mem;
		root=ALLOCATE;
		for(int i=1;i<=n;i++)
			read(str[i]);
		sort(str+1,str+n+1,cmp);
		for(int i=1;i<=n;i++)
			ans=ans&&insert(str[i]);
		printf(ans?"YES\n":"NO\n");
	}




	return 0;
}


