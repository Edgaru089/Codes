/*
DOCUMENT CODE "20180619-bnds0077.cpp"
CREATION DATE 2018-06-19
SIGNATURE CODE_20180619_BNDS0077
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180619_BNDS0077

#include <cstdlib>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {

	int n;
	cin >> n;
	cout << n << "=";

	bool flag = true;
	for (int i = 2; i <= n; i++) {
		while (n%i == 0) {
			if (flag)
				flag = false;
			else
				cout << "*";
			cout << i;
			n /= i;
		}
	}
	cout << endl;

	return 0;
}

#endif

