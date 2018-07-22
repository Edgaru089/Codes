/*
DOCUMENT NAME "20180719-luogu2005.cpp"
CREATION DATE 2018-07-19
SIGNATURE CODE_20180719_LUOGU2005
COMMENT A/B Problem II
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180719_LUOGU2005

#include <cstdlib>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

const int MaxD = 20000;

int d1[MaxD], d2[MaxD];
int d2k[10][MaxD], d2klen[10];
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

void genk() {
	for (int i = 1; i <= high2; i++)
		d2k[1][i] = d2[i];
	d2klen[1] = high2;
	for (int i = 2; i <= 9; i++) {
		d2klen[i] = d2klen[i - 1];
		for (int j = 1; j <= d2klen[i - 1]; j++)
			d2k[i][j] = d2k[i - 1][j];
		for (int j = 1; j <= d2klen[i]; j++) {
			d2k[i][j] += d2[j];
			if (d2k[i][j] >= 10) {
				d2k[i][j + 1] += d2k[i][j] / 10;
				d2k[i][j] %= 10;
			}
		}
		if (d2k[i][d2klen[i] + 1] > 0)
			d2klen[i]++;
	}
}

void divide() {
	for (int i = high1 - high2 + 1; i >= 1; i--) {
		for (int j = 9; j >= 1; j--)
			if (isgreaterorequal(d1, d2k[j], high1, d2klen[j], i - 1)) {
				result[i] = j;
				resultlen = max(resultlen, i);

				int borrow = 0;
				for (int k = i; k <= i + d2klen[j] - 1; k++) {
					d1[k] -= borrow;
					if (d1[k] < d2k[j][k - i + 1]) {
						d1[k] += 10;
						borrow = 1;
					}
					d1[k] = d1[k] - d2k[j][k - i + 1];
				}
				for (int k = i + high2; k <= high1 && borrow != 0; k++) {
					if (d1[k] >= borrow) {
						d1[k] -= borrow;
						borrow = 0;
					}
				}
				while (high1 > 0 && d1[high1] == 0)
					high1--;

				break;
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

	genk();
	divide();

	output(result, resultlen);
	cout << endl;

	return 0;
}

#endif

