#include <cstdlib>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <vector>

// WARN: C++11
#include <initializer_list>

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

template<typename Int>
class Matrix{
public:

	Matrix(){}
	Matrix(size_t n){
		v.resize(n);
		for(auto& i:v)
			i.resize(n,0);
		for(int i=0;i<n;i++)
			v[i][i]=1;
	}
	Matrix(size_t n,Int val){
		v.resize(n);
		for(auto& i:v)
			i.resize(n,val);
	}
	Matrix(const initializer_list<initializer_list<Int>>& val){
		v.resize(val.size());
		int i=0;
		for(auto& j:val){
			v[i]=vector<Int>(j);
			i++;
		}
	}

	Matrix<Int> multiply(const Matrix<Int>& right,Int mod=-1)const{
		ASSERT(v.size()==right.v.size());
		int n=v.size();
		Matrix<Int> ans(n,0);
		if(mod>0)
			for(int i=0;i<n;i++)
				for(int j=0;j<n;j++)
					for(int k=0;k<n;k++)
						ans[i][j]=(ans[i][j]+(*this)[i][k]*right[k][j])%mod;
		else
			for(int i=0;i<n;i++)
				for(int j=0;j<n;j++)
					for(int k=0;k<n;k++)
						ans[i][j]+=(*this)[i][k]*right[k][j];
		return ans;
	}

	size_t size()const{
		return v.size();
	}

	const vector<Int>& operator[](size_t x)const{
		return v[x];
	}

	vector<Int>& operator[](size_t x){
		return v[x];
	}

	void initialize(size_t size){
		v.resize(size);
		for(auto& i:v)
			i.resize(size);
	}

private:
	vector<vector<Int>> v;
};

typedef long long ll;
typedef Matrix<long long> mat;

mat qm(mat base,ll exp,ll mod){
	mat ans(base.size());
	while(exp){
		if(exp&1)
			ans=ans.multiply(base,mod);
		base=base.multiply(base,mod);
		exp>>=1;
	}
	return ans;
}

ll m,a,c,x,n,g;




int main(int argc, char* argv[]) {

	read(n);

	mat init={
		{1,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0}
	},trans={
		{0,1,0,0,0,0,0,1},
		{1,0,1,0,0,0,0,0},
		{0,1,0,1,0,0,0,0},
		{0,0,1,0,1,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,1,0,1,0},
		{0,0,0,0,0,1,0,1},
		{1,0,0,0,0,0,1,0}
	};


	printf("%lld\n",init.multiply(qm(trans,n,1000),1000)[0][4]);

	return 0;
}


