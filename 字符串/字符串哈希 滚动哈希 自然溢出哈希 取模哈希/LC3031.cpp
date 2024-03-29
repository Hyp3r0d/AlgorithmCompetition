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
	int minimumTimeToInitialState(string word, int k) {
		int n = word.size(); u64 b = 19997;
		std::vector<u64>z(n + 1); z[0] = 1;
		for (i64 i = 1; i <= n; i++) {
			z[i] = z[i - 1] * b;
		}
		word = " " + word;
		std::vector<u64>hash(n + 1);
		for (i64 i = 1; i <= n; i++) {
			hash[i] = hash[i - 1] * b + word[i];
		}
		auto get = [&](i64 l, i64 r) {
			return hash[r] - hash[l - 1] * z[r - l + 1];
		};
		for (i64 i = k; i < n; i += k) {
			i64 len = n - i;
			if (get(i + 1, i + len) == get(1, 1 + len - 1)) {
				return i / k;
			}
		}
		return (n + k - 1) / k;
	}
};