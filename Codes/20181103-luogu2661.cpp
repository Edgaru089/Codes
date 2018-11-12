/*
 DOCUMENT NAME "20181103-luogu2661.cpp"
 CREATION DATE 2018-11-03
 SIGNATURE CODE_20181103_LUOGU2661
 COMMENT P2661 ÐÅÏ¢´«µÝ
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181103_LUOGU2661

#include <cstdlib>
#include <iostream>
#include <queue>
using namespace std;

template<typename IntType>
void read(IntType& val) {
	val = 0;
	int c;
	bool inv = false;
	while (!isdigit(c = getchar()))
		if (c == '-')
			inv = true;
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = getchar()));
	if (inv)
		val = -val;
}

const int MaxN = 200000 + 10;

int n;
int a[MaxN];

struct q{
	q(){}
	q(int u,int step):u(u),step(step){}
	int u,step;
};

queue<q> Q;
bool been[MaxN];



void bfs(){
}




int main(int argc, char* argv[]) {

	return 0;
}

#endif

