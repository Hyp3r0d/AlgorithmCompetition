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




i64 nxt[maxn][30];

int main() {
	i64 n, k, m;
	std::cin >> n >> k >> m;
	std::vector<i64>a(n + 1);
	for (i64 i = 1; i <= n; i++) {
		std::cin >> a[i];
	}
	nxt[1][0] = k + 1;
	i64 hed = 1, tal = k + 1;
	for (i64 i = 2; i <= n; i++) {
		while (tal + 1 <= n and a[i] - a[hed] > a[tal + 1] - a[i]) {
			hed++, tal++;
		}
		if (a[i] - a[hed] >= a[tal] - a[i])nxt[i][0] = hed;
		else nxt[i][0] = tal;
	}
	for (i64 j = 1; j <= 20; j++) {
		for (i64 i = 1; i <= n; i++) {
			nxt[i][j] = nxt[nxt[i][j - 1]][j - 1];
		}
	}
	/*倍增*/
	/*向右跳 m 下*/
	for (i64 i = 1; i <= n; i++) {
		i64 cur = i;
		for (i64 j = 0; j <= 20; j++) {
			if ((m >> j) & 1) {
				cur = nxt[cur][j];
			}
		}
		std::cout << cur << " \n"[i == n];
	}

}
