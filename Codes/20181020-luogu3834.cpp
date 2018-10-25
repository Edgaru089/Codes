/*
 DOCUMENT NAME "20181020-luogu3834.cpp"
 CREATION DATE 2018-10-20
 SIGNATURE CODE_20181020_LUOGU3834
 COMMENT P3834 【模板】可持久化线段树1（主席树）
*/

#include "Overall.hpp"

#ifdef CODE_20181020_LUOGU3834

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

typedef pair<int, int> pii;
const int MaxN = 2e5 + 10;

template<typename IntType>
void read(IntType& x) {
	x = 0;
	int c = 0;
	bool inv = false;
	while (!isdigit(c = getchar()))
		if (c == '-')
			inv = true;
	do {
		x = (x << 1) + (x << 3) + c - '0';
	} while (isdigit(c = getchar()));
	if (inv)
		x = -x;
}

int n, m;
pii d[MaxN];
int ds[MaxN], dx[MaxN];

bool cmp2(const pii& x, const pii& y) {
	return x.second < y.second;
}


struct node{
	int left,right;
	int sum;
	node* lson,*rson;
};

node* root[MaxN];
int vercnt=1;
node mem[4*MaxN],*memtop=mem;
#define ALLOCATE (++memtop)

void build(int left=1,int right=n,node*& p=root[0]){
	p=ALLOCATE;
	p->left=left;
	p->right=right;
	if(left==right){

	}else{
		int mid=(left+right)/2;
		build(left,mid,p->lson);
		build(mid+1,right,p->rson);
	}
}

void _add(int pos,int val,node*& cur,node* prev){
	cur=ALLOCATE;
	memcpy(cur,prev,sizeof(node));
	if(prev->left==prev->right&&prev->right==pos){
		cur->sum+=val;
	}else{
		if(pos<=prev->lson->right)
			_add(pos,val,cur->lson,prev->lson);
		else
			_add(pos,val,cur->rson,prev->rson);
		cur->sum=cur->lson->sum+cur->rson->sum;
	}
}

void addpnt(int pos){
	_add(pos,1,root[vercnt],root[vercnt-1]);
	vercnt++;
}


// (l, r]
int _kth(int k,node* l,node* r){
	if(l->left==l->right)
		return l->left;
	if(k<=r->lson->sum-l->lson->sum)
		return _kth(k,l->lson,r->lson);
	else
		return _kth(k-(r->lson->sum-l->lson->sum),l->lson,r->lson);
}

// [l, r]
int kth(int k,int l,int r){
	return dx[_kth(k,root[l-1],root[r])];
}




int main(int argc, char* argv[]) {

	read(n); read(m);
	for (int i = 1; i <= n; i++) {
		read(d[i].first);
		d[i].second = i;
	}

	sort(d + 1, d + n + 1);
	for (int i = 1; i <= n; i++) {
		dx[i]=d[i].first;
		ds[d[i].second]=i;
	}

	build();

	for(int i=1;i<=n;i++)
		addpnt(ds[i]);

	for(int i=1;i<=m;i++){
		int l,r,k;
		read(l);read(r);read(k);
		printf("%d\n",kth(k,l,r));
	}


	return 0;
}

#endif

