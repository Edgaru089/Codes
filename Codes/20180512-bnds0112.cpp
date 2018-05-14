/*
DOCUMENT CODE "20180512-bnds0112.cpp"
CREATION DATE 2018-05-12
SIGNATURE CODE_20180512_BNDS0112
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180512_BNDS0112

#include <cstdlib>
#include <iostream>
using namespace std;

const int infinity = 1000000000;

int n;
int dis[1000][1000];

int main(int argc, char* argv[]) {

	cin >> n;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			cin >> dis[i][j];
			if (dis[i][j] == -1)
				dis[i][j] = infinity;
		}


	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (dis[i][j] > dis[i][k] + dis[k][j])
					dis[i][j] = dis[i][k] + dis[k][j];
			}
		}
	}


	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (j > 1)
				cout << ' ';
			if (dis[i][j] < infinity)
				cout << dis[i][j];
			else
				cout << -1;
		}
		cout << endl;
	}

	return 0;
}

#endif

