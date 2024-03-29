
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
constexpr i64 maxn = 2e5 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;



/* 求一系列字符串的最长公共子串 */
class Solution {
public:
	i64 height[100010];
	i64 sa[100010], rk[100010], oldrk[100010];
	i64 id[100010], key1[100010], cnt[100010];
	i64 b[100010], sublen[100010], s[100010];
	void init(i64 n) {
		auto cmp = [&](i64 x, i64 y, i64 w) {
			return oldrk[x] == oldrk[y] and oldrk[x + w] == oldrk[y + w];
		};
		i64 m = 100000;
		for (i64 i = 1; i <= n; i++)++cnt[rk[i] = s[i]];
		for (i64 i = 1; i <= m; i++)cnt[i] += cnt[i - 1];
		for (i64 i = n; i >= 1; i--)sa[cnt[rk[i]]--] = i;//计数排序

		for (i64 w = 1, p;; w <<= 1, m = p) {
			p = 0;
			for (i64 i = n; i > n - w; --i)id[++p] = i;
			for (i64 i = 1; i <= n; i++) {
				if (sa[i] > w)id[++p] = sa[i] - w;
			}
			memset(cnt, 0, sizeof(cnt));
			for (i64 i = 1; i <= n; i++) {
				++cnt[key1[i] = rk[id[i]]];
			}
			for (i64 i = 1; i <= m; i++)cnt[i] += cnt[i - 1];
			for (i64 i = n; i >= 1; i--)sa[cnt[key1[i]]--] = id[i];
			for (i64 i = 1; i <= n; i++) {
				oldrk[i] = rk[i];
			}
			p = 0;
			for (i64 i = 1; i <= n; i++) {
				rk[sa[i]] = cmp(sa[i], sa[i - 1], w) ? p : ++p;
			}
			if (p == n) {
				for (i64 i = 1; i <= n; i++)sa[rk[i]] = i;
				break;
			}
		}
		for (i64 i = 1, j = 0; i <= n; i++) {
			if (j)--j;
			while (s[i + j] == s[sa[rk[i] - 1] + j])++j;
			height[rk[i]] = j;
		}
	}
	int longestCommonSubpath(int n, vector<vector<int>>& paths) {
		int m = paths.size();
		i64 len = 0;
		for (i64 i = 0; i < m; i++) {
			for (i64 j = 0; j < paths[i].size(); j++) {
				s[++len] = paths[i][j] + 1;
				b[len] = i + 1;
				sublen[len] = paths[i].size() - j;
			}
		}
		init(len);
		std::unordered_set<i64>st;
		i64 l = 0, r = len;
		while (l < r) {
			i64 mid = (l + r + 1) >> 1;
			bool flag = false;
			for (i64 i = 1, j; i <= len; i = j) {
				st.clear();
				for (j = i; j <= len and (j == i or height[j] >= mid); j++) {
					// 从第二个字符串开始要求公共前缀 >= mid
					if (sublen[sa[j]] >= mid)st.insert(b[sa[j]]);
				}
				if (st.size() == m) {
					flag = true; break;
				}
			}
			if (flag) {
				l = mid;
			} else r = mid - 1;
		}
		return l;
	}
};