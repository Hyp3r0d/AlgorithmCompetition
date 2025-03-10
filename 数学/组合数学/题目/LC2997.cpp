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
const i64 mod = 1e9 + 7;
const i64 maxn = 1e6 + 5;
const i64 inf = 0x3f3f3f3f3f3f3f3f;
class Solution {
public:
    int stringCount(int n) {
        auto qpow = [&](i64 x, i64 y) -> i64{
            i64 ret = 1;
            while (y) {
                if (y & 1)ret = ret * x % mod;
                x = x * x % mod;
                y >>= 1;
            }
            return ret % mod;
        };
        i64 ans = 0;
        ans = (ans % mod + 3 * qpow(25, n) % mod + n % mod * qpow(25, n - 1) % mod) % mod;
        ans = (ans % mod - 3 * qpow(24, n) % mod - 2 * n % mod * qpow(24, n - 1) % mod + mod) % mod;
        ans = (ans % mod + qpow(23, n) % mod + n % mod * qpow(23, n - 1) % mod) % mod;
        return ((qpow(26, n) % mod - ans) % mod + mod) % mod;
    }
};