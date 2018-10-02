/*
 DOCUMENT NAME "20180923-now174B.cpp"
 CREATION DATE 2018-09-23
 SIGNATURE CODE_20180923_NOW174B
 COMMENT B-¹«Æ½¾ºÈü
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180923_NOW174B

#include <cstdlib>
#include <iostream>
#include <queue>
#include <set>
using namespace std;

constexpr int MaxN = 5000 + 10, MaxM = 1e6 + 10;

struct node {
	int v;
	bool win;
	node* next;
};

node* h[MaxN];
node mem[2 * MaxM], *memtop = mem;
#define ALLOCATE (++memtop)

void addedge(int winner, int loser) {
	node* p = ALLOCATE;
	p->v = loser;
	p->win = true;
	p->next = h[winner];
	h[winner] = p;
	p = ALLOCATE;
	p->v = winner;
	p->win = false;
	p->next = h[loser];
	h[loser] = p;
}

struct st {
	int u;
	bool nextwin;
	set<int> beens;
};

queue<st> Q;

int main(int argc, char* argv[]) {

	

	return 0;
}

#endif

