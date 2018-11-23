#include <cstdlib>
#include <iostream>
#include <cctype>
#include <cstdio>
#include <vector>
using namespace std;

#define FILENAME "filecodehere"

#if (defined LOCAL || defined D)
#define DEBUG(...) printf(__VA_ARGS__)
#else
#define DEBUG(...)
#endif

const int bufferreadsize = 30 * 1024 * 1024;
const int bufferwritesize = 5 * 1024 * 1024;
char buffer[bufferreadsize], *buffertop = buffer;
#define GETCHAR *(buffertop++)
#define UNGETCHAR(c) (--buffertop)

template<typename IntType>
inline IntType read() {
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
inline string read<string>() {
	string str;
	str.clear();
	int c;
	while (iscntrl(c = GETCHAR) || c == ' ' || c == '\t');
	do {
		str.push_back(c);
	} while (!(iscntrl(c = GETCHAR) || c == ' ' || c == '\t'));
	UNGETCHAR(c);
	return str;
}
template<typename IntType>
inline void read(IntType& x) { x = read<IntType>(); }

char bufferwrite[bufferwritesize], *writetop = bufferwrite;
#define PUTCHAR(c) (*(writetop++) = (c))

inline void putstr(char* str) {
	while ((*str) != '\0') {
		PUTCHAR(*str);
		str++;
	}
}

template<typename IntType>
inline void println(IntType val) {
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

/******************** End of quickread template ********************/

const int MaxN=10000+10;

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
    Matrix(const initializer_list<initializer_list<IntType>>& vals) {
        size = vals.size();
        val.resize(size);
        int i = 0;
        for (auto& ix : vals) {
            val[i].resize(size);
            int j = 0;
            for (auto& jx : ix) {
                val[i][j] = jx;
                j++;
            }
            i++;
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

    void initalaize(const initializer_list<initializer_list<IntType>>& vals) {
        size = vals.size();
        val.resize(size);
        int i = 0;
        for (auto& ix : vals) {
            val[i].resize(size);
            int j = 0;
            for (auto& jx : ix) {
                val[i][j] = jx;
                j++;
            }
            i++;
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


int gcd(int n, int m) {
	if(!m)
		return n;
	else
		return gcd(m,n%m);
}



int main(int argc, char* argv[]) {/*
#if (defined LOCAL) || (defined ONLINE_JUDGE)
	FILE* in = stdin, *out = stdout;
#else
	FILE* in = fopen(FILENAME ".in", "rb");
	FILE* out = fopen(FILENAME ".out", "wb");
#endif
	fread(buffer, 1, bufferreadsize, in);
	fclose(in);	*/

    int n, m;
	cin >> n >> m;
	//cout<<gcd(n,m)<<endl;
	MatrixLL ans = MatrixLL({ { 1, 1 }, { 0, 0 } }).multply(qm(MatrixLL({ { 1, 1 }, { 1, 0 } }), gcd(n, m)-1, 100000000), 100000000);
	cout << ans.val[0][1] << endl;
	
	/*
	fwrite(bufferwrite, 1, writetop - bufferwrite, out);
	fclose(out);
	*/return 0;
}

