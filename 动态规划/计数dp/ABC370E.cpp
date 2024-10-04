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
const i64 mod = 998244353;
const i64 maxn = 2e5 + 5;
const i64 inf = 0x3f3f3f3f3f3f3f3f;


int main() {
	i64 n, k; std::cin >> n >> k;
	std::vector<i64>a(n + 1);
	for (i64 i = 1; i <= n; i++)std::cin >> a[i];
	std::vector<i64>dp(n + 1); dp[0] = 1;
	i64 sum = 1; std::unordered_map<i64, i64>w;
	w[0] = 1;
	for (i64 i = 1; i <= n; i++)a[i] += a[i - 1];
	for (i64 i = 1; i <= n; i++) {
		i64 pad = ((sum - w[a[i] - k]) % mod + mod) % mod;
		dp[i] = (dp[i] % mod + pad) % mod;
		w[a[i]] += dp[i]; sum = (sum % mod + dp[i]) % mod;
		w[a[i]] %= mod;
	}
	std::cout << dp[n] << "\n";
	return 0;
}