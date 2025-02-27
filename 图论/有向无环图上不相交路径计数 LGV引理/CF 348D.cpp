/*LGV定理,矩阵计数路径数*/
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
constexpr i64 maxn = 3e3 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

i64 dp[maxn][maxn], n, m;

/*记忆化搜索写法*/
int main() {
    std::cin >> n >> m;
    std::vector<string>G(n + 1);
    for (i64 i = 1; i <= n; i++) {
        std::cin >> G[i]; G[i] = " " + G[i];
    }
    auto f = [&] (i64 sx, i64 sy, i64 tx, i64 ty)->i64 {
        memset(dp, -1, sizeof(dp));
        dp[sx][sy] = (G[sx][sy] == '.');
        function<i64(i64, i64)> dfs = [&](i64 x, i64 y) {
            if (!(x >= sx and x <= tx and y >= sy and y <= ty)) {
                return dp[x][y] = 0;
            }
            if (dp[x][y] != -1) {
                return dp[x][y];
            }
            if (G[x][y] == '#') return dp[x][y] = 0;
            dp[x][y] = 0;
            dp[x][y] = (dfs(x - 1, y) + dp[x][y]) % mod;
            dp[x][y] = (dp[x][y] + dfs(x, y - 1)) % mod;
            return dp[x][y];
        };
        dfs(tx, ty);
        return dp[tx][ty];
    };
    /*LGV引理的应用*/
    i64 f11 = f(1, 2, n - 1, m) % mod;
    i64 f12 = f(1, 2, n, m - 1) % mod;
    i64 f21 = f(2, 1, n - 1, m) % mod;
    i64 f22 = f(2, 1, n, m - 1) % mod;
    std::cout  << (((f11 * f22) % mod - (f12 * f21) % mod + mod) % mod) << "\n";
    ;
    return 0;
}




/*递推写法*/
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
constexpr i64 maxn = 3e3 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

i64 dp[maxn][maxn], n, m;

/*记忆化搜索写法*/
int main() {
    std::cin >> n >> m;
    std::vector<string>G(n + 1);
    for (i64 i = 1; i <= n; i++) {
        std::cin >> G[i]; G[i] = " " + G[i];
    }
    auto f = [&] (i64 sx, i64 sy, i64 tx, i64 ty)->i64 {
        memset(dp, 0, sizeof(dp));
        dp[sx][sy] = (G[sx][sy] == '.');
        for (int i = 1; i <= tx; i++) {
            for (int j = 1; j <= ty; j++) {
                if (G[i][j] == '#')continue;
                dp[i][j] = (dp[i][j] % mod + dp[i - 1][j]) % mod;
                dp[i][j] = (dp[i][j] % mod + dp[i][j - 1]) % mod;
            }
        }
        return dp[tx][ty];
    };
    /*LGV引理的应用*/
    i64 f11 = f(1, 2, n - 1, m) % mod;
    i64 f12 = f(1, 2, n, m - 1) % mod;
    i64 f21 = f(2, 1, n - 1, m) % mod;
    i64 f22 = f(2, 1, n, m - 1) % mod;
    std::cout  << (((f11 * f22) % mod - (f12 * f21) % mod + mod) % mod) << "\n";
    ;
    return 0;
}