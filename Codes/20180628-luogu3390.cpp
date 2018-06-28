/*
DOCUMENT NAME "20180628-luogu3390.cpp"
CREATION DATE 2018-06-28
SIGNATURE CODE_20180628_LUOGU3390
COMMENT ¡¾Ä£°å¡¿¾ØÕó¿ìËÙÃÝ
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180628_LUOGU3390

#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

template<typename IntType = int>
struct Matrix {
	Matrix() :size(0) {}
	Matrix(const Matrix<IntType>& copy) {
		size = copy.size;
		val.resize(copy.size);
		for (int i = 0; i < copy.size; i++) {
			val[i].resize(copy.size);
			for (int j = 0; j < copy.size; j++)
				val[i][j] = copy[i][j];
		}
	}

	void initalaize(int n) {
		size = n;
		val.resize(n);
		for (auto& i : val)
			i.resize(n, 0);
	}

	void initalaize(IntType** vals, int n) {
		size = n;
		val.resize(n);
		for (int i = 0; i < n; i++) {
			val[i].resize(n);
			for (int j = 0; j < n; j++)
				val[i][j] = vals[i][j];
		}
	}

	void initalaizeUnit(int n) {
		size = n;
		val.resize(n);
		for (int i = 0; i < n; i++) {
			val[i].resize(n);
			for (int j = 0; j < n; j++)
				if (i == j)
					val[i][j] = 1;
				else
					val[i][j] = 0;
		}
	}

	Matrix<IntType> multply(const Matrix& x, IntType mod = -1) const {
		if (x.size != size)
			return Matrix<IntType>();
		Matrix<IntType> ans;
		ans.initalaize(size);
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				ans[i][j] = 0;
				for (int k = 0; k < size; k++) {
					if (mod == -1)
						ans[i][j] += val[i][k] * x[k][j];
					else
						ans[i][j] = (ans[i][j] + val[i][k] * x[k][j]) % mod;
				}
			}
		}
		return ans;
	}

	const vector<IntType>& operator [] (int id) const { return val[id]; }
	vector<IntType>& operator [] (int id) { return val[id]; }

	const Matrix<IntType>& operator = (const Matrix<IntType>& x) {
		size = x.size;
		val.resize(x.size);
		for (int i = 0; i < x.size; i++) {
			val[i].resize(x.size);
			for (int j = 0; j < x.size; j++)
				val[i][j] = x[i][j];
		}
		return *this;
	}

	vector<vector<IntType>> val;
	int size;
};

typedef Matrix<long long> MatrixLL;


MatrixLL qm(const MatrixLL& base, long long expotent, int mod) {
	MatrixLL ans, factor = base;
	ans.initalaizeUnit(base.size);

	while (expotent != 0) {
		if (expotent % 2 == 1)
			ans = ans.multply(factor, mod);
		expotent /= 2;
		factor = factor.multply(factor, mod);
	}

	return ans;
}


int main(int argc, char* argv[]) {

	long long n, k;
	MatrixLL base;

	cin >> n >> k;
	base.initalaize(n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> base[i][j];

	MatrixLL answer = qm(base, k, 1000000007);
	//for (int i = 1; i <= k - 1; i++)
	//	base = base.multply(base, 1000000007);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (j != 0)
				cout << " ";
			cout << answer[i][j];
		}
		cout << endl;
	}

	return 0;
}

#endif

