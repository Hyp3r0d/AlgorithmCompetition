#include<bits/stdc++.h>

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

constexpr i64 mod = 1e9 + 7;
constexpr i64 maxn = 2e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

struct Matrix {
public:
	i64 n; vector<vector<i64>>a;
	Matrix(int len = 4): a(len), n(len) {
		for (int i = 0; i < len; i++) {
			a[i].assign(len, 0);
		}
	}
	void init() {
		for (int i = 0; i < n; i++)a[i][i] = 1;
	}
	friend Matrix operator*(Matrix x, Matrix y) {
		Matrix ret(x.n);
		for (int i = 0; i < x.n; i++) {
			for (int j = 0; j < x.n; j++) {
				for (int k = 0; k < x.n; k++) {
					ret.a[i][k] = (ret.a[i][k] % mod + x.a[i][j] % mod * y.a[j][k]) % mod;
				}
			}
		}
		return ret;
	}
	friend Matrix quickPower(Matrix x, i64 y) {
		Matrix ret(x.n);
		ret.init();
		while (y) {
			if (y & 1)ret = ret * x;
			x = x * x;
			y >>= 1;
		}
		return ret;
	};
};


int main() {
	i64 n, k; std::cin >> n >> k;
	// k / 2 even, k - k / 2 odd
	auto check = [&](i64 x) {
		i64 cnt = 0;
		for (i64 i = 0; i <= 2; i++) {
			auto cur = ((x >> i) & 1);
			if (cur)cnt++; // 1为odd
		}
		return (cnt % 2) == 0;
	};
	auto qpow = [&](i64 x, i64 y) {
		i64 ret = 1;
		while (y) {
			if (y & 1)ret = ret * x % mod;
			x = x * x % mod;
			y >>= 1;
		}
		return ret % mod;
	};
	Matrix cur((1 << 3));
	for (i64 i = 0; i < (1 << 3); i++) {
		if (check(i)) {
			i64 q = 1;
			i64 cnt = 0;
			for (i64 j = 0; j <= 2; j++) {
				if ((i >> j) & 1)cnt++;
			}
			q = (q % mod * qpow(k - k / 2, cnt) % mod) % mod;
			q = (q % mod * qpow(k / 2, 3 - cnt) % mod) % mod;
			cur.a[0][i] = q;
		}
	}
	auto ver = [&](i64 x, i64 y) {
		return (x % 4) == (y >> 1);
	};
	Matrix t((1 << 3));
	for (i64 j = 0; j < (1 << 3); j++) {
		if (check(j)) {
			for (i64 k = 0; k < (1 << 3); k++) {
				if (ver(k, j)) {
					t.a[k][j] = 1;
				}
			}
			i64 z = (j & 1) ? k - k / 2 : k / 2;
			for (int i = 0; i < (1 << 3); i++) {
				t.a[i][j] = (t.a[i][j] % mod * z) % mod;
			}
		}
	}
	cur = (cur * quickPower(t, n - 3));
	i64 ans = 0;
	for (i64 i = 0; i < (1 << 3); i++) {
		if (check(i))ans = (ans % mod + cur.a[0][i]) % mod;
	}
	std::cout << ans % mod << "\n";
	return 0;
}