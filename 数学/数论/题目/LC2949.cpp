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

constexpr i64 mod = 999911659;
constexpr i64 maxn = 2e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

class Solution {
public:
	long long beautifulSubstrings(string s, int k) {
		int n = s.size();
		s = " " + s;
		std::vector<i64>v;
		for (i64 i = 1; i <= n; i++) {
			if ((i * i) % (4 * k) == 0) {
				v.push_back(i);
			}
		}
		i64 ans = 0; std::unordered_map<i64, i64>f[2];
		i64 x = 0;// 元 - 辅
		f[0][0] = 0;
		auto check = [&](char z) {
			return z == 'a' or z == 'e' or z == 'i' or z == 'o' or z == 'u';
		};
		for (i64 i = 1; i <= n; i++) {
			if (check(s[i]))x++;
			else {
				x--;
			}
			for (auto len : v) {
				if (len > i)break;
				i64 res = i - len;
				if ((res & 1) == (i & 1) && f[i & 1][res] == x) {
					ans++;
				}
			}
			f[i & 1][i] = x;
		}
		return ans;
	}
};