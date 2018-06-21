/*
DOCUMENT CODE "20180619-bnds0093.cpp"
CREATION DATE 2018-06-19
SIGNATURE CODE_20180619_BNDS0093
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180619_BNDS0093

#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

int n, k;
int w[100], v[100];
int d[500];

int main(int argc, char* argv[]) {

	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		cin >> w[i] >> v[i];
	}

	for (int i = 1; i <= n; i++)
		for (int j = k; j >= w[i]; j--)
			if (d[j] < d[j - w[i]] + v[i])
				d[j] = d[j - w[i]] + v[i];

	int Max = 0;
	for (int i = 0; i <= k; i++)
		Max = max(Max, d[i]);

	cout << Max << endl;

	return 0;
}

#endif

