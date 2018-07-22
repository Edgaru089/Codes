/*
DOCUMENT NAME "20180720-luogu3203.cpp"
CREATION DATE 2018-07-20
SIGNATURE CODE_20180720_LUOGU3203
COMMENT [HNOI2010]µØ∑…√‡—Ú / ∑÷øÈ¥Û∑®
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180720_LUOGU3203

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

const int MaxN = 200000 + 10, MaxM = 100000 + 10;

int read() {
	int val = 0;
	char c;
	while (!isdigit(c = getchar()));
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = getchar()));
	return val;
}
void read(int& val) { val = read(); }
template<typename... Args>
void read(int& val, Args&... args) { val = read(); read(args...); }

int n, m;

int k[MaxN];

int blocksize; // Advised block size
int blockcnt;
int belong[MaxN], step[MaxN], nexts[MaxN];


int main(int argc, char* argv[]) {

	read(n);
	for (int i = 1; i <= n; i++)
		read(k[i]);
	read(m);

	blocksize = sqrt(n);
	for (int i = 1; i <= n; i++)
		belong[i] = ((i - 1) / blocksize) + 1;
	int left = n - n % blocksize + 1, right = n;
	for (int i = n; i >= 1; i--) {
		if (i < left) {
			left -= blocksize;
			right = left + blocksize - 1;
		}
		int x = i + k[i];
		if (x > n) {
			step[i] = 1;
			nexts[i] = -1;
		}
		else if (x > right) {
			step[i] = 1;
			nexts[i] = x;
		}
		else if (x <= right) {
			step[i] = step[x] + 1;
			nexts[i] = nexts[x];
		}
	}

	int x, y, z;
	for (int i = 1; i <= m; i++) {
		read(x);
		if (x == 1) {
			read(y); y++;
			int cnt = 0;
			while (y != -1) {
				cnt += step[y];
				y = nexts[y];
			}
			printf("%d\n", cnt);
		}
		else if (x == 2) {
			read(y, z); y++;
			k[y] = z;
			int left = y - (y - 1) % blocksize, right = min(left + blocksize - 1, n);
			for (int i = right; i >= left; i--) {
				int x = i + k[i];
				if (x > n) {
					step[i] = 1;
					nexts[i] = -1;
				}
				else if (x > right) {
					step[i] = 1;
					nexts[i] = x;
				}
				else if (x <= right) {
					step[i] = step[x] + 1;
					nexts[i] = nexts[x];
				}
			}
		}
	}

	return 0;
}

#endif

