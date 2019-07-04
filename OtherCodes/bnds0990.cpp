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
template<>
void read<string>(string& val){
	val.clear();
	int c;
	while(iscntrl(c=getchar())||c=='\t'||c==' ');
	do{
		val.push_back(c);
	}while(!(iscntrl(c=getchar())||c=='\t'||c==' '));
}


struct node{
	node* next[26];
	bool end;
};

node* root;
node mem[10000],*memtop=mem;
#define ALLOCATE (++memtop)


string s;
char c[1000];
int d[1000];
int l;
int n,m;


void insert(const char s[],int n){
	node** p=&root;
	for(int i=1;i<=n;i++){
		int d=s[i-1]-'a';
		if(!(*p))
			(*p)=ALLOCATE;
		p=&(*p)->next[d];
	}
	if(!(*p))
		(*p)=ALLOCATE;
	(*p)->end=true;
}

void insert(const string str){
	insert(s.c_str(),s.size());
}

int ans[10000];
int dfs(int i){
	DEBUG("dfs(%d)\n",i);
	if(i>=l)
		return 0;
	if(ans[i]>=0)
		return ans[i];
	int ans=0;
	node* p=root;
	for(int j=i;j<=l&&p;j++){
		DEBUG("    j=%d, d[j]=%d\n",j,d[j]);
		p=p->next[d[j]];
		if(p&&p->end)
			ans=max(ans,j-i+1+dfs(j+1));
	}
	return ::ans[i]=ans;
}



int main(int argc, char* argv[]) {

	read(n);read(m);
	for(int i=1;i<=n;i++){
		read(s);
		insert(s);
	}

	for(int i=1;i<=m;i++){
		read(s);
		l=s.size();
		for(int i=1;i<=l;i++){
			d[i]=s[i-1]-'a';
		}
		memset(ans,-1,sizeof(ans));
		printf("%d\n",dfs(1));
	}






	return 0;
}


