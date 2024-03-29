/*与概率递推不同,本题应当先算出各种情况的种数量,结合古典概型进行运算*/
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

i64 dp[5005][5005][2];

void solve() {
	i64 n, d; std::cin >> n >> d;
	std::vector<i64>A(n + 1), p(n + 1);
	p[0] = 1;
	for (i64 i = 1; i <= n; i++) {
		p[i] = p[i - 1] % mod * i % mod;
	}
	for (i64 i = 1; i <= n; i++)std::cin >> A[i];
	auto inv = [&](i64 x) {
		i64 ret = 1, b = mod - 2;
		while (b) {
			if (b & 1) {
				ret = ret * x % mod;
			}
			x = x * x % mod;
			b >>= 1;
		}
		return ret;
	};
	std::sort(A.begin() + 1, A.begin() + 1 + n);
	auto C = [&](i64 n, i64 m) {
		return p[n] % mod * inv(p[n - m] % mod) % mod * inv(p[m] % mod) % mod % mod;
	};

	dp[0][0][0] = 1;
	//dp[1][1][1] = dp[1][0][0] = 1;
	for (i64 i = 1; i <= n; i++) {
		for (i64 j = 0; j <= i; j++) {
			dp[i][j][0] = (dp[i][j][0] % mod + dp[i - 1][j][0]) % mod;
			dp[i][j][0] = (dp[i][j][0] % mod + dp[i - 1][j][1]) % mod;
			if (j and A[i] - d > A[i - 1])
				dp[i][j][1] = (dp[i][j][1] % mod + dp[i - 1][j - 1][0]) % mod;
			if (j)
				dp[i][j][1] = (dp[i][j][1] % mod + dp[i - 1][j - 1][1]) % mod;
		}
	}
	for (i64 i = 1; i <= n; i++) {
		std::cout  << (dp[n][i][1] % mod + dp[n][i][0]) % mod*inv(C(n, i)) % mod << "\n";;
	}
}
int main() {
	solve();
}