/*
DOCUMENT CODE "20180430-luogu1305.cpp"
CREATION DATE 2018-04-30
SIGNATURE CODE_20180430_LUOGU1305
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180430_LUOGU1305

#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

struct node {
	char c;
	int lson, rson;
	int father;
};

int n;
int root;

node h[27];


string prev(int p = root) {
	if (p == 0)
		return "";
	string str;
	str += h[p].c;
	str += prev(h[p].lson);
	str += prev(h[p].rson);
	return str;
}

int main(int argc, char* argv[]) {
	string str;

	cin >> n;

	for (int i = 1; i <= n; i++) {
		cin >> str;

		int id = str[0] - 'a' + 1;
		h[id].c = str[0];
		if (str[1] != '*') {
			h[id].lson = str[1] - 'a' + 1;
			h[str[1] - 'a' + 1].father = id;
		}
		if (str[2] != '*') {
			h[id].rson = str[2] - 'a' + 1;
			h[str[2] - 'a' + 1].father = id;
		}
	}

	int p = str[0] - 'a' + 1;
	while (h[p].father != 0)
		p = h[p].father;
	root = p;

	cout << prev() << endl;
	return 0;
}

#endif

