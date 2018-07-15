/*
DOCUMENT NAME "20180714-poj1475.cpp"
CREATION DATE 2018-07-14
SIGNATURE CODE_20180714_POJ1475
COMMENT Pushing Boxes
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180714_POJ1475

#include <cstdlib>
#include <iostream>
#include <queue>
using namespace std;

const int MaxN = 20 + 10, MaxM = 20 + 10;

int n, m;
bool flag[MaxN][MaxM];

int sx, sy;
int tx, ty;
int youx, youy;

bool canget[MaxN][MaxM];
int minstep[MaxN][MaxM];


int boxx, boxy;
int myx, myy;

bool boxbeen[MaxN][MaxM];

void check() {

}

struct que {
	int bx, by;
	int boxstep, mystep;
	string step;
};

struct cmp {
	bool operator () (que x, que y) {
		if (x.boxstep > y.boxstep)
			return true;
		else if (x.boxstep == y.boxstep&&x.mystep > y.mystep)
			return true;
		else
			return false;
	}
};

priority_queue<que, vector<que>, cmp> Q;

void bfs() {
	boxbeen[sx][sy] = true;
	Q.push(que{ sx, sy, 0, 0, "" });

	myx = youx;
	myy = youy;
	boxx = sx;
	boxy = sy;

	while (!Q.empty()) {
		que q = Q.top(); Q.pop();
		if (q.bx == tx && q.by == ty) {

		}

		check();

	}
}


int main(int argc, char* argv[]) {


	return 0;
}

#endif

