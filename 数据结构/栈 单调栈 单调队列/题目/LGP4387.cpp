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
constexpr i64 mod = 998244353;
constexpr i64 maxn = 2e5 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


i64 q;
void solve() {
	auto check = [&]()->bool {
		i64 n; std::cin >> n;
		std::vector<i64>v(n + 1);
		std::vector<i64>stk; i64 idx = 0;
		for (i64 i = 1; i <= n; i++)std::cin >> v[i];
		for (i64 i = 1; i <= n; i++) {
			i64 cur; std::cin >> cur;
			while (idx + 1 <= n and ((not stk.size()) or stk.back() != cur)) {
				idx++;
				stk.push_back(v[idx]);
			}
			if ((not stk.size()) or stk.back() != cur)return false;
			stk.pop_back();
		}
		if (stk.size())return false;
		return true;
	};
	if (check()) {
		puts("Yes");
	} else puts("No");
}
int main() {
	std::cin >> q;
	while (q--) {
		solve();
	}
}