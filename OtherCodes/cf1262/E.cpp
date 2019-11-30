#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
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

#define FOR(i, first, last)               for(int i = first; i <= last; ++i)
#define ROF(i, last, first)               for(int i = last; i >= first; --i)
#define FORSTEP(i, first, last, step)     for(int i = first; i <= last; i += step)
#define ROFSTEP(i, last, first, stepabs)  for(int i = last; i >= first; i -= step)

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

const int MaxN=1e6+10;

int n,m;

vector<vector<bool>> burnt;

vector<vector<bool>> core;
vector<vector<int>> bs;

vector<vector<int>> ls,rs;
vector<vector<int>> us,ds;

vector<vector<int>> st;

void init(){
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++){
			if(!burnt[i][j])
				ls[i][j]=rs[i][j]=us[i][j]=ds[i][j]=0;
			else{
				if(j!=0)
					ls[i][j]=ls[i][j-1]+1;
				else
					ls[i][j]=1;
				if(i!=0)
					us[i][j]=us[i-1][j]+1;
				else
					us[i][j]=1;
			}
		}
	for(int i=n-1;i>=0;i--)
		for(int j=m-1;j>=0;j--){
			if(!burnt[i][j])
				continue;
			if(j!=m-1)
				rs[i][j]=rs[i][j+1]+1;
			else
				rs[i][j]=1;
			if(i!=n-1)
				ds[i][j]=ds[i+1][j]+1;
			else
				ds[i][j]=1;
		}

	bs[0][0]=(int)burnt[0][0];
	for(int i=1;i<n;i++)
		bs[i][0]=bs[i-1][0]+(int)burnt[i][0];
	for(int j=1;j<m;j++)
		bs[0][j]=bs[0][j-1]+(int)burnt[0][j];
	for(int i=1;i<n;i++)
		for(int j=1;j<m;j++)
			bs[i][j]=(int)burnt[i][j]+bs[i-1][j]+bs[i][j-1]-bs[i-1][j-1];
}

// core[][]
bool rebuild(int k){
	for(auto& i:st)
		for(auto& j:i)
			j=0;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			if(core[i][j]){
				st[i-k][j-k]++;
				if(j+k+1<m)
					st[i-k][j+k+1]--;
				if(i+k+1<n)
					st[i+k+1][j-k]--;
				if(j+k+1<m&&i+k+1<n)
					st[i+k+1][j+k+1]++;
			}

	for(int i=1;i<n;i++)
		st[i][0]+=st[i-1][0];
	for(int j=1;j<m;j++)
		st[0][j]+=st[0][j-1];
	for(int i=1;i<n;i++)
		for(int j=1;j<m;j++)
			st[i][j]+=st[i-1][j]+st[i][j-1]-st[i-1][j-1];

	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			if(burnt[i][j]&&st[i][j]==0)
				return false;
			else if(!burnt[i][j]&&st[i][j]!=0)
				return false;
	return true;
}

void simulate(int k){
	//if(k==0)
		//core=burnt;
	//else
		FOR(i,0,n-1)
			FOR(j,0,m-1)
				if(i>=k&&j>=k&&i+k<n&&j+k<m&&
				   bs[i+k][j+k]-(i>k?bs[i-k-1][j+k]:0)-(j>k?bs[i+k][j-k-1]:0)+((i>k&&j>k)?bs[i-k-1][j-k-1]:0)==(2*k+1)*(2*k+1))
					core[i][j]=true;
				else
					core[i][j]=false;
}

void print(){
	FOR(i,0,n-1){
		FOR(j,0,m-1)
			if(core[i][j])
				putchar('X');
			else
				putchar('.');
		putchar('\n');
	}
	fflush(stdout);
}

bool check(int k){
	DEBUG("------------------ check(k=%d) ------------------\n",k);
	simulate(k);
#ifdef D
	print();
#endif
	bool ans=rebuild(k);
	PRINTARR2D("%d",st,0,n,0,m);
	DEBUG(ans?"----RET=true\n":"----RET=false\n");
	return ans;
}




int main(int argc, char* argv[]) {

	read(n);read(m);
	string str;
	burnt.resize(n);
	core.resize(n);
	ls.resize(n);
	rs.resize(n);
	us.resize(n);
	ds.resize(n);
	st.resize(n);
	bs.resize(n);
	for(int i=0;i<n;i++){
		read(str);
		burnt[i].resize(m);
		for(int j=0;j<m;j++)
			if(str[j]=='X')
				burnt[i][j]=true;
			else
				burnt[i][j]=false;
		core[i].resize(m);
		ls[i].resize(m);
		rs[i].resize(m);
		us[i].resize(m);
		ds[i].resize(m);
		st[i].resize(m);
		bs[i].resize(m);
	}

	init();

	PRINTARR2D("%d",bs,0,n,0,m);
	PRINTARR2D("%d",ls,0,n,0,m);
	PRINTARR2D("%d",rs,0,n,0,m);
	PRINTARR2D("%d",us,0,n,0,m);
	PRINTARR2D("%d",ds,0,n,0,m);

	int l=0,r=min(n,m);
	while(l<r-1){
		int mid=(l+r)/2;
		if(check(mid))
			l=mid;
		else
			r=mid;
	}


	int ans;
	if(check(r))
		ans=r;
	else
		ans=l;

	printf("%d\n",ans);
	simulate(ans);
	print();

	burnt.resize(0);
	core.resize(0);
	ls.resize(0);
	rs.resize(0);
	us.resize(0);
	ds.resize(0);
	st.resize(0);

	return 0;
}


