/*
DOCUMENT NAME "20180729-luoguT24410.cpp"
CREATION DATE 2018-07-29
SIGNATURE CODE_20180729_LUOGUT24410
COMMENT
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180729_LUOGUT24410

#include <cstdlib>
#include <iostream>
#include <cmath>
using namespace std;

double n, m;

int main(int argc, char* argv[]) {

	cin >> n >> m;
	double x = 2 * sqrt(n*n + m * m);
	double s = x * x / 2.0;
	double c = x / sqrt(2) * 4;

	printf("%.2lf %.2lf\n", c, s);

	return 0;
}

#endif

