/*
DOCUMENT CODE "20180619-bnds0095.cpp"
CREATION DATE 2018-06-19
SIGNATURE CODE_20180619_BNDS0095
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180619_BNDS0095

#include <cstdlib>
#include <iostream>
using namespace std;

bool flag[100][100], been[100][100];
int n;

void dfs(int x, int y) {
	if (x<1 || x>n || y<1 || y>n)
		return;
	if (!flag[x][y])
		return;
	if (been[x][y])
		return;
	been[x][y] = true;
	dfs(x + 1, y);
	dfs(x - 1, y);
	dfs(x, y + 1);
	dfs(x, y - 1);
}

int main(int argc, char* argv[]) {

	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> flag[i][j];
			flag[i][j] = !flag[i][j];
		}
	}

	dfs(1, 1);

	if (been[n][n])
		cout << "YES" << endl;
	else
		cout << "NO" << endl;

	return 0;
}

#endif

