#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
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

const int MaxN=4e5+10;

int n;
int a[MaxN],a0[MaxN];
map<int,int> m,mr;
int c[MaxN],mc;
int s[MaxN],st;

int ax,ay;
vector<int> aq;
vector<vector<int> > ans;
vector<pair<int,int> > ra;



int main(int argc, char* argv[]) {

	read(n);
	FOR(i,1,n){
		read(a0[i]);
		map<int,int>::iterator it=m.find(a0[i]);
		if(it==m.end()){
			a[i]=m.size()+1;
			m.insert(make_pair(a0[i],a[i]));
			mr.insert(make_pair(a[i],a0[i]));
		}else
			a[i]=it->second;
		c[a[i]]++;
	}

	FOR(i,1,m.size())
		mc=max(mc,c[i]);

	FOR(i,1,m.size())
		s[c[i]]++;
	PRINTARR("%d",s,1,mc);
	ROF(i,mc,1)
		s[i]+=s[i+1];
	PRINTARR("%d",s,1,mc);

	int lm=sqrt(n)+1;
	FOR(i,1,lm){
		st+=s[i];
		int j=st/i;
		if(j<i)
			continue;
		DEBUG("i=%d, st=%d, j=%d\n",i,st,j);
		if(ax*ay<i*j){
			ax=i;
			ay=j;
		}
	}

	printf("%d\n",ax*ay);
	printf("%d %d\n",ax,ay);
	FOR(i,1,m.size()){
		int r0=mr[i];
		ra.push_back(make_pair(min(ax,c[i]),r0));
	}
	sort(ra.begin(),ra.end(),greater<pair<int,int> >());
	FOR(i,0,ra.size()){
		FOR(j,1,ra[i].first){
			aq.push_back(ra[i].second);
			if(aq.size()>ax*ay)
				break;
		}
		if(aq.size()>ax*ay)
			break;
	}
	PRINTARR("%d",aq,0,aq.size());
	ASSERT(ax*ay<=aq.size());

	ans.resize(ax);
	FOR(i,0,ax-1)
		ans[i].resize(ay,0);

	int i=-1,j=-1;
	FOR(k,0,ax*ay-1){
		i++;i%=ax;
		j++;j%=ay;
		if(ans[i][j]!=0){
			i++;
			i%=ax;
		}
		ans[i][j]=aq[k];
	}

	FOR(i,0,ax-1){
		FOR(j,0,ay-1){
			if(j==0)
				printf("%d",ans[i][j]);
			else
				printf(" %d",ans[i][j]);
		}
		printf("\n");
	}



	return 0;
}


// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP

