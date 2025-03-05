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
constexpr i64 maxn = 2e5 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;



i64 fac[20005];
void init() {
	fac[0] = 1;
	for (i64 i = 1; i <= 2e4; i++)fac[i] = fac[i - 1] % mod * i % mod;
}
i64 ksm(i64 x, i64 y) {
	i64 ret = 1;
	while (y) {
		if (y & 1)ret = ret % mod * x % mod;
		x = (x % mod) * (x % mod) % mod;
		y >>= 1;
	}
	return ret % mod;
}
i64 inv(i64 x) {
	return ksm(x, mod - 2) % mod;
}
i64 comb(i64 n, i64 m) {
	return fac[n] % mod * inv(fac[m] % mod * fac[n - m]) % mod;
}
class Solution {
public:
	int idealArrays(int n, int maxValue) {
		init();
		vector<vector<i64>>p(maxValue + 1);
		for (i64 i = 2; i <= maxValue; i++) {
			i64 x = i;
			for (i64 j = 2; j <= sqrt(x); j++) {
				if (x % j == 0) {
					i64 cnt = 0; while (x % j == 0)x /= j, cnt++;
					p[i].push_back(cnt);
				}
			}
			if (x > 1)p[i].push_back(1);
		}
		i64 ans = 0;
		for (i64 i = 1; i <= maxValue; i++) {
			i64 w = 1;
			for (auto j : p[i])w = (w % mod * comb(n + j - 1, j)) % mod;
			ans = (ans % mod + w) % mod;
		}
		return ans % mod;
	}
};








/*预处理做法*/
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
constexpr i64 mod = 1e9 + 7;
constexpr i64 maxn = 3e4 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

class Solution {
public:
    i64 fac[maxn]; i64 invfac[maxn];
    i64 inv[maxn];
    std::vector<pair<i64, i64>>g[maxn];
    int idealArrays(int n, int maxValue) {
        fac[0] = fac[1] = 1;
        inv[1] = 1; invfac[0] = invfac[1] = 1;
        for (i64 i = 2; i <= maxValue + n + 5; i++) {
            fac[i] = fac[i - 1] % mod * i % mod;
            inv[i] = inv[mod % i] % mod * (mod - mod / i) % mod;
            invfac[i] = invfac[i - 1] % mod * inv[i] % mod;
        }
        auto comb = [&](i64 n, i64 m) {
            if (n < m)return 0ll;
            return fac[n] % mod * invfac[n - m] % mod * invfac[m] % mod;
        };
        for (i64 i = 2; i <= maxValue; i++) {
            i64 x = i;
            for (i64 j = 2; j <= sqrt(x); j++) {
                if (x % j == 0) {
                    i64 cnt = 0;
                    while (x % j == 0) {
                        x /= j; cnt++;
                    }
                    g[i].push_back({cnt, j});
                }
            }
            if (x > 1)g[i].push_back({1, x});
        }
        i64 ans = 0;
        for (i64 i = 1; i <= maxValue; i++) {
            i64 w = 1;
            for (auto [x, y] : g[i]) {
                w = w % mod * comb(x + n - 1, n - 1) % mod;
            }
            ans = (ans % mod + w) % mod;
        }
        return ans % mod;
    }
};