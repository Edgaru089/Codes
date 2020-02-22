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

typedef long long ll;
const int MaxN=1e5+10;

ll n,m;
ll w0[MaxN];
ll w[MaxN];

vector<ll> h[MaxN];
void addedge(ll u,ll v){
	h[u].push_back(v);
	h[v].push_back(u);
}

ll fa[MaxN],ssize[MaxN];
ll dep[MaxN];
void dfs1(ll u,ll from,ll step){
	fa[u]=from;
	dep[u]=step;
	ssize[u]=1;
	for(ll v:h[u]){
		if(v!=from){
			dfs1(v,u,step+1);
			ssize[u]+=ssize[v];
		}
	}
}

ll dfn[MaxN],sstime;
ll hson[MaxN],top[MaxN];
ll tail[MaxN];
vector<ll> childs[MaxN];
void dfs2(ll u,ll t){
	dfn[u]=++sstime;
	top[u]=t;
	tail[t]=u;
	childs[t].push_back(u);
	ll ms=0,mx=0;
	for(ll v:h[u]){
		if(v!=fa[u]){
			if(ssize[v]>mx){
				mx=ssize[v];
				ms=v;
			}
		}
	}
	hson[u]=ms;
	if(ms)
		dfs2(ms,t);
	for(ll v:h[u]){
		if(v!=fa[u]&&v!=ms){
			dfs2(v,v);
		}
	}
}

const ll infinity=1e15;

const ll imat[2][2]={
	{0,-infinity},
	{-infinity,-infinity},
};

void floydmult2(const ll x[][2],const ll y[][2],ll ans[][2]){
	const ll n=2;
	FOR(i,0,n-1)
		FOR(j,0,n-1)
			ans[i][j]=-infinity;
	FOR(i,0,n-1)
		FOR(j,0,n-1)
			FOR(k,0,n-1)
				ans[i][j]=max(ans[i][j],x[i][k]+y[k][j]);
}

ll ldp[MaxN][2];

struct node{
	ll left,right;
	node* lson,*rson;
	ll mat[2][2];
};

node* root;
node mem[3*MaxN],*memtop=mem;
#define ALLOCATE (++memtop)

void update(node* p){
	if(p&&p->lson){
		floydmult2(p->lson->mat,p->rson->mat,p->mat);
	}
}

void build(ll left=1,ll right=n,node*& p=root){
	p=ALLOCATE;
	p->left=left;
	p->right=right;
	if(left==right){
		p->mat[0][0]=p->mat[0][1]=p->mat[1][0]=p->mat[1][1]=-infinity;
	}else{
		ll mid=(left+right)/2;
		build(left,mid,p->lson);
		build(mid+1,right,p->rson);
		update(p);
	}
}

void change(ll pos,ll val[][2],node* p=root){
	if(p->left==pos&&p->right==pos){
		memcpy(p->mat,val,sizeof(p->mat));
		DEBUG("          HIT-> change(pos=%d:p->[left,right]=[%d,%d], mat[0,1][0]=[%d,%d])\n",pos,p->left,p->right,p->mat[0][0],p->mat[1][0]);
		return;
	}
	if(p->lson->right>=pos)
		change(pos,val,p->lson);
	else
		change(pos,val,p->rson);
	update(p);
	DEBUG("                change(pos=%d:p->[left,right]=[%d,%d], mat[0,1][0]=[%d,%d])\n",pos,p->left,p->right,p->mat[0][0],p->mat[1][0]);
}

void query(ll left,ll right,ll ans[][2],node* p=root){
	if(p->left==left&&p->right==right){
		memcpy(ans,p->mat,sizeof(p->mat));
		DEBUG("          HIT->  query([left,right]=[%d,%d]:p->[left,right]=[%d,%d], mat[0,1][0]=[%d,%d])\n",left,right,p->left,p->right,p->mat[0][0],p->mat[1][0]);
		return;
	}
	if(p->lson->right>=right)
		query(left,right,ans,p->lson);
	else if(p->rson->left<=left)
		query(left,right,ans,p->rson);
	else{
		ll ans1[2][2],ans2[2][2];
		query(left,p->lson->right,ans1,p->lson);
		query(p->rson->left,right,ans2,p->rson);
		floydmult2(ans1,ans2,ans);
	}
	DEBUG("                 query([left,right]=[%d,%d]:p->[left,right]=[%d,%d], mat[0,1][0]=[%d,%d])\n",left,right,p->left,p->right,p->mat[0][0],p->mat[1][0]);
}

ll ldt[MaxN][2];

void bindldp(ll u,ll ans[][2]){
	ans[0][0]=ans[0][1]=ldp[u][0];
	ans[1][0]=ldp[u][1];
	ans[1][1]=-infinity;
}

void initdfs(ll t,ll step=0){
	string sp(5*step,' ');
	DEBUG(sp.c_str());
	DEBUG("initdfs(t=%d)\n",t);
	ASSERT(top[t]==t);
	ASSERT(dfn[tail[t]]-dfn[t]+1 == childs[t].size());

	for(ll u:childs[t]){
		DEBUG(sp.c_str());
		DEBUG("   child u=%d\n",u);
		ldp[u][0]=0;
		ldp[u][1]=w[u];
		for(ll v:h[u]){
			if(v!=fa[u]&&v!=hson[u]){
				initdfs(v,step+1);
				DEBUG(sp.c_str());
				DEBUG("      LIGHTchild v=%d, ldt[v][0,1]=[%d, %d]\n",v,ldt[v][0],ldt[v][1]);
				ldp[u][0]+=max(ldt[v][0],ldt[v][1]);
				ldp[u][1]+=ldt[v][0];
			}
		}
	}

	ll tmp[2][2];
	tmp[1][1]=-infinity;
	for(ll u:childs[t]){
		DEBUG(sp.c_str());
		DEBUG("   child u=%d, ldp[u][0,1]=[%d,%d]\n",u,ldp[u][0],ldp[u][1]);
		//tmp[0][0]=tmp[0][1]=ldp[u][0];
		//tmp[1][0]=ldp[u][1];
		bindldp(u,tmp);
		change(dfn[u],tmp);
	}

	query(dfn[t],dfn[tail[t]],tmp);
	//floydmult2(imat,tmp,t2);
	//ldt[t][0]=max(tmp[0][0],tmp[1][0]);
	ldt[t][0]=tmp[0][0];
	ldt[t][1]=tmp[1][0];
	DEBUG(sp.c_str());
	DEBUG("ldt[t=%d][0,1]=[%d, %d]\n",t,ldt[t][0],ldt[t][1]);
}
/*
void upchange(ll u){
	ASSERT(top[u]==u);

	ll dt[2];
	memcpy(dt,ldt,sizeof(dt));
	ll tmp[2][2];
		//,t2[2][2];
	query(dfn[u],dfn[tail[u]],tmp);
	//floydmult2(imat,tmp,t2);
	ldt[u][0]=tmp[0][0];
	ldt[u][1]=tmp[1][0];

	if(fa[u]==0)
		return;

	ldp[fa[u]][0]-=dt[0];
	ldp[fa[u]][1]-=dt[1];
	ldp[fa[u]][0]+=ldt[u][0];
	ldp[fa[u]][1]+=ldt[u][1];

	tmp[0][0]=tmp[0][1]=ldp[fa[u]][0];
	tmp[1][0]=ldp[fa[u]][1];
	tmp[1][1]=-infinity;

	change(dfn[fa[u]],tmp);
	upchange(top[fa[u]]);
}

void opchange(ll pos,ll val){
	ldp[pos][1]-=w[pos];
	ldp[pos][1]+=w[pos]=val;

	ll tmp[2][2];
	tmp[0][0]=tmp[0][1]=ldp[pos][0];
	tmp[1][0]=ldp[pos][1];
	tmp[1][1]=-infinity;

	change(dfn[pos],tmp);
	upchange(top[pos]);
}
*/

void upchange(ll u){
	u=top[u];

	ll lastldt[2],tmp[2][2];
	memcpy(lastldt,ldt[u],sizeof(lastldt));

	query(dfn[u],dfn[tail[u]],tmp);
	ldt[u][0]=tmp[0][0];
	ldt[u][1]=tmp[1][0];

	if(!fa[u])
		return;

	ldp[fa[u]][0]-=max(lastldt[0],lastldt[1]);
	ldp[fa[u]][1]-=lastldt[0];
	ldp[fa[u]][0]+=max(ldt[u][0],ldt[u][1]);
	ldp[fa[u]][1]+=ldt[u][0];

	//tmp[0][0]=tmp[0][1]=ldp[fa[u]][0];
	//tmp[1][0]=ldp[fa[u]][1];
	//tmp[1][1]=-infinity;
	bindldp(fa[u],tmp);
	change(dfn[fa[u]],tmp);

	upchange(fa[u]);
}

void opchange(ll pos,ll val){
	ldp[pos][1]-=w[pos];
	ldp[pos][1]+=w[pos]=val;

	ll tmp[2][2];
	bindldp(pos,tmp);
	change(dfn[pos],tmp);
	upchange(pos);
}

ll opquery(){
	return max(ldt[1][0],ldt[1][1]);
}



int main(int argc, char* argv[]) {
	string str;

	read(n,m);
	read(str);
	long long sum=0;
	FOR(i,1,n){
		read(w[i]);
		sum+=w[i];
		w0[i]=w[i];
	}
	FOR(i,1,n-1){
		ll u,v;
		read(u,v);
		addedge(u,v);
	}

	dfs1(1,0,1);
	dfs2(1,1);
	build();

	PRINTARR("%d",hson,1,n);
	PRINTARR("%d",dfn,1,n);

	//FOR(i,1,n)
		//opchange(dfn[i],w0[i]);
	initdfs(1);

	DEBUG("initans=%d\n",opquery());

	const ll inf=1e10;

	FOR(i,1,m){
		ll a,x,b,y;
		read(a,x,b,y);
		ll delta=0;
		if(x==0){
			opchange(a,inf);
			delta+=inf-w0[a];
		}else{
			opchange(a,-inf);
			//delta-=inf;
		}
		if(y==0){
			opchange(b,inf);
			delta+=inf-w0[b];
		}else{
			opchange(b,-inf);
			//delta-=inf;
		}
		ll ans=sum-opquery()+delta;
		if(ans>=inf||ans<=-inf)
			printf("-1\n");
		else
			printf("%lld\n",ans);
		opchange(a,w0[a]);
		opchange(b,w0[b]);
	}




	return 0;
}

// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP

