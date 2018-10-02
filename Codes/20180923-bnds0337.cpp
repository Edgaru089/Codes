/*
 DOCUMENT NAME "20180923-bnds0337.cpp"
 CREATION DATE 2018-09-23
 SIGNATURE CODE_20180923_BNDS0337
 COMMENT #337. 2017-8-24Ä£Äâ²âÑé£¨Èý£©
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180923_BNDS0337

#include <cstdlib>
#include <iostream>
#include <set>
#include <map>
#include <cstring>
using namespace std;

constexpr int MaxN = 1e5 + 10, MaxK = 2 * MaxN;

constexpr int buffersize = 20 * 1024 * 1024;
char buffer[buffersize], *buffertop = buffer;
#define GETCHAR *(buffertop++)
#define UNGETCHAR(c) (--buffertop)
template<typename IntType = int>
IntType read() {
	IntType ans = 0;
	int c;
	while (!isdigit(c = GETCHAR));
	do {
		ans = (ans << 3) + (ans << 1) + c - '0';
	} while (isdigit(c = GETCHAR));
	UNGETCHAR(c);
	return ans;
}
template<typename IntType>
void read(IntType& val) { val = read<IntType>(); }
template<typename IntType, typename... Args>
void read(IntType& val, Args&... args) { val = read<IntType>(); read(args...); }
void readstr(string& str) {
	str.clear();
	int c;
	while (iscntrl(c = GETCHAR) || isblank(c));
	do {
		str.push_back(c);
	} while (!(iscntrl(c = GETCHAR) || isblank(c)));
	UNGETCHAR(c);
}

int t, n, a, x[MaxN], y[MaxN], k[MaxN];
set<int> S;
map<int, int> M;

int p[600000];

int setfind(int x) {
	if (p[x] < 0)
		return x;
	else
		return p[x] = setfind(p[x]);
}

void setunion(int x, int y) {
	x = setfind(x);
	y = setfind(y);
	if (x == y)
		return;
	if (p[y] < p[x]) {
		p[x] += p[y];
		p[y] = x;
	}
	else {
		p[y] += p[x];
		p[x] = y;
	}
}


int main(int argc, char* argv[]) {
	fread(buffer, 1, buffersize, stdin);

	read(t);
	for (int l = 1; l <= t; l++) {

		read(n);
		for (int i = 1; i <= n; i++) {
			read(x[i], y[i], k[i]);
			S.insert(x[i]);
			S.insert(y[i]);
		}
		a = 0;
		for (int i : S) {
			a++;
			M[i] = a;
		}
		memset(p, -1, 4 * (a + 10));

		for (int i = 1; i <= n; i++) {
			x[i] = M[x[i]];
			y[i] = M[y[i]];
		}

		for (int i = 1; i <= n; i++)
			if (k[i] == 1)
				setunion(x[i], y[i]);

		bool flag = true;
		for (int i = 1; i <= n && flag; i++)
			if (k[i] == 0 && (setfind(x[i]) == setfind(y[i])))
				flag = false;

		if (flag)
			printf("YES\n");
		else
			printf("NO\n");
	}


	return 0;
}


#endif

