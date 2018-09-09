/*
DOCUMENT NAME "20180904-luogu2877.cpp"
CREATION DATE 2018-09-04
SIGNATURE CODE_20180904_LUOGU2877
COMMENT P2827 òÇò¾
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180904_LUOGU2877

#include <cstdlib>
#include <iostream>
using namespace std;

const int MaxN = 1e5 + 10, MaxM = 7e6 + 10;

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
template<>
string read<string>() {
	string str;
	str.clear();
	int c;
	while (iscntrl(c = getchar()) || isblank(c));
	do {
		str.push_back(c);
	} while (!(iscntrl(c = getchar()) || isblank(c)));
	ungetc(c, stdin);
	return str;
}
template<typename IntType>
void read(IntType& x) { x = read<IntType>(); }
template<typename IntType, typename... Args>
void read(IntType& x, Args&... args) { x = read<IntType>(); read(args...); }

template<typename Type, int Size = 4 * MaxN>
class queue {
public:
	queue() { clear(); }
	void clear() { left = 1; right = 0; }
	Type front() { return arr[left]; }
	void push(Type x) { arr[++right] = x; }
	void pop() { left++; }
	bool empty() { return !(right >= left); }
private:
	int left, right;
	Type arr[Size];
};

int n, m, q, u, v, t;
double p;



int main(int argc, char* argv[]) {

	return 0;
}

#endif

