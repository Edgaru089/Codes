#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <string>
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

inline void putstr(const char* str) {
	while ((*str) != '\0') {
		putchar(*str);
		str++;
	}
}

template<typename IntType>
inline void print(IntType val) {
	if (val == 0)
		putchar('0');
	if (val < 0) {
		putchar('-');
		val = -val;
	}
	char buf[16], *buftop = buf + 15;
	while (val > 0) {
		*buftop = (val % 10 + '0');
		buftop--;
		val /= 10;
	}
	for (buftop++; buftop <= buf + 15; buftop++)
		putchar(*buftop);
}

const int MaxN=1e6+10;

int n;
int a[MaxN];

struct node{
	int v;
	node* next;
};

node* h[MaxN];
node mem[2*MaxN],*memtop=mem;
#define ALLOCATE (++memtop)

void addedge(int u,int v){
	node* p=ALLOCATE;
	p->v=v;
	p->next=h[u];
	h[u]=p;
}

template<typename T>
class stack{
public:

	void push(T x){
		arr[t++]=x;
	}

	T top()const{
		return arr[t-1];
	}

	T pop(){
		return arr[--t];
	}

	void clear(){
		t=0;
	}

	size_t size()const{
		return t;
	}

	const T* data()const{
		return arr;
	}

private:
	size_t t;
	T arr[MaxN];
};

template<typename T,size_t arrsize=2*MaxN>
class svector{
public:

	T& operator [] (size_t i){
		return arr[i];
	}
	const T& operator [] (size_t i)const{
		return arr[i];
	}

	void clear(){
		s=0;
	}

	void push_back(T x){
		arr[s++]=x;
	}

	size_t size()const{
		return s;
	}

private:
	size_t s;
	T arr[arrsize];
};

stack<int> s;
bool been[MaxN];
svector<int> ans;
bool ok=false;

void dfs(int u){
	if(been[u]){
		while(s.top()!=u)
			ans.push_back(s.pop());
		ans.push_back(u);
		ok=true;
		return;
	}
	s.push(u);
	been[u]=true;
	for(node* p=h[u];p;p=p->next){
		int v=p->v;
		dfs(v);
		if(ok)
			return;
	}
	s.pop();
	been[u]=false;
}



int main(int argc, char* argv[]) {

	int t;
	read(t);
	while(t--){

		read(n);
		//n=1;

		memset(h,0,sizeof(node*)*(n+4));
		memtop=mem;

		FOR(i,1,n){
			read(a[i]);
			//a[i]=0;
			addedge(i,i-a[i]);
		}

		//if(n==1&&a[1]==0){
			//puts("1\n1\n");
			//continue;
		//}

		s.clear();
		ans.clear();
		memset(been,0,sizeof(bool)*(n+4));
		ok=false;

		FOR(i,1,n){
			dfs(i);
			if(ok)
				break;
		}
		if(ok){
			if(ans.size()==1&&ans[0]==1)
				puts("1\n1\n");
			else{
				print((int)ans.size());
				putchar('\n');
				print(ans[0]);
				FOR(i,1,ans.size()-1){
					putchar(' ');
					print(ans[i]);
				}
				putchar('\n');
			}
		}
	}

	fflush(stdout);

	return 0;
}


// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP

