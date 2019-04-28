// bzoj3998 [TJOI2015] 弦论
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

const int MaxN=500000+10;
const int Charset=26;

struct node{
	int maxlen;
	int cnt,size;
	node* ch[Charset];
	node* prev;
};

node* root,*last;
node mem[2*MaxN],*memtop=mem;
#define ALLOCATE (++memtop)

void insert(int c){
	node* p=last,*np=ALLOCATE;
	np->cnt=1;
	np->maxlen=p->maxlen+1;
	last=np;
	while(p&&!p->ch[c]){
		p->ch[c]=np;
		p=p->prev;
	}
	if(!p){
		np->prev=root;
	}else{
		node* q=p->ch[c];
		if(q->maxlen==p->maxlen+1)
			np->prev=q;
		else{
			node* nq=ALLOCATE;
			memcpy(nq->ch,q->ch,sizeof(q->ch));
			// nq->cnt=0
			nq->maxlen=p->maxlen+1;
			nq->prev=q->prev;
			q->prev=np->prev=nq;
			while(p&&p->ch[c]==q){
				p->ch[c]=nq;
				p=p->prev;
			}
		}
	}
}

bool cmp(node* x,node* y){
	return x->maxlen>y->maxlen;
}

int n;
char s[MaxN];
node* d[2*MaxN];
int t,k;

void dfs(int k,node* p=root){
	DEBUG("dfs(k=%d, p.id=%d)\n",k,(int)(p-mem));
	if(k==0||p->cnt>=k)
		return;
	k-=p->cnt;
	for(int i=0;i<Charset;i++){
		if(!p->ch[i])
			continue;
		if(k<=p->ch[i]->size){
			putchar(i+'a');
			DEBUG("trans %d='%c'",i,(char)(i+'a'));
			dfs(k,p->ch[i]);
			return;
		}else
			k-=p->ch[i]->size;
	}
}

int main(int argc, char* argv[]) {

	scanf("%s%d%d",s,&t,&k);
	n=strlen(s);

	last=root=ALLOCATE;
	for(int i=0;i<n;i++)
		insert(s[i]-'a');

	int cnt=memtop-mem;
	for(int i=1;i<=cnt;i++)
		d[i]=mem+i;
	sort(d+1,d+cnt+1,cmp);

	// print automation
#ifdef D
	for(int i=1;i<=cnt;i++){
		for(int j=0;j<Charset;j++){
			if(mem[i].ch[j])
				printf("%d %d %c\n",i,(int)(mem[i].ch[j]-mem),(char)(j+'a'));
		}
	}
	printf("------\n");
	for(int i=1;i<=cnt;i++){
		if(mem[i].prev)
			printf("%d %d\n",i,(int)(mem[i].prev-mem));
	}
	printf("------arr------\n");
	for(int i=1;i<=cnt;i++)
		printf(" %d",(int)(d[i]-mem));
	printf("\n");
#endif

	if(t==1){
		for(int i=1;i<=cnt;i++)
			if(d[i]->prev)
				d[i]->prev->cnt+=d[i]->cnt;
		root->cnt=0;
	}else{
		for(int i=1;i<=cnt;i++)
			d[i]->cnt=1;
		root->cnt=0;
	}

	for(int i=1;i<=cnt;i++){
		d[i]->size=d[i]->cnt;
		for(int j=0;j<Charset;j++){
			if(d[i]->ch[j])
				d[i]->size+=d[i]->ch[j]->size;
		}
	}

	if(root->size<k)
		printf("-1\n");
	else{
		dfs(k);
		printf("\n");
	}


	return 0;
}


