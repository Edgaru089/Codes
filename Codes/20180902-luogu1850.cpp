/*
DOCUMENT NAME "20180902-luogu1850.cpp"
CREATION DATE 2018-09-02
SIGNATURE CODE_20180902_LUOGU1850
COMMENT P1850 ªªΩÃ “
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180902_LUOGU1850

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <initializer_list>
using namespace std;

const int infinity = 1e9;
const int MaxV = 300 + 10, MaxE = 90000 + 10;
const int MaxN = 2000 + 10, MaxM = 2000 + 10;

template<typename IntType = int>
IntType read() {
	IntType val = 0;
	int c;
	bool invflag = false;
	while (!isdigit(c = getchar()))
		if (c == '-')
			invflag = true;
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = getchar()));
	ungetc(c, stdin);
	if (invflag)
		return -val;
	else
		return val;
}
template<typename IntType>
void read(IntType& x) { x = read<IntType>(); }
template<typename IntType, typename... Args>
void read(IntType& x, Args&... args) { x = read<IntType>(); read(args...); }

int v, e;
int n, m;
int c[MaxN], d[MaxN];
double k[MaxN];
int dis[MaxV][MaxV];
double dp[MaxN][MaxM][2];

template<typename Value, typename Compare = less<Value>>
void update(Value& val, const Value& other, Compare compare = less<Value>()) {
	if (compare(other, val))
		val = other;
}

template<typename Value, typename Compare = less<Value>>
void update(Value& val, initializer_list<Value> others, Compare compare = less<Value>()) {
	for (auto& i : others)
		if (compare(i, val))
			val = i;
}


int main(int argc, char* argv[]) {

	read(n, m, v, e);
	for (int i = 1; i <= n; i++)
		scanf("%d", c + i);
	for (int i = 1; i <= n; i++)
		scanf("%d", d + i);
	for (int i = 1; i <= n; i++)
		scanf("%lf", k + i);
	for (int i = 1; i <= v; i++)
		for (int j = 1; j <= v; j++)
			if (i != j)
				dis[i][j] = infinity;
	for (int i = 1; i <= e; i++) {
		int u, v, l;
		scanf("%d%d%d", &u, &v, &l);
		dis[u][v] = dis[v][u] = min(dis[u][v], l);
	}

	for (int k = 1; k <= v; k++)
		for (int i = 1; i <= v; i++)
			for (int j = 1; j <= v; j++)
				update(dis[i][j], dis[i][k] + dis[k][j]);

	for (int i = 1; i <= n; i++)
		for (int j = 0; j <= m; j++)
			dp[i][j][0] = dp[i][j][1] = infinity;

	dp[1][0][0] = dp[1][1][1] = 0;
	for (int i = 2; i <= n; i++)
		for (int j = 0; j <= m; j++) {
			update(dp[i][j][0], {
				dp[i - 1][j][0] + dis[c[i - 1]][c[i]],
				dp[i - 1][j][1] + dis[d[i - 1]][c[i]] * k[i - 1] + dis[c[i - 1]][c[i]] * (1 - k[i - 1])
			});
			if (j > 0)
				update(dp[i][j][1], {
					dp[i - 1][j - 1][0] + dis[c[i - 1]][d[i]] * k[i] + dis[c[i - 1]][c[i]] * (1 - k[i]),
					dp[i - 1][j - 1][1] +
					dis[c[i - 1]][c[i]] * (1 - k[i - 1])*(1 - k[i]) +
					   dis[c[i - 1]][d[i]] * (1 - k[i - 1])*k[i] +
					   dis[d[i - 1]][c[i]] * k[i - 1] * (1 - k[i]) +
					   dis[d[i - 1]][d[i]] * k[i - 1] * k[i]
				});
		}

	double ans = infinity;
	for (int i = 0; i <= m; i++) {
		ans = min({ ans, dp[n][i][0], dp[n][i][1] });
	}

	printf("%.2lf\n", ans);

	return 0;
}

#endif

