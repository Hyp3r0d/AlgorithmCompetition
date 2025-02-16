/*使用具体数学中关于约瑟夫环的迭代式*/

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
	auto J = [&](i64 n, i64 q) ->i64{
		i64 N = n * q;
		while (N > n) {
			N = (N - n - 1) / (q - 1) + N - n;
		}
		return N;
	};
	i64 n, q; while (std::cin >> n >> q) {
		std::cout << J(n, q) << "\n";
	}
	return 0;
}