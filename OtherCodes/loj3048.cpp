// 十二省联考 异或粽子

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <queue>
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

const int MaxN=500000+10,MaxK=200000+10;
typedef long long ll;

int n,k;
ll a[MaxN],s[MaxN];

struct node{
	int cnt,size;
	node* ch[2];
};

node* root;
node mem[MaxN*32],*memtop=mem;
#define ALLOCATE (++memtop)

void insert(ll val){
	node* p=root;
	for(int i=31;i>=0;i--){
		int step=(val>>i)&1;
		p->size++;
		if(!p->ch[step])
			p->ch[step]=ALLOCATE;
		p=p->ch[step];
	}
	p->size++;
	p->cnt++;
}

int nsize(node* p){
	return p?p->size:0;
}

ll kth(ll val,int k){
	ll ans=0;
	node* p=root;
	for(int i=31;i>=0;i--){
		int step=(val>>i)&1;
		if(nsize(p->ch[step^1])>=k){
			ans|=((step^1)<<i);
			p=p->ch[step^1];
		}
		else{
			ans|=(step<<i);
			k-=nsize(p->ch[step^1]);
			p=p->ch[step];
		}
	}
	return ans;
}

struct st{
	st(){}
	st(int i,int k,ll sum):i(i),k(k),sum(sum){}

	int i,k;
	ll sum;

	bool operator < (const st right) const{
		return sum<right.sum;
	}
};

priority_queue<st> Q;




int main(int argc, char* argv[]) {

	read(n);read(k);
	k*=2;
	for(int i=1;i<=n;i++)
		read(a[i]);
	for(int i=1;i<=n;i++)
		s[i]=s[i-1]^a[i];
	PASS;

	root=ALLOCATE;
	for(int i=0;i<=n;i++)
		insert(s[i]);
	PASS;
	for(int i=0;i<=n;i++){
		ll ks=kth(s[i],1);
//		if(ks==s[i]&&n>1){
//			Q.push(st(i,2,s[i]^kth(s[i],2)));
//		}else
			Q.push(st(i,1,s[i]^ks));
	}

	PASS;

	ll ans=0;
	for(int i=1;i<=k;i++){
		st x=Q.top();
		Q.pop();
		DEBUG("(i=%d s=%lld, k=%d s=%lld)\n",x.i,s[x.i],x.k,kth(s[x.i],x.k));
		ans+=x.sum;
		ll ks=kth(s[x.i],x.k+1);
//		if(ks!=s[x.i])
//		if(x.k<=n)
			Q.push(st(x.i,x.k+1,s[x.i]^kth(s[x.i],x.k+1)));
//		else
//			Q.push(st(x.i,x.k+2,s[x.i]^kth(s[x.i],x.k+2)));
	}
	
	printf("%lld\n",ans/2);


	return 0;
}


