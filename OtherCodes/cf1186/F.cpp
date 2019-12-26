#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
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
#define PRINTARR2D(formatstr, arr, beginoff, size, beginy, sizey)\
do{fprintf(stderr,#arr ":");									\
for (int __i = beginy; __i <= beginy + sizey - 1; __i++)		\
	fprintf(stderr,"\t%d", __i);								\
fprintf(stderr,"\n");											\
for (int __i = beginoff; __i <= beginoff + size - 1; __i++) {	\
	fprintf(stderr, "%d:", __i);								\
	for(int __j = beginy; __j <= beginy + sizey -1; __j++)		\
		fprintf(stderr,"\t" formatstr, arr[__i][__j]);			\
	fprintf(stderr, "\n");										\
}}while(false)
#else
#define DEBUG(...)
#define PRINTARR(a, b, c, d)
#define PRINTARR2D(a, b, c, d, e, f)
#define PASS
#define ASSERT(expr)
#endif

#define FOR(i, first, last)               for(int i = (first); i <= (last); ++i)
#define ROF(i, last, first)               for(int i = (last); i >= (first); --i)
#define FORSTEP(i, first, last, step)     for(int i = (first); i <= (last); i += (step))
#define ROFSTEP(i, last, first, stepabs)  for(int i = (last); i >= (first); i -= (step))

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

const int MaxN=1e6+10,MaxM=1e6+10;

int n,m;
int m0;
int u[MaxN],v[MaxN];

struct node{
	int v;
	int id;
	node* next;
};

node* h[MaxN];
node mem[2*MaxM+2*MaxN],*memtop=mem;
#define ALLOCATE (++memtop)

int deg[MaxN];

void addedge(int u,int v,int id){
	node* p=ALLOCATE;
	p->v=v;
	p->id=id;
	p->next=h[u];
	h[u]=p;
	p=ALLOCATE;
	p->v=u;
	p->id=id;
	p->next=h[v];
	h[v]=p;
	deg[u]++;
	deg[v]++;
}

int ssize[MaxN];
bool been[MaxN];
bool path[MaxN];
bool killed[MaxM+MaxN];

void dfs0(int u,int& cnt){
	cnt+=deg[u];
	been[u]=true;
	for(node* p=h[u];p;p=p->next){
		if(!been[p->v])
			dfs0(p->v,cnt);
	}
}

vector<int> eu;
void dfs(int u,int sa){
	for(node* p=h[u];p;p=p->next){
		if(!path[p->id]){
			path[p->id]=true;
			eu.push_back(p->id);
			if(eu.size()==sa)
				throw 0;
			dfs(p->v,sa);
			eu.pop_back();
			path[p->id]=false;
		}
	}
}



int main(int argc, char* argv[]) {

	read(n);read(m);
	FOR(i,1,m){
		read(u[i]);
		read(v[i]);
		addedge(u[i],v[i],i);
	}

	m0=m;
	FOR(i,1,n){
		if(deg[i]&1){
			m++;
			u[m]=0;
			v[m]=i;
			addedge(0,i,-1);
			DEBUG("Adding (0, %d)\n",i);
		}
	}

	FOR(i,0,n){
		if(!been[i]){
			dfs0(i,ssize[i]);
			ssize[i]/=2;
			DEBUG("i=%d, ssize[i]=%d\n",i,ssize[i]);
		}
	}

#ifdef D
	FOR(i,0,n){
		for(node* p=h[i];p;p=p->next)
			DEBUG("%d %d\n",i,p->v);
	}
#endif
	
	memset(been,0,sizeof(been));

	FOR(i,0,n){
		if(ssize[i]>0){
			eu.clear();
			try{
				dfs(i,ssize[i]);
			}catch(int x){
				DEBUG("Caught int=%d\n",x);
				ASSERT(x==0);
			}
			DEBUG("i=%d, eu.size()=%lld\n",i,(long long)eu.size());
			//PRINTARR("%d",eu,0,eu.size());
			FOR(j,0,(int)eu.size()-1){
				PASS;
				if(j&1){
					if(eu[j]>0){
						int l=j-1,r=j+1;
						if(l<0)
							l=eu.size()-1;
						if(r>=eu.size())
							r=0;
						if(eu[l]>0&&eu[r]>0)
							killed[eu[j]]=true;
					}
				}
			}
		}
	}

	int ans=0;
	FOR(i,1,m0)
		if(!killed[i])
			ans++;
	printf("%d\n",ans);
	FOR(i,1,m0)
		if(!killed[i])
			printf("%d %d\n",u[i],v[i]);




	return 0;
}


// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP

