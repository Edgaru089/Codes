// 子串查找
#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
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

const int MaxN=1e6+10;
const int Charset=26*2;

struct node{
	int cnt;
	int maxlen;
	node* trans[Charset];
	node* prev;
};

node* root,*last;
node mem[2*MaxN],*memtop=mem;
#define ALLOCATE (++memtop)

void insert(int ch){
	node* np=ALLOCATE,*p=last;
	last=np;
	np->cnt=1;
	np->maxlen=p->maxlen+1;
	while(p&&!p->trans[ch]){
		p->trans[ch]=np;
		p=p->prev;
	}
	if(!p)
		np->prev=root;
	else{
		node* q=p->trans[ch];
		if(q->maxlen==p->maxlen+1)
			np->prev=q;
		else{
			node* nq=ALLOCATE;
			memcpy(nq->trans,q->trans,sizeof(q->trans));
			nq->maxlen=p->maxlen+1;
			nq->prev=q->prev;
			q->prev=np->prev=nq;
			while(p&&p->trans[ch]==q)
				p->trans[ch]=nq;
		}
	}
}

char s[MaxN];
int n;
node* d[2*MaxN];
int cnt,c[2*MaxN],maxpos;


int conv(char c){
	if(c>='A'&&c<='Z')
		return c-'A';
	else if(c>='a'&&c<='z')
		return c-'a'+26;
	else
		return -1;
}



int main(int argc, char* argv[]) {

	scanf("%s",s);
	n=strlen(s);

	last=root=ALLOCATE;
	for(int i=0;i<n;i++)
		insert(conv(s[i]));

	cnt=memtop-mem;
	for(int i=1;i<=cnt;i++){
		maxpos=max(maxpos,mem[i].maxlen);
		c[mem[i].maxlen]++;
	}
	for(int i=1;i<=maxpos;i++)
		c[i]+=c[i-1];
	for(int i=1;i<=cnt;i++)
		d[c[mem[i].maxlen]--]=i+mem;

	for(int i=cnt;i>=1;i--)
		if(d[i]->prev)
			d[i]->prev->cnt+=d[i]->cnt;

	scanf("%s",s);
	n=strlen(s);

	int ans=0;
	node* p=root;
	for(int i=0;i<n;i++){
		int c=conv(s[i]);
		if(!p->trans[c]){
			while(p&&!p->trans[c])
				p=p->prev;
			if(!p)
				break;
			else
				p=p->trans[c];
		}else{
			p=p->trans[c];
		}
	}

	if(!p)
		ans=0;
	else
		ans=p->cnt;

	printf("%d\n",ans);


	return 0;
}


