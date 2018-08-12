/*
DOCUMENT NAME "20180806-luogu1024.cpp"
CREATION DATE 2018-08-06
SIGNATURE CODE_20180806_LUOGU1024
COMMENT 一元三次方程求解
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180806_LUOGU1024

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;


template<typename Function>
double solve(double l, double r, double eps, Function func) {
	double fl = func(l), fr = func(r);
	if (fl*fr > 0)
		return -1024.0;
	else {
		if (fabs(l - r) < eps)
			return (l + r) / 2.0;
		else {
			double mid = (l + r) / 2.0;
			double fmid = func(mid);
			if (fl*fmid <= 0)
				return solve(l, mid, eps, func);
			else if (fr*fmid <= 0)
				return solve(mid, r, eps, func);
			else return fmid;
		}
	}
}


double a, b, c, d;

int main(int argc, char* argv[]) {

	cin >> a >> b >> c >> d;
	vector<double> ans;
	for (double l = -110.0; l <= 110.0; l += 0.89873 - 1e-4) {
		double val = solve(l, l + 0.89873, 1e-4, [=](double x) {return a * x*x*x + b * x*x + c * x + d; });
		if (val != -1024.0) {
			ans.push_back(val);
		}
	}

	for (int i = 0; i < ans.size(); i++)
		if (i != 0)
			printf(" %.2lf", ans[i]);
		else
			printf("%.2lf", ans[i]);
	printf("\n");

	return 0;
}

#endif

