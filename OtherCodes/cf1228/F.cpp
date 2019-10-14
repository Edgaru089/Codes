#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
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
#define PRINTARR_I(formatstr, arr_i, beginoff, size)			\
do{fprintf(stderr,"arr_i:");									\
for (int __i = beginoff; __i <= beginoff + size - 1; __i++)		\
	fprintf(stderr,"\t%d", __i);								\
fprintf(stderr,"\n");											\
for (int i = beginoff; i <= beginoff + size - 1; i++)			\
	fprintf(stderr,"\t" formatstr, arr_i);						\
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
#define PRINTARR_I(a, b, c, d)
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

const int MaxN=17+1;
const int MaxC=1<<MaxN;

int n,c;

vector<int> e[MaxC];

void addedge(int u,int v){
	e[u].push_back(v);
	e[v].push_back(u);
}

enum argtype{
	unknown=0,
	son_of_root,
	middle,
	leaf,
};

char argname[][12]={
	"unknown",
	"son_of_root",
	"middle",
	"leaf",
};


template<typename IntType>
IntType iabs(IntType x){
	return (x<0)?(-x):x;
}

int fcnt;
void _verify_bintree(int u,int from){
	if(e[u].size()!=3&&e[u].size()!=1){
		//fcnt+=iabs(3-e[u].size());
		fcnt+=iabs(max(3,(int)e[u].size())-min(3,(int)e[u].size()));
		DEBUG("defect at u=%d, e[u].size=%d, fcnt=%d\n",u,e[u].size(),fcnt);
	}
	for(int v:e[u]){
		if(v==from)
			continue;
		_verify_bintree(v,u);
	}
}

bool verify_bintree(int u,int from,int tolerance){
	fcnt=0;
	DEBUG("verify_bintree(u=%d, from=%d, tolerance=%d): calling\n",u,from,tolerance);
	_verify_bintree(u,from);
	DEBUG("verify_bintree(u=%d, from=%d, tolerance=%d)->fcnt=%d, %s\n",u,from,tolerance,fcnt,(fcnt<=tolerance)?"true":"false");
	return fcnt<=tolerance;
}

int tsize=-1;
bool _verify_bintree_size(int u,int from,int step=1){
	bool flag=true;
	if(e[u].size()==1)
		if(tsize==-1)
			tsize=step;
		else
			flag=(tsize==step);
	for(int v:e[u]){
		if(!flag)
			break;
		if(v==from)
			continue;
		flag=flag&&_verify_bintree_size(v,u,step+1);
	}
#ifdef D
	if(step==1)
		DEBUG("_verify_bintree_size(u=%d, from=%d)->%s\n",u,from,flag?"true":"false");
#endif
	return flag;
}

bool verify_bintree_size(int u,int from){
	tsize=-1;
	return _verify_bintree_size(u,from,1);
}



int dlen,oth;
vector<int> diam,bt;
void _dfs_getdiam_dryrun(int u,int from,int step){
	if(dlen<step){
		dlen=step;
		oth=u;
	}
	for(int v:e[u]){
		if(v!=from)
			_dfs_getdiam_dryrun(v,u,step+1);
	}
}

void _dfs_getdiam(int u,int from){
	bt.push_back(u);
	if(bt.size()==dlen)
		diam=bt;
	for(int v:e[u]){
		if(v!=from)
			_dfs_getdiam(v,u);
		if(!diam.empty())
			break;
	}
	bt.pop_back();
}

void dfs_getdiam(){
	dlen=0;
	_dfs_getdiam_dryrun(1,0,1);
	_dfs_getdiam_dryrun(oth,0,1);
	_dfs_getdiam(oth,0);
}

int root=0;
int fa[MaxC];

void dfs_fa(int u,int from){
	fa[u]=from;
	for(int v:e[u])
		if(v!=from)
			dfs_fa(v,u);
}

bool udfs_checkchain(int u,int from){

	bool ok=true;
	bool get=false;
	for(int v:e[u])
		if(v!=from&&v!=fa[u]){
			ok=ok&&verify_bintree(v,u,0)&&verify_bintree_size(v,u);
			get=true;
		}
	if(!ok||!get)
		return false;
	else if(u==root)
		return true;
	else
		return udfs_checkchain(fa[u],u);
}

int p[MaxC];
int pcnt;
int setfind(int x){
	if(p[x]<0)
		return x;
	else
		return p[x]=setfind(p[x]);
}

void setunion(int x,int y){
	x=setfind(x);
	y=setfind(y);
	if(x!=y){
		p[x]+=p[y];
		p[y]=x;
		pcnt--;
	}
}



int main(int argc, char* argv[]) {

	read(n);
	c=(1<<n)-2;

	memset(p,-1,sizeof(p));
	pcnt=c;

	for(int i=1;i<=c-1;i++){
		int u,v;
		read(u);read(v);
		addedge(u,v);
		setunion(u,v);
	}

	if(pcnt!=1){
		DEBUG("not connected\n");
		printf("0\n");
		return 0;
	}

	if(n==2){
		printf("2\n1 2\n");
		return 0;
	}

	argtype t=unknown;

	vector<int> deg[6];
	for(int i=1;i<=c;i++){
		if(e[i].size()>4){
			printf("0\n");
			return 0;
		}
		deg[e[i].size()].push_back(i);
	}

	PRINTARR_I("%d",deg[i].size(),0,6);

	if(deg[2].size()==1){
		if(deg[4].size()==1&&verify_bintree(deg[4][0],0,2)){
			dfs_getdiam();
			root=diam[diam.size()/2];
			dfs_fa(root,0);
			DEBUG("deg[4][0]=%d, root=%d\n",deg[4][0],root);
			PRINTARR("%d",fa,1,c);
			if(udfs_checkchain(deg[4][0],0)){
				t=middle;
				printf("1\n%d\n",deg[4][0]);
			}
		}
	}else if(deg[2].size()==2){
		if(verify_bintree(deg[1][0],0,2)){
			dfs_getdiam();
			root=diam[diam.size()/2];
			DEBUG("root=%d\n",root);
			PRINTARR("%d",diam,0,diam.size());
			if(e[root].size()==2){
				DEBUG("root degree success\n");
				t=leaf;
				int ans=0;
				for(int i:deg[2]){
					for(int j:e[i]){
						if(e[j].size()==1){
							ans=i;
							break;
						}
					}
				}
				printf("1\n%d\n",ans);
			}
		}
	}else if(deg[2].size()==0){
		dfs_getdiam();
		int x=diam[diam.size()/2-1];
		int y=diam[diam.size()/2];
		PRINTARR("%d",diam,0,sizeof(diam));

		if(diam.size()/2+1==n&&verify_bintree(x,y,0)&&verify_bintree(y,x,0)){
			if(verify_bintree_size(x,y)){
				tsize=-1;
				if(verify_bintree_size(y,x)){
					if(x>y)
						swap(x,y);
					printf("2\n%d %d\n",x,y);
					t=son_of_root;
				}
			}
		}
	}

	DEBUG("type=%s\n",argname[t]);

	if(t==unknown){
		printf("0\n");
	}


	return 0;
}


