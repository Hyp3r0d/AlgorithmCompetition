/*tarjan 缩点模板*/

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
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f3f;


int main() {
	i64 n, m; std::cin >> n >> m;
	std::vector<i64>d(n + 5), z(n + 5);
	std::vector<i64>b(m + 1);
	for (i64 i = 1; i <= m; i++) {
		std::cin >> b[i];
	}
	i64 tot = 0;
	for (i64 i = 1; i <= m - 1; i++) {
		i64 u = b[i], v = b[i + 1];
		if (u > v)swap(u, v);
		if (v - u <= u - v + n) {
			d[u]++; d[v]--;
			tot += (v - u);
			z[u] += (v - u); z[v] -= (v - u);
		} else {
			tot += (u - v + n);
			d[v]++; d[n + 1]--;
			d[1]++; d[u]--;
			z[v] += (u - v + n); z[n + 1] -= (u - v + n);
			z[1] += (u - v + n); z[u] -= (u - v + n);
		}
	}
	for (i64 i = 1; i <= n; i++) {
		z[i] += z[i - 1]; d[i] += d[i - 1];
	}
	i64 ans = tot;
	for (i64 i = 1; i <= n; i++) {
		i64 t1 = z[i], t2 = d[i];
		i64 z = tot; z += t2 * n; z -= t1;
		ans = std::min(ans, z);
	}
	std::cout << ans << "\n";
	return 0;
}