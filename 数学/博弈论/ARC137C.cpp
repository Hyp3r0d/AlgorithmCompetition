/*300兆字节 1- 2 秒*/

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

void solve() {
	auto ch = [&]() {
		vector<bool>dp((1 << 6) + 5, false);
		for (i64 i = 0; i < (1 << 6); i++) {
			i64 x = -1; bool f = false;
			for (i64 j = 0; j <= 5; j++) {
				if ((i >> j) & 1)x = j;
			}
			for (i64 j = 0; j < x; j++) {
				if (((i >> j) & 1) == 0) {
					dp[i] = dp[i] | (not (dp[i - (1 << x) + (1 << j)])); // 必赢状态需要有后置状态为必输
					if (dp[i])break;
				}
			}
			if (not dp[i]) {
				for (i64 j = 0; j <= 5; j++) {
					if ((i >> j) & 1)std::cout  << " " << j;
				}
				std::cout  << "\n";
;
			}
		}
	};
	//ch();
	i64 n; std::cin >> n;
	vector<i64>A(n + 5, 0);
	for (i64 i = 1; i <= n; i++)std::cin >> A[i];
	if (A[n] - A[n - 1] == 1 and (((n - 2) & 1) ^ (A[n - 1] & 1)) == 0)puts("Bob");
	else puts("Alice");
}
int main() {
	solve();
}