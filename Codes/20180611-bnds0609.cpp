/*
DOCUMENT CODE "20180611-bnds0609.cpp"
CREATION DATE 2018-06-11
SIGNATURE CODE_20180611_BNDS0609
TOPIC test 2018-06-11
�÷� 72/100
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180611_BNDS0609

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

int d, g;
int t[101], f[101], h[101];

// ��ʾ��ǰʱ��Ϊ i ���߶�Ϊ j ��״���ܷ�ﵽ
// ��ʼ��dp[0 ~ 10][0] = 1, ���� = 0
bool dp[2000][200];

int main(int argc, char* argv[]) {
	cin >> d >> g;
	for (int i = 1; i <= g; i++) {
		cin >> t[i] >> f[i] >> h[i];
	}

	for (int i = 0; i <= 10; i++)
		dp[i][0] = true;

	int maxTime = 10, minTime = INT_MAX;
	for (int l = 1; l <= g; l++) {
		int T = t[l], F = f[l], H = h[l];
		for (int i = 2000 - T; i >= T; i--) {
			for (int j = d; j >= 0; j--) {
				if (dp[i][j]) {
					dp[i][j + H] = true;  // ���ڽŵ���
					// �Ե�
					for (int k = i; k <= i + F; k++)
						dp[k][j] = true;
					maxTime = max(maxTime, i + F);
					if (j + H >= d)
						minTime = min(minTime, i);
				}
			}
		}
	}

	//cout << (minTime == INT_MAX ? "Failed" : "Success") << endl;

	if (minTime != INT_MAX)
		cout << minTime << endl;
	else
		cout << maxTime << endl;

	return 0;
}

#endif

