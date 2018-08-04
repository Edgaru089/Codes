/*
DOCUMENT NAME "20180726-luogu4525.cpp"
CREATION DATE 2018-07-26
SIGNATURE CODE_20180726_LUOGU4525
COMMENT 【模板】自适应辛普森法1 / 自适应性辛普森法（ASR）
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180726_LUOGU4525

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

double a, b, c, d, l, r;

int main(int argc, char* argv[]) {

	scanf("%lf%lf%lf%lf%lf%lf", &a, &b, &c, &d, &l, &r);

	printf("%.6lf\n", asr(l, r, [&](double x) {return (c*x + d) / (a*x + b); }));

	return 0;
}

#endif

