/*
DOCUMENT CODE "20180616-bnds0178.cpp"
CREATION DATE 2018-06-16
SIGNATURE CODE_20180616_BNDS0178
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180616_BNDS0178

#include <cstdlib>
#include <iostream>
using namespace std;

enum State {
	Rising,
	Dropping
};

int n;
int a[100001];
State state;
int cur;

int main(int argc, char* argv[]) {

	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}

	int count = 1;
	int i = 1;
	while (i + 1 <= n && a[i + 1] == a[i])
		i++;
	if (i + 1 > n) {
		cout << count << endl;
		return 0;
	}
	i++;
	if (a[i - 1] < a[i])
		state = Dropping;
	else
		state = Rising;
	count++;

	i++;
	cur = a[i - 1];
	for (; i <= n; i++) {
		if (state == Dropping) {
			if (a[i] > cur) {
				cur = a[i];
			}
			else if (a[i] < cur) {
				state = Rising;
				cur = a[i];
				count++;
			}
		}
		else if (state == Rising) {
			if (a[i] < cur)
				cur = a[i];
			else if (a[i] > cur) {
				state = Dropping;
				cur = a[i];
				count++;
			}
		}
	}

	cout << count << endl;

	return 0;
}

#endif

