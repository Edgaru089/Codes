/*
DOCUMENT CODE "luogu1309.cpp"
CREATION DATE 2017-11-11
SIGNATURE CODE_20171111_LUOGU1309
TOPIC ÈðÊ¿ÂÖ
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20171111_LUOGU1309

#include <cstdlib>
#include <iostream>
#include <functional>
#include <algorithm>
using namespace std;

struct st {

	st() {}
	st(int id, int score, int weight) :id(id), score(score), weight(weight) {}

	int id;
	int score;
	int weight;
};

int n, r, q;
st player[200001];
st winner[100001], loser[100001];

const bool compare(const st x, const st y) {
	if (x.score > y.score)
		return true;
	else if (x.score == y.score&&x.id < y.id)
		return true;
	else
		return false;
}

template<typename Iterator, typename Compare>
int Merge(Iterator sourceA, Iterator sourceB, int sizeA, int sizeB, Iterator dest, Compare compare) {
	int offsetA = 0, offsetB = 0;
	int offsetD = 0;

	while (offsetA < sizeA&&offsetB < sizeB) {
		if (compare(sourceA[offsetA], sourceB[offsetB])) {
			dest[offsetD] = sourceA[offsetA];
			offsetA++;
		}
		else {
			dest[offsetD] = sourceB[offsetB];
			offsetB++;
		}
		offsetD++;
	}

	while (offsetA < sizeA) {
		dest[offsetD] = sourceA[offsetA];
		offsetA++;
		offsetD++;
	}
	while (offsetB < sizeB) {
		dest[offsetD] = sourceB[offsetB];
		offsetB++;
		offsetD++;
	}

	return offsetD;
}

int main(int argc, char* argv[]) {

	int a;
	cin >> n >> r >> q;
	n *= 2;
	for (int i = 0; i < n; i++) {
		cin >> a;
		player[i].score = a;
		player[i].id = i;
	}
	for (int i = 0; i < n; i++) {
		cin >> a;
		player[i].weight = a;
	}

	sort(player, player + n, compare);
	for (int l = 1; l <= r; l++) {
		for (int i = 0; i < n; i += 2) {
			if (player[i].weight > player[i + 1].weight) {
				player[i].score++;
				winner[i / 2] = player[i];
				loser[i / 2] = player[i + 1];
			}
			else {
				player[i + 1].score++;
				winner[i / 2] = player[i + 1];
				loser[i / 2] = player[i];
			}
		}

		Merge(winner, loser, n / 2, n / 2, player, compare);
	}

	cout << player[q - 1].id + 1 << endl;

	return 0;
}

#endif

