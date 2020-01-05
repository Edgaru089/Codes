#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include <queue>
using namespace std;

#define ASSERT(expr) do{\
	if(!(expr)){\
		fprintf(stderr,"Debug Assertion Failed on line %d, in function %s:\n  Expression: %s\n",__LINE__,__func__,#expr);\
		abort();\
	}\
}while(false)

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
#endif

#define FOR(i, first, last)               for(int i = (first); i <= (last); ++i)
#define ROF(i, last, first)               for(int i = (last); i >= (first); --i)
#define FORSTEP(i, first, last, step)     for(int i = (first); i <= (last); i += (step))
#define ROFSTEP(i, last, first, stepabs)  for(int i = (last); i >= (first); i -= (stepabs))

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

const int MaxN=1e5+10;

int n;

struct px{
	int a,b,c;
};

px a[MaxN];

struct node{
	int v;
	node* next;
};

node* h[3*MaxN];
node mem[6*MaxN],*memtop=mem;
#define ALLOCATE (++memtop)

int deg[3*MaxN];
void addedge(int u,int v){
	deg[u]++;
	deg[v]++;
	node* p=ALLOCATE;
	p->v=v;
	p->next=h[u];
	h[u]=p;
	p=ALLOCATE;
	p->v=u;
	p->next=h[v];
	h[v]=p;
}

bool been[3*MaxN];
vector<int> ans;
void dfs(int u){
	been[u]=true;
	ans.push_back(u);
	for(node* p=h[u];p;p=p->next){
		int v=p->v;
		if(!been[v])
			dfs(v);
	}
}

int from[3*MaxN];
void bfs(int n){
	queue<int> Q;
	FOR(i,1,n)
		if(deg[i]==1){
			been[i]=true;
			Q.push(i);
			from[i]=0;
		}
	while(!Q.empty()){
		int u=Q.front();
		Q.pop();
		ans.push_back(u);
		for(node* p=h[u];p;p=p->next){
			int v=p->v;
			if(v!=from[u])
				deg[v]--;
			if(!been[v]&&deg[v]==1){
				been[v]=true;
				Q.push(v);
				from[v]=u;
			}
		}
	}
}

map<pair<int,int>,int> m,cnt;
map<int,pair<int,int>> mr;
int bl[3*MaxN];




int main(int argc, char* argv[]) {

	int t;
	read(t);
	while(t--){

		cnt.clear();
		m.clear();
		mr.clear();

		read(n);
		FOR(i,1,n-2){
			read(a[i].a);
			read(a[i].b);
			read(a[i].c);
			m.insert(make_pair(make_pair(min(a[i].a,a[i].b),max(a[i].a,a[i].b)),0));
			m.insert(make_pair(make_pair(min(a[i].b,a[i].c),max(a[i].b,a[i].c)),0));
			m.insert(make_pair(make_pair(min(a[i].a,a[i].c),max(a[i].a,a[i].c)),0));
			cnt[make_pair(min(a[i].a,a[i].b),max(a[i].a,a[i].b))]++;
			cnt[make_pair(min(a[i].b,a[i].c),max(a[i].b,a[i].c))]++;
			cnt[make_pair(min(a[i].a,a[i].c),max(a[i].a,a[i].c))]++;
		}

		{
			int i=1;
			for(auto&[a,b]:m){
				b=i;
				mr.insert(make_pair(b,a));
				i++;
			}
		}

		memset(h,0,sizeof(node*)*(n+4));
		memtop=mem;
		FOR(i,1,m.size()){
			if(cnt[mr[i]]==1){
				DEBUG("addedge(%d, %d)\n",mr[i].first,mr[i].second);
				addedge(mr[i].first,mr[i].second);
			}
		}

		memset(been,0,sizeof(bool)*(n+4));
		ans.clear();
		dfs(1);
		ASSERT(ans.size() == n);
		printf("%d",ans[0]);
		FOR(i,1,ans.size()-1)
			printf(" %d",ans[i]);
		printf("\n");

		if(n==3){
			printf("1\n");
		}else{
			memset(h,0,sizeof(node*)*(m.size()+4));
			memtop=mem;
			memset(bl,0,sizeof(int)*(m.size()+4));
			memset(deg,0,sizeof(int)*(m.size()+4));
			FOR(i,1,n-2){
				int pi=m[make_pair(min(a[i].a,a[i].b),max(a[i].a,a[i].b))];
				if(bl[pi]==0)
					bl[pi]=i;
				else
					addedge(bl[pi],i);
				pi=m[make_pair(min(a[i].b,a[i].c),max(a[i].b,a[i].c))];
				if(bl[pi]==0)
					bl[pi]=i;
				else
					addedge(bl[pi],i);
				pi=m[make_pair(min(a[i].a,a[i].c),max(a[i].a,a[i].c))];
				if(bl[pi]==0)
					bl[pi]=i;
				else
					addedge(bl[pi],i);
			}

			memset(been,0,sizeof(bool)*(n+4));
			ans.clear();
			bfs(n-2);
			ASSERT(ans.size() == n-2);
			printf("%d",ans[0]);
			FOR(i,1,ans.size()-1)
				printf(" %d",ans[i]);
			printf("\n");

		}
	}

	return 0;
}


// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP

