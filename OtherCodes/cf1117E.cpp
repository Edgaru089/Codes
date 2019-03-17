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
void read<string>(string& str){
	str.clear();
	int c;
	while(!(iscntrl(c=getchar())||c==' '||c=='\t'));
	do{
		str.push_back((char)c);
	}while(iscntrl(c=getchar())||c==' '||c=='\t');
}

const int MaxN=10000+10;

string str0,str1,str2,str3;
int n,trans[MaxN];
char a[MaxN],b[MaxN],c[MaxN];

void encode(int x,char& a,char& b,char& c){
	a='a'+x%26;
	b='a'+(x/26)%26;
	c='a'+x/26/26;
}

int decode(char a,char b,char c){
	return (a-'a')+(b-'a')*26+(c-'a')*26*26;
}



int main(int argc, char* argv[]) {
	
	cin>>str0;
	n=str0.size();
	
	// encode
	for(int i=1;i<=n;i++)
		encode(i,a[i],b[i],c[i]);
	
	cout<<"? ";
	for(int i=1;i<=n;i++)
		cout<<a[i];
	cout<<endl;

	cin>>str1;

	cout<<"? ";
	for(int i=1;i<=n;i++)
		cout<<b[i];
	cout<<endl;

	cin>>str2;
	
	cout<<"? ";
	for(int i=1;i<=n;i++)
		cout<<c[i];
	cout<<endl;

	cin>>str3;

	for(int i=1;i<=n;i++)
		trans[decode(str1[i-1],str2[i-1],str3[i-1])]=i;

	cout<<"! ";
	for(int i=1;i<=n;i++)
		cout<<str0[trans[i]-1];
	cout<<endl;

	return 0;
}


