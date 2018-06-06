/*
DOCUMENT CODE "20180530-bnds0592.cpp"
CREATION DATE 2018-05-30
SIGNATURE CODE_20180530_BNDS0592
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180530_BNDS0592

#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

vector<int> id, temp;
vector<int> a;

int n;

int main(int argc, char* argv[]) {

	cin >> n;
	a.reserve(n);
	for (int i = 1; i <= n; i++) {
		int k;
		cin >> k;
		a.push_back(k);
	}

	id.reserve(n);
	temp.reserve(n);
	for (int i = 0; i < n; i++)
		id.push_back(i);

	int i = 1 << 30;
	while (i > 0 && id.size() > 2) {

		for (int k : id) {
			if ((a[k] & i) == 1)
				temp.push_back(k);
		}

		i >>= 1;
		if (temp.size() == 1 || temp.size() >= 2)
			id = temp;
	}

	cout << (a[id[0]] & a[id[1]]) << endl;

	return 0;
}

#endif

