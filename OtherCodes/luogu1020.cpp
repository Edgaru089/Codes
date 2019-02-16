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

const int MaxN=100000+10,MaxA=50000+10;

int n;
int a[MaxN];

class segtree{
public:
	segtree():memtop(mem){
	}
public:

	struct node{
		int left,right;
		int max;
		node* lson,*rson;
	};

	node* root;
	node mem[2*MaxA],*memtop;

	void build(){
		root=0;
		memtop=mem;
		_build(1,MaxA,root);
	}

	void _build(int left,int right,node*& p){
		p=++memtop;
		p->left=left;
		p->right=right;
		p->max=0;
		if(left!=right){
			int mid=(left+right)/2;
			_build(left,mid,p->lson);
			_build(mid+1,right,p->rson);
		}else
			p->lson=p->rson=0;
	}
	
	int query(int left,int right,node* p){
		if(right<left)
			return 0;
		if(p->left==left&&p->right==right)
			return p->max;
		if(p->lson->right>=right)
			return query(left,right,p->lson);
		else if(p->rson->left<=left)
			return query(left,right,p->rson);
		else
			return max(query(left,p->lson->right,p->lson),
					   query(p->rson->left,right,p->rson));
	}

	void updatepnt(int pos,int val,node* p){
		if(p->left==pos&&p->right==pos)
			p->max=max(p->max,val);
		else{
			if(p->lson->right>=pos)
				updatepnt(pos,val,p->lson);
			else
				updatepnt(pos,val,p->rson);
			p->max=max(p->lson->max,p->rson->max);
		}
	}


};

segtree s;

int run(int* arr,int n,bool equal=true){
	s.build();
	int ans=0;
	for(int i=1;i<=n;i++){
		int prev;
		if(equal)
			prev=s.query(1,arr[i],s.root);
		else
			prev=s.query(1,arr[i]-1,s.root);
		s.updatepnt(arr[i],prev+1,s.root);
		ans=max(ans,prev+1);
	}
	return ans;
}




int main(int argc, char* argv[]) {
	
	n=0;
	int x;
	while(cin>>x&&x)
		a[++n]=x;
	
	for(int i=1;i<=n;i++)
		a[i]=50001-a[i];
	printf("%d\n",run(a,n));
	for(int i=1;i<=n;i++)
		a[i]=50001-a[i];
	printf("%d\n",run(a,n,false));
	
	return 0;
}


