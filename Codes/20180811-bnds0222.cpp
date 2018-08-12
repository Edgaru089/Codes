/*
DOCUMENT NAME "20180811-bnds0222.cpp"
CREATION DATE 2018-08-11
SIGNATURE CODE_20180811_BNDS0222
COMMENT 求m区间内的最小值
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180811_BNDS0222

#include <cstdlib>
#include <iostream>
using namespace std;

constexpr int MaxN = 2000000 + 10;

int n, m;
int a[MaxN];
int ans[MaxN];

template<typename IntType = int>   // 模板默认类型需要C++11
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
template<typename IntType, typename... Args>     // 模板参数包需要C++11
void read(IntType& x, Args&... args) { x = read<IntType>(); read(args...); }

template<typename Type, int Size = MaxN>
class deque {
public:
	deque() { clear(); }
	void clear() { left = 1; right = 0; }
	const Type& front() { return arr[left]; }
	const Type& back() { return arr[right]; }
	void push_back(const Type& x) { arr[++right] = x; }
	void pop_front() { left++; }
	void pop_back() { right--; }
	bool empty() { return !(right >= left); }
private:
	int left, right;
	Type arr[Size];
};
// pair<id, val>
deque<pair<int, int>> Q;



int main(int argc, char* argv[]) {

	read(n, m);
	for (int i = 1; i <= n; i++)
		read(a[i]);

	for (int i = 1; i <= n; i++) {
		while (!Q.empty() && Q.front().first < i - m)
			Q.pop_front();
		if (!Q.empty())
			ans[i] = Q.front().second;
		while (!Q.empty() && Q.back().second > a[i])
			Q.pop_back();
		Q.push_back(make_pair(i, a[i]));
	}

	for (int i = 1; i <= n; i++)
		printf("%d\n", ans[i]);

	return 0;
}

#endif

