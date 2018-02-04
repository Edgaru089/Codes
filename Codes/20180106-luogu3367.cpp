/*
DOCUMENT CODE "20180106-luogu3367.cpp"
CREATION DATE 2018-01-06
SIGNATURE CODE_20180106_LUOGU3367
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180106_LUOGU3367

#include <cstdlib>
#include <iostream>
#include <cstring>
using namespace std;

int p[10001];

int Find(short x) {
	if (p[x] < 0)
		return x;
	else
		return p[x] = Find(p[x]);
}

void Union(int x, int y) {
	x = Find(x);
	y = Find(y);
	if (x != y) {
		p[x] += p[y];
		p[y] = x;
	}
}


int main(int argc, char* argv[]) {
	int n, m;
	cin >> n >> m;

	memset(p, -1, sizeof(p));

	int z, x, y;

	for (int i = 1; i <= m; i++) {
		cin >> z >> x >> y;
		if (z == 1)
			Union(x, y);
		else if (z == 2) {
			if (Find(x) == Find(y))
				cout << "Y" << endl;
			else
				cout << "N" << endl;
		}
	}

	return 0;
}

#endif

