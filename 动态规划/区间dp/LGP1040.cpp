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

constexpr i64 mod = 45989;
constexpr i64 maxn = 3e4 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

i64 n, a[maxn];
i64 dp[105][105], root[105][105];
i64 z[105], p[105];
int main() {
	std::cin >> n;
	for (i64 i = 1; i <= n; i++) {
		std::cin >> a[i];
	}
	for (i64 i = 1; i <= n; i++) {
		for (i64 j = i; j >= 1; j--) {
			if (i == j) {
				dp[i][j] = a[i];
				root[i][j] = i;
			} else {
				i64 idx = -1;
				for (i64 k = j; k <= i; k++) {
					i64 l = (k - j) ? dp[j][k - 1] : 1;
					i64 r = (i - k) ? dp[k + 1][i] : 1;

					if (l * r + a[k] > dp[j][i]) {
						dp[j][i] = l * r + a[k]; idx = k;
					}
				}
				root[j][i] = idx;
				z[idx] = root[j][idx - 1]; p[idx] = root[idx + 1][i];
			}
		}
	}
	std::function<void(i64, i64)>dfs = [&](i64 l, i64 r) {
		if (l > r)return;
		std::cout << root[l][r] << " ";
		dfs(l, root[l][r] - 1);
		dfs(root[l][r] + 1, r);
	};
	std::cout << dp[1][n] << "\n";
	dfs(1, n);
	return 0;
}