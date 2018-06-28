/*
DOCUMENT CODE "20180627-bnds0616.cpp"
CREATION DATE 2018-06-27
SIGNATURE CODE_20180627_BNDS0616
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180627_BNDS0616

#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

// 定义了每个数中存多少位
#define DIGITS 500

//////////////////// 高精度整数 ////////////////////
struct BigInt {

	// 两个构造函数
	// 默认情况下会把所有没用的位设为零
	BigInt() { memset(digits, 0, sizeof(digits)); }
	BigInt(string x) {
		memset(digits, 0, sizeof(digits));
		for (int i = 1; i <= x.length(); i++) {
			digits[i] = x[x.length() - i] - '0';
		}   // 注意倒序（个十百千的顺序）
	}

	// 转换为可以输出的字符串
	string toString() const {
		string str;
		int back = 0;

		// 先找到最后一个不是零的数位
		//（复杂度不高完全没必要把长度存下来）
		for (int i = DIGITS; i >= 1; i--) {
			if (digits[i] != 0) {
				back = i;
				break;
			}
		}

		// 倒着放到字符串里
		for (int i = back; i >= 1; i--)
			str += to_string(digits[i]);

		// 如果字符串里什么也没有：所有数位都是零，手动赋一个零
		if (str == "")
			str = "0";

		return str;
	}

	// 用只有16位的short
	short digits[DIGITS + 2];

	//////////////////// 高精度加法 ////////////////////
	void add(const BigInt& x) {
		int inc = 0; // 进位标记

		 // 从最低位开始累加
		for (int i = 1; i <= DIGITS; i++) {
			// 加起来
			digits[i] = digits[i] + x.digits[i] + inc;

			// 如果结果大于了十：要进位
			if (digits[i] >= 10) {
				inc = 1;               // 标记进位
				digits[i] -= 10;   // 把结果减去十
			}
			else // 如果不需要进位，把标记清空
				inc = 0;
		}
	}

};

//typedef unsigned long long AnsType;
typedef BigInt AnsType;

//vector<vector<AnsType>> ans;
AnsType ans[1000][100];
AnsType One("1"), Zero("0");
bool flag[1000][100];
const AnsType& func(int i, int j) {
	if (i == j || j == 0)
		return One;
	else if (i < 0 || j < 0 || i < j)
		return Zero;
	else if (flag[i][j])
		return ans[i][j];
	else {
		flag[i][j] = true;
		ans[i][j].add(func(i - 1, j));
		ans[i][j].add(func(i - 1, j - 1));
		return ans[i][j];
	}
}

int qm(int base, int expotent, int mod) {
	int ans = 1;
	int factor = base % mod;
	while (expotent != 0) {
		if (expotent % 2 == 1)
			ans = (ans*factor) % mod;
		expotent /= 2;
		factor = (factor*factor) % mod;
	}
	return ans;
}

int main(int argc, char* argv[]) {

	int k, x;
	cin >> k >> x;
	int l = qm(x, x, 1000);
	//cout << l << endl;
	cin >> l;
	//ans.resize(l);
	//for (int i = 0; i < l; i++)
	//	ans[i].resize(min(i + 1, l));
	cout << func(l - 1, k - 1).toString() << endl;


	return 0;
}

#endif

