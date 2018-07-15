/*
DOCUMENT NAME "20180713-bnds0128.cpp"
CREATION DATE 2018-07-13
SIGNATURE CODE_20180713_BNDS0128
COMMENT Á¢ÌåÍ¼
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180713_BNDS0128

#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

char map[1000][3000];

vector<string> block = {
	"..+---+",
	"./   /|",
	"+---+ |",
	"|   | +",
	"|   |/.",
	"+---+.."
};

void printBlock(int x, int y, int z) {
	int lbCX, lbCY;
	lbCX = 4 * x + 2 * y;
	lbCY = 2 * y + 3 * z;
	for (int i = lbCY; i < lbCY + block.size(); i++)
		for (int j = lbCX; j < lbCX + block[0].size(); j++) {
			int u = block.size() - (i - lbCY) - 1, v = j - lbCX;
			if (block[u][v] == '.')
				continue;
			if (map[i][j] != '.')
				continue;
			else
				map[i][j] = block[u][v];
		}
}

int shrinkMap() {
	bool flag = false;
	int i;
	for (i = 999; i > 0 && !flag; i--)
		for (int j = 0; j < 3000 && !flag; j++)
			if (map[i][j] != '.')
				flag = true;
	int lines = i + 2;
	int maxy = 0;
	for (int i = lines - 1; i >= 0; i--) {
		for (int j = 3000 - 1; j >= 0; j--)
			if (map[i][j] != '.')
				maxy = max(maxy, j);
	}
	for (int i = lines - 1; i >= 0; i--)
		map[i][maxy + 1] = 0;
	return lines;
}

int m, n;
int height[1000][1000];
int height2[1000][1000];

int main(int argc, char* argv[]) {

	memset(map, '.', sizeof(map));

	cin >> m >> n;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++) {
			cin >> height[i][j];
		}

	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			height2[j][i] = height[i][j];
	swap(m, n);
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n / 2; j++)
			swap(height2[i][j], height2[i][n - j - 1]);

	for (int y = 0; y < n; y++)
		for (int x = m - 1; x >= 0; x--)
			for (int z = height2[x][y] - 1; z >= 0; z--)
				printBlock(x, y, z);

	int lines = shrinkMap();

	for (int i = lines - 1; i >= 0; i--)
		cout << map[i] << endl;

	return 0;
}

#endif

