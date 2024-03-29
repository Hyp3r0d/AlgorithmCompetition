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
constexpr i64 maxn = 2e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


i64 q[maxn], hed = 1, tal = 0;

int main() {
	i64 n, m; std::cin >> n >> m;
	std::vector g(n + 1, std::vector<char>(m + 1));
	char tmp = getchar(); tmp = getchar();
	for (i64 i = 1; i <= n; i++) {
		i64 z = 0; char c;
		while ((c = getchar()) != '\n') {
			if (isalpha(c))g[i][++z] = c;
		}
	}

	std::vector pos(n + 1, std::vector<i64>(m + 1, 0));

	for (i64 i = 1; i <= n; i++) {
		for (i64 j = 1; j <= m; j++) {
			if (g[i][j] == 'F') {
				pos[i][j] = pos[i - 1][j] + 1;
			} else pos[i][j] = 0;
		}


	}
	i64 ans = 0;
	auto cal = [&](i64 idx) {
		std::vector<i64>z(m + 1);
		for (i64 i = 1; i <= m; i++) {
			z[i] = pos[idx][i];
		}
		std::vector<i64>pre(m + 1, 0); // 左边第一个小于的
		std::vector<i64>suf(m + 1, m + 1); // 右边第一个小于的
		hed = 1, tal = 0;
		for (i64 i = 1; i <= m; i++) {
			while (hed <= tal and z[q[tal]] >= z[i]) {
				tal--;
			}
			if (hed <= tal)
				pre[i] = q[tal];
			q[++tal] = i;
		}
		hed = 1, tal = 0;
		for (i64 i = m; i >= 1; i--) {
			while (hed <= tal and z[q[tal]] >= z[i]) {
				tal--;
			}
			if (hed <= tal)
				suf[i] = q[tal];
			q[++tal] = i;
		}
		for (i64 i = 1; i <= m; i++) {
			i64 x = z[i];
			i64 l = pre[i], r = suf[i];
			ans = std::max(ans, x * (r - l - 1));
		}
	};

	for (i64 i = 1; i <= n; i++) {
		cal(i);
	}
	std::cout << 3 * ans << "\n";
}