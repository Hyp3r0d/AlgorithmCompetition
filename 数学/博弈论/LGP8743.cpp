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
constexpr i64 maxn = 4e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

int main() {
	i64 T; std::cin >> T;
	while (T--) {
		i64 n; std::cin >> n;
		std::vector<i64>x(n + 5);
		i64 sum = 0;
		vector<i64>cnt(25);
		for (i64 i = 1; i <= n; i++) {
			std::cin >> x[i]; sum ^= x[i];
			for (i64 j = 25; j >= 0; j--) {
				cnt[j] += ((x[i] >> j) & 1);
			}
		}
		if (not sum) {
			puts("0"); continue;
		}
		for (i64 i = 25; i >= 0; i--) {
			if (cnt[i] % 2 == 0)continue;
			else if (cnt[i] == 1) {
				puts("1");
			} else if ((n - cnt[i]) & 1) {
				puts("-1");
			} else {
				puts("1");
			}
			break;
		}
	}
	return 0;
}