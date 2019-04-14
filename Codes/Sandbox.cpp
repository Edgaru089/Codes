/*
DOCUMENT CODE "Sandbox.cpp"
CREATION DATE 2017-05-18
SIGNATURE CODE_SANDBOX
TOPIC 沙箱 用来写一些没用的测试性东西
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_SANDBOX

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>

#include <functional>
#include <random>

using namespace std;


int n, k;
int a[100];
double b[100];


int main(int argc, char* argv[]) {
//	random_device de();

	mt19937 mt(_Random_device());

	cin >> n >> k;

	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i <= n; i++)
		b[i] = a[i];
	sort(b + 1, b + n + 1);

	cout << "bk=" << b[k] << ", ax=" << b[k] / 2.0 << endl;

	double sum = 0;
	int cnt = 0;

	for (;;) {
		cnt++;
		for (int i = 1; i <= n; i++)
			b[i] = uniform_real_distribution(0.0, (double)a[i])(mt);
		sort(b + 1, b + n + 1);
		sum += b[k];
		cout << "\rat=" << sum / cnt;
	}


	return 0;
}


#endif
