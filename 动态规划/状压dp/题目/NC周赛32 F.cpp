
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

constexpr i64 mod = 1e9 + 7;
constexpr i64 maxn = 4e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;



int main () {

	int n, m; std::cin >> n >> m;
	std::vector<string>s(n + 1);
	for (int i = 1; i <= n; i++) {
		std::cin >> s[i];
		s[i] = " " + s[i];
	}
	i64 z = 1; for (int x = 0; x < n; x++)z *= 3;

	std::map<char, int>mp = {{'r', 0}, {'e', 1}, {'d', 2}};

	std::vector dp(m + 1, std::vector<i64>(z + 1, inf));

	int a[m + 1][n + 1];

	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			a[i][j - 1] = mp[s[j][i]];
		}
	}

	auto check = [&](int x) {
		vector<int>tmp;
		for (int i = 0; i < n; i++) {
			tmp.push_back(x % 3);
			x /= 3;
		}
		for (int i = 1; i < n; i++) {
			if (tmp[i] == tmp[i - 1])return false;
		}
		return true;
	};

	auto valid = [&](int x, int y) {
		for (int i = 0; i < n; i++) {
			if (x % 3 == y % 3)return false;
			x /= 3, y /= 3;
		}
		return true;
	};



	for (int i = 0; i < z; i++) {
		if (check(i)) {
			int cnt = 0;
			int tmp = i; std::vector<int>v;
			for (int j = 0; j < n; j++) {
				v.push_back(tmp % 3);
				tmp /= 3;
				if (v[j] != a[1][j])cnt++;
			}
			dp[1][i] = cnt;
		}
	}
	for (int i = 2; i <= m; i++) {
		for (int j = 0; j < z; j++) {
			for (int k = 0; k < z; k++) {
				if (valid(j, k) and check(j) and check(k)) {
					int cnt = 0;
					int tmp = k; std::vector<int>v;
					for (int p = 0; p < n; p++) {
						v.push_back(tmp % 3);
						tmp /= 3;
						if (v[p] != a[i][p])cnt++;
					}
					dp[i][k] = std::min(dp[i][k], dp[i - 1][j] + cnt);
				}
			}
		}
	}


	std::cout << *min_element(dp[m].begin(), dp[m].begin() + z) << "\n";
	return 0;
}