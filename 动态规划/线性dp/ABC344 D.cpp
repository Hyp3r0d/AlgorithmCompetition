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
	string t; std::cin >> t;
	i64 sz = t.size();
	vector<i64>dp(sz + 1, inf);
	dp[0] = 0;
	t = " " + t;
	i64 n; std::cin >> n;
	vector<vector<string>>z(n);
	for (i64 i = 0; i < n; i++) {
		i64 v; std::cin >> v;
		while (v--) {
			string cur; std::cin >> cur;
			z[i].push_back(cur);
		}
	}
	//std::cout << t.substr(1, 3) << "\n";
	for (i64 j = 0; j < n; j++) {
		for (i64 i = 1; i <= sz; i++) {

			for (auto g : z[j]) {
				if (i >= g.size()) {
					if (t.substr(i - g.size() + 1, g.size()) == g) {
						dp[i] = std::min(dp[i], dp[i - g.size()] + 1);
					}
				}
			}
		}
	}
	std::cout << (dp[sz] == inf ? -1 : dp[sz]);
}