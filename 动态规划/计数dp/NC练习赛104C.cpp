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
const i64 mod = 1e9 + 7;
const i64 maxn = 1e6 + 5;
const i64 inf = 0x3f3f3f3f3f3f3f3f;



int main() {
	string s; std::cin >> s; i64 n = s.size();
	s = " " + s;

	std::vector dp(10, std::vector<i64>(10, 0));
	dp[0][0] = 1;

	for (i64 i = 1; i <= n; i++) {
		std::vector ndp(10, std::vector<i64>(10, 0));
		for (i64 j = 0; j <= 7; j++) {
			for (i64 k = 0; k <= 9; k++) {
				ndp[j][k] = (ndp[j][k] % mod + dp[j][k]) % mod;
			}
		}

		i64 cur = s[i] - '0';
		for (i64 j = 1; j <= 7; j++) {
			if (j == 1) {
				for (i64 s = 0; s <= 9; s++) {
					ndp[j][cur] = (ndp[j][cur] % mod + dp[j - 1][s]) % mod;
				}
			} else if (j == 2 or j == 4) {
				for (i64 s = 0; s < cur; s++) {
					ndp[j][cur] = (ndp[j][cur] % mod + dp[j - 1][s]) % mod;
				}
			} else {
				for (i64 s = cur + 1; s <= 9; s++) {
					ndp[j][cur] = (ndp[j][cur] % mod + dp[j - 1][s]) % mod;
				}
			}
		}
		dp = ndp;
	}

	i64 ans = 0;
	for (i64 s = 0; s <= 9; s++) {
		ans = (ans % mod + dp[7][s]) % mod;
	}
	std::cout << ans;
}