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
using namespace std;

constexpr i64 mod = 45989;
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
			for (i64 j = 0;	 j < y.n; j++) {
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
	};
};


int main() {
	i64 n, m, t, a, b; std::cin >> n >> m >> t >> a >> b;
	std::vector<vector<i64>>g(n + 1);
	for (i64 i = 1; i <= m; i++) {
		i64 u, v; std::cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	Matrix c(n);
	c.a[a][0] = 1;
	Matrix trans(n);
	for (i64 i = 0; i < n; i++) {
		for (auto v : g[i]) {
			trans.a[i][v] = 1;
		}
	}
	c = quickPower(trans, t) * c;
	i64 ans = c.a[b][0] % mod;
	std::cout << ans % mod << "\n";
}