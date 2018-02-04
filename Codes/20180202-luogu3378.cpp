/*
DOCUMENT CODE "20180202-luogu3378.cpp"
CREATION DATE 2018-02-02
SIGNATURE CODE_20180202_LUOGU3378
TOPIC ¶ÑÄ£°å
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180202_LUOGU3378

#include <iostream>
#include <cstdlib>
#include <climits>
#include <queue>
#include <functional>
using namespace std;

#define LSON(a) (a * 2)
#define RSON(a) (a * 2 + 1)
#define FATHER(a) (a / 2)

#define ISROOT(a) (a / 2 <= 0)

int arr[1000001];
int n;

void condense(int x) {
	int w = x, xval = arr[x];
	if (LSON(x) <= n&&xval > arr[LSON(x)]) {
		w = LSON(x);
		xval = arr[LSON(x)];
	}
	if (RSON(x) <= n&&xval > arr[RSON(x)]) {
		w = RSON(x);
		xval = arr[RSON(x)];
	}
	if (x != w) {
		swap(arr[x], arr[w]);
		condense(w);
	}
}

void pushup(int x) {
	if (ISROOT(x)) // Root
		return;
	if (arr[FATHER(x)] > arr[x]) {
		swap(arr[FATHER(x)], arr[x]);
		pushup(FATHER(x));
	}
}

void construct() {
	int mid = n / 2;
	for (int i = mid; i >= 1; i--) {
		condense(i);
	}
}

void makesorted() {
	int total = n;
	while (n > 1) {
		swap(arr[1], arr[n]);
		n--;
		condense(1);
	}
	n = total;
}

void pop() {
	if (n >= 1) {
		swap(arr[1], arr[n]);
		n--;
		condense(1);
	}
}

void push(int x) {
	n++;
	arr[n] = x;
	pushup(n);
}


//priority_queue<int, vector<int>, greater<int>> Q;
int main() {
	int n;
	int a, b;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a;
		if (a == 1) {
			cin >> b;
			//Q.push(b);
			push(b);
		}
		else if (a == 2) {
			//cout << Q.top() << endl;
			cout << arr[1] << endl;
		}
		else if (a == 3) {
			//Q.pop();
			pop();
		}
	}
}

#endif

