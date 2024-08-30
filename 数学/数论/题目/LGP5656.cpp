
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

i64 exgcd(i64 a, i64 b, i64 &x, i64 &y) {
	if (b == 0) {
		x = 1; y = 0; return a;
	}
	i64 d = exgcd(b, a % b, x, y);
	i64 tmp = x; x = y;
	y = tmp - a / b * y;
	return d;
}

void solve() {
	i64 a, b, c; std::cin >> a >> b >> c;
	i64 x = 0, y = 0;
	i64 d = exgcd(a, b, x, y);
	if (c % d) {
		puts("-1"); return;
	}
	i64 x2, y2;
	exgcd(b, a, y2, x2);
	i64 xmin = (x * (c / d) % (b / d) + (b / d)) % (b / d);
	i64 ymin = (y2 * (c / d) % (a / d) + (a / d)) % (a / d);
	if (xmin <= 0)xmin += (b / d);
	if (ymin <= 0)ymin += (a / d);
	if (xmin * a >= c) {
		std::cout << xmin << " " << ymin << "\n";
	} else {
		i64 p = (((c - xmin * a))) / ((b / d));
		if (c - xmin * a - p * (b / d) <= 0)p--;
		
		std::cout << p + 1 << " ";
		std::cout << xmin << " " << ymin << " ";
		std::cout << (c - ymin * b) / a << " " <<  (c - xmin * a) / b << "\n";
	}
}

int main() {
	i64 t; std::cin >> t;
	while (t--)solve();
}