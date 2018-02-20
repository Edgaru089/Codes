/*
DOCUMENT CODE "20180204-marcool0622.cpp"
CREATION DATE 2018-02-04
SIGNATURE CODE_20180204_MARCOOL0622
TOPIC É¨À× ¼òµ¥ËÑË÷
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180204_MARCOOL0622

#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

#define EMPTY           0
#define MINE            1
#define NUMBER          2
#define EMPTY_VISITED   3
#define NUMBER_VISITED  4

#define VISITED(a) ((a)>=EMPTY_VISITED)
#define NOTVISITED(a) (!VISITED(a))

int n, m;
int map[51][51];
int ans = 0;

#define INRANGE(x,y)    ((x) >= 1 && (x) <= n && (y) >= 1 && (y) <= m)
#define SETNUMBER(x,y)  if (INRANGE(x,y) && !VISITED(map[x][y]) && map[x][y] != MINE) map[x][y] = NUMBER

void dfs(int x, int y) {
	if (!INRANGE(x, y))
		return;
	if (map[x][y] == NUMBER)
		map[x][y] = NUMBER_VISITED;
	if (map[x][y] != EMPTY)
		return;
	map[x][y] = EMPTY_VISITED;

	dfs(x - 1, y);
	dfs(x - 1, y + 1);
	dfs(x - 1, y - 1);
	dfs(x, y + 1);
	dfs(x, y - 1);
	dfs(x + 1, y);
	dfs(x + 1, y + 1);
	dfs(x + 1, y - 1);
}

int main(int argc, char* argv[]) {
	cin >> n >> m;
	string str;
	for (int i = 1; i <= n; i++) {
		cin >> str;
		for (int j = 1; j <= m; j++) {
			char ch = str[j - 1];
			if (ch == '.')
				; // Nothing
			else if (ch == '*') {
				map[i][j] = MINE;
				SETNUMBER(i - 1, j);
				SETNUMBER(i - 1, j + 1);
				SETNUMBER(i - 1, j - 1);
				SETNUMBER(i, j + 1);
				SETNUMBER(i, j - 1);
				SETNUMBER(i + 1, j);
				SETNUMBER(i + 1, j + 1);
				SETNUMBER(i + 1, j - 1);
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (map[i][j] == EMPTY) {
				ans++;
				dfs(i, j);
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (map[i][j] == NUMBER)
				ans++;
		}
	}

	cout << ans << endl;

	return 0;
}

#endif

