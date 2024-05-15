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
    i64 n; std::cin >> n; i64 tot = 0;
    pair<i64, i64>k[50];
    for (i64 i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            i64 c = 0;
            while (n % i == 0)n /= i, c++;
            k[++tot] = {c, i};
        }
    }
    if (n >= 2) {
        k[++tot] = {1, n};
    }
    vector<i64>pre(tot + 5, 0);
    i64 p = 1;
    std::sort(k + 1, k + 1 + tot, [&](pair<i64, i64>a, pair<i64, i64>b)->bool{
        return a.first < b.first;
    });
    for (i64 i = tot; i >= 1; i--) {
        p *= k[i].second;
        pre[i] = p;
    }
    i64 ans = 0;
    for (i64 i = 1; i <= tot; i++) {
        ans += (k[i].first - k[i - 1].first) * pre[i];
    }
    std::cout  << ans << "\n";
;
}
int main() {
    i64 T; std::cin >> T;
    while (T--)solve();
}