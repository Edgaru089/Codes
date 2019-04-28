#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <map>
#include <vector>
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

const int MaxN=300000+10;

struct node{
	int maxlen;
	map<int,node*> trans;
	node* prev;
};

node* root,*last;
node mem[3*MaxN],*memtop=mem;
#define ALLOCATE (++memtop)

void insert(int c){
	node* p=last,*np=ALLOCATE;
	np->maxlen=p->maxlen+1;
	last=np;
	while(p&&!p->trans[c]){
		p->trans[c]=np;
		p=p->prev;
	}
	if(!p)
		np->prev=root;
	else{
		node* q=p->trans[c];
		if(q->maxlen==p->maxlen+1)
			np->prev=q;
		else{
			node* nq=ALLOCATE;
			nq->trans=q->trans;
			nq->maxlen=p->maxlen+1;
			nq->prev=q->prev;
			q->prev=nq;
			np->prev=nq;
			while(p&&p->trans[c]==q){
				p->trans[c]=nq;
				p=p->prev;
			}
		}
	}
}

int n;
int a[MaxN];
vector<int> ans;

void dfs(node* p){
	DEBUG("dfs(p.id=%d)\n",(int)(p-mem));
	if(ans.size()>=n)
		return;
	auto i=*p->trans.begin();
	ans.push_back(i.first);
	dfs(i.second);
}



int main(int argc, char* argv[]) {

	read(n);
	for(int i=1;i<=n;i++)
		read(a[i]);

	last=root=ALLOCATE;
	for(int i=1;i<=n;i++)
		insert(a[i]);
	for(int i=1;i<=n;i++)
		insert(a[i]);
	PASS;

	dfs(root);

	for(int i=0;i<ans.size();i++)
		if(i==0)
			printf("%d",ans[i]);
		else
			printf(" %d",ans[i]);
	printf("\n");

	return 0;
}


