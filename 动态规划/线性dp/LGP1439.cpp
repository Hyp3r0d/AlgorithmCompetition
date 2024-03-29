/*A Star搜索*/
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

constexpr i64 mod = 1e9 + 7;
constexpr i64 maxn = 2e7 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


i64 w[maxn], len = 0;
int main() {
	i64 n; std::cin >> n;
	std::unordered_map<i64, i64>s;
	std::vector<i64>x(n + 1), y(n + 1); std::unordered_map<i64, i64>z;
	for (i64 i = 1; i <= n; i++) {
		std::cin >> x[i]; z[x[i]] = i;
	}
	for (i64 i = 1; i <= n; i++) {
		std::cin >> y[i];
	}
	for (i64 i = 1; i <= n; i++) {
		if (z[y[i]] > w[len])w[++len] = z[y[i]];
		else {
			i64 l = 0, r = len; i64 ans = 0;
			while (l < r) {
				i64 mid = (l + r) >> 1;
				if (w[mid] >= z[y[i]])r = mid;
				else l = mid + 1;
			}
			w[r] = z[y[i]];
		}
	}
	std::cout  << len << "\n";;
	return 0;
}
