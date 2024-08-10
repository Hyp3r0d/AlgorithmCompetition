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

constexpr i64 mod = 998244353;
constexpr i64 maxn = 1e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

constexpr f64 eps = 1e-7; // 定义精度


std::vector<i64>w(105, -1);

void Gauss(vector<vector<f64>>& matrix, i64 n, i64 m) {
	i64 lead = 0;// 该行主元所在列
	for (i64 r = 0; r < n; ++r) {
		if (lead == n) return;
		i64 i = r;
		while (fabs(matrix[i][lead]) < eps) {
			++i;
			if (i == n) {
				i = r; ++lead;
				if (lead == n) return;
			}
		}
		w[r] = lead;
		// 交换第r行和第i行
		swap(matrix[i], matrix[r]);

		// 将主元所在行的主元化为1
		f64 lv = matrix[r][lead];
		for (i64 j = 0; j < m; ++j) {
			matrix[r][j] /= lv;
		}

		// 将主元所在列的其他行化为0
		for (i64 i = 0; i < n; ++i) {
			if (i != r) {
				f64 lv = matrix[i][lead];
				for (i64 j = 0; j < m; ++j) {
					matrix[i][j] -= lv * matrix[r][j];
				}
			}
		}
		++lead;
	}
}




int main() {
	i64 n ; std::cin >> n;
	std::vector a(n + 5, std::vector<f64>(n + 5, 0.0));
	for (i64 i = 0; i < n; i++) {
		for (i64 j = 0; j <= n; j++)std::cin >> a[i][j];
	}
	Gauss(a, n, n + 1);
	/*for (i64 i = 0; i < n; i++) {
		for (i64 j = 0; j <= n; j++) {
			std::cout << fixed << setprecision(4) << a[i][j] << " \n"[j == n];
		}
	}*/		
	i64 x = 0, y = n - 1;
	while (x < n and w[x] != -1)x++;
	x--;
	while (y >= 0 and abs(a[y][n]) < eps)y--;
	
	if (x < y) {
		puts("No Solution");
		return 0;
	}


	std::vector<bool>vis(n + 1, false);
	for (i64 i = 0; i < n; i++) {
		vis[w[i]] = true;
	}
	std::vector<f64>ans(n + 1, 0); for (i64 i = 0; i < n; i++) {
		if (not vis[i])ans[i] = 1;
	}
	// 非主元都是1
	for (i64 i = x; i >= 0; i--) {
		ans[w[i]] = a[i][n];
		for (i64 j = n - 1; j > w[i]; j--) {
			ans[w[i]] -= a[i][j] * ans[j];
		}
	}
	for (i64 i = 0; i < n; i++) {
		printf("%.2lf\n", ans[i]);
	}
	return 0;
}
