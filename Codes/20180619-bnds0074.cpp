/*
DOCUMENT CODE "20180619-bnds0074.cpp"
CREATION DATE 2018-06-19
SIGNATURE CODE_20180619_BNDS0074
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180619_BNDS0074

#include <cstdlib>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int a[30], b[30], c[30];
string s1, s2;

int main(int argc, char* argv[]) {

	cin >> s1 >> s2;

	for (int i = 0; i < s1.size(); i++)
		a[s1.size() - i] = s1[i] - '0';
	for (int i = 0; i < s2.size(); i++)
		b[s2.size() - i] = s2[i] - '0';

	int sizea = s1.size(), sizeb = s2.size();
	int sizec = max(sizea, sizeb);

	for (int i = 1; i <= sizec; i++) {
		c[i] += a[i] + b[i];
		c[i + 1] += c[i] / 10;
		c[i] %= 10;
	}

	for (int i = 29; i >= 1; i--)
		if (c[i] != 0) {
			sizec = i;
			break;
		}

	for (int i = sizec; i >= 1; i--)
		cout << c[i];
	cout << endl;

	return 0;
}

#endif

