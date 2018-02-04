/*
DOCUMENT CODE "luogu1093.cpp"
CREATION DATE 2017-11-11
SIGNATURE CODE_20171111_LUOGU1093
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20171111_LUOGU1093

#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

struct st {
	st() {}
	st(int id, int a, int b, int c) :id(id), chinese(a), math(b), english(c), total(a + b + c) {}
	int id;
	int chinese, math, english;
	int total;
};

st s[301];
int n;

bool compare(st x, st y) {
	if (x.total > y.total)
		return true;
	else if (x.total == y.total&&x.chinese > y.chinese)
		return true;
	else if (x.total == y.total&&x.chinese == y.chinese&&x.id < y.id)
		return true;
	else
		return false;
}

int main(int argc, char* argv[]) {
	cin >> n;
	int a, b, c;
	for (int i = 1; i <= n; i++) {
		cin >> a >> b >> c;
		s[i] = st(i, a, b, c);
	}
	
	sort(s + 1, s + n + 1, compare);

	for (int i = 1; i <= 5; i++) {
		cout << s[i].id << " " << s[i].total << endl;
	}

	return 0;
}

#endif

