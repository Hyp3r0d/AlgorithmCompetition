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

constexpr i64 mod = 999911659;
constexpr i64 maxn = 2e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


i64 q[maxn], hed = 1, tal = 0;
int main() {
	i64 n, m; std::cin >> n >> m;
	std::vector<i64>z(n + 1, 0);
	for (i64 i = 1; i <= n; i++) {
		std::cin >> z[i];
	}
	q[++tal] = 0;
	for (i64 i = 1; i <= n; i++) {
		z[i] += z[i - 1];
	}
	i64 ans = -inf;
	for (i64 i = 1; i <= n; i++) {
		while (hed <= tal and z[q[tal]] > z[i])tal--;
		q[++tal] = i;
		while (hed <= tal and q[tal] - q[hed] > m)hed++;
		ans = std::max(ans, z[q[tal]] - z[q[hed]]);
	}
	std::cout << ans << "\n";
}
