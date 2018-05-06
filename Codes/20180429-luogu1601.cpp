/*
DOCUMENT CODE "20180429-luogu1601.cpp"
CREATION DATE 2018-04-29
SIGNATURE CODE_20180429_LUOGU1601
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180429_LUOGU1601

#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

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
		for (int i = 1000; i >= 1; i--) {
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

	short digits[1002];

};

BigInt add(BigInt x, BigInt y) {
	BigInt sum;
	int inc = 0;
	for (int i = 1; i <= 1000; i++) {
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

int main(int argc, char* argv[]) {
	string x, y;
	cin >> x >> y;
	cout << add(BigInt(x), BigInt(y)).toString() << endl;
	return 0;
}

#endif

