#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <map>
#include <vector>

#ifdef D
#include <custom/Debug.hpp>
#endif

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
#define PRINT(...) dbg(__VA_ARGS__)
#define PRINTVAL(...) dbgv(__VA_ARGS__)
#define PRINTSEQ(...) dbgr(__VA_ARGS__)
#define PRINTSEQVAL(...) dbgm(__VA_ARGS__)
#define PRINTCOMPACT(...) dbgs(__VA_ARGS__)
#else
#define DEBUG(...)
#define PRINTARR(a, b, c, d)
#define PRINTARR2D(a, b, c, d, e, f)
#define PASS
#define ASSERT(expr)
#define PRINT(...)
#define PRINTVAL(...)
#define PRINTSEQ(...)
#define PRINTSEQVAL(...)
#define PRINTCOMPACT(...)
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
#if __cplusplus >= 201103
template<typename IntType,typename... Args>
void read(IntType& val, Args&... args){
	read(val); read(args...);
}
#endif

// End of template:edgar:edgar-laptop(LAPTOP-EDGAR-15)

const int MaxN=1e6+10;

int n;
string str;

struct node{
	int step;
	//unordered_map<int,node*> next;
	map<int,node*> next;
	node* prev;

	bool flag;
};

node mem[2*MaxN],*memtop=mem;
#define ALLOCATE (++memtop)
node* root,*last;

void insert(int ch){
	node* p=last,*np=ALLOCATE;
	np->step=p->step+1;
	last=np;
	while(p&&!p->next[ch]){
		p->next[ch]=np;
		p=p->prev;
	}
	if(!p)
		np->prev=root;
	else{
		node* q=p->next[ch];
		if(q->step==p->step+1)
			np->prev=q;
		else{
			ASSERT(q->step > p->step+1);
			node* nq=ALLOCATE;
			nq->next=q->next;
			nq->step=p->step+1;
			nq->prev=q->prev;
			np->prev=q->prev=nq;
			while(p&&p->next[ch]==q){
				p->next[ch]=nq;
				p=p->prev;
			}
		}
	}
}

void mark(node* p=last){
	while(p&&p!=root){
		p->flag=true;
		p=p->prev;
	}
}

int get(char ch){
	if(ch>='0'&&ch<='9')
		return ch-'0';
	else if(ch>='A'&&ch<='Z')
		return ch-'A'+10;
	else
		return ch-'a'+10+26;
}


vector<int> ans;

void dfs(node* p=root,int step=0){
	if(p->flag)
		ans.push_back(n-step+1);
	for(auto x:p->next){
		dfs(x.second,step+1);
	}
}


int main(int argc, char* argv[]) {

	read(str);
	n=str.size();

	last=root=ALLOCATE;

	for(char c:str)
		insert(get(c));

	mark();
	dfs();

	DEBUG("ans.size() = %d\n",(int)ans.size());
	//PRINTARR("%d",ans,0,ans.size());
	ASSERT(ans.size() == str.size());

	printf("%d",ans[0]);
	FOR(i,1,(int)ans.size()-1)
		printf(" %d",ans[i]);
	printf("\n");


	return 0;
}

// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP

