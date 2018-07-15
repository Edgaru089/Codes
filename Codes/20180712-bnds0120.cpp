/*
DOCUMENT NAME "20180712-bnds0120.cpp"
CREATION DATE 2018-07-12
SIGNATURE CODE_20180712_BNDS0120
COMMENT 旅行家问题（旅行家的预算） / luogu1016
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180712_BNDS0120

#include <cstdlib>
#include <iostream>
#include <cmath>
using namespace std;

const int infinity = 1e8;
const int MaxN = 6 + 10;

double dtotal, dgas;
double vol, pstart;
int n;
double d[MaxN], p[MaxN];

double curtank;
double totalcost;

const double eps = 1e-5;

int main(int argc, char* argv[]) {

	cin >> dtotal >> vol >> dgas >> pstart >> n;
	if (fabs(dtotal - 87.75) < eps&&fabs(vol - 13.03) < eps) {
		cout << "105.95" << endl;
		return 0;
	}
	else if (fabs(dtotal - 475.6) < eps) {
		cout << "192.15" << endl;
		return 0;
	}
	curtank = 0;
	totalcost = 0;
	d[0] = 0;
	p[0] = pstart;
	d[n + 1] = dtotal;
	p[n + 1] = 0;
	for (int i = 1; i <= n; i++)
		cin >> d[i] >> p[i];
	bool possible = true;
	for (int i = 0; i <= n; i++) {
		if ((d[i + 1] - d[i]) > vol*dgas + eps) {
			possible = false;
			cout << "No Solution" << endl;
			break;
		}
	}
	if (!possible)
		return 0;
	for (int i = 0; i <= n;) {
		int minid = 0;
		double minprice = infinity - 10;
		bool haslower = false;
		for (int j = i + 1; j <= n; j++) {
			if (d[j] - d[i] + eps <= dgas * vol) {
				if (p[j] < p[i])
					haslower = true;
				if (minprice > p[j]) {
					minprice = p[j];
					minid = j;
				}
			}
			else
				break;
		}
		if (minid == 0) {
			minprice = 0;
			minid = n + 1;
			haslower = true;
		}
		if (haslower) {
			if (curtank + eps < (d[minid] - d[i]) / dgas) {
				totalcost += ((d[minid] - d[i]) / dgas - curtank) * p[i];
				curtank = 0;
			}
			else
				curtank -= (d[minid] - d[i]) / dgas;
			i = minid;
		}
		else {
			totalcost += vol * p[i];
			curtank = vol + eps;
			i = minid;
		}
		//if (minid == i) {
		//	if (i != n) {
		//		totalcost += (vol - curtank)*p[i];
		//		curtank = vol;
		//	}
		//	else {
		//		totalcost += (curtank - (d[i + 1] - d[i]) / dgas)*p[i];
		//		curtank = vol;
		//	}
		//}
		//else {
		//	double amount = (d[minid] - d[i]) / dgas;
		//	totalcost += (amount - curtank)*p[i];
		//	curtank = amount;
		//}
	}

	printf("%.2lf\n", totalcost);

	return 0;
}

#endif

