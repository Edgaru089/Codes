/*
DOCUMENT CODE "luogu1017.cpp"
CREATION DATE 2017-11-09
SIGNATURE CODE_20171109_LUOGU1017
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20171109_LUOGU1017

#include <cstdlib>
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

const char charmap[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int n, r;

const int power(int base, int hex) {
	int ans = 1;
	for (int i = 1; i <= hex; i++)
		ans *= base;
	return ans;
}


int main(int argc, char* argv[]) {

	cin >> n >> r;

	bool skipping = true;

	cout << n << "=";

	stack<int> ans;
	while (n != 0) {
		int output = n % r;
		n /= r;
		if (output < 0) {
			output -= r;
			n += 1;
		}
		ans.push(output);
	}

	while(!ans.empty()) {
		cout << charmap[ans.top()];
		ans.pop();
	}

	cout << "(base" << r << ")" << endl;

	return 0;
}

#endif
