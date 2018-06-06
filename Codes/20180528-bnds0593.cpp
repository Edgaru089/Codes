/*
DOCUMENT CODE "20180528-bnds0593.cpp"
CREATION DATE 2018-05-28
SIGNATURE CODE_20180528_BNDS0593
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180528_BNDS0593

#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

#define DEFLATE_DIGIT_COUNT 9
#define DEFLATE_NUMBER      1000000000

#define DIGITS 50

int pow10(int x) {
	int ans = 1;
	while (--x >= 0)
		ans *= 10;
	return ans;
}

struct BigInt {

	BigInt() { memset(digits, 0, sizeof(digits)); }
	BigInt(int x) {
		memset(digits, 0, sizeof(digits));
		digits[1] = x;
	}
	BigInt(string x) {
		memset(digits, 0, sizeof(digits));
		int tmp = 0, i = 1, k = 0;
		for (int j = x.size() - 1; j >= 0; j--) {
			k++;
			char c = x[j];
			tmp += pow10(k - 1)*(c - '0');
			if (k >= DEFLATE_DIGIT_COUNT) {
				digits[i] = tmp;
				tmp = 0;
				i++;
				k = 0;
			}
		}
		digits[i] = tmp;
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
		for (int i = 1; i <= back; i++) {
			char c[12];
			sprintf(c, "%0*d", DEFLATE_DIGIT_COUNT, digits[i]);
			str = c + str;
		}
		if (str == "")
			str = "0";

		size_t pos = str.find_first_not_of('0');
		if (pos != string::npos) {
			str = str.substr(pos);
		}

		return str;
	}

	int digits[DIGITS + 2];

};

BigInt add(BigInt& x, BigInt& y) {
	BigInt sum;
	int inc = 0;
	for (int i = 1; i <= DIGITS; i++) {
		sum.digits[i] = x.digits[i] + y.digits[i] + inc;
		if (sum.digits[i] >= DEFLATE_NUMBER) {
			inc = sum.digits[i] / DEFLATE_NUMBER;
			sum.digits[i] %= DEFLATE_NUMBER;
		}
		else
			inc = 0;
	}
	return sum;
}

BigInt anx[780][800];
bool flag[780][800];

BigInt& ans(int count, int sum) {
	if (flag[count][sum])
		return anx[count][sum];
	if (count == 1) {
		flag[count][sum] = true;
		anx[count][sum] = BigInt(1);
		return anx[count][sum];
	}
	else {
		anx[count][sum] = BigInt(0);
		for (int i = 0; i <= sum; i++) {
			anx[count][sum] = add(anx[count][sum], ans(count - 1, sum - i));
		}
		flag[count][sum] = true;
		return anx[count][sum];
	}
}

int main(int argc, char* argv[]) {
	int count, sum;
	cin >> count >> sum;
	cout << ans(count, sum).toString() << endl;
	return 0;
}

#endif

