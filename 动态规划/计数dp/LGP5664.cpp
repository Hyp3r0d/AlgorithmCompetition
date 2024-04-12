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
constexpr i64 maxn = 4e3 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

struct Comb {
public:
	i64 mo; //模数
	std::vector<i64>fac;
	std::vector<i64>invfac;
	std::vector<i64>inv; i64 len; // 维护范围
	Comb() {}

	Comb(i64 mo, i64 len = 1e6): mo(mo), len(len) {
		init();
	}
	void init() {
		fac.assign(len + 5, 0);
		invfac.assign(len + 5, 0);
		inv.assign(len + 5, 0);
		fac[0] = fac[1] = 1;
		inv[1] = 1;
		invfac[0] = invfac[1] = 1;
		for (i64 i = 2; i <= len; i++) {
			fac[i] = fac[i - 1] % mo * i % mo;
			inv[i] = (mo - mo / i) % mo * inv[mo % i] % mo;
			invfac[i] = (invfac[i - 1] % mo * inv[i]) % mo;
		}
	}
	i64 comb(i64 n, i64 m) {
		if (m < 0 || m > n) {
			return 0ll;
		}
		return fac[n] % mo * invfac[n - m] % mo * invfac[m] % mo;
	}
	/*小质数求组合数*/
	i64 lucas(i64 n, i64 m) {
		if (m == 0) {
			return 1ll;
		}
		return (comb(n % mo, m % mo) * lucas(n / mo, m / mo)) % mo;
	}
};


int main() {
	i64 n, m; std::cin >> n >> m;
	std::vector a(n + 1, std::vector<i64>(m + 1, 0));
	std::vector<i64>sum(n + 1);
	for (i64 i = 1; i <= n; i++) {
		for (i64 j = 1; j <= m; j++) {
			std::cin >> a[i][j];
			sum[i] = (sum[i] % mod + a[i][j]) % mod;
		}
	}
	i64 tot = 0;
	//Comb c(998244353, 4005);
	for (i64 cur = 1; cur <= m; cur++) {
		// n  + 1 为偏移量,
		std::vector dp(n + 1, std::vector<i64>(2 * n + 3, 0));
		i64 p = n + 1;
		dp[0][p] = 1;
		// 前 0 行  i 比 j 多 0 个种数为1
		for (i64 i = 1; i <= n; i++) {
			for (i64 j = -i; j <= i; j++) {//枚举差值
				dp[i][j + p] = (dp[i][j + p] % mod + dp[i - 1][j + p - 1] % mod * a[i][cur] % mod) % mod; // 选该列
				dp[i][j + p] = (dp[i][j + p] % mod + dp[i - 1][j + p + 1] % mod * ((sum[i] - a[i][cur]) % mod + mod) % mod) % mod;
				// 选其他的列
				dp[i][j + p] = (dp[i - 1][j + p] % mod + dp[i][j + p]) % mod;
				//这一行不搭配列
			}
		}

		for (i64 i = p + 1; i <= p + n; i++) {
			tot = (tot % mod + dp[n][i]) % mod;
		}
	}
	i64 ans = 1;
	for (i64 i = 1; i <= n; i++) {
		i64 x = 1;
		for (i64 j = 1; j <= m; j++) {
			x += a[i][j]; x %= mod;
		}
		ans = (ans % mod * x) % mod;
	}
	ans = ((ans - 1) % mod + mod) % mod;
	std::cout  << ((ans - tot) % mod + mod) % mod;
}