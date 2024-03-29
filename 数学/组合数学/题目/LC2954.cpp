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
constexpr i64 maxn = 2e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


class Solution {
public:

	i64 ksm(i64 x, i64 y) {
		if (y <= 0) {
			return 1ll;
		}
		i64 ret = 1;
		while (y) {
			if (y & 1) {
				ret = ret * x % mod;
			}
			x = x * x % mod;
			y >>= 1;
		}
		return ret % mod;
	}

	i64 inv(i64 x) {
		return ksm(x, mod - 2) % mod;
	}

	i64 fac[maxn];
	void init() {
		fac[0] = 1;
		for (i64 i = 1; i <= 1e5; i++) {
			fac[i] = fac[i - 1] % mod * i % mod;
		}
	}

	i64 comb(i64 n, i64 m) {

		if (m > n) {
			return 0ll;
		}

		return fac[n] % mod * inv((fac[m] % mod * fac[n - m]) % mod) % mod;

	}

	int numberOfSequence(int n, vector<int>& sick) {
		sick.insert(sick.begin(), -1);
		sick.push_back(n);
		i64 tot = 0;
		init();
		for (i64 i = 1; i < sick.size(); i++) {
			tot += sick[i] - sick[i - 1] - 1;
		}
		i64 ans = 1;
		for (i64 i = 1; i < sick.size(); i++) {
			ans = (ans % mod * comb(tot, sick[i] - sick[i - 1] - 1)) % mod;
			if (i != 1 and i != sick.size() - 1) {
				ans = (ans % mod * ksm(2, sick[i] - sick[i - 1] - 2)) % mod;
			}
			tot -= (sick[i] - sick[i - 1] - 1);
		}
		return ans % mod;
	}
};