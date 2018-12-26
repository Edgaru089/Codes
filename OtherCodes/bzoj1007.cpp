// bzoj1007: [HNOI2008]水平可见直线
// 2018-12-15

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <limits>
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

const int MaxN=50000+10;
int n;
int a[MaxN],b[MaxN];
int id[MaxN];

template<typename Type, int Size = MaxN>
class stack {
public:
	stack() :stacktop(0) {}
	void clear() { stacktop = 0; }
	void push(Type x) { arr[stacktop++] = x; }
	void pop() { if (stacktop > 0) stacktop--; }
	Type top() { return arr[stacktop - 1]; }
	bool empty() { return stacktop <= 0; }
	int size() { return stacktop; }
	// Id begins with one
	Type& operator [] (int id){ return arr[id-1]; }
	const Type& operator[] (int id) const { return arr[id-1]; }
	Type* data() {return arr;}

	int stacktop;
	Type arr[Size];
};

stack<int> S;


bool cmp(int x,int y){
	return a[x]<a[y]||(a[x]==a[y]&&(b[x]>b[y]));
}

double intersectx(int k1,int b1,int k2,int b2){
	if(k1==k2)
		return numeric_limits<double>::max();
	else{
		double x=(double)(b2-b1)/(k1-k2);
		return x;
	}
}

int main(int argc, char* argv[]) {
	
	read(n);
	for(int i=1;i<=n;i++){
		read(a[i]);read(b[i]);
		id[i]=i;
	}

	sort(id+1,id+n+1,cmp);
	PRINTARR("%d",id,1,n);

	for(int i=1;i<=n;i++){
		int k=a[id[i]],b=::b[id[i]];
		DEBUG("i=%d, id=%d, k=%d, b=%d\n",i,id[i],k,b);
		PRINTARR("%d",S.arr,0,S.size());
		if(S.empty())
			S.push(id[i]);
		else
			while(!S.empty()){
				if(a[S.top()]==k)
					break;
				else if(S.size()<=1){
					S.push(id[i]);
					break;
				}
				else{
					int k1=a[S[S.size()-1]],b1=::b[S[S.size()-1]];
					int k2=a[S[S.size()]],b2=::b[S[S.size()]];
					if(intersectx(k1,b1,k,b)<=intersectx(k1,b1,k2,b2))
						S.pop();
					else
						break;
				}
			}
	}
	DEBUG("Loop ended\n");
	PRINTARR("%d",S.arr,0,S.size());

	for(int i=1;i<=S.size();i++){
		id[i]=S[i-1];
	}

	sort(id+1,id+S.size()+1);

	for(int i=1;i<=S.size();i++){
		printf("%d ",id[i]);
	}
	printf("\n");	
	
	return 0;
}


