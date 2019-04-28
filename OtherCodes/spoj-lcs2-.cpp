#pragma GCC optimize(2)

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

const int infinity=1e9;
const int MaxN=100000+10;
const int Charset=27;

char s[MaxN];

struct node{
	int maxlen;
	int max,min;
	node* prev;
	node* tr[Charset];
};

node* root,*last;
node mem[2*MaxN],*memtop=mem;
#define ALLOCATE (memtop++)

void insert(int ch){
	node* u=ALLOCATE;
	u->maxlen=last->maxlen+1;
	node* p=last;
	last=u;
	while(p&&!p->tr[ch]){
		p->tr[ch]=u;
		p=p->prev;
	}
	if(!p)
		u->prev=root;
	else{
		node* q=p->tr[ch];
		if(q->maxlen==p->maxlen)
			u->prev=q;
		else{
			node* nq=ALLOCATE;
			memcpy(nq->tr,q->tr,sizeof(q->tr));
			nq->maxlen=p->maxlen+1;
			nq->prev=q->prev;
			u->prev=q->prev=nq;
			while(p&&p->tr[ch]==q){
				p->tr[ch]=nq;
				p=p->prev;
			}
		}
	}
}

node* a[2*MaxN];
int cnt;
int c[2*MaxN];

bool cmp(node* x,node* y){
	return x->maxlen>y->maxlen;
}


int main(int argc, char* argv[]) {

	scanf("%s",s);
	int len=strlen(s);
	last=root=ALLOCATE;
	for(int i=0;i<len;i++)
		insert(s[i]-'a');

//	cnt=memtop-mem;
//	for(int i=0;i<cnt;i++)
//		a[i]=mem+i;
//	sort(a,a+cnt,cmp);
	cnt=memtop-mem;
	int maxpos=0;
	for(int i=0;i<cnt;i++){
		maxpos=max(maxpos,mem[i].maxlen);
		c[mem[i].maxlen]++;
	}
	for(int i=1;i<=maxpos;i++)
		c[i]+=c[i-1];
	for(int i=0;i<cnt;i++)
		a[(c[mem[i].maxlen]--)-1]=mem+i;


	for(node* p=mem;p<memtop;p++){
		p->min=infinity;
	}

	while(scanf("%s",s)>0){
		len=strlen(s);
		node* p=root;
		int st=0;
		for(int i=0;i<len;i++){
			int c=s[i]-'a';
			if(!p->tr[c]){
				while(p&&!p->tr[c])
					p=p->prev;
				if(!p){
					p=root;
					st=0;
				}else{
					st=p->maxlen+1;
					p=p->tr[c];
				}
			}else{
				st++;
				p=p->tr[c];
			}
			p->max=max(p->max,st);
		}
		for(int i=0;i<cnt;i++){
			node* x=a[i];
			x->min=min(x->min,x->max);
			if(x->prev)
				x->prev->max=max(x->prev->max,x->max);
			x->max=0;
		}
	}

	int ans=0;
	for(int i=0;i<cnt;i++)
		if(mem[i].min<infinity)
			ans=max(ans,mem[i].min);

	printf("%d\n",ans);


	return 0;
}



