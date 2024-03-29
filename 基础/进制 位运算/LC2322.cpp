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

constexpr i64 mod = 1e9 + 7;
constexpr i64 maxn = 2e7 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

class Solution {
public:
	int minimumScore(vector<int>& nums, vector<vector<int>>& edges) {
		i64 n = nums.size();
		std::vector<std::vector<i64>>g(n);
		for (i64 i = 0; i < n - 1; i++) {
			auto e = edges[i];
			i64 u = e[0], v = e[1];
			g[u].push_back(v); g[v].push_back(u);

		}
		std::vector<i64>dep(n);
		std::vector<i64>sz(n);
		std::vector<i64>w1(n), w2(n);
		/*处理出前缀和*/
		std::function<void(i64, i64)>dfs1 = [&](i64 u, i64 f) {
			w1[u] = nums[u];
			sz[u] = 1;
			for (auto v : g[u]) {
				if (v == f)continue;
				dep[v] = dep[u] + 1;
				dfs1(v, u);
				sz[u] += sz[v];
				w1[u] ^= w1[v];

			}
		};

		i64 v1 = 0, v2 = 0; i64 v3 = 0;
		i64 p = 0; i64 ans = inf;
		std::function<void(i64, i64)>dfs2 = [&](i64 u, i64 f) {
			w2[u] = nums[u];
			for (auto v : g[u]) {
				if (v == f)continue;
				dfs2(v, u);
				w2[u] ^= w2[v];
			}
			if (u != p) {
				v3 = v2 ^ w2[u];
				i64 mx = std::max({v1, w2[u], v3});
				i64 mn = std::min({v1, w2[u], v3});
				ans = std::min(ans, mx - mn);
			}
			return;
		};
		dfs1(0, -1);
		for (i64 i = 0; i < n - 1; i++) {
			auto e = edges[i];
			i64 u = e[0], v = e[1];
			if (dep[u] < dep[v])swap(u, v);
			v2 = w1[u], v1 = w1[0] ^ w1[u];
			if (sz[u] != 1) {
				p = u;
				dfs2(u, v);
			}
			if (sz[0] - sz[u] != 1) {
				v2 = w1[0] ^ w1[u], v1 = w1[u];
				p = v; dfs2(v, u);
			}
		}
		return ans ;
	}
};