/*
DOCUMENT CODE "luogu1042.cpp"
CREATION DATE 2017-11-09
SIGNATURE CODE_20171109_LUOGU1042
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20171109_LUOGU1042

#include <cstdlib>
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

typedef pair<int, int> IntPair;

char input;

vector<IntPair> ans11, ans21;

int w11, l11;
int w21, l21;

void add11(char c) {
	if (c == 'W')
		w11++;
	else if (c == 'L')
		l11++;
	if ((w11 >= 11 || l11 >= 11) && abs(w11 - l11) >= 2) {
		ans11.push_back(IntPair(w11, l11));
		w11 = l11 = 0;
	}
}

void add21(char c) {
	if (c == 'W')
		w21++;
	else if (c == 'L')
		l21++;
	if ((w21 >= 21 || l21 >= 21) && abs(w21 - l21) >= 2) {
		ans21.push_back(IntPair(w21, l21));
		w21 = l21 = 0;
	}
}

int main(int argc, char* argv[]) {

	while ((input = getchar()) != 'E') {
		add11(input);
		add21(input);
	}

	ans11.push_back(IntPair(w11, l11));
	ans21.push_back(IntPair(w21, l21));

	for (IntPair i : ans11)
		cout << i.first << ":" << i.second << endl;
	cout << endl;
	for (IntPair i : ans21)
		cout << i.first << ":" << i.second << endl;

	return 0;
}

#endif
