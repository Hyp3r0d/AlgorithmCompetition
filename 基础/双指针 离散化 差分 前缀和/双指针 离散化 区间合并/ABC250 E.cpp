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
	i64 n; std::cin >> n;
	std::vector<i64>a(n + 1), b(n + 1);
	for (i64 i = 1; i <= n; i++) {
		std::cin >> a[i];
	}
	for (i64 i = 1; i <= n; i++) {
		std::cin >> b[i];
	}
	std::set<i64>A, B;
	std::unordered_map<i64, i64>AA, BB;
	i64 q; std::cin >> q;
	std::vector<std::vector<pair<i64, i64>>>z(n + 1);
	for (i64 i = 1; i <= q; i++) {
		i64 x, y; std::cin >> x >> y;
		z[x].push_back({y, i});
	}
	i64 p = 0;
	auto del = [&](i64 x) {
		BB[x]--; if (BB[x] == 0)B.erase(x);
	};
	std::vector<i64>ans(q + 1);
	for (i64 i = 1; i <= n; i++) {
		A.insert(a[i]); AA[a[i]]++;
		std::sort(z[i].begin(), z[i].end(), [&](auto x, auto y)->bool{
			return x.first < y.first;
		});
		for (auto [v, idx] : z[i]) {
			if (p < v) {
				while (p < v) {
					p++; B.insert(b[p]);
					BB[b[p]]++;

				}
			} else if (p > v) {
				while (p > v) {
					del(b[p]);
					p--;
				}
			}
			if (A == B)ans[idx] = true;
		}
	}
	for (i64 i = 1; i <= q; i++) {
		puts(ans[i] ? "Yes" : "No");
	}
	return 0;
}