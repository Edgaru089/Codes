/*
DOCUMENT CODE "20180422-luogu3372.cpp"
CREATION DATE 2018-04-22
SIGNATURE CODE_20180422_LUOGU3372
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180422_LUOGU3372

#include <cstdlib>
#include <iostream>
using namespace std;

struct st {
	long long sum, lazy;
	int left, right;
	st* lson, *rson;
};

st pool[200001], *h[100001];
int d[100001], n;
st* root;

void build(int left = 1, int right = n, st*& p = root) {

}

int main(int argc, char* argv[]) {

	return 0;
}

#endif

