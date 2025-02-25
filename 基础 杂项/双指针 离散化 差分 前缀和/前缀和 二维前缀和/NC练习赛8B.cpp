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

constexpr i64 mod = 998244353;
constexpr i64 maxn = 4e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


void solve() {
	i64 n, m; std::cin >> n >> m;
	vector<i64>pre(n + 5, 0);//d1[x] * b[x]的前缀
	vector<i64>p(n + 5, 0);//位置前缀和
	vector<i64>suf(n + 5, 0);//d2[x] * b[x]的后缀
	vector<i64>b(n + 5, 0);//货物数量
	p[1] = 0;
	for (i64 i = 2; i <= n; i++) {
		std::cin >> p[i]; p[i] = (p[i - 1] % mod + p[i]) % mod;
	}
	for (i64 i = 1; i <= n; i++) {
		std::cin >> b[i];
		pre[i] = (p[i] % mod * b[i]) % mod;
		suf[i] = ((p[n] - p[i]) % mod + mod) % mod * b[i] % mod;
	}
	for (i64 i = 1; i <= n; i++) {
		pre[i] = (pre[i] % mod + pre[i - 1]) % mod;
		b[i] = (b[i] % mod + b[i - 1]) % mod;
	}
	for (i64 i = n; i >= 1; i--)suf[i] = (suf[i] % mod + suf[i + 1]) % mod;
	for (i64 i = 1; i <= m; i++) {
		i64 x, l, r;
		std::cin >> x >> l >> r;
		if (x > r) {
			i64 v1 = ((suf[l] - suf[r + 1]) % mod + mod) % mod;
			i64 v2 = (((b[r] - b[l - 1]) % mod + mod) % mod) * ((p[n] - p[x]) % mod + mod) % mod;
			std::cout  << ((v1 - v2) % mod + mod) % mod << "\n";
;
		} else if (x < l) {
			i64 v1 = ((pre[r] - pre[l - 1]) % mod + mod) % mod;
			i64 v2 = ((b[r] - b[l - 1]) % mod + mod) % mod * ((p[x] - p[0]) % mod + mod) % mod;
			std::cout  << ((v1 - v2) % mod + mod) % mod << "\n";
;
		} else {
			i64 v1 = ((pre[r] - pre[x]) % mod + mod) % mod;
			i64 v2 = ((b[r] - b[x]) % mod + mod) % mod * p[x] % mod;
			v1 = ((v1 - v2) % mod + mod) % mod;
			i64 v3 = ((suf[l] - suf[x]) % mod + mod) % mod;
			i64 v4 = ((b[x - 1] - b[l - 1]) % mod + mod % mod) * ((p[n] - p[x]) % mod + mod) % mod;
			v3 = ((v3 - v4) % mod + mod) % mod;
			std::cout  << (v1 % mod + v3) % mod << "\n";
;
		}
	}
}
int main() {
	solve();
}