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
	while(iscntrl(c=getchar())||c==' '||c=='\t');
	do{
		str.push_back(c);
	}while(!(iscntrl(c=getchar())||c==' '||c=='\t'));
}


template<typename Int>
Int gcd(Int m,Int n){
	if(n==0)
		return m;
	else
		return gcd(n,m%n);
}


template<typename Int>
class Fraction{
public:

	Fraction():x(1),y(1){}
	Fraction(Int x):x(x),y(1){}
	Fraction(Int x,Int y){
		Int g=gcd(x,y);
		this->x=x/g;
		this->y=y/g;
	}

	typedef Fraction<Int> Frac;

	Frac operator * (Frac right) const {
		return Frac(x*right.x,y*right.y);
	}

	template<typename Int2>
	Frac operator * (Int2 right) const {
		return Frac(x*right,y);
	}

	Frac operator / (Frac right) const {
		return Frac(x*right.y,y*right,x);
	}

	template<typename Int2>
	Frac operator / (Int2 right) const {
		return Frac(x,y*right);
	}

	template<typename Float>
	Float toFloat(){
		return (Float)(x)/(Float)(y);
	}


private:
	//  x/y
	Int x,y;
};

typedef __int128 ll;
typedef Fraction<ll> fr;

ll a,b,c,d,e,f,g;
ll n;

//fr ans;
long double ans;




int main(int argc, char* argv[]) {

	read(a);read(b);read(c);read(d);read(e);read(f);read(g);
	n=a+b+c+d+e+f+g;

	ans=5040;

	ans=ans*a;
	ans=ans/n;
	ans=ans*b;
	ans=ans/(n-1);
	ans=ans*c;
	ans=ans/(n-2);
	ans=ans*d;
	ans=ans/(n-3);
	ans=ans*e;
	ans=ans/(n-4);
	ans=ans*f;
	ans=ans/(n-5);
	ans=ans*g;


	//printf("%.3Lf\n",ans.toFloat<long double>());
	printf("%.3Lf\n",ans);


	return 0;
}


