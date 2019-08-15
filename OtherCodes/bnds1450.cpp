#include <cstdlib>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <list>
#include <vector>
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

const int MaxN=10000+10,MaxK=1000+10;

int n,k;
int a[MaxN];


struct as{
	int a;
	int id;
};

as ak[MaxN],ax[MaxN];

struct st{
	st(){}
	st(int pos,bool k=false):s(pos),t(pos),k(k){}
	st(int s,int t,bool k=false):s(s),t(t),k(k){}
	int s,t;
	bool k;
};

list<st> ans;

bool used[MaxN];

bool cmp(as x,as y){
	return x.a<y.a;
}


int main(int argc, char* argv[]) {

	read(n);
	read(k);
	for(int i=1;i<=n;i++){
		read(a[i]);
		ak[i].a=a[i];
		ak[i].id=i;
	}

	sort(ak+1,ak+k+1,cmp);

	int mink=ak[1].a,maxk=ak[k].a;

	for(int i=1;i<=k;i++)
		ans.push_back(st(i,true));

#ifdef D

#endif

	int m=n-k;
	for(int i=1;i<=m;i++)
		ax[i]=ak[k+i];
	sort(ax+1,ax+m+1,cmp);

	PRINTARR("%d",ax,1,m);

	vector<st> tmp;

	for(list<st>::iterator i=ans.begin();i!=--ans.end();){
		if(!i->k)
			continue;
		int idx=i->s;
		int idy=(++i)->s;
		int x=a[idx],y=a[idy];
		bool rev=false;
		if(x>y){
			rev=true;
			swap(x,y);
		}
		bool pushing=false;
		int ns=0,nt=0;
		DEBUG("Pushing x=%d, y=%d (idx=%d, idy=%d)\n",x,y,idx,idy);
		tmp.clear();
		for(int j=1;j<=m;j++){
			if(!used[j]&&ax[j].a>=x&&ax[j].a<=y){
				DEBUG("  inserting j=%d, id=%d, val=%d\n",j,j+k,ax[j].a);
				used[j]=true;
				if(pushing)
					nt=j+k;
				else{
					pushing=true;
					ns=nt=j+k;
				}
			}else
				if(pushing){
					DEBUG("Insert(Iq) s=%d, t=%d\n",ns,nt);
					tmp.push_back(st(ns,nt));
					pushing=false;
				}

		}
		if(pushing){
			DEBUG("Insert(Oq) s=%d, t=%d\n",ns,nt);
			tmp.push_back(st(ns,nt));
			pushing=false;
		}
		if(rev){
			for(int j=tmp.size();j>=0;j--)
				ans.insert(i,tmp[j]);
		}else{
			for(int j=0;j<tmp.size();j++)
				ans.insert(i,tmp[j]);
		}
	}




	for(list<st>::iterator i=ans.begin();i!=ans.end();i++){
		DEBUG("New iterator\n");
		for(int j=i->s;j<=i->t;j++)
			printf("%d\n",j);
	}


	return 0;
}


