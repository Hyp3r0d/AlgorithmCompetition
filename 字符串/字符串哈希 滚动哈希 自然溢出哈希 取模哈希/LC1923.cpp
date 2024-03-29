
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

class Solution {
public:

	int longestCommonSubpath(int n, vector<vector<int>>& paths) {
		u64 b1 = 233, b2 = 199997;
		std::sort(paths.begin(), paths.end(), [&](auto x, auto y)->bool{
			return x.size() < y.size();
		});
		i64 l = 1, r = paths[0].size();
		auto check = [&](i64 mid) {
			u64 m1 = 1, m2 = 1;
			for (i64 i = 1; i <= mid; i++) {
				m1 = m1 * b1;
				m2 = m2 * b2;
			}
			u64 hs1 = 0, hs2 = 0;
			std::set<pair<u64, u64>>pre;
			for (i64 i = 0; i < mid; i++) {
				hs1 = hs1 * b1 + paths[0][i];
				hs2 = hs2 * b2 + paths[0][i];
			}

			pre.insert({hs1, hs2});
			for (i64 i = mid ; i < paths[0].size(); i ++) {
				hs1 = hs1 * b1 + (u64)paths[0][i] - ((u64)paths[0][i - mid]) * m1;
				hs2 = hs2 * b2 + (u64)paths[0][i] - ((u64)paths[0][i - mid]) * m2;
				pre.insert({hs1, hs2});
			}
			for (i64 i = 1; i < paths.size(); i++) {
				std::set<pair<u64, u64>>cur;
				hs1 = 0; hs2 = 0;
				for (i64 j = 0; j < mid; j ++) {
					hs1 = hs1 * b1 + paths[i][j];
					hs2 = hs2 * b2 + paths[i][j];
				}
				for (i64 j = mid; j < paths[i].size(); j++) {
					hs1 = hs1 * b1 + (u64)paths[i][j] - ((u64)paths[i][j - mid]) * m1;
					hs2 = hs2 * b2 + (u64)paths[i][j] - ((u64)paths[i][j - mid]) * m2;
					if (pre.count({hs1, hs2})) {
						cur.insert({hs1, hs2});
					}
				}
				if (not cur.size()) {
					return false;
				}
				pre = cur;
			}
			return true;
		};
		i64 ans = 0;
		while (l <= r) {
			i64 mid = (l + r) >> 1;
			if (check(mid)) {
				l = mid + 1, ans = mid;
			}
			else {
				r = mid - 1;
			}
		}
		return ans;
	}
};