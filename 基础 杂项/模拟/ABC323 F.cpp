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


int main() {
	i64 sx, sy, bx, by, gx, gy;
	std::cin >> sx >> sy >> bx >> by >> gx >> gy;
	i64 lag = 0;
	if (sx == bx) {
		if (sy < by and by == gy)lag += 2;
		else if (gy == by and by < sy)lag += 2;
		else if (sy < by and by < gy)lag += 0;
		else if (gy < by and by < sy)lag += 0;
		else {
			if (bx == gx)lag += 4;
			else lag += 2;
		}
	} else if (sy == by) {
		if (sx < bx and bx == gx)lag += 2;
		else if (gx == bx and bx < sx)lag += 2;
		else if (sx < bx and bx < gx)lag += 0;
		else if (gx < bx and bx < sx)lag += 0;
		else {
			if (by == gy)lag += 4;
			else lag += 2;
		}
	} else if (sx != bx and sy != by) {
		if (!((sx < bx && bx < gx) || (gx < bx && bx < sx)) && !((sy < by && by < gy) || (gy < by && by < sy))) {
			lag += 2;
		}
	}
	if (bx == gx || by == gy) {
		lag += 0;
	}
	else if (bx != gx and by != gy) lag += 2;
	i64 d1 = abs(bx - sx) + abs(by - sy), d2 = abs(bx - gx) + abs(by - gy);

	cout << d1 + d2 + lag - 1 << "\n";
}