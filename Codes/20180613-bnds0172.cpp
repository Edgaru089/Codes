/*
DOCUMENT CODE "20180613-bnds0172.cpp"
CREATION DATE 2018-06-13
SIGNATURE CODE_20180613_BNDS0172
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180613_BNDS0172

#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

int n, m;
int d[10001], prefix[10001];

// ��ǰΪ i ���ӣ�ƣ��ֵΪ��ʱ��������
int dp[20002];

// [begin, end]
int section(int begin, int end) {
	if (begin > end)
		return 0;
	return prefix[end] - prefix[begin - 1];
}

int main(int argc, char* argv[]) {

	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> d[i];
		prefix[i] = prefix[i - 1] + d[i];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= m; j++) {
			dp[i + j] = max(dp[i + j], dp[i]); // Ъ��
			dp[i + 2 * j] = max(dp[i + 2 * j], dp[i] + section(i + 1, i + j)); // ��ǰ�� j ���ӣ�����Ϣ j ����
		}
	}

	cout << dp[n] << endl;

	return 0;
}

#endif

