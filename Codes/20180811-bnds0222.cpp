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

constexpr int MaxN = 40 * 1024 * 1024 / 4 / 4 + 10;

int n, m;
int a[MaxN];
int ans[MaxN];

constexpr int buffersize = 40 * 1024 * 1024;
char buffer[buffersize], *buffertop = buffer;
#define GETCHAR (*(buffertop++))
#define UNGETCHAR(c) (--buffertop)

template<typename IntType = int>   // 模板默认类型需要C++11
IntType read() {
	IntType val = 0;
	int c;
	bool invflag = false;
	while (!isdigit(c = GETCHAR))
		if (c == '-')
			invflag = true;
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = GETCHAR));
	UNGETCHAR(c);
	if (invflag)
		return -val;
	else
		return val;
}
template<>
string read<string>() {
	string str;
	str.clear();
	int c;
	while (iscntrl(c = GETCHAR) || isblank(c));
	do {
		str.push_back(c);
	} while (!(iscntrl(c = GETCHAR) || isblank(c)));
	UNGETCHAR(c);
	return str;
}
template<typename IntType>
void read(IntType& x) { x = read<IntType>(); }
template<typename IntType, typename... Args>     // 模板参数包需要C++11
void read(IntType& x, Args&... args) { x = read<IntType>(); read(args...); }

char bufferwrite[buffersize], *writetop = bufferwrite;
#define PUTCHAR(c) (*(writetop++) = (c))

template<typename IntType>
void println(IntType val) {
	if (val == 0)
		PUTCHAR('0');
	if (val < 0) {
		PUTCHAR('-');
		val = -val;
	}
	char buf[16], *buftop = buf + 15;
	while (val > 0) {
		*buftop = (val % 10 + '0');
		buftop--;
		val /= 10;
	}
	for (buftop++; buftop <= buf + 15; buftop++)
		PUTCHAR(*buftop);
	PUTCHAR('\n');
}

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

struct pii {
	int id;
	int val;
};

// pair<id, val>
deque<pii> Q;



int main(int argc, char* argv[]) {
	fread(buffer, 1, buffersize, stdin);

	read(n, m);
	for (int i = 1; i <= n; i++)
		read(a[i]);

	for (int i = 1; i <= n; i++) {
		while (!Q.empty() && Q.front().id < i - m)
			Q.pop_front();
		if (!Q.empty())
			ans[i] = Q.front().val;
		while (!Q.empty() && Q.back().val > a[i])
			Q.pop_back();
		Q.push_back(pii{ i, a[i] });
	}

	for (int i = 1; i <= n; i++)
		println(ans[i]);

	fwrite(bufferwrite, 1, writetop - bufferwrite, stdout);

	return 0;
}

#endif

