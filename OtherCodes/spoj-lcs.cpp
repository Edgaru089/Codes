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

const int MaxN=250000+10;
const int Charset=27;

struct node{
	int maxlen;
	node* trans[27];
	node* prev;
};

node* root,*last;
node mem[2*MaxN],*memtop=mem;
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
			memcpy(nq->trans,q->trans,sizeof(nq->trans));
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

char s1[MaxN],s2[MaxN];
int len1,len2;


int main(int argc, char* argv[]) {

	root=ALLOCATE;
	last=root;

	scanf("%s%s",s1+1,s2+1);
	len1=strlen(s1+1);
	len2=strlen(s2+1);

	for(int i=1;i<=len1;i++)
		insert(s1[i]-'a');

	node* p=root;
	int len,ans=0;
	for(int i=1;i<=len2;i++){
		if(p->trans[s2[i]-'a']){
			len++;
			p=p->trans[s2[i]-'a'];
		}else{
			while(p&&!p->trans[s2[i]-'a'])
				p=p->prev;
			if(p){
				len=p->maxlen+1;
				p=p->trans[s2[i]-'a'];
			}
			else{
				p=root;
				len=0;
			}
		}
		ans=max(ans,len);
	}

	printf("%d\n",ans);

	return 0;
}


