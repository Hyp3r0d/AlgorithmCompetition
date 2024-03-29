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
	long long getMaxFunctionValue(vector<int>& a, i64 k) {
		i64 n = a.size();
		vector<std::vector<i64>>nes(n); auto rnes = nes;
		vector<i64> deg(n, 0);
		for (i64 i = 0; i < n; ++i) {
			nes[i].push_back(a[i]);
			rnes[a[i]].push_back(i);
			deg[a[i]]++;
		}
		queue<i64> q;
		for (i64 i = 0; i < n; ++i) {
			if (deg[i] == 0) {
				q.push(i);
			}
		}
		while (q.size()) {
			i64 cur = q.front(); q.pop();
			for (i64 ne : nes[cur]) {
				if (--deg[ne] == 0) {
					q.push(ne);
				}
			}
		}

		vector<vector<i64>> pts;          /* pts[i] = 环内的点 */
		vector<i64> len;                        /* len[i] = 环 i 的长度 */
		vector<i64> cycle(n, -1), idx(n, -1);   /* cycle[i] = 点在哪个环上; idx[i] = 点在环的哪个位置 */
		for (i64 i = 0; i < n; ++i) {
			if (deg[i] && cycle[i] == -1) {
				pts.push_back({0});
				i64 cur = i;
				do {
					pts.back().push_back(cur);
					cycle[cur] = pts.size() - 1;
					idx[cur] = pts.back().size() - 1;
					cur = a[cur];
				} while (cur != i);
				len.push_back(pts.back().size() - 1);
			}
		}
		for (auto& v : pts) {
			for (i64 len = v.size(), i = 1; i < len; ++i)
				v.push_back(v[i]);
			for (i64 i = 1; i < v.size(); ++i)
				v[i] += v[i - 1];
		}
		/* 环内残缺的部分 */
		vector<i64> st(1, 0);
		i64 res = 0;
		std::function<void(i64, i64)> dfs = [&](i64 root, i64 node) {
			auto &v = pts[cycle[root]];
			i64 out = min((i64)st.size() - 1, k + 1), in = k + 1 - out;
			res = max(res,
			          st.back() - st[st.size() - 1 - out]                          /* 环外的部分 */
			          + (in / len[cycle[root]]) * v[len[cycle[root]]]              /* 环内完整的数量 */
			          + v[idx[root] + in % len[cycle[root]] - 1] - v[idx[root] - 1]);
			for (i64 ne : rnes[node]) {
				if (deg[ne] == 0) {
					st.push_back(st.back() + ne);
					dfs(root, ne);
					st.pop_back();
				}
			}
		};

		for (i64 i = 0; i < n; ++i) {
			if (deg[i]) {
				dfs(i, i);
			}
		}

		return res;
	}
};
