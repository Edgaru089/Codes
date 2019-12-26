#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <string>
#include <utility>
#include <cmath>
#include <unordered_map>
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

typedef long long ll;

template<size_t N,int Mod=1e9+7,typename Int=long long>
class Matrix{
public:
	Matrix(){
		FOR(i,0,N-1)
			FOR(j,0,N-1)
				if(i==j)
					arr[i][j]=1;
				else
					arr[i][j]=0;
	}
	template<typename T>
	Matrix(T val){
		FOR(i,0,N-1)
			FOR(j,0,N-1)
				arr[i][j]=val;
	}
	template<typename T>
	Matrix(initializer_list<initializer_list<T>> l){
		FOR(i,0,N-1)
			FOR(j,0,N-1)
				arr[i][j]=l.begin()[i].begin()[j];
	}
	Matrix(const Matrix<N,Mod,Int>& copy){
		memcpy(arr,copy.arr,sizeof(arr));
	}

	template<typename Tn>
	Matrix<N,Mod,Int> multiply(const Matrix<N,Mod,Tn>& x,int mod=Mod)const{
		Matrix<N,Mod,Int> ans(0);
		FOR(i,0,N-1)
			FOR(j,0,N-1)
				FOR(k,0,N-1)
					ans[i][j]=(ans[i][j]+arr[i][k]*x[k][j])%mod;
		return ans;
	}

	template<typename Tn>
	inline Matrix<N,Mod,Int> operator * (const Matrix<N,Mod,Tn>& x)const{
		return multiply(x,Mod);
	}

	Int* operator [] (size_t off){
		return arr[off];
	}

	const Int* operator [] (size_t off)const{
		return arr[off];
	}
private:
	Int arr[N][N];
};

template<size_t N,int Mod,typename Type,typename Int>
Matrix<N,Mod,Type> matpow(Matrix<N,Mod,Type> base,Int exp){
	Matrix<N,Mod,Type> ans;
	while(exp){
		if(exp&1)
			ans=ans*base;
		base=base*base;
		exp>>=1;
	}
	return ans;
}
template<size_t N,int Mod,typename Type,typename Int>
Matrix<N,Mod,Type> matpow(Matrix<N,Mod,Type> base,Int exp,int mod){
	Matrix<N,Mod,Type> ans;
	while(exp){
		if(exp&1)
			ans=ans.multiply(base,mod);
		base=base.multiply(base,mod);
		exp>>=1;
	}
	return ans;
}

ll qpow(ll base,ll exp,ll mod){
	ll ans=1;
	while(exp){
		if(exp&1)
			ans=ans*base%mod;
		base=base*base%mod;
		exp>>=1;
	}
	return ans;
}

ll inv(ll x,ll mod){
	return qpow(x,mod-2,mod);
}

const int Mod=1000000007;

template<size_t N>
using mat=Matrix<N,Mod,long long>;

ll n,f1,f2,f3,c;

mat<4> rt={
	{1,0,0,1},
	{0,0,0,1},
	{0,1,0,1},
	{0,0,1,1}
},r0={
	{-3+Mod,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0}
};
mat<5> qt={
	{1,0,0,1,1},
	{0,0,0,1,0},
	{0,1,0,1,0},
	{0,0,1,1,0},
	{0,0,0,1,1}
},q0={
	{1,0,0,0,3},
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0}
};
mat<3> ft={
	{0,0,1},
	{1,0,1},
	{0,1,1}
},f01={
	{1,0,0},
	{0,0,0},
	{0,0,0}
},f02={
	{0,1,0},
	{0,0,0},
	{0,0,0}
},f03={
	{0,0,1},
	{0,0,0},
	{0,0,0}
};

class bsgs{
public:

private:
	unordered_map<int,int> m;
}


int main(int argc, char* argv[]) {

	read(n);
	read(f1);
	read(f2);
	read(f3);
	read(c);

	ll ans;
	if(n<=3){
		switch(n){
			case 1:
				ans=f1;
				break;
			case 2:
				ans=f2;
				break;
			case 3:
				ans=f3;
				break;
		}
	}else{
		auto qx=q0*matpow(qt,n-3);
		ASSERT(qx[0][4]==n);
		auto rx=r0*matpow(rt,n-3);
		auto fx1=matpow(ft,n-3,inv());
		auto fx2=matpow(ft,n-3);
		auto fx3=matpow(ft,n-3);

		ans=((ll)qx[0][3]+rx[0][3])*2%Mod;
		ans=qpow(c,ans,Mod)*qpow(f1,fx1[0][2],Mod)%Mod*qpow(f2,fx2[0][2],Mod)%Mod*qpow(f3,fx3[0][2],Mod)%Mod;
	}

	printf("%lld\n",ans);


	return 0;
}


// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP

