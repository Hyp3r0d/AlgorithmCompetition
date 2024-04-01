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
constexpr i64 maxn = 4e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

void solve() {
	i64 n, k;
	std::cin >> n >> k;
	std::vector pre(n + 5, std::vector<i64>(k + 5, 0));
	std::vector suf(n + 5, std::vector<i64>(k + 5, 0));
	std::string s; std::cin >> s;
	s = " " + s;
	/*DP 出前缀与后最j 次操作后的 1长度最大值*/
	for (i64 i = 1; i <= n; i++) {
		for (i64 j = 0; j <= k; j++) {
			if (s[i] == '0') {
				if (j > 0) {
					pre[i][j] = std::max(pre[i][j], pre[i - 1][j - 1] + 1);
				} else {
					pre[i][j] = 0;
				}
			} else {
				pre[i][j] = std::max(pre[i][j], pre[i - 1][j] + 1);
			}
		}
	}
	for (i64 i = n; i >= 1; i--) {
		for (i64 j = 0; j <= k; j++) {
			if (s[i] == '0') {
				if (j > 0) {
					suf[i][j] = std::max(suf[i][j], suf[i + 1][j - 1] + 1);
				} else {
					suf[i][j] = 0;
				}
			} else {
				suf[i][j] = std::max(suf[i][j], suf[i + 1][j] + 1);
			}
		}
	}
	for (i64 j = 0; j <= k; j++) {
		i64 mx = 0;
		for (i64 i = 1; i <= n; i++) {
			mx = std::max(mx, pre[i][j]);
			pre[i][j] = std::max(pre[i][j], mx);
		}
	}
	for (i64 j = 0; j <= k; j++) {
		i64 mx = 0;
		for (i64 i = n; i >= 1; i--) {
			mx = std::max(mx, suf[i][j]);
			suf[i][j] = std::max(suf[i][j], mx);
		}
	}
	std::vector<i64>dp(n + 5, -inf);
	for (i64 i = 1; i <= n; i++) {
		i64 cnt = 0;
		dp[0] = std::max(pre[i][k], suf[i][k]);
		for (i64 j = i; j <= n; j++) {
			i64 len = j - i + 1;
			if (s[j] == '1')cnt++;
			if (cnt <= k) {
				dp[len] = std::max(dp[len], pre[i - 1][k - cnt]);
				dp[len] = std::max(dp[len], suf[j + 1][k - cnt]);
			}
		}
	}
	for (i64 i = 1; i <= n; i++) {
		i64 ans = 0;
		for (i64 len = 0; len <= n; len++) {
			if (dp[len] != -1) {
				ans = std::max(ans, i * len + dp[len]);
			}
		}
		std::cout  << ans << " \n"[i == n];
	}
}
int main() {
	i64 T; std::cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}