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

constexpr i64 mod = 1e9 + 7;
constexpr i64 maxn = 2e3 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


int main() {
	i64 n; std::cin >> n;
	vector<string>s(n + 1);
	for (i64 i = 1; i <= n; i++) {
		std::cin >> s[i];
	}
	std::vector<i64>fa(n + 1), sz(n + 5, 1);
	std::iota(fa.begin() + 1, fa.begin() + 1 + n, 1);

	sort(s.begin() + 1, s.begin() + 1 + n, [&](string x, string y)->bool{
		return x.size() < y.size();
	});
	auto find = [&](i64 x) {
		while (x != fa[x])x = fa[x] = fa[fa[x]];
		return x;
	};
	auto merge = [&](i64 x, i64 y) {
		x = find(x), y = find(y);
		if (x == y)return false;
		fa[x] = y; sz[y] += sz[x];
		return true;
	};
	for (i64 i = 1; i <= n; i++) {
		for (i64 j = i - 1; j >= 1; j--) {
			if (s[i].substr(0, s[j].size()) == s[j]) {
				merge(j, i); break;
			}
		}
	}
	std::set<i64>st;
	for (i64 i = 1; i <= n; i++) {
		st.insert(find(i));
	}

	i64 t = st.size(); std::vector<i64>w(t + 1); i64 cur = 0;
	for (auto c : st) {
		w[++cur] = c;
	}
	vector dp(t + 1, std::vector<i64>(t + 1, 0));
	dp[0][0] = 1; i64 ans = 0;
	for (i64 i = 1; i <= t; i++) {
		for (i64 j = 0; j <= i; j++) {
			dp[i][j] += dp[i - 1][j];
			if (j >= 1) {
				dp[i][j] += dp[i - 1][j - 1] * sz[w[i]];
			}
			if (i == t)ans += dp[i][j];
		}
	}
	std::cout << ans << "\n";
	return 0;
}