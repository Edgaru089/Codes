#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <cmath>
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
		fprintf(stderr,"Debug Assertion Failed on line %d, in function %s:\n  Expression: %s\n",__LINE__,__func__,#expr);\
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
void read<string>(string& str){
	str.clear();
	int c;
	while(iscntrl(c=getchar())||c==' '||c=='\t');
	do{
		str.push_back(c);
	}while(!(iscntrl(c=getchar())||c==' '||c=='\t'));
}

const int MaxN=200000+10,LogN=(int)(log2(MaxN))+2;

int n,m;
int p[MaxN];

struct node{
	int v;
	node* next;
};
node* h[MaxN];
node mem[2*MaxN],*memtop=mem;
#define ALLOCATE (++memtop)

void addedge(int u,int v){
	node* p=ALLOCATE;
	p->v=v;
	p->next=h[u];
	h[u]=p;
	p=ALLOCATE;
	p->v=u;
	p->next=h[v];
	h[v]=p;
}

namespace st{
	int n,d[2*MaxN];
	int lg[2*MaxN];
	int st[2*MaxN][LogN+1];
	int stpos[2*MaxN][LogN+1];

	void init(){
		lg[0]=1;
		for(int i=1;i<=n;i++){
			lg[i]=lg[i-1];
			if(i==(1<<lg[i]))
				lg[i]++;
		}

		for(int i=1;i<=n;i++){
			st[i][0]=d[i];
			stpos[i][0]=i;
		}
		for(int j=1;j<=lg[n];j++)
			for(int i=1;i<=n-(1<<j)+1;i++){
				int l=i,r=i+(1<<(j-1)),len=1<<(j-1);
				if(st[l][len]<st[r][len]){
					st[i][j]=st[l][len];
					stpos[i][j]=stpos[l][len];
				}else{
					st[i][j]=st[r][len];
					stpos[i][j]=stpos[r][len];
				}
//				st[i][j]=OP(st[i][j-1],st[i+(1<<(j-1))][j-1]);
			}
	}

	int query(int l,int r){
		if(l>r)
			swap(l,r);
		int len=r-l+1;
		int lglen=lg[len];
		int rx=r-(1<<lglen)+1;
//		return OP(st[l][lglen],st[r-(1<<lglen)+1][lglen]);
		if(st[l][lglen]<st[rx][lglen])
			return stpos[l][lglen];
		else
			return stpos[rx][lglen];
	}
}


int dep[MaxN],pos[MaxN];
int did[2*MaxN];

void dfs(int u,int from,int step){
	dep[u]=step;
	did[++st::n]=u;
	st::d[st::n]=step;
	pos[u]=st::n;
	for(node* p=h[u];p;p=p->next){
		int v=p->v;
		if(v!=from){
			dfs(v,u,step+1);
			st::d[++st::n]=step;
			did[st::n]=u;
		}
	}
}

int lca(int u,int v){
	return did[st::query(pos[u],pos[v])];
}

int pmax[MaxN],pmaxid[MaxN];
int pans[MaxN];


int main(int argc, char* argv[]) {

	read(n);read(m);
	for(int i=1;i<=n;i++){
		int v;
		read(p[i]);read(v);
		if(v!=0)
			addedge(i,v);
	}

	dfs(1,0,1);

	PRINTARR("%d",dep,1,n);
	PRINTARR("%d",did,1,st::n);

	for(int i=1;i<=n;i++){
		if(pmax[p[i]]<dep[i]){
			pmax[p[i]]=dep[i];
			pmaxid[p[i]]=i;
		}
	}

	for(int i=1;i<=n;i++){
		int v=pmaxid[p[i]];
		int x=lca(i,v);
		int len=dep[i]+dep[v]-2*dep[x];
		pans[p[i]]=max(pans[p[i]],len);
	}

	for(int i=1;i<=m;i++)
		printf("%d\n",pans[p[i]]/2);



	return 0;
}


