/*
DOCUMENT CODE "20180117-pi.cpp"
CREATION DATE 2018-01-17
SIGNATURE CODE_20180117_PI
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180117_PI

#include <cstdlib>
#include <iostream>
#include <iomanip>

#include <SFML/System.hpp>

using namespace std;
using namespace sf;

int main(int argc, char* argv[]) {
	long long n;
	cin >> n;
	double pi = 0;
	double sum;
	Clock cl;
	cl.restart();
	for (long long i = 1; i <= n; i++) {
		sum = 4.0 / (2.0 * i - 1.0);
		if (((i + 1) & 1))
			sum *= -1.0;
		pi += sum;
		if (cl.getElapsedTime() >= milliseconds(100)) {
			cl.restart();
			printf("\r%.20lf", pi);
		}
	}
	return 0;
}

#endif

