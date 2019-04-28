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
const int Charset=26;

struct node{
	int cnt;
	int maxlen;
	node* ch[Charset];
	node* prev;
};

node* root,*last;
node mem[2*MaxN],*memtop=mem;
#define ALLOCATE (++memtop)

void insert(int c){
	node* np=ALLOCATE,*p=last;
	np->cnt=1;
	np->maxlen=p->maxlen+1;
	last=np;
	while(p&&!p->ch[c]){
		p->ch[c]=np;
		p=p->prev;
	}
	if(!p)
		np->prev=root;
	else{
		node* q=p->ch[c];
		if(q->maxlen==p->maxlen+1)
			np->prev=q;
		else{
			node* nq=ALLOCATE;
			memcpy(nq->ch,q->ch,sizeof(q->ch));
			nq->maxlen=p->maxlen+1;
			nq->prev=q->prev;
			np->prev=q->prev=nq;
			while(p&&p->ch[c]==q){
				p->ch[c]=nq;
				p=p->prev;
			}
		}
	}
}

char s[MaxN];
int n;

int c[2*MaxN];
node* d[2*MaxN];
int incnt[2*MaxN];
int cnt;

void tod(node* p){
	d[++cnt]=p;
	for(int i=0;i<Charset;i++){
		if(p->ch[i]){
			incnt[p->ch[i]-mem]--;
			if(incnt[p->ch[i]-mem]==0)
				tod(p->ch[i]);
		}
	}
}

bool cmp(node* x,node* y){
	return x->maxlen<y->maxlen;
}


int main(int argc, char* argv[]) {

	scanf("%s",s);
	n=strlen(s);

	last=root=ALLOCATE;
	for(int i=0;i<n;i++)
		insert(s[i]-'a');

//	for(node* p=mem+1;p<=memtop;p++)
//		for(int i=0;i<Charset;i++)
//			if(p->ch[i])
//				incnt[p->ch[i]-mem]++;
//	tod(root);
//	ASSERT(cnt==(memtop-mem));

//	cnt=memtop-mem;
//	for(int i=1;i<=cnt;i++)
//		d[i]=mem+i;
//	sort(d+1,d+cnt+1,cmp);
	cnt=memtop-mem;
	int maxpos=0;
	for(int i=1;i<=cnt;i++){
		c[mem[i].maxlen]++;
		maxpos=max(maxpos,mem[i].maxlen);
	}
	for(int i=1;i<=maxpos;i++)
		c[i]+=c[i-1];
	for(int i=1;i<=cnt;i++)
		d[c[mem[i].maxlen]--]=mem+i;


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
#endif

	int ans=0;
	for(int i=cnt;i>=1;i--){
		node* p=d[i];
		if(p&&p->cnt){
			if(p->prev)
				p->prev->cnt+=p->cnt;
			if(p->cnt>1)
				ans=max(ans,p->maxlen*p->cnt);
		}
	}

	printf("%d\n",ans);


	return 0;
}


