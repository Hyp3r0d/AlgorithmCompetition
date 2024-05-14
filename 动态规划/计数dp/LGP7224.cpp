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
constexpr i64 maxn = 1e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;



i64 fac[maxn];
i64 qpow(i64 x, i64 y) {
    i64 ret = 1;
    while (y) {
        if (y & 1)ret = ret % mod * x % mod;
        x = x * x % mod;
        y >>= 1;

    }
    return ret % mod;
}

i64 inv(i64 x) {
    return qpow(x, mod - 2) % mod;
}


i64 comb(i64 n, i64 m) {
    if (m > n)return 0ll;
    return fac[n] % mod * inv(fac[n - m] % mod * fac[m] % mod) % mod;
}

i64 cnt[maxn];

i64 dp[maxn]; i64 a[maxn];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nui64ptr); cout.tie(nui64ptr);
    fac[0] = 1;
    for (i64 i = 1; i <= 1e6; i++) {
        fac[i] = (fac[i - 1] % mod * i) % mod;
    }
    i64 n, m; std::cin >> n >> m;
    for (i64 i = 1; i <= n; i++) {
        std::cin >> a[i]; cnt[a[i]]++;
    }
    dp[1] = 1;
    /*多重背包一维优化*/
    for (i64 i = 2; i <= 1e6; i++) {
        if (not cnt[i])continue;
        for (i64 j = (m / i) * i; j >= i; j -= i) {
            for (i64 k = 1, s = i; k <= cnt[i] and j % s == 0; k++, s *= i) {
                dp[j] = (dp[j] % mod + dp[j / s] % mod * comb(cnt[i], k) % mod) % mod;
            }
        }
    }
    i64 ans = qpow(2, n) % mod;
    for (i64 i = 1; i <= m; i++) {
        ans = (((ans - dp[i] % mod * qpow(2, cnt[1])) % mod) + mod) % mod;
    }
    std::cout << ans % mod << "\n";
    return 0;
}