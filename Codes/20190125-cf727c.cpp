/*
 DOCUMENT NAME "20190125-cf727c.cpp"
 CREATION DATE 2019-01-25
 SIGNATURE CODE_20190125_CF727C
 COMMENT Guess the Array
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20190125_CF727C

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
using namespace std;

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
	} while ((c = getchar()) != EOF && isdigit(c));
	if (inv)
		val = -val;
}

const int MaxN = 5000 + 10;

int n;
int a[MaxN];
int s12, s23, s13;

int main(int argc, char* argv[]) {

	cin >> n;

	cout << "? 1 2" << endl;
	cin >> s12;
	cout << "? 2 3" << endl;
	cin >> s23;
	cout << "? 3 1" << endl;
	cin >> s13;

	int s3 = (s12 + s23 + s13) / 2;
	a[1] = s3 - s23;
	a[2] = s3 - s13;
	a[3] = s3 - s12;

	int x;
	for (int i = 4; i <= n; i++) {
		cout << "? 1 " << i << endl;
		cin >> x;
		a[i] = x - a[1];
	}

	cout << "!";
	for (int i = 1; i <= n; i++)
		cout << " " << a[i];
	cout << endl;

	return 0;
}

#endif

