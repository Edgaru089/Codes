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

typedef long long ll;
const int MaxN=1e5+10,MaxM=1e5+10;

int n,m;
ll a[MaxN],c[MaxN];
ll r[MaxN];
ll t,d;

// orig --> sorted
int sid[MaxN];
// sorted --> orig
int rsid[MaxN];

struct node{
	int left,right;
	ll sum;
	node* lson,*rson;
};

node* root;
node mem[2*MaxN],*memtop=mem;
#define ALLOCATE (++memtop)

void build(int left=1,int right=n,node*& p=root){
	p=ALLOCATE;
	p->left=left;
	p->right=right;
	if(left==right){
		r[left]=a[left];
		p->sum=a[left];
	}else{
		int mid=(left+right)/2;
		build(left,mid,p->lson);
		build(mid+1,right,p->rson);
		p->sum=p->lson->sum+p->rson->sum;
	}
}

int queryminpos(node* p=root){
	if(p->left==p->right)
		return p->left;
	if(p->lson->sum>0)
		return queryminpos(p->lson);
	else if(p->rson->sum>0)
		return queryminpos(p->rson);
	else
		return -1;
}

int query(){
	return rsid[queryminpos()];
}


void minuspos(int pos,ll val,node* p=root){
	if(p->left==p->right&&p->left==pos){
		r[rsid[p->left]]-=val;
		p->sum-=val;
		return;
	}
	if(p->lson->right>=pos)
		minuspos(pos,val,p->lson);
	else if(p->rson->left<=pos)
		minuspos(pos,val,p->rson);
	p->sum=p->lson->sum+p->rson->sum;
}

int minus(int origpos,ll val){
	minuspos(sid[origpos],val);
}

bool cmp(int x,int y){
	return c[x]<c[y]||(c[x]==c[y]&&x<y);
}


int main(int argc, char* argv[]) {
	
	read(n);read(m);
	for(int i=1;i<=n;i++)
		read(a[i]);
	for(int i=1;i<=n;i++)
		read(c[i]);

	for(int i=1;i<=n;i++)
		sid[i]=i;
	sort(sid+1,sid+n+1,cmp);
	for(int i=1;i<=n;i++)
		rsid[sid[i]]=i;

	build();

	for(int i=1;i<=m;i++){
		ll ans=0;
		read(t);read(d);
		if(r[t]>=d){
			ans=c[t]*d;
			minuspos(t,d);
		}else{
			ans+=c[t]*r[t];
			d-=r[t];
			minuspos(t,r[t]);
			while(d>0){
				int pos=queryminpos();
				if(pos==-1){
					ans=0;
					break;
				}else{
					int delta=min(d,r[pos]);
					d-=delta;
					minuspos(pos,delta);
					ans+=c[pos]*delta;
				}
			}
		}
		cout<<ans<<endl;
	}
	
	
	return 0;
}


