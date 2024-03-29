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
constexpr i64 maxn = 5e2 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


i64 rk[maxn][maxn];

int main() {
	i64 n; std::cin >> n;
	std::vector z(n + 1, std::vector<i64>(n + 1, 0));
	for (i64 i = 1; i <= n; i++) {
		for (i64 j = 1; j <= n; j++) {
			std::cin >> z[i][j];
			rk[i][z[i][j]] = j;
		}
	}
	std::vector q(n + 1, std::vector<bool>(n + 1, false));
	for (i64 i = 1; i <= n; i++) {
		q[i][i] = true;
		std::function<void(i64)>dfs = [&](i64 u) {
			for (i64 j = 1; j <= n; j++) {
				if (not q[i][j] and rk[j][u] <= rk[j][j]) {
					q[i][j] = true;
					dfs(j);
				}
			}
		};
		dfs(i);
		i64 ans = n + 1;
		for (i64 j = 1; j <= n; j++) {
			if (q[i][j] and rk[i][j] < ans)ans = rk[i][j];
		}
		std::cout << z[i][ans] << "\n";
	}
	return 0;
}