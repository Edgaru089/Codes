#include <cstdlib>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <cstdio>
using namespace std;

#if (defined LOCAL) || (defined D)
#define DEBUG(...) printf(__VA_ARGS__)
#define PRINTARR(formatstr, arr, beginoff, size)				\
do{printf(#arr ":");											\
for (int __i = beginoff; __i <= beginoff + size - 1; __i++)		\
	printf("\t%d", __i);										\
printf("\n");													\
for (int __i = beginoff; __i <= beginoff + size - 1; __i++)		\
	printf("\t" formatstr, arr[__i]);							\
printf("\n"); }while(false)
#define PASS printf("Passing function \"%s\" on line %d\n", __func__, __LINE__)
#define ASSERT(expr) do{\
	if(!(expr)){\
		printf("Debug Assertation Failed on line %d, in function %s:\n  Expression: %s\n",__LINE__,__func__,#expr);\
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

template<>
void read<string>(string& val){
	val.clear();
	int c;
	while(iscntrl(c=getchar())||c==' '||c=='\t');
	do{
		val.push_back(c);
	}while(!(iscntrl(c=getchar())||c==' '||c=='\t'));
}

const int MaxN=1e5+10;
int n,m;

string str;
int mask0=0,mask1=0x7fffffff;


int main(int argc, char* argv[]) {
	
	read(n);read(m);
	for(int i=1;i<=n;i++){
		int t;
		read(str);read(t);
		switch(str[0]){
			case 'A': // And
				mask0&=t;
				mask1&=t;
				break;
			case 'O': // Or
				mask0|=t;
				mask1|=t;
				break;
			case 'X': // Xor
				mask0^=t;
				mask1^=t;
				break;
			default:
				printf("error string: %s\n",str.c_str());
				abort();
		}
	}
	
	int ans=0;
	for(int i=30;i>=0;i--){
		if(mask0&(1<<i))
			ans+=(1<<i);
		else if(mask1&(1<<i))
			if(m>=(1<<i)){
				ans+=(1<<i);
				m-=(1<<i);
			}
	}
	
	printf("%d\n",ans);
	
	return 0;
}


