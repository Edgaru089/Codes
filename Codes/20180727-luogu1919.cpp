/*
DOCUMENT NAME "20180727-luogu1919.cpp"
CREATION DATE 2018-07-27
SIGNATURE CODE_20180727_LUOGU1919
COMMENT 【模板】A*B Problem升级版（FFT快速傅里叶） / 压位高精
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180727_LUOGU1919

#include <cstdlib>
#include <iostream>
#include <cstring>
using namespace std;

constexpr int MaxN = 60000 + 10;

constexpr int buffersize = 80 * 1024 * 1024;
char buffer[buffersize], *buffertop = buffer;
#define GETCHAR *(buffertop++)
#define UNGETCHAR(c) (--buffertop)
//#define GETCHAR getchar()
//#define UNGETCHAR(c) ungetc(c, stdin);

template<typename IntType = int>
IntType read() {
	IntType ans = 0;
	int c;
	while (!isdigit(c = GETCHAR));
	do {
		ans = (ans << 3) + (ans << 1) + c - '0';
	} while (isdigit(c = GETCHAR));
	UNGETCHAR(c);
	return ans;
}

template<typename IntType>
void read(IntType& val) { val = read<IntType>(); }
template<typename IntType, typename... Args>
void read(IntType& val, Args&... args) { val = read<IntType>(); read(args...); }

void readstr(string& str) {
	int c;
	while (iscntrl(c = GETCHAR) || isblank(c));
	do {
		str.push_back(c);
	} while (!(iscntrl(c = GETCHAR) || isblank(c)));
	UNGETCHAR(c);
}

int n;
string str1, str2;

constexpr int DigitCnt = 9;
constexpr long long DigitMod = 1e9;
constexpr int ArrSize = MaxN;
class bigint {
public:
	bigint() {}
	void fromString(const string& str) {
		int tmp = 0;
		int digitcnt = 0, digitmul = 1;
		for (int i = str.size() - 1; i >= 0; i--) {
			tmp += digitmul * (str[i] - '0');
			digitcnt++;
			digitmul *= 10;
			if (digitcnt == DigitCnt) {
				size++;
				val[size] = tmp;
				tmp = 0;
				digitcnt = 0;
				digitmul = 1;
			}
		}
		if (tmp > 0) {
			size++;
			val[size] = tmp;
		}
	}

	void print() {
		for (int i = size; i >= 1; i--) {
			if (i == size)
				printf("%lld", val[i]);
			else
				printf("%0*lld", DigitCnt, val[i]);
		}
	}

	long long& operator [] (const int& index) { return *(val + index); }
	const long long& operator [] (const int& index) const { return *(val + index); }

	long long val[ArrSize];
	int size = 0;
};

bigint operator * (const bigint& a, const bigint& b) {
	bigint ans;
	memset(ans.val, 0, sizeof(ans.val));
	ans.size = 0;
	for (int i = 1; i <= a.size; i++)
		for (int j = 1; j <= b.size; j++) {
			ans[i + j - 1] += a[i] * b[j];
			ans[i + j] += ans[i + j - 1] / DigitMod;
			ans[i + j - 1] %= DigitMod;
		}
	if (ans[a.size + b.size] != 0)
		ans.size = a.size + b.size;
	else
		ans.size = a.size + b.size - 1;
	return ans;
}


bigint a, b;

int main(int argc, char* argv[]) {
	memset(buffer, -1, sizeof(buffer));
	fread(buffer, 1, buffersize, stdin);
	read(n);
	str1.reserve(n);
	str2.reserve(n);

	readstr(str1);
	readstr(str2);
	a.fromString(str1);
	b.fromString(str2);

	(a*b).print();

	return 0;
}

#endif

