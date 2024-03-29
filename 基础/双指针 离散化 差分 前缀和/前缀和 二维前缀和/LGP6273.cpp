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
constexpr i64 maxn = 5e2 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

int main() {
	i64 n; std::cin >> n;
	string s; std::cin >> s; s = " " + s;

	string tmp = s;

	sort(tmp.begin() + 1, tmp.begin() + 1 + n);

	i64 k = unique(tmp.begin() + 1, tmp.begin() + 1 + n) - tmp.begin() - 1;

	std::vector<i64>z(n + 1);

	for (i64 i = 1; i <= n; i++) {
		z[i] = lower_bound(tmp.begin() + 1, tmp.begin() + 1 + k, s[i]) - tmp.begin();
	}// 离散化

	std::vector pre(n + 1, std::vector<i64>(k + 1, 0));
	for (i64 i = 1; i <= n; i++) {
		pre[i][z[i]]++;
		for (i64 j = 1; j <= k; j++) {
			pre[i][j] += pre[i - 1][j];
		}
	}

	i64 ans = 0;
	std::map<std::vector<i64>, i64>cnt;
	cnt[vector<i64>(k - 1, 0)]++;
	for (i64 i = 1; i <= n; i++) {
		vector<i64>a;
		for (i64 j = 2; j <= k; j++) {
			a.push_back(pre[i][j] - pre[i][j - 1]);
		}
		ans = (ans % mod + cnt[a]) % mod;
		cnt[a]++;
	}
	std::cout << ans << "\n";
	return 0;
}