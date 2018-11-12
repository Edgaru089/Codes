/*
 DOCUMENT NAME "20181105-luogu1966.cpp"
 CREATION DATE 2018-11-05
 SIGNATURE CODE_20181105_LUOGU1966
 COMMENT P1966 火柴排队
*/

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

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

const int MaxN=10000000+10;
const int Mod=99999997;

int n;
int a[MaxN],b[MaxN];
int ia[MaxN],ib[MaxN];
int ixa[MaxN],ixb[MaxN];
int c[MaxN];


struct node{
	int left,right;
	int sum;
	node* lson,*rson;
};

node* root;
node mem[2*MaxN],*memtop=mem;
#define ALLOCATE (++memtop)

void build(int left=1,int right=n,node*& p=root){
	p=ALLOCATE;
	p->left=left;
	p->right=right;
	if(left!=right){
		int mid=(left+right)/2;
		build(left,mid,p->lson);
		build(mid+1,right,p->rson);
	}
}

void update(node* p){
	if(p->lson&&p->rson)
		p->sum=p->lson->sum+p->rson->sum;
}

void add(int pos,int val,node* p=root){
	if(p->left==pos&&p->right==pos){
		p->sum+=val;
		return;
	}
	if(p->lson->right>=pos)
		add(pos,val,p->lson);
	else
		add(pos,val,p->rson);
	update(p);
}

int query(int left,int right,node* p=root){
	if(p->left==left&&p->right==right)
		return p->sum;
	if(p->lson->right>=right)
		return query(left,right,p->lson);
	else if(p->rson->left<=left)
		return query(left,right,p->rson);
	else
		return query(left,p->lson->right,p->lson)+
			   query(p->rson->left,right,p->rson);
}

bool cmpa(int ix,int iy){
	return a[ix]<a[iy];
}

bool cmpb(int ix,int iy){
	return b[ix]<b[iy];
}


int main(int argc, char* argv[]) {

	read(n);
	for(int i=1;i<=n;i++)
		read(a[i]);
	for(int i=1;i<=n;i++)
		read(b[i]);
	for(int i=1;i<=n;i++)
		ia[i]=ib[i]=i;

	sort(ia+1,ia+n+1,cmpa);
	sort(ib+1,ib+n+1,cmpb);

	for(int i=1;i<=n;i++)
		c[ib[i]]=ia[i];

	long long ans=0;
	build();
	for(int i=1;i<=n;i++){
		if(c[i]<n)
			ans+=query(c[i]+1,n);
		add(c[i],1);
	}

	printf("%lld\n",ans%Mod);

	return 0;
}

