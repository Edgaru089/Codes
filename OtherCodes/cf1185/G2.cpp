#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <string>
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

typedef long long ll;
const int MaxN=50+10,MaxT=2500+200;
const ll Mod=1e9+7;

int n,ts;
ll t[MaxN],g[MaxN];
ll cntg[5],durg[5];

ll a[MaxN][MaxT],bc[MaxN][MaxN][MaxT];
ll pe[MaxN][MaxN][MaxN][4];

ll fact[10000];




int main(int argc, char* argv[]) {

	read(n);read(ts);

	fact[0]=1;
	FOR(i,1,9999)
		fact[i]=fact[i-1]*i%Mod;
	a[0][0]=bc[0][0][0]=1;

	FOR(i,1,n){
		read(t[i]);
		read(g[i]);

		switch(g[i]){
			case 1:
				ROF(j,ts,0)
					ROF(k,cntg[1],0){
						a[k+1][j+t[i]]=(a[k+1][j+t[i]]+a[k][j])%Mod;
					}
				break;
			case 2:
				ROF(j,ts,0)
					ROF(k,cntg[2],0)
						ROF(l,cntg[3],0){
							bc[k+1][l][j+t[i]]+=bc[k][l][j];
							bc[k+1][l][j+t[i]]%=Mod;
						}
				break;
			case 3:
				ROF(j,ts,0)
					ROF(k,cntg[2],0)
						ROF(l,cntg[3],0){
							bc[k][l+1][j+t[i]]+=bc[k][l][j];
							bc[k][l+1][j+t[i]]%=Mod;
							if(bc[k][l+1][j+t[i]])
								DEBUG("bc[%d][%d][%lld]=%lld\n",k,l+1,j+t[i],bc[k][l+1][j+t[i]]);
						}
				break;
		}

		cntg[g[i]]++;
		durg[g[i]]+=t[i];
	}

	pe[0][0][0][0]=1;
	FOR(x,0,cntg[1])
		FOR(y,0,cntg[2])
			FOR(z,0,cntg[3])
				FOR(tr,0,3)
					if(pe[x][y][z][tr]){
						if(tr!=1&&x+1<=cntg[1]){
							pe[x+1][y][z][1]+=pe[x][y][z][tr];
							pe[x+1][y][z][1]%=Mod;
						}
						if(tr!=2&&y+1<=cntg[2]){
							pe[x][y+1][z][2]+=pe[x][y][z][tr];
							pe[x][y+1][z][2]%=Mod;
						}
						if(tr!=3&&z+1<=cntg[3]){
							pe[x][y][z+1][3]+=pe[x][y][z][tr];
							pe[x][y][z+1][3]%=Mod;
						}
					}

	PRINTARR("%lld",cntg,1,3);
	PRINTARR("%lld",durg,1,3);

	ll ans=0;
	FOR(x,0,cntg[1]){
		FOR(dur,0,ts){
			if(a[x][dur])
				FOR(y,0,cntg[2])
					FOR(z,0,cntg[3]){
						if(bc[y][z][ts-dur]!=0)
							PASS;
						else
							continue;
						ll dt=a[x][dur]*bc[y][z][ts-dur]%Mod;
						dt=dt*fact[x]%Mod;
						dt=dt*fact[y]%Mod;
						dt=dt*fact[z]%Mod;
						ans+=dt*pe[x][y][z][1]%Mod;
						ans+=dt*pe[x][y][z][2]%Mod;
						ans+=dt*pe[x][y][z][3]%Mod;
						ans%=Mod;
						if(dt!=0)
							DEBUG("x=%d, y=%d, z=%d, delta=%lld\n",x,y,z,dt);
					}
		}
	}

	printf("%lld\n",ans);


	return 0;
}


// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP

