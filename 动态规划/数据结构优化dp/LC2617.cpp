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


/*单调栈 + 二分优化dp*/
/*滑窗范围不确定, 故用单调栈维护dp值的单调性, 二分出合法的下标来更新答案*/


/*  利用库函数二分 */
/* 写法1 */
class Solution {
public:
	int minimumVisitedCells(vector<vector<int>>& grid) {
		int n = grid.size(); int m = grid[0].size();
		vector<vector<pair<int, int>>>col(m + 5);//列单调栈
		vector g(n + 5, vector<int>(m + 5, 0));
		for (int i = 1; i <= n; i++)for (int j = 1; j <= m; j++)g[i][j] = grid[i - 1][j - 1];
		vector dp(n + 5, vector<int>(m + 5, 0x3f3f3f3f));
		dp[n][m] = 1;
		for (int i = n; i >= 1; i--) {
			std::vector<pair<int, int>>q;//本行的单调栈
			for (int j = m; j >= 1; j--) {
				auto &st = col[j];
				if (i == n and j == m)continue;
				int v = g[i][j];
				while (q.size() and q.back().second >= dp[i][j + 1])q.pop_back();
				q.push_back({j + 1, dp[i][j + 1]});
				while (st.size() and st.back().second >= dp[i + 1][j])st.pop_back();
				st.push_back({i + 1, dp[i + 1][j]});
				/*下标单调递减, 值单调递增, 选择第一个, 即满足条件的值最小的*/
				auto idx = lower_bound(q.begin(), q.end(), j + v, [&](pair<int, int>s, int t)->bool{
					return s.first > t;
				}) - q.begin();
				/*auto idx = lower_bound(q.begin(), q.end(), pair<i64, i64>{j + v, 0}, [&](pair<int, int>s, auto t)->bool{
					return s.first > t.first;
				}) - q.begin();*/
				if (idx < q.size())
					dp[i][j] = min(dp[i][j], q[idx].second + 1);
				idx = lower_bound(st.begin(), st.end(), i + v, [&](pair<int, int>s, int t)->bool{
					return s.first > t;
				}) - st.begin();
				if (idx < st.size())dp[i][j] = min(dp[i][j], st[idx].second + 1);
			}
		}

		if (dp[1][1] == 0x3f3f3f3f)return -1;
		return dp[1][1];
	}
};





/* 写法2 */
class Solution {
public:
	int minimumVisitedCells(vector<vector<int>>& grid) {
		int n = grid.size(); int m = grid[0].size();
		vector<vector<pair<int, int>>>col(m + 5);//列单调栈
		vector g(n + 5, vector<int>(m + 5, 0));
		for (int i = 1; i <= n; i++)for (int j = 1; j <= m; j++)g[i][j] = grid[i - 1][j - 1];
		vector dp(n + 5, vector<int>(m + 5, 0x3f3f3f3f));
		dp[n][m] = 1;

		for (int i = n; i >= 1; i--) {
			std::vector<pair<int, int>>q;//本行的单调栈
			for (int j = m; j >= 1; j--) {
				auto &st = col[j];
				int v = g[i][j];
				auto idx = lower_bound(q.begin(), q.end(), j + v, [&](pair<int, int>s, int t)->bool{
					return s.first > t;
				}) - q.begin();
				if (idx < q.size())
					dp[i][j] = min(dp[i][j], q[idx].second + 1);
				idx = lower_bound(st.begin(), st.end(), i + v, [&](pair<int, int>s, int t)->bool{
					return s.first > t;
				}) - st.begin();
				if (idx < st.size())dp[i][j] = min(dp[i][j], st[idx].second + 1);
				while (q.size() and q.back().second >= dp[i][j])q.pop_back();
				q.push_back({j, dp[i][j]});
				while (st.size() and st.back().second >= dp[i][j])st.pop_back();
				st.push_back({i, dp[i][j]});
			}
		}

		//也可以先维护值, 再加入栈, 避免越界
		if (dp[1][1] == 0x3f3f3f3f)return -1;
		return dp[1][1];
	}
};



/*  手动单调栈上二分 * /
/*写法 1 */
class Solution {
public:
	int minimumVisitedCells(vector<vector<int>>& grid) {
		int n = grid.size(); int m = grid[0].size();
		vector<vector<pair<int, int>>>col(m + 5);//列单调栈
		vector g(n + 5, vector<int>(m + 5, 0));
		for (int i = 1; i <= n; i++)for (int j = 1; j <= m; j++)g[i][j] = grid[i - 1][j - 1];
		vector dp(n + 5, vector<int>(m + 5, 0x3f3f3f3f));
		dp[n][m] = 1;

		for (int i = n; i >= 1; i--) {
			std::vector<pair<int, int>>q;//本行的单调栈
			for (int j = m; j >= 1; j--) {
				auto &st = col[j];
				int v = g[i][j]; i64 idx = -1, l = 0, r = q.size();
				while (l < r) {
					i64 mid = (l + r) >> 1;
					if (q[mid].first <= j + v) {
						r = mid, idx = mid;
					} else {
						l = mid + 1;
					}
				}

				if (idx != -1 and idx < q.size())
					dp[i][j] = min(dp[i][j], q[idx].second + 1);
				idx = -1; l = 0, r = st.size();
				while (l < r) {
					i64 mid = (l + r) >> 1;
					if (st[mid].first <= i + v) {
						r = mid, idx = mid;
					} else {
						l = mid + 1;
					}
				}
				if (idx < st.size() and idx != -1)dp[i][j] = min(dp[i][j], st[idx].second + 1);
				while (q.size() and q.back().second >= dp[i][j])q.pop_back();
				q.push_back({j, dp[i][j]});
				while (st.size() and st.back().second >= dp[i][j])st.pop_back();
				st.push_back({i, dp[i][j]});
			}
		}
		//也可以先维护值, 再加入栈, 避免越界
		if (dp[1][1] == 0x3f3f3f3f)return -1;
		return dp[1][1];
	}
};




/* 写法 2 */
class Solution {
public:
	int minimumVisitedCells(vector<vector<int>>& grid) {
		int n = grid.size(); int m = grid[0].size();
		vector<vector<pair<int, int>>>col(m + 5);//列单调栈
		vector g(n + 5, vector<int>(m + 5, 0));
		for (int i = 1; i <= n; i++)for (int j = 1; j <= m; j++)g[i][j] = grid[i - 1][j - 1];
		vector dp(n + 5, vector<int>(m + 5, 0x3f3f3f3f));
		dp[n][m] = 1;

		for (int i = n; i >= 1; i--) {
			std::vector<pair<int, int>>q;//本行的单调栈
			for (int j = m; j >= 1; j--) {
				auto &st = col[j];
				int v = g[i][j]; i64 idx = -1, l = 0, r = q.size() - 1;
				while (l <= r) {
					i64 mid = (l + r) >> 1;
					if (q[mid].first <= j + v) {
						r = mid - 1, idx = mid;
					} else {
						l = mid + 1;
					}
				}

				if (idx != -1)
					dp[i][j] = min(dp[i][j], q[idx].second + 1);
				idx = -1; l = 0, r = st.size() - 1;
				while (l <= r) {
					i64 mid = (l + r) >> 1;
					if (st[mid].first <= i + v) {
						r = mid - 1, idx = mid;
					} else {
						l = mid + 1;
					}
				}
				if (idx != -1)dp[i][j] = min(dp[i][j], st[idx].second + 1);
				while (q.size() and q.back().second >= dp[i][j])q.pop_back();
				q.push_back({j, dp[i][j]});
				while (st.size() and st.back().second >= dp[i][j])st.pop_back();
				st.push_back({i, dp[i][j]});
			}
		}
		//也可以先维护值, 再加入栈, 避免越界
		if (dp[1][1] == 0x3f3f3f3f)return -1;
		return dp[1][1];
	}
};


/*线段树优化dp*/

class Solution {
public:
	/*void pushup(int p, sq tr[]） {

	}*/
	int n; int  m;
	struct sq {
		int l; int r; int mn; int laz;
	} tr1[maxn], tr2[maxn];

	void build(int p, int l, int r, sq tr[]) {
		tr[p].l = l; tr[p].r = r;
		tr[p].mn = tr[p].laz = inf;
		if (l == r) {
			return;
		}
		int mid = (l + r) >> 1;
		build(p << 1, l, mid, tr);
		build(p << 1 | 1, mid + 1, r, tr);
		tr[p].mn = std::min(tr[p << 1].mn, tr[p << 1 | 1].mn);
	}
	void pushdown(int p, sq tr[]) {
		if (tr[p].laz != inf) {
			int lz = tr[p].laz;
			tr[p].laz = inf;
			tr[p << 1].mn = min(tr[p << 1].mn, lz);
			tr[p << 1 | 1].mn = min(tr[p << 1 | 1].mn, lz);
			tr[p << 1].laz = min(tr[p << 1].laz, lz);
			tr[p << 1 | 1].laz = min(tr[p << 1 | 1].laz, lz);
		}
	}
	int query(int p, int l, int r, sq tr[]) {
		if (l > r)return inf;
		if (tr[p].l >= l and tr[p].r <= r)return tr[p].mn;
		pushdown(p, tr);
		int mid = (tr[p].l + tr[p].r) >> 1;
		int ret = inf;
		if (r > mid)ret = min(ret, query(p << 1 | 1, l, r, tr));
		if (l <= mid)ret = min(ret, query(p << 1, l, r, tr));
		return ret;
	}

	void modify(int p, int l, int r, int v, sq tr[]) {
		if (l > r)return;
		if (tr[p].l >= l and tr[p].r <= r) {
			tr[p].mn = min(tr[p].mn, v);
			tr[p].laz = min(tr[p].laz, v);
			return;
		}
		pushdown(p, tr);
		int mid = (tr[p].l + tr[p].r) >> 1;
		if (r > mid)modify(p << 1 | 1, l, r, v, tr);
		if (l <= mid)modify(p << 1, l, r, v, tr);
		tr[p].mn = std::min(tr[p << 1].mn, tr[p << 1 | 1].mn);
	}
	int minimumVisitedCei64s(vector<vector<int>>& grid) {
		n = grid.size(); m = grid[0].size();
		build(1, 1, m * n, tr1);
		build(1, 1, m * n, tr2);
		modify(1, 1, 1, 1, tr1);
		modify(1, 1, 1, 1, tr2);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (not grid[i][j])continue;
				int v = grid[i][j];
				int s1 = i + 1, s2 = min(i + v, n - 1);
				int w = min(query(1, i + j * n + 1, i + j * n + 1, tr1), query(1, j + i * m + 1, j + i * m + 1, tr2));
				modify(1, s1 + j * n + 1, s2 + j * n + 1, w + 1, tr1);
				s1 = j + 1, s2 = min(j + v, m - 1);
				modify(1, i * m + s1 + 1, s2 + i * m + 1, w + 1, tr2);
			}
		}
		int ans = min(query(1, n * m, n * m, tr1), query(1, n * m, n * m, tr2));
		if (ans == inf)return -1;
		return ans;
	}
};



