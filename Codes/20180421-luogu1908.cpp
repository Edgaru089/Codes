/*
DOCUMENT CODE "20180421-luogu1908.cpp"
CREATION DATE 2018-04-21
SIGNATURE CODE_20180421_LUOGU1908
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180421_LUOGU1908

#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

template<typename Iterator, typename Compare>
void mergeSort(Iterator begin, Iterator end, Compare comp, int& count) {
	int len = end - begin;
	if (len == 1)
		return;
	else if (len == 2) {
		if (!comp(*begin, *(begin + 1))) {
			swap(*begin, *(begin + 1));
			count++;
		}
	}
	else {
		int mid = len / 2;
		mergeSort(begin, begin + mid + 1, comp, count);
		mergeSort(begin + mid + 1, end, comp, count);

		Iterator left1 = begin, left2 = begin + mid + 1;
		while (left1 < begin + mid + 1 && left2 < end) {
			if(comp(*left1,*left2))

		}
	}
}

int main(int argc, char* argv[]) {
	vector<int> vec;
	int n;
	cin >> n;
	vec.reserve(n);
	for (int i = 1; i <= n; i++) {
		int t;
		cin >> t;
		vec.push_back(t);
	}
	int count = 0;
	mergeSort(vec.begin(), vec.end(), [](int x, int y) {return x <= y; }, count);
	cout << count << endl;
	return 0;
}

#endif

