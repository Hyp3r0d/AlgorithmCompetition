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
constexpr i64 maxn = 2e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


class Solution {
public:

	int numsOfGoodMatrix(int n, int m, int x) {
		auto qpow = [&](i64 x, i64 y) {
			i64 ret = 1;
			while (y) {
				if (y & 1)ret = ret * x % mod;
				x = x * x % mod;
				y >>= 1;
			}
			return ret % mod;
		};
		return qpow(2, n + m - 1) % mod * qpow(x / 2, n * m) % mod % mod;
	}
};