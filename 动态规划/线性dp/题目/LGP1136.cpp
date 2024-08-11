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

i64 dp[105][105][105][2];
int main() {
    i64 n, k; std::cin >> n >> k;
    string s; std::cin >> s; s = " " + s;
    std::vector<i64>a(n + 1);
    for (i64 i = 1; i <= n; i++) {
        a[i] = (s[i] == 'z');
    }
    for (i64 i = 0; i <= n; i++)for (i64 j = 0; j <= k; j++)for (i64 w = 0; w <= k; w++)for (i64 z = 0; z <= 1; z++)dp[i][j][w][z] = -inf;
    dp[0][0][0][1] = 0;
    for (i64 i = 1; i <= n; i++) {
        for (i64 j = 0; j <= k; j++) {
            for (i64 w = 0; w <= k; w++) {
                // 不改
                dp[i][j][w][a[i]] = std::max(dp[i - 1][j][w][0] + a[i], dp[i - 1][j][w][1]);
                if (a[i]) {// 将 z 改为 j
                    if (w) {
                        dp[i][j][w][0] = std::max(dp[i][j][w - 1][0], dp[i][j][w - 1][1]);
                    }
                } else {
                    if (j >= 1) {
                        // 将 j 改为 z
                        dp[i][j][w][1] = std::max(dp[i][j - 1][w][0] + 1, dp[i][j - 1][w][1]);
                    }
                }
            }
        }
    }

    i64 ans = 0;
    for (i64 q = 0; q <= k; q++) {
        ans = std::max({ans, dp[n][q][q][0], dp[n][q][q][1]});
    }

    std::cout << ans << "\n";
    return 0;
}