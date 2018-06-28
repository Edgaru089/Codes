/*
DOCUMENT CODE "20180625-bnds0616.cpp"
CREATION DATE 2018-06-25
SIGNATURE CODE_20180625_BNDS0616
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180625_BNDS0616

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

struct BigInt {
	int digits[60];
	int top = 0;
	BigInt() {
		top = 0;
		memset(digits, 0, sizeof(digits));
	}
	BigInt(int x) {
		top = 0;
		memset(digits, 0, sizeof(digits));
		while (x != 0) {
			top++;
			digits[top] = x % 10;
			x /= 10;
		}
	}
	void add() {
		digits[1]++;
		for (int i = 1; i <= top; i++) {
			if (digits[i] > 10) {
				digits[i + 1]++;
				digits[i] -= 10;
			}
		}
		if (digits[top + 1] > 0)
			top++;
	}

	void add(const BigInt& add) {
		int maxtop = max(top, add.top);
		for (int i = 1; i <= maxtop; i++) {
			digits[i] += add.digits[i];
			if (digits[i] > 10) {
				digits[i + 1] += digits[i] / 10;
				digits[i] %= 10;
			}
		}
		top = maxtop;
		if (digits[top + 1] > 0)
			top++;
	}

	void output() const {
		if (top == 0)
			putchar('0');
		for (int i = top; i >= 1; i--)
			putchar(digits[i] + '0');
	}
};

int k, x;
int limit;
int read() {
	char c;
	int val = 0;

	while (!isdigit(c = getchar()));

	do {
		val = val * 10 + (c - '0');
	} while (isdigit(c = getchar()));

	return val;
}

int read(int& val) {
	return val = read();
}


//vector<thread*> th;
BigInt ans[1001][101];
BigInt zero, one(1);
bool flag[1001][101];

int qm(int base, int expotent, int mod) {
	int ans = 1;
	int factor = base;
	while (expotent > 0) {
		if (expotent % 2 == 1)
			ans = (ans*factor) % mod;
		expotent /= 2;
		factor = (factor*factor) % mod;
	}
	return ans;
}

const BigInt& func(int i, int j) {
	if (j == 0 || i == j)
		return one;
	else if (j < 0 || i < 0 || i > j)
		return zero;
	else if (flag[i][j])
		return ans[i][j];
	else {
		flag[i][j] = true;
		ans[i][j].add(func(i - 1, j));
		ans[i][j].add(func(i - 1, j - 1));
		return ans[i][j];
	}
}

int main(int argc, char* argv[]) {

	read(k); read(x);

	limit = qm(x, x, 1000);
	//read(limit);
	//printf("%d\n", limit);
	func(k - 1, limit - 1).output();
	putchar('\n');

	return 0;
}

#endif

