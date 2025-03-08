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


int main() {
    i64 n, s; std::cin >> n >> s;
    std::vector<i64>a(n + 1);
    for (i64 i = 1; i <= n; i++)std::cin >> a[i];
    i64 ans = 0;
    for (i64 i = 1; i <= n; i++) {
        std::vector<i64>dp(s + 1);
        dp[0] = 1;
        /*空间一维01背包*/
        for (i64 j = i; j <= n; j++) {
            for (i64 k = s; k >= a[j]; k--) {
                dp[k] = (dp[k] % mod + dp[k - a[j]]) % mod;
            }
            ans = (ans % mod + dp[s]) % mod;
        }
    }
    std::cout << ans << "\n";
    return 0;
}




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


int main() {
    i64 n, s; std::cin >> n >> s;
    std::vector<i64>a(n + 1);
    for (i64 i = 1; i <= n; i++)std::cin >> a[i];
    i64 ans = 0;
    for (i64 i = 1; i <= n; i++) {
        std::vector dp(n - i + 2, std::vector(s + 1, 0));
        dp[0][0] = 1;
        /*空间二维01背包*/
        for (i64 j = i; j <= n; j++) {
            i64 cur = j - i + 1;
            for (i64 k = 0; k <= s; k++) {

                dp[cur][k] = (dp[cur][k] % mod + dp[cur - 1][k]) % mod;
                if (k >= a[j]) {
                    dp[cur][k] = (dp[cur][k] % mod + dp[cur - 1][k - a[j]]) % mod;
                }
            }
            ans = (ans % mod + dp[cur][s]) % mod;
        }
    }
    std::cout << ans << "\n";
    return 0;
}




/*正解*/
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

i64 dp[3005][3005];
void solve() {
    i64 n, s; std::cin >> n >> s;
    vector<i64>A(n + 5, 0);
    for (i64 i = 1; i <= n; i++)std::cin >> A[i];
    i64 ans = 0;
    for (i64 i = 0; i <= n; i++)dp[i][0] = i + 1;
    for (i64 i = 1; i <= n; i++) {
        for (i64 j = 1; j <= s; j++) {
            dp[i][j] = (dp[i][j] % mod + dp[i - 1][j]) % mod;
            if (j >= A[i]) {
                dp[i][j] = (dp[i][j] % mod + dp[i - 1][j - A[i]]) % mod;
            }
        }
        //所有以i结尾的区间的方案数
        ans = (ans % mod + dp[i][s]) % mod;
    }
    std::cout  << ans << "\n";;
}
int main() {
    solve();
}
