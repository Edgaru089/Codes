/*
DOCUMENT CODE "20180430-luogu1115.cpp"
CREATION DATE 2018-04-30
SIGNATURE CODE_20180430_LUOGU1115
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180430_LUOGU1115

#include <cstdlib>
#include <iostream>
#include <climits>
using namespace std;

int sum = 0, Max = 0;
int d[200001], n;

template<typename Type>
Type max(Type& a, Type& b) {
	if (a > b || a == b)
		return a;
	else
		return b;
}

int main(int argc, char* argv[]) {
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> d[i];
	Max = INT_MIN;
	for (int i = 1; i <= n; i++)
		Max = max(Max, d[i]);
	for (int i = 1; i <= n; i++) {
		sum += d[i];
		Max = max(Max, sum);
		if (sum < 0)
			sum = 0;
	}
	cout << Max << endl;
	return 0;
}

#endif

