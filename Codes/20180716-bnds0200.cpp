/*
DOCUMENT NAME "20180716-bnds0200.cpp"
CREATION DATE 2018-07-16
SIGNATURE CODE_20180716_BNDS0200
COMMENT Mayan”Œœ∑ luogu1312
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180716_BNDS0200

#include <cstdlib>
#include <iostream>
#include <tuple>
#include <utility>
using namespace std;

typedef int color;
const int MaxN = 10, MaxColor = 15;
const int n = 7, m = 5;

int step;

struct state {
	color c[MaxN][MaxN];
	color* operator [] (int id) { return c[id]; }
};

state init, cur;

template<typename ValType, int Size = 200000>
class stack {
public:
	stack() :stacktop(0) {}
	void push(const ValType& val) { arr[stacktop++] = val; }
	template<typename... Args>
	void push_construct(Args... args) { arr[stacktop++] = ValType(args...); }
	void pop() { if (stacktop > 0) stacktop--; }
	ValType& top() { return arr[stacktop - 1]; }
	bool empty() { return stacktop <= 0; }
	int getsize() { return stacktop; }
	ValType* getdata() { return arr; }
private:
	int stacktop;
	ValType arr[Size];
};

stack<state> states;
stack<tuple<int, int, int>> ops;

bool checkfall(state& s = cur) {
	bool flag = false;
	for (int i = 1; i <= 6; i++)
		for (int j = 1; j <= 5; j++) {
			if (s[i][j] != 0 && s[i + 1][j] == 0) {
				s[i + 1][j] = s[i][j];
				s[i][j] = 0;
				flag = true;
			}
		}
	return flag;
}

void update(state& s = cur) {
	checkfall(s);
	bool clearflag[MaxN][MaxN] = {};
	for (int i = 1; i <= 7; i++)
		for (int j = 1; j <= 5; j++) {
			if (s[i][j] == 0)
				continue;
			if (s[i - 1][j] == s[i][j] && s[i][j] == s[i + 1][j])
				clearflag[i - 1][j] = clearflag[i][j] = clearflag[i + 1][j] = true;
			if (s[i][j - 1] == s[i][j] && s[i][j] == s[i][j + 1])
				clearflag[i][j - 1] = clearflag[i][j] = clearflag[i][j + 1] = true;
		}
	bool changed = false;
	for (int i = 1; i <= 7; i++)
		for (int j = 1; j <= 5; j++)
			if (clearflag[i][j]) {
				s[i][j] = 0;
				changed = true;
			}
	if (changed)
		update(s);
}

bool checkpossible(state& s = cur) {
	int colorcnt[MaxColor];
	for (int i = 1; i <= 7; i++)
		for (int j = 1; j <= 5; j++)
			colorcnt[s[i][j]]++;
	for (int i = 1; i <= 10; i++)
		if (colorcnt[i] == 1 || colorcnt[i] == 2)
			return false;
	return true;
}

bool checkempty(state& s = cur) {
	bool flag = true;
	for (int i = 1; i <= 7 && flag; i++)
		for (int j = 1; j <= 5 && flag; j++)
			if (s[i][j] != 0)
				flag = false;
	return flag;
}

void pushstate() {
	states.push(cur);
}

void popstate() {
	cur = states.top();
	states.pop();
}

bool solved = false;

void dfs() {
	update();

	if (solved)
		return;
	if (checkempty()) {
		solved = true;
		return;
	}
	if (ops.getsize() >= step || !checkpossible())
		return;

	for (int j = 1; j <= 5; j++)
		for (int i = 7; i >= 1; i--) {
			if (cur[i][j] == 0)
				continue;
			// right
			if (j <= 4 && cur[i][j] != cur[i][j + 1]) {
				ops.push_construct(j - 1, 7 - i, 1);
				pushstate();
				swap(cur[i][j], cur[i][j + 1]);
				dfs();
				if (solved)
					return;
				popstate();
				ops.pop();
			}
			//left
			if (j >= 2 && cur[i][j - 1] == 0) {
				ops.push_construct(j - 1, 7 - i, -1);
				pushstate();
				swap(cur[i][j], cur[i][j - 1]);
				dfs();
				if (solved)
					return;
				popstate();
				ops.pop();
			}
		}
}


int main(int argc, char* argv[]) {

	cin >> step;
	for (int i = 1; i <= 5; i++) {
		int x, j = 0;
		do {
			cin >> x;
			init[7 - j++][i] = x;
		} while (x != 0);
	}

	cur = init;
	dfs();

	if (!solved)
		cout << -1 << endl;
	else {
		for (int i = 0; i < ops.getsize(); i++) {
			auto op = ops.getdata()[i];
			cout << get<0>(op) << " " << get<1>(op) << " " << get<2>(op) << endl;
		}
	}

	return 0;
}

#endif

