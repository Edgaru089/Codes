/*
DOCUMENT NAME "20180726-luogu4526.cpp"
CREATION DATE 2018-07-26
SIGNATURE CODE_20180726_LUOGU4526
COMMENT 【模板】自适应辛普森法2 / 自适应性辛普森法（ASR）
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180726_LUOGU4526

#include <cstdlib>
#include <iostream>
#include <cmath>
using namespace std;

const double eps = 1e-8;

template<typename Function>
double simpson(double l, double r, Function func) {
	double mid = (l + r) / 2.0;
	return (func(l) + 4.0 * func(mid) + func(r))*(r - l) / 6.0;
}

template<typename Function>
double _asr(double l, double r, Function func, double ans) {
	double mid = (l + r) / 2.0;
	double lans = simpson(l, mid, func), rans = simpson(mid, r, func);
	if (fabs(ans - lans - rans) < eps)
		return lans + rans;
	else
		return _asr(l, mid, func, lans) + _asr(mid, r, func, rans);
}

template<typename Function>
double asr(double left, double right, Function func) {
	return _asr(left, right, func, simpson(left, right, func));
}

double a;

int main(int argc, char* argv[]) {

	scanf("%lf", &a);

	if (a < 0)
		printf("orz\n");
	else
		printf("%.5lf\n", asr(eps, 20, [&](double x) {return pow(x, a / x - x); }));

	return 0;
}

#endif

