/*
DOCUMENT CODE "20180611-bnds0607.cpp"
CREATION DATE 2018-06-11
SIGNATURE CODE_20180611_BNDS0607
TOPIC test 2018-06-11
ตรทึ 100/100
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180611_BNDS0607

#include <cstdlib>
#include <iostream>
using namespace std;

int n;
int a[10001];

int d[10001];

int lowbit(int x) { return x & -x; }

void add(int id, int amount) {
	while (id <= n) {
		d[id] += amount;
		id += lowbit(id);
	}
}

int prefix(int id) {
	int sum = 0;
	while (id > 0) {
		sum += d[id];
		id -= lowbit(id);
	}
	return sum;
}


int main(int argc, char* argv[]) {
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];

	int sum = 0;
	for (int i = 1; i <= n; i++) {
		sum += prefix(n - a[i] + 1);
		add(n - a[i] + 1, 1);
	}

	cout << sum << endl;

	return 0;
}

#endif

