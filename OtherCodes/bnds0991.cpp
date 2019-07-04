rinclude <cstdlib>
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
	node* next[10];
	bool end;
};

node* root;
node mem[800],*memtop=mem;
#define ALLOCATE (++memtop)


string s;
char c[100];
int d[100];


bool insert(int d[],int n){
	node** p=&root;
	for(int i=1;i<=n;i++){
		if(!(*p))
			(*p)=ALLOCATE;
		if((*p)->end)
			return false;
		p=&(*p)->next[d[i]];
	}
	if(!(*p))
		(*p)=ALLOCATE;
	if((*p)->end)
		return false;
	(*p)->end=true;
	return true;
}




int main(int argc, char* argv[]) {

	bool eof=false;
	int i=0;
	for(;;){
		root=0;
		memset(mem,0,sizeof(mem));
		memtop=mem;
		i++;
		bool done=false;
		for(;;){
			if(scanf("%s",c)==EOF){
				eof=true;
				break;
			}
			if(strcmp(c,"9")==0)
				break;
			int n=strlen(c);
			for(int i=1;i<=n;i++){
				d[i]=c[i-1]-'0';
			}
			if(!insert(d,n)){
				if(!done){
					done=true;
					printf("Set %d is not immediately decodable\n",i);
				}
			}
		}
		if(eof)
			break;
		if(!done){
			printf("Set %d is immediately decodable\n",i);
		}
	}

	return 0;
}


