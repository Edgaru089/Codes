#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>

#ifdef D
#include <custom/Debug.hpp>
#endif

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
#define PRINT(...) dbg(__VA_ARGS__)
#define PRINTVAL(...) dbgv(__VA_ARGS__)
#define PRINTSEQ(...) dbgr(__VA_ARGS__)
#define PRINTSEQVAL(...) dbgm(__VA_ARGS__)
#define PRINTCOMPACT(...) dbgs(__VA_ARGS__)
#else
#define DEBUG(...)
#define PRINTARR(a, b, c, d)
#define PRINTARR2D(a, b, c, d, e, f)
#define PASS
#define ASSERT(expr)
#define PRINT(...)
#define PRINTVAL(...)
#define PRINTSEQ(...)
#define PRINTSEQVAL(...)
#define PRINTCOMPACT(...)
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
#if __cplusplus >= 201103
template<typename IntType,typename... Args>
void read(IntType& val, Args&... args){
	read(val); read(args...);
}
#endif

// End of template:edgar:edgar-laptop(LAPTOP-EDGAR-15)

const int MaxN=10000+10,MaxM=100+10,MaxK=10000000+10;

int n,m;
int q[MaxM];
bool ans[MaxM];

vector<pair<int,int>> h[MaxN];

void addedge(int u,int v,int len){
	h[u].push_back(make_pair(v,len));
	h[v].push_back(make_pair(u,len));
}


bool been[MaxN];

int getsize(int u,int from){
	int ss=1;
	for(auto[v,len]:h[u]){
		if(!been[v]&&v!=from){
			ss+=getsize(v,u);
		}
	}
	return ss;
}

pair<int,int> getroot(int u,int from,int& ss,int tss){
	ss=1;
	int mx,ms=n+1;
	int cmaxs=0;
	for(auto[v,len]:h[u]){
		if(!been[v]&&v!=from){
			int sv;
			auto[vx,vs]=getroot(v,u,sv,tss);
			if(ms>vs){
				mx=vx;
				ms=vs;
			}
			cmaxs=max(cmaxs,sv);
			ss+=sv;
		}
	}
	cmaxs=max(cmaxs,tss-ss);
	if(ms>cmaxs){
		ms=cmaxs;
		mx=u;
	}
	return make_pair(mx,ms);
}

int dis[MaxN];
vector<int> childs;

void getdis(int u,int from,int l){
	DEBUG("      getdis(u=%d, from=%d, l=%d), childs.size()=%d\n",u,from,l,(int)childs.size());
	dis[u]=l;
	childs.push_back(u);

	been[u]=true;
	for(auto[v,len]:h[u]){
		if(!been[v]&&v!=from){
			getdis(v,u,l+len);
		}
	}
	//been[u]=false;
}

bool ex[MaxK];
vector<int> es;

void getans(int u){
	DEBUG("getans(u=%d)\n",u);
	for(auto[v,len]:h[u]){
		if(!been[v]){
			DEBUG("   checking v=%d, len=%d\n",v,len);
			childs.clear();
			getdis(v,u,len);
			DEBUG("   getdis done, childs.size()=%d\n",(int)childs.size());
			FOR(i,1,m){
				if(ans[i])
					continue;
				for(int x:childs){
					if(dis[x]<=MaxK+q[i]-5&&q[i]-dis[x]>=0&&ex[q[i]-dis[x]]){
						ans[i]=true;
						break;
					}
				}
			}
			for(int x:childs){
				if(dis[x]<=MaxK&&!ex[dis[x]]){
					ex[dis[x]]=true;
					es.push_back(dis[x]);
				}
				been[x]=false;
			}
		}
	}
	FOR(i,1,m)
		if(ex[q[i]])
			ans[i]=true;
	for(int x:es)
		ex[x]=false;
	es.clear();
}

void dfs(int u){
	been[u]=true;

	getans(u);

	for(auto[v,len]:h[u]){
		if(!been[v]){
			int sv=getsize(v,u);
			dfs(getroot(v,u,sv,sv).first);
		}
	}

	been[u]=false;
}





int main(int argc, char* argv[]) {

	read(n,m);
	FOR(i,1,n-1){
		int u,v,l;
		read(u,v,l);
		addedge(u,v,l);
	}

	//int sv=getsize(1,0);
	//auto[r,rx]=getroot(1,0,sv,sv);
	//printf("r=%d, rx=%d\n",r,rx);

	FOR(i,1,m)
		read(q[i]);

	dfs(1);

	FOR(i,1,m)
		if(ans[i])
			printf("AYE\n");
		else
			printf("NAY\n");

	return 0;
}

// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP

