/*
DOCUMENT NAME "20180713-bnds0557.cpp"
CREATION DATE 2018-07-13
SIGNATURE CODE_20180713_BNDS0557
COMMENT 高精度除法（高精除高精）
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180713_BNDS0557

#include <cstdlib>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

const int MaxD = 100;

int d1[MaxD], d2[MaxD];
int high1, high2;
int result[MaxD], leftover[MaxD];
int resultlen;

bool isgreaterorequal(int caller[], int aux[], int callerlen, int auxlen, int calleroffset = 0) {
	int high1 = callerlen - calleroffset, high2 = auxlen;
	if (high1 > high2)
		return true;
	if (high1 < high2)
		return false;
	for (int i = high1; i >= 1; i--) {
		if (caller[i + calleroffset] > aux[i])
			return true;
		if (caller[i + calleroffset] < aux[i])
			return false;
	}
	return true;
}

void divide() {
	for (int i = high1 - high2 + 1; i >= 1; i--) {
		while (isgreaterorequal(d1, d2, high1, high2, i - 1)) {
			result[i]++;
			resultlen = max(resultlen, i);

			int borrow = 0;
			for (int j = i; j <= i + high2 - 1; j++) {
				d1[j] -= borrow;
				if (d1[j] < d2[j - i + 1]) {
					d1[j] += 10;
					borrow = 1;
				}
				d1[j] = d1[j] - d2[j - i + 1];
			}
			for (int j = i + high2; j <= high1 && borrow != 0; j++) {
				if (d1[j] >= borrow) {
					d1[j] -= borrow;
					borrow = 0;
				}
			}
			if (d1[high1] == 0)
				high1--;
		}
	}
}

void convert(string source, int dest[], int& len) {
	if (source != "0")
		len = source.size();
	for (int i = 0; i < source.size(); i++)
		dest[source.size() - i] = source[i] - '0';
}

void output(int d[], int len) {
	for (int i = len; i >= 1; i--)
		printf("%d", d[i]);
	if (len == 0)
		printf("0");
}

int main(int argc, char* argv[]) {

	string a, b;

	cin >> a >> b;

	convert(a, d1, high1);
	convert(b, d2, high2);

	divide();

	output(result, resultlen);
	cout << endl;
	output(d1, high1);
	cout << endl;

	return 0;
}

#endif

