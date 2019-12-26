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

const int MaxN=2000+10,MaxA=30;

int n,m;
string str[MaxN];
int p;
int s[MaxN][MaxN];

int l[MaxA],r[MaxA],t[MaxA],b[MaxA];



int main(int argc, char* argv[]) {

	int t0;
	read(t0);
	while(t0--){

		FOR(i,1,26){
			l[i]=t[i]=MaxN;
			r[i]=b[i]=0;
		}

		p=0;
		read(n);read(m);
		FOR(i,1,n){
			read(str[i]);
			FOR(j,1,m){
				if(str[i][j-1]=='.')
					s[i][j]=0;
				else
					s[i][j]=str[i][j-1]-'a'+1;
				if(s[i][j]){
					l[s[i][j]]=min(l[s[i][j]],j);
					r[s[i][j]]=max(r[s[i][j]],j);
					t[s[i][j]]=min(t[s[i][j]],i);
					b[s[i][j]]=max(b[s[i][j]],i);
				}
				p=max(p,s[i][j]);
			}
		}


		bool ok=true;
		for(int i=p;i>=1&&ok;i--){
			if(r[i]-l[i]+1>1&&b[i]-t[i]+1>1){
				ok=false;
				break;
			}
			if(r[i]==l[i]){
				int y=l[i];
				FOR(x,t[i],b[i]){
					if(s[x][y]!=i&&s[x][y]!=-1){
						ok=false;
						break;
					}
					s[x][y]=-1;
				}
			}else{
				int x=t[i];
				FOR(y,l[i],r[i]){
					if(s[x][y]!=i&&s[x][y]!=-1){
						ok=false;
						break;
					}
					s[x][y]=-1;
				}
			}
		}

		if(!ok)
			printf("NO\n");
		else{
			printf("YES\n");
			printf("%d\n",p);
			int cnt=1;
			FOR(i,1,p){
				if(r[i]==0)
					cnt++;
				else{
					FOR(j,1,cnt)
						printf("%d %d %d %d\n",t[i],l[i],b[i],r[i]);
					cnt=1;
				}
			}
		}


	}

	return 0;
}


// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP

