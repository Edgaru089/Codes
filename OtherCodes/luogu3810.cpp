#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
using namespace std;

#if (defined LOCAL) || (defined D)
#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define PRINTARR(formatstr, arr, beginoff, size)				\
do{fprintf(stderr,#arr ":");									\
for (int __i = beginoff; __i <= beginoff + size - 1; __i++)		\
	fprintf(stderr,"\t%d", __i);								\
fprintf(stderr,"\n");											\
for (int __i = beginoff; __i <= beginoff + size - 1; __i++)		\
	fprintf(stderr,"\t" formatstr, arr[__i]);					\
fprintf(stderr,"\n"); }while(false)
#define PASS fprintf(stderr,"Passing function \"%s\" on line %d\n", __func__, __LINE__)
#define ASSERT(expr) do{\
	if(!(expr)){\
		fprintf(stderr,"Debug Assertation Failed on line %d, in function %s:\n  Expression: %s\n",__LINE__,__func__,#expr);\
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

const int MaxN=1e5+10,MaxK=2e5+10;

int n,k;

struct st{
	st(){}
	st(int a,int b,int c):a(a),b(b),c(c){}
	int a,b,c;
	int cnt;
	int id;
	int ans;
	bool operator ==(st right){
		return a==right.a&&b==right.b&&c==right.c;
	}
	bool operator !=(st right){
		return a!=right.a || b!=right.b || c!=right.c;
	}
};

st a0[MaxN];
int aid[MaxN];
st a[MaxN];

bool cmpa(st a,st b){
	return a.a<b.a||
		(a.a==b.a&&a.b<b.b)||
		(a.a==b.a&&a.b==b.b&&a.c<b.c);
}

bool cmpb(st a,st b){
	return a.b<b.b||
		(a.b==b.b&&a.c<b.c);
}


int bs[MaxK];

int lbit(int x){
	return x&(-x);
}

void add(int pos,int x){
	while(pos<=k){
		bs[pos]+=x;
		pos+=lbit(pos);
	}
}

int query(int a){
	int ans=0;
	while(a){
		ans+=bs[a];
		a-=lbit(a);
	}
	return ans;
}


int ans0[MaxN];

void cdq(int l,int r){
	if(l==r)
		return;

	int mid=(l+r)/2;
	cdq(l,mid);
	cdq(mid+1,r);

	sort(a+l,a+mid+1,cmpb);
	sort(a+mid+1,a+r+1,cmpb);

	int x=l,y=mid+1;
	// this is O(n^2)!!!
	//memset(bs,0,sizeof(bs));
	DEBUG("CDQ REP(l=%d, mid=%d, r=%d)\n",l,mid,r);
#ifdef D
	printf("  ");
	for(int i=l;i<=r;i++)
		printf("%3d",i);
	printf("\n");
	printf("a:");
	for(int i=l;i<=r;i++)
		printf("%3d",a[i].a);
	printf("\n");
	printf("b:");
	for(int i=l;i<=r;i++)
		printf("%3d",a[i].b);
	printf("\n");
	printf("c:");
	for(int i=l;i<=r;i++)
		printf("%3d",a[i].c);
	printf("\n");
#endif
	DEBUG("CDQ REP(l=%d, mid=%d, r=%d)\n",l,mid,r);
	while(y<=r){
		DEBUG("   REP IXE(y=%d)\n",y);
		while(a[x].b<=a[y].b&&x<=mid){
			DEBUG("    REP IXET(x=%d)\n",x);
			add(a[x].c,a[x].cnt);
			x++;
		}
		int delta;
		a[y].ans+=delta=query(a[y].c);
		DEBUG("   REP IXE(y=%d) END, id=%d, DeltaANS=%d\n",y,a[y].id,delta);
		y++;
	}
	// this is O(n\log^2 n)
	for(int i=l;i<x;i++)
		add(a[i].c,-a[i].cnt);
}


int main(int argc, char* argv[]) {

	int n0;
	read(n0);read(k);
	for(int i=1;i<=n0;i++){
		read(a0[i].a);
		read(a0[i].b);
		read(a0[i].c);
		a0[i].id=i;
	}

	sort(a0+1,a0+n0+1,cmpa);
	
	int cnt=0;
	n=0;
	for(int i=1;i<=n0;i++){
		aid[i]=n+1;
		cnt++;
		if(a0[i]!=a0[i+1]||i==n0){
			n++;
			a[n]=a0[i];
			a[n].cnt=cnt;
			cnt=0;
		}
	}

#ifdef D
	printf("   ");
	for(int i=1;i<=n;i++)
		printf("%3d",i);
	printf("\n");
	printf("a: ");
	for(int i=1;i<=n;i++)
		printf("%3d",a[i].a);
	printf("\n");
	printf("b: ");
	for(int i=1;i<=n;i++)
		printf("%3d",a[i].b);
	printf("\n");
	printf("c: ");
	for(int i=1;i<=n;i++)
		printf("%3d",a[i].c);
	printf("\n");
	printf("cnt");
	for(int i=1;i<=n;i++)
		printf("%3d",a[i].cnt);
	printf("\n");
#endif

	DEBUG("n0=%d, n=%d\n",n0,n);

	cdq(1,n);

	for(int i=1;i<=n;i++)
		ans0[a[i].ans+a[i].cnt-1]+=a[i].cnt;
	for(int i=0;i<n0;i++)
		printf("%d\n",ans0[i]);

	return 0;
}


