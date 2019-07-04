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
		fprintf(stderr,"Debug Assertation Failed on line %d, in function %s:\n  Expression: %s\n",__LINE__,__func__,#expr);\
		abort();\
	}\
}while(false)
#else
#define DEBUG(...)
#define PRINTARR(a, b, c, d)
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

const int MaxN=50+10;

int n;
char s[MaxN];
bool flag[MaxN][MaxN];





int main(int argc, char* argv[]) {

	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<=n;j++){
			char c=s[j];
			if(c=='#')
				flag[i][j]=false;
			else
				flag[i][j]=true;
		}
	}

	bool ok=true;
	while(ok){
		bool checked=false;
		for(int i=1;i<=n&&ok;i++){
			for(int j=1;j<=n&&ok;j++){
				if(!flag[i][j])
					continue;
				int dir=0;
				if(flag[i-1][j])
					dir=1; // up
				if(flag[i+1][j])
					if(dir!=0)
						dir=-1;
					else
						dir=2; // down
				if(flag[i][j-1])
					if(dir!=0)
						dir=-1;
					else
						dir=3; // left
				if(flag[i][j+1])
					if(dir!=0)
						dir=-1;
					else
						dir=4; //right
				DEBUG("(i=%d, j=%d), dir=%d\n",i,j,dir);
				if(dir==-1)
//					if((i==1||i==n)&&(j==1||j==n))
//						ok=false;
//					else
						continue;
				else if(dir==0)
					ok=false;
				else{
					checked=true;
					PASS;
					int x=i,y=j;
					switch(dir){
						case 1:
							x--;
							break;
						case 2:
							x++;
							break;
						case 3:
							y--;
							break;
						case 4:
							y++;
							break;
					}
					DEBUG("      x=%d, y=%d\n",x,y);
					if(flag[x][y]&&flag[x+1][y]&&flag[x-1][y]&&flag[x][y+1]&&flag[x][y-1])
						flag[x][y]=flag[x+1][y]=flag[x-1][y]=flag[x][y+1]=flag[x][y-1]=false;
					else
						ok=false;
				}
			}
		}
		if(!checked)
			break;
	}

	if(ok)
		printf("YES\n");
	else
		printf("NO\n");

	return 0;
}


