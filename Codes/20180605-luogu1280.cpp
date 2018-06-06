/*
DOCUMENT CODE "20180605-luogu1280.cpp"
CREATION DATE 2018-06-05
SIGNATURE CODE_20180605_LUOGU1280
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180605_LUOGU1280

#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

int n, m, a[100];
int s[10][100][100];

int main(int argc, char* argv[]) {

	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		char c;
		cin >> c;
		a[i] = c - '0';
	}

	for (int i = 1; i <= n; i++) {
		for (int j = i; j <= n; j++) {
			for (int k = i; k <= j; k++) {
				s[0][i][j] *= 10;
				s[0][i][j] += a[k];
			}
		}
	}

	for (int k = 1; k <= m; k++) {
		for (int i = 1; i < n; i++) {
			for (int j = i + k; j <= n; j++) {
				for (int l = i; l <= j - 1; l++) { // Place a multply mark behind a[l]
					for (int a = 0; a <= k - 1; a++) {
						for (int b = k - 1 - a; b <= k; b++) {
							s[k][i][j] = max(s[k][i][j], s[a][i][l] * s[b][l + 1][j]);
						}
					}
				}
			}
		}
	}

	cout << s[m][1][n] << endl;

	return 0;
}

#endif

