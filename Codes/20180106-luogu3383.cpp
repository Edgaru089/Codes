/*
DOCUMENT CODE "20180106-luogu3383.cpp"
CREATION DATE 2018-01-06
SIGNATURE CODE_20180106_LUOGU3383
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180106_LUOGU3383

#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

vector<int> primes;
bool isPrime[10000000];

int main(int argc, char* argv[]) {

	int n, m;

	cin >> n >> m;

	for (int i = 2; i <= n; i++)
		isPrime[i] = true;
	isPrime[0] = isPrime[1] = false;

	for (int i = 2; i <= n; i++) {
		if (isPrime[i])
			primes.push_back(i);
		for (int j : primes) {
			if (i*j > n)
				break;
			isPrime[i*j] = false;
			if (i%j == 0)
				break;
		}
	}

	int x;
	for (int i = 1; i <= m; i++) {
		cin >> x;
		if (isPrime[x])
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
	}

	return 0;
}

#endif

