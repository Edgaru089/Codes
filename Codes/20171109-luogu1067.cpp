/*
DOCUMENT CODE "luogu1067.cpp"
CREATION DATE 2017-11-09
SIGNATURE CODE_20171109_LUOGU1067
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20171109_LUOGU1067

#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
	int n;
	vector<int> factors;

	cin >> n;
	factors.resize(n + 1);
	for (int i = 1; i <= n + 1; i++)
		cin >> factors[i - 1];

	if (factors[0] == -1)
		cout << "-";
	if (abs(factors[0]) != 1)
		cout << factors[0];
	if (n > 0)
		cout << "x^" << n;
	for (int i = 1; i < n + 1; i++) {
		if (factors[i] == 0)
			continue;
		if (factors[i] > 0)
			cout << "+";
		if (factors[i] == -1 && i != n)
			cout << "-";
		else if (abs(factors[i]) != 1 || i == n)
			cout << factors[i];
		if (i < n)
			cout << "x";
		if (i < n - 1)
			cout << "^" << n - i;
	}
	cout << endl;

	return 0;
}

#endif
