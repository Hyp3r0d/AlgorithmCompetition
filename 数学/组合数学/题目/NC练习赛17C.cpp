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
constexpr i64 maxn = 2e3 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


i64 fac[maxn], inv[maxn], up[maxn], a[maxn];

i64 n, k;

i64 qpow(i64 x, i64 y) {
    i64 ret = 1;
    while (y) {
        if (y & 1)ret = ret % mod * x % mod;
        x = x % mod * x % mod;
        y >>= 1;
    }
    return ret % mod;
}

void pre() {
    fac[0] = 1;
    for (i64 i = 1; i <= n; i++) {
        fac[i] = fac[i - 1] % mod * i % mod;
    }
    inv[n] = qpow(fac[n], mod - 2) % mod;
    for (i64 i = n - 1; i >= 0; i--) {
        inv[i] = inv[i + 1] % mod * (i + 1) % mod;
    }
    up[0] = 1;
    for (i64 i = 1; i <= n; i++)up[i] = up[i - 1] % mod * (k - 1 + i) % mod;
}

int main() {
    std::cin >> n >> k;
    pre();
    for (i64 i = 1; i <= n; i++)std::cin >> a[i];

    if (not k) {
        for (i64 i = 1; i <= n; i++) {
            std::cout << a[i] << " \n"[i == n];
        }
    } else {
        std::cout << a[1] % mod << " ";
        for (i64 i = 2; i <= n; i++) {
            i64 sum = 0;
            for (i64 j = i - 1, l = 1; j >= 0; j--, l++) {
                sum += up[j] % mod * inv[j] % mod * a[l] % mod;
                sum %= mod;
            }
            std::cout << sum << " \n"[i == n];
        }
    }
    return 0;
}