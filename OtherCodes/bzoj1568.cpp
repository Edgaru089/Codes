#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <climits>
#include <string>
#include <cmath>
using namespace std;

#if (defined LOCAL) || (defined D)
#define DEBUG(...) do{printf(__VA_ARGS__);fflush(stdout);}while(false)
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
template<>
void read<string>(string& val){
	val.clear();
	int c;
	while(iscntrl(c=getchar())||c==' '||c=='\t');
	do{
		val.push_back(c);
	}while(!(iscntrl(c=getchar())||c==' '||c=='\t'));
	return;
}


const int MaxN=100000+10;
const int MaxT=50000+10;

int n;
string k;
int x,y;

struct node{
	int left,right;
	double k,b;          // 直线参数
	node* lson,*rson;
};

node* root;
node mem[2.2*MaxT],*memtop=mem;
#define ALLOCATE (++memtop)

const double xval=-100000.0;

pair<double,double> intersect(double k1,double b1,double k2,double b2){
	if(k1==k2)
		return make_pair(xval,xval);
	else{
		double x=(b2-b1)/(k1-k2);
		return make_pair(x,k1*x+b1);
	}
}

bool issame(double x,double y){
	return fabs(x-y)<1e6;
}

void build(int left=1,int right=MaxT-10,node*& p=root){
	p=ALLOCATE;
	p->left=left;
	p->right=right;
	if(left==right){
		p->k=p->b=xval;
	}else{
		int mid=(left+right)/2;
		build(left,mid,p->lson);
		build(mid+1,right,p->rson);
		p->k=p->b=xval;
	}
}

void insert(int left,int right,double k,double b,node* p=root){
	DEBUG("Insert(left=%d, right=%d, k=%.3lf, b=%.3lf, p->left=%d, p->right=%d, p->k=%.3lf, p->b=%.3lf, ix=%.3lf, iy=%.lf)\n",
			left,right,k,b,p->left,p->right,p->k,p->b,intersect(k,b,p->k,p->b).first,intersect(k,b,p->k,p->b).second);
	if(k==xval&&b==xval)
		return;
	if(p->left==left&&p->right==right){
		int mid=(left+right)/2;
		pair<double,double> px=intersect(p->k,p->b,k,b);
		double x=px.first,y=px.second;
		if((x<left&&!issame(x,left))||(x>right&&!issame(x,right))){
			if(p->k*mid+p->b<k*mid+b){
				p->k=k;
				p->b=b;
			}
		}else{
			if(x<mid||issame(x,mid)){
				if(p->k*left+p->b<k*left+b){
					insert(left,mid,p->k,p->b);
					p->k=k;
					p->b=b;
				}else
					insert(left,mid,k,b);
			}else{
				if(p->k*right+p->b<k*right+b){
					insert(mid+1,right,p->k,p->b);
					p->k=k;
					p->b=b;
				}else
					insert(mid+1,right,k,b);
			}
		}
	}else if(p->lson->right>=right)
		insert(left,right,k,b,p->lson);
	else if(p->rson->left<=left)
		insert(left,right,k,b,p->rson);
	else{
		insert(left,p->lson->right,k,b,p->lson);
		insert(p->rson->left,right,k,b,p->rson);
	}
}

double query(int pos,node* p=root){
	double curans=p->k*pos+p->b,nextans=xval;
	if(p->left!=p->right){
		if(p->lson->right>=pos)
			nextans=query(pos,p->lson);
		else /* p->rson->left <= pos */
			nextans=query(pos,p->rson);
	}
	return max(curans,nextans);
}


int main(int argc, char* argv[]) {

	read(n);
	build();
	double a,b;
	for(int i=1;i<=n;i++){
		read(k);
		DEBUG("string k=%s\n",k.c_str());
		if(k[0]=='P'){        // Project
			scanf("%lf%lf\n",&a,&b);
			insert(1,MaxT-10,a,b);
		}else if(k[0]=='Q'){  // Query
			read(x);
			printf("%.0lf\n",query(x)/100.0f);
		}
	}

	return 0;
}


