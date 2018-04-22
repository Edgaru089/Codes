/*
DOCUMENT CODE "20180421-luogu1498.cpp"
CREATION DATE 2018-04-21
SIGNATURE CODE_20180421_LUOGU1498
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180421_LUOGU1498

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> tri = { " /\\ ","/__\\" };

int power(int x, int n) {
	int ans = 1;
	for (int i = 1; i <= n; i++)
		ans *= x;
	return ans;
}

vector<string> generate_totem(int n) {
	if (n == 1)
		return tri;
	vector<string> result, upper, lower;
	result = generate_totem(n - 1);
	upper = lower = result;
	for (string& i : upper)
		i = string(power(2, n - 1), ' ') + i;
	for (string& i : lower)
		i = i + i;
	for (string& i : lower)
		upper.push_back(i);
	int len = upper[upper.size() - 1].length();
	for (string& i : upper)
		i.resize(len, ' ');
	return upper;
}

int main(int argc, char* argv[]) {
	int n;
	cin >> n;
	vector<string> result = generate_totem(n);

	for (string& i : result) {
		int count = 0;
		for (int j = i.length() - 1; j > 0; j--) {
			if (i[j] != ' ')
				break;
			count++;
		}
		i.resize(i.length() - count);
	}

	for (string& i : result)
		cout << i << endl;
	return 0;
}

#endif

