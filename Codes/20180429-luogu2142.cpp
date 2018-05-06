/*
DOCUMENT CODE "20180429-luogu2142.cpp"
CREATION DATE 2018-04-29
SIGNATURE CODE_20180429_LUOGU2142
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180429_LUOGU2142

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

#define DIGITS 20100

struct BigInt {

	BigInt() { memset(digits, 0, sizeof(digits)); }
	BigInt(int x) {
		memset(digits, 0, sizeof(digits));
		int i = 1;
		while (x != 0) {
			digits[i] = x % 10;
			x /= 10;
			i++;
		}
	}
	BigInt(string x) {
		memset(digits, 0, sizeof(digits));
		for (int i = 1; i <= x.length(); i++) {
			digits[i] = x[x.length() - i] - '0';
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
		for (int i = back; i >= 1; i--) {
			str += to_string(digits[i]);
		}
		if (str == "")
			str = "0";
		return str;
	}

	short digits[DIGITS + 2];

};

BigInt add(BigInt x, BigInt y) {
	BigInt sum;
	int inc = 0;
	for (int i = 1; i <= DIGITS; i++) {
		sum.digits[i] = x.digits[i] + y.digits[i] + inc;
		if (sum.digits[i] >= 10) {
			inc = 1;
			sum.digits[i] -= 10;
		}
		else
			inc = 0;
	}
	return sum;
}

BigInt multply(BigInt x, BigInt y) {
	BigInt ans, tmp;
	for (int i = 1; i <= DIGITS; i++) {
		if (x.digits[i] == 0)
			continue;
		memset(tmp.digits, 0, sizeof(tmp.digits));
		for (int j = 1; j <= DIGITS / 2; j++) {
			if (y.digits[j] == 0)
				continue;
			tmp.digits[i + j - 1] = y.digits[j] * x.digits[i];
		}
		for (int j = 1; j <= DIGITS; j++) {
			tmp.digits[j + 1] += tmp.digits[j] / 10;
			tmp.digits[j] %= 10;
		}
		ans = add(ans, tmp);
	}
	return ans;
}

enum Result {
	Less,
	Equal,
	Greater
};

Result compare(BigInt x, BigInt y) {
	int backX = 0, backY = 0;
	for (int i = DIGITS; i >= 1; i--) {
		if (x.digits[i] != 0) {
			backX = i;
			break;
		}
	}
	for (int i = DIGITS; i >= 1; i--) {
		if (y.digits[i] != 0) {
			backY = i;
			break;
		}
	}
	if (backX > backY)
		return Greater;
	else if (backX < backY)
		return Less;
	else {
		for (int i = backX; i >= 1; i--) {
			if (x.digits[i] > y.digits[i])
				return Greater;
			else if (x.digits[i] < y.digits[i])
				return Less;
		}
		return Equal;
	}
}

BigInt minusX(BigInt x, BigInt y) {
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

string s1, s2;
BigInt x, y;

int main(int argc, char* argv[]) {
	
	cin >> s1 >> s2;
	
	x = BigInt(s1);
	y = BigInt(s2);

	if (compare(x, y) == Less) {
		cout << "-";
		swap(x, y);
	}

	cout << minusX(x, y).toString() << endl;

	return 0;
}

#endif

