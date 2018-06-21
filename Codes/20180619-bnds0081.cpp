/*
DOCUMENT CODE "20180619-bnds0081.cpp"
CREATION DATE 2018-06-19
SIGNATURE CODE_20180619_BNDS0081
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180619_BNDS0081

#include <cstdlib>
#include <iostream>
using namespace std;

bool isPrime(int x) {
	for (int i = 2; i < x; i++)
		if (x%i == 0)
			return false;
	return true;
}

int reverse(int x) {
	int sum = 0;
	while (x != 0) {
		sum = sum * 10 + x % 10;
		x /= 10;
	}
	return sum;
}

int main(int argc, char* argv[]) {

	int x;

	cin >> x;

	if (isPrime(x) && isPrime(reverse(x)))
		cout << "Yes" << endl;
	else
		cout << "no" << endl;

	return 0;
}

#endif

