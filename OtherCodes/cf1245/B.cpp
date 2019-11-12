#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
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

int t;
int n,r,p,s;
string str;





int main(int argc, char* argv[]) {

	cin>>t;
	while(t--){

		cin>>n;
		cin>>r>>p>>s;
		cin>>str;

		string ans;
		int score=0;

		int rt=0,pt=0,st=0;
		for(char c:str)
			switch(c){
				case 'R':
					rt++;
					break;
				case 'P':
					pt++;
					break;
				case 'S':
					st++;
					break;
			}

		for(char c:str){
			if(c=='R'){
				if(p>0){
					ans.push_back('P');
					p--;
					score++;
				}else{
					if(s>pt){
						ans.push_back('S');
						s--;
					}else{
						ans.push_back('R');
						r--;
					}
				}
				rt--;
			}else if(c=='P'){
				if(s>0){
					ans.push_back('S');
					s--;
					score++;
				}else{
					if(p>rt){
						ans.push_back('P');
						p--;
					}else{
						ans.push_back('R');
						r--;
					}
				}
				pt--;
			}else if(c=='S'){
				if(r>0){
					ans.push_back('R');
					r--;
					score++;
				}else{
					if(s>pt){
						ans.push_back('S');
						s--;
					}else{
						ans.push_back('P');
						p--;
					}
				}
				st--;
			}
		}

		if(((n&1)&&score>=n/2+1)||(!(n&1)&&score>=n/2))
			cout<<"YES"<<endl<<ans<<endl;
		else
			cout<<"NO"<<endl;
	}


	return 0;
}


