#include<bits/extc++.h>

using i8 = signed char;
using u8 = unsigned char;
using i16 = signed short int;
using u16 = unsigned short int;
using i32 = signed int;
using u32 = unsigned int;
using f32 = float;
using i64 = signed long long;
using u64 = unsigned long long;
using f64 = double;
using i128 = __int128_t;
using u128 = __uint128_t;
using f128 = long double;
constexpr i64 mod = 1145141;
constexpr i64 maxn = 4e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

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

int main() {
	i64 n, m; std::cin >> n >> m;
	Matrix x(n + 5);
	for (i64 i = 1; i <= n; i++) {
		x.a[i][i] = x.a[i][n + 1] = 1;
	}
	for (i64 i = 1; i <= m; i++) {
		i64 a, b; std::cin >> a >> b;
		x.a[a][b] = x.a[b][a] = 1;
	}
	i64 ans = inf;
	std::vector<bool>l(n + 1);
	auto ret = guassElimination(x, n);
	std::function<void(i64, i64)>dfs = [&](i64 cur, i64 num) {
		if (num >= ans)return;
		if (cur == 0) {
			ans = num; return;
		}
		if (ret.a[cur][cur]) {
			bool v = ret.a[cur][n + 1];
			for (i64 i = cur + 1; i <= n; i++) {
				if (ret.a[cur][i])v = v ^ l[i];
			}
			dfs(cur - 1, num + v);
		} else {
			dfs(cur - 1, num);
			l[cur] = 1;
			dfs(cur - 1, num + 1);
			l[cur] = 0;
		}
	};
	dfs(n, 0); std::cout  << ans << "\n";;
}