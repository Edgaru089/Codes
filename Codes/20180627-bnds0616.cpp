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

// ������ÿ�����д����λ
#define DIGITS 500

//////////////////// �߾������� ////////////////////
struct BigInt {

	// �������캯��
	// Ĭ������»������û�õ�λ��Ϊ��
	BigInt() { memset(digits, 0, sizeof(digits)); }
	BigInt(string x) {
		memset(digits, 0, sizeof(digits));
		for (int i = 1; i <= x.length(); i++) {
			digits[i] = x[x.length() - i] - '0';
		}   // ע�⵹�򣨸�ʮ��ǧ��˳��
	}

	// ת��Ϊ����������ַ���
	string toString() const {
		string str;
		int back = 0;

		// ���ҵ����һ�����������λ
		//�����ӶȲ�����ȫû��Ҫ�ѳ��ȴ�������
		for (int i = DIGITS; i >= 1; i--) {
			if (digits[i] != 0) {
				back = i;
				break;
			}
		}

		// ���ŷŵ��ַ�����
		for (int i = back; i >= 1; i--)
			str += to_string(digits[i]);

		// ����ַ�����ʲôҲû�У�������λ�����㣬�ֶ���һ����
		if (str == "")
			str = "0";

		return str;
	}

	// ��ֻ��16λ��short
	short digits[DIGITS + 2];

	//////////////////// �߾��ȼӷ� ////////////////////
	void add(const BigInt& x) {
		int inc = 0; // ��λ���

		 // �����λ��ʼ�ۼ�
		for (int i = 1; i <= DIGITS; i++) {
			// ������
			digits[i] = digits[i] + x.digits[i] + inc;

			// ������������ʮ��Ҫ��λ
			if (digits[i] >= 10) {
				inc = 1;               // ��ǽ�λ
				digits[i] -= 10;   // �ѽ����ȥʮ
			}
			else // �������Ҫ��λ���ѱ�����
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

