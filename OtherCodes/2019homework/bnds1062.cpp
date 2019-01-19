#include <cstdlib>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <string>
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

namespace BigNum{
#define DIGITS 200

	class BigInt {
	public:
		BigInt() { memset(digits, 0, sizeof(digits)); }
		BigInt(string x) {
			memset(digits, 0, sizeof(digits));
			for (int i = 1; i <= x.length(); i++) {
				digits[i] = x[x.length() - i] - '0';
			}
		}
		template<typename IntType>
		BigInt(IntType val){
			memset(digits,0,sizeof(digits));
			int i=0;
			while(val!=0){
				digits[++i]=val%10;
				val/=10;
			}
		}

		string toString() {
			string str;
			int back = 0;
			for (int i = DIGITS; i >= 1; i--) {
				if (digits[i] != 0) {
					back = i;
					break;
				}
			}
			for (int i = back; i >= 1; i--)
				str += to_string(digits[i]);
			if (str == "")
				str = "0";
			return str;
		}

		BigInt operator + (const BigInt& y) {
			BigInt& x=*this;
			BigInt sum;
			int inc = 0;

			for (int i = 1; i <= DIGITS; i++) {
				sum.digits[i] = x.digits[i] + y.digits[i] + inc;
				if (sum.digits[i] >= 10) {
					inc = 1;
					sum.digits[i] -= 10;
				} else
					inc = 0;
			}
			return sum;
		}

		BigInt operator * (const BigInt& y) {
			BigInt& x=*this;
			BigInt ans, tmp;

			for (int i = 1; i <= DIGITS; i++) {
				if (x.digits[i] == 0)
					continue;
				memset(tmp.digits, 0, sizeof(tmp.digits));
				for (int j = 1; j <= DIGITS; j++)
					tmp.digits[i + j - 1] = y.digits[j] * x.digits[i];
				for (int j = 1; j <= DIGITS; j++) {
					tmp.digits[j + 1] += tmp.digits[j] / 10;
					tmp.digits[j] %= 10;
				}
				ans = ans + tmp;
			}
			return ans;
		}

		BigInt operator - (const BigInt& y) {
			BigInt& x=*this;
			BigInt sum;
			int inc = 0;

			for (int i = 1; i <= DIGITS; i++) {
				sum.digits[i] = x.digits[i] - y.digits[i] + inc;
				if (sum.digits[i] < 0) {
					inc = -1;
					sum.digits[i] += 10;
				}
				else
					inc = 0;
			}
			return sum;
		}

	private:
		unsigned char digits[DIGITS + 2];
	};
}


//typedef long long ll;
typedef BigNum::BigInt ll;
//typedef __int128 ll;
const int MaxK=1000;

template<typename Integer>
class Fraction{
public:

	/*Integer gcd(Integer x,Integer y){
		if(y==0)
			return x;
		else
			return gcd(y,x%y);
	}*/

public:

	Fraction(){}
	Fraction(Integer top,Integer bottom):top(top),bot(bottom){
		simplify();
	}

	Fraction<Integer> operator * (const Fraction<Integer>& right){
		return Fraction<Integer>(top*right.top,bot*right.bot);
	}

	template<typename IntType>
	Fraction<Integer> operator * (const IntType& right){
		return Fraction<Integer>(top*right,bot);
	}

	Fraction<Integer> operator + (const Fraction<Integer>& right){
		return Fraction<Integer>(top*right.bot+bot*right.top,bot*right.bot);
	}

	template<typename IntType>
	Fraction<Integer> operator + (const IntType& right){
		return Fraction<Integer>(top+bot*right,bot);
	}

	Fraction<Integer> operator - (const Fraction<Integer>& right){
		return Fraction<Integer>(top*right.bot-bot*right.top,bot*right.bot);
	}

	template<typename IntType>
	Fraction<Integer> operator - (const IntType& right){
		return Fraction<Integer>(top-bot*right,bot);
	}

	template<typename ApproxType>
	ApproxType getApprox(){
		return (ApproxType)top/(ApproxType)bot;
	}

	pair<Integer,Integer> getPair(){
		return make_pair(top,bot);
	}

	void simplify(){
		/*Integer val=gcd(top,bot);
		top/=val;
		bot/=val;*/
	}

private:
	Integer top,bot;
};

int n,m,k;
Fraction<ll> on,off;


int main(int argc, char* argv[]) {
	
	read(n);read(m);read(k);
	on=Fraction<ll>(m,1ll);
	off=Fraction<ll>(n-m,1ll);
	
	Fraction<ll> n0=Fraction<ll>(1ll,n),one=Fraction<ll>(1ll,1ll),tmpx,tmpy;
	for(int i=1;i<=k;i++){
		tmpx=on-n0*on+n0*off;
		tmpy=off-n0*off+n0*on;
		on=tmpx;
		off=tmpy;
	}
	
	pair<ll,ll> x=on.getPair();
	cout<<x.first.toString()<<'/'<<x.second.toString()<<endl;
	
	return 0;
}


