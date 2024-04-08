/*多重背包 二维*/


/*LeetCode 2585*/
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

class Solution {
public:

	int waysToReachTarget(int target, vector<vector<int>>& types) {
		int dp[maxn][maxn]; memset(dp, 0, sizeof(dp));
		dp[0][0] = 1;
		int n = types.size();
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j <= target; j++) {
				//dp[i][j] = (dp[i][j] % mod + dp[i - 1][j]) % mod;
				for (int k = 0; k * types[i - 1][1] <= j and k <= types[i - 1][0]; k++) {
					dp[i][j] = (dp[i][j] % mod + dp[i - 1][j - k * types[i - 1][1]]) % mod;
				}
			}
		}
		return dp[n][target] % mod;
	}
};



/*多重背包 一维*/
class Solution {
public:
	int waysToReachTarget(int target, vector<vector<int>>& types) {
		int dp[10005]; memset(dp, 0, sizeof(dp));
		dp[0] = 1;
		int n = types.size();
		for (auto p : types) {
			int count = p[0], marks = p[1];
			for (int j = target; j >= 0; j--) {
				for (int k = 1; k <= count and k * marks <= j; k++) {
					dp[j] = (dp[j] % mod + dp[j - k * marks]) % mod;
				}
			}
		}
		return dp[target] % mod;
	}
};
/*多重背包 一维*/
class Solution {
public:

	int countSubMultisets(vector<int>& nums, int l, int r) {
		int n = nums.size(); i64 tot = accumulate(nums.begin(), nums.end(), 0ll);
		vector<i64>dp(tot + 5, 0);
		std::unordered_map<i64, i64>cnt;
		for (auto x : nums)cnt[x]++;
		dp[0] = cnt[0] + 1;// 0 提出单独计算
		cnt.erase(0);
		for (auto [x, y] : cnt) {
			for (i64 j = tot; j >= 0; j--) {
				for (int k = 1; k <= y and k * x <= j; k++) {
					dp[j] = (dp[j] % mod + dp[j - k * x]) % mod;
				}
			}
		}
		i64 ans = 0;
		for (int i = l; i <= r; i++) {
			ans = (ans % mod + dp[i]) % mod;
		}
		return ans % mod;
	}
};




/*多重背包O(1)优化*/
/*LeetCode 2902*/


class Solution {
public:
	int countSubMultisets(vector<int>& nums, int l, int r) {
		int n = nums.size(); i64 tot = accumulate(nums.begin(), nums.end(), 0ll);
		vector<i64>dp(tot + 5, 0);
		std::unordered_map<i64, i64>cnt;
		for (auto x : nums)cnt[x]++;
		dp[0] = cnt[0] + 1;/*多重背包问题求方案数*/
		cnt.erase(0); r = min(r, (int)tot); i64 sum = 0;
		for (auto [x, y] : cnt) {
			auto ndp = dp;
			sum = min(sum + x * y, (i64)r);
			for (i64 j = x; j <= sum; j++) {
				ndp[j] = (ndp[j] + ndp[j - x]) % mod;
				if (j >= (y + 1)*x) {
					ndp[j] = ((ndp[j] - dp[j - (y + 1) * x]) % mod + mod) % mod;
				}
			}
			dp = ndp;
		}
		i64 ans = 0;
		for (int i = l; i <= r; i++) {
			ans = (ans % mod + dp[i]) % mod;
		}
		return ans % mod;
	}
};



/*0 - 1 背包 二维*/

/* Atcoder Beginner contest 222 E*/
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

i64 fa[maxn][30];  i64 dep[maxn];
void solve() {
	i64 n, m, k; std::cin >> n >> m >> k;
	vector< i64>A(m + 1, 0); for ( i64 i = 1; i <= m; i++)std::cin >> A[i];
	vector<vector<pair< i64,  i64>>>tr(n + 1);
	vector< i64>d(n + 1, 0);
	for ( i64 i = 1; i <= n - 1; i++) {
		i64 u, v; std::cin >> u >> v;
		tr[u].push_back({v, i});
		tr[v].push_back({u, i});
	}
	vector< i64>p(n + 1);//节点转化为边差分
	function<void( i64,  i64)>dfs = [&]( i64 u,  i64 f) {
		fa[u][0] = f;
		dep[u] = dep[fa[u][0]] + 1;
		for ( i64 i = 1; (1 << i) <= dep[u]; i++) {
			fa[u][i] = fa[fa[u][i - 1]][i - 1];
		}
		for (auto [v, i] : tr[u]) {
			if (v == f)continue;
			p[v] = i; dfs(v, u);
		}
	};
	dfs(1, 0);
	auto lca = [&]( i64 u,  i64 v) {
		if (dep[u] < dep[v])swap(u, v);
		if (dep[u] != dep[v]) {
			for ( i64 i = log2(dep[u] - dep[v]); i >= 0; i--) {
				if (dep[fa[u][i]] >= dep[v]) {
					u = fa[u][i];
				}
			}
		}
		if (u == v)return u;
		for ( i64 i = log2(dep[u]); i >= 0; i--) {
			if (fa[u][i] != fa[v][i]) {
				u = fa[u][i]; v = fa[v][i];
			}
		}
		if (u != v) {
			u = fa[u][0];
		}
		return u;
	};
	for ( i64 i = 1; i <= m - 1; i++) {
		i64 u = A[i], v = A[i + 1];
		i64 lc = lca(u, v);
		d[p[u]]++; d[p[v]]++;
		d[p[lc]] -= 2;
	}
	function<void( i64,  i64)>dfs2 = [&]( i64 u,  i64 f) {
		for (auto [v, i] : tr[u]) {
			if (v == f)continue;
			dfs2(v, u);
			d[p[u]] += d[i];
		}
	};
	dfs2(1, 0);
	i64 tot = accumulate(d.begin() + 1, d.begin() + 1 + n, 0);
	vector dp(n + 1, vector< i64>(tot + 1, 0));
	dp[0][0] = 1;
	for ( i64 i = 1; i <= n - 1; i++) {
		for ( i64 j = tot; j >= 0; j--) {
			dp[i][j] = (dp[i][j] % mod + dp[i - 1][j]) % mod;
			if (j >= d[i])
				dp[i][j] = (dp[i][j] % mod + dp[i - 1][j - d[i]]) % mod;
		}
	}  i64 ans = 0;
	for ( i64 i = 0; i <= tot; i++)if (i + i - tot == k)ans = (ans % mod + dp[n - 1][i]) % mod;
	std::cout  << ans << "\n";
	;
}
int main() {
	solve();
}


/*0 - 1 背包一维*/


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

i64 fa[maxn][30];  i64 dep[maxn];
i64 dp[1000005];
void solve() {
	i64 n, m, k; std::cin >> n >> m >> k;
	vector< i64>A(m + 1, 0); for ( i64 i = 1; i <= m; i++)std::cin >> A[i];
	vector<vector<pair< i64,  i64>>>tr(n + 1);
	vector< i64>d(n + 1, 0);
	for ( i64 i = 1; i <= n - 1; i++) {
		i64 u, v; std::cin >> u >> v;
		tr[u].push_back({v, i});
		tr[v].push_back({u, i});
	}
	vector< i64>p(n + 1);//节点转化为边差分
	function<void( i64,  i64)>dfs = [&]( i64 u,  i64 f) {
		fa[u][0] = f;
		dep[u] = dep[fa[u][0]] + 1;
		for ( i64 i = 1; (1 << i) <= dep[u]; i++) {
			fa[u][i] = fa[fa[u][i - 1]][i - 1];
		}
		for (auto [v, i] : tr[u]) {
			if (v == f)continue;
			p[v] = i; dfs(v, u);
		}
	};
	dfs(1, 0);
	auto lca = [&]( i64 u,  i64 v) {
		if (dep[u] < dep[v])swap(u, v);
		if (dep[u] != dep[v]) {
			for ( i64 i = log2(dep[u] - dep[v]); i >= 0; i--) {
				if (dep[fa[u][i]] >= dep[v]) {
					u = fa[u][i];
				}
			}
		}
		if (u == v)return u;
		for ( i64 i = log2(dep[u]); i >= 0; i--) {
			if (fa[u][i] != fa[v][i]) {
				u = fa[u][i]; v = fa[v][i];
			}
		}
		if (u != v) {
			u = fa[u][0];
		}
		return u;
	};
	for ( i64 i = 1; i <= m - 1; i++) {
		i64 u = A[i], v = A[i + 1];
		i64 lc = lca(u, v);
		d[p[u]]++; d[p[v]]++;
		d[p[lc]] -= 2;
	}
	function<void( i64,  i64)>dfs2 = [&]( i64 u,  i64 f) {
		for (auto [v, i] : tr[u]) {
			if (v == f)continue;
			dfs2(v, u);
			d[p[u]] += d[i];
		}
	};
	dfs2(1, 0);
	dp[0] = 1;
	i64 tot = accumulate(d.begin() + 1, d.begin() + 1 + n, 0); i64 cnt = 0;
	for (i64 i = 1; i <= n - 1; i++) {
		if (not d[i]) {
			cnt++; continue;
		}
		for (i64 j = tot; j >= 0; j--) {
			if (j >= d[i])
				dp[j] = (dp[j] % mod + dp[j - d[i]]) % mod;
		}
	}
	auto qpow = [&](i64 x, i64 y) {
		i64 ret = 1;
		while (y) {
			if (y & 1)ret = ret % mod * x % mod;
			x = x % mod * x % mod;
			y >>= 1;
		}
		return ret % mod;
	};
	i64 ans = 0;
	for ( i64 i = 0; i <= tot; i++)if (i + i - tot == k)ans = (ans % mod + dp[i]) % mod;
	std::cout  << (ans % mod * qpow(2, cnt) % mod) << "\n"; // 0 抽出单独计算
	;
}
int main() {
	solve();
}


/* 完全背包 一维*/
/* LeetCode518*/
class Solution {
public:
	/*完全背包模板*/
	int change(int amount, vector<int>& coins) {
		vector<int> dp(amount + 1);
		dp[0] = 1;
		/*注意！背包问题求得是组合数方案，若枚举次序相反则为排列数*/
		for (int& coin : coins) {
			for (int i = coin; i <= amount; i++) {
				dp[i] += dp[i - coin];
			}
		}
		return dp[amount];
	}
};


