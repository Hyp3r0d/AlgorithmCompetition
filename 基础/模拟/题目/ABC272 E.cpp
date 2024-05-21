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

int main() {
	int n, m; std::cin >> n >> m;
	std::vector<int>a(n + 1);
	std::vector<set<i64>>st(m + 2);
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
		i64 l = a[i] >= 0 ? 1ll : (-x + i - 1) / i;
		i64 r = min(m + 1, (n - x + i - 1) / i);
		for (i64 j = l; j <= r; j++) {
			st[j].insert(j * i + x);
		}
	}
	for (i64 i = 1; i <= m; i++) {
		for (i64 j = 0; j <= n; j++) {
			if (!st[i].count(j)) {
				std::cout << j << "\n";
				break;
			}
		}
	}
}