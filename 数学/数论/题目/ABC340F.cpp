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

constexpr i64 mod = 999911659;
constexpr i64 maxn = 2e5 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


i64 exgcd(i64 a, i64 b, i64 &x, i64 &y) {
	if (b == 0) {
		x = 1, y = 0; return a;
	}
	i64 d = exgcd(b, a % b, x, y);
	i64 tmp = x; x = y;
	y = tmp - a / b * y;
	return d;
}


int main() {
	i64 a, b, x, y; std::cin >> a >> b;
	i64 d = exgcd(abs(a), abs(b), x, y);
	if (2 % d) {
		puts("-1"); return 0;
	}
	i64 t = b / d;
	i64 x0 = x * 2 / d;
	if (a < 0)x0 *= -1;
	i64 y0 = y * 2 / d;
	if (-b < 0)y0 *= -1;
	std::cout << y0 << " " << x0 << "\n";
	return 0;
}