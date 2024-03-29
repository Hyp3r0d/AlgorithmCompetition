struct Matrix {
public:
	i64 n; std::vector<std::vector<i64>>a;
	Matrix(i64 len = 4): n(len), a(len) {
		for (i64 i = 0; i < len; i++) {
			a[i].assign(len, 0);
		}
	}
	void init() {
		for (i64 i = 0; i < n; i++) {
			for (i64 j = 0; j < n; j++) {
				if (i == j)a[i][j] = 1;
				else a[i][j] = 0;
			}
		}
	}
	friend Matrix operator*(Matrix x, Matrix y) {
		i64 n = x.n;
		Matrix ret(n);
		for (i64 i = 0; i < n; i++) {
			for (i64 j = 0; j < n; j++) {
				for (i64 k = 0; k < n; k++) {
					ret.a[i][j] = (ret.a[i][j] % mod + x.a[i][k] % mod * y.a[k][j] % mod) % mod;
				}
			}
		}
		return ret;
	}
	friend Matrix operator+(Matrix x, Matrix y) {
		Matrix ret(x.n);
		for (i64 i = 0; i < x.n; i++) {
			for (i64 j = 0; j < y.n; j++) {
				ret.a[i][j] = (x.a[i][j] % mod + y.a[i][j]) % mod;
			}
		}
		return ret;
	}
	friend Matrix quickPower(Matrix x, i64 y) {
		Matrix ret(x.n);
		for (i64 i = 0; i < x.n; i++)ret.a[i][i] = 1;
		while (y) {
			if (y & 1)ret = ret * x;
			x = x * x;
			y >>= 1;
		}
		return ret;
	}
	/*高斯消元解异或方程组*/
	friend Matrix guassElimination(Matrix x, i64 n) {
		/*增广矩阵为 n * (n + 1)的矩阵*/
		for (i64 i = 1; i <= n; i++) {
			i64 k = i;
			while (k <= n and not x.a[k][i])k++;
			if (k > n)continue;
			swap(x.a[i], x.a[k]);
			for (i64 j = 1; j <= n; j++) {
				if (i == j or not x.a[j][i])continue;
				for (i64 k = i + 1; k <= n + 1; k++) {
					x.a[j][k] ^= x.a[i][k];
				}
				x.a[j][i] = 0;
			}
		}
		return x;
	}
};
