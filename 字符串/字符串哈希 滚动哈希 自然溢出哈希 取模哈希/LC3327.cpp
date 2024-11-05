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
constexpr i64 maxn = 2e5 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


class Solution {
public:
	vector<bool> findAnswer(vector<int>& parent, string s) {
		i64 n = s.size();
		s = " " + s;
		std::vector<vector<i64>>g(n + 1);
		for (i64 i = 1; i < n; i++) {
			g[parent[i] + 1].push_back(i + 1);
			g[i + 1].push_back(parent[i] + 1);
		}
		std::vector<bool>res(n, false);
		std::vector<i64>sz(n + 1), pos(n + 1);
		string str = " "; i64 d = 0;
		std::function<void(i64, i64)>dfs = [&](i64 u, i64 f) {
			sz[u] = 1; ++d;
			for (auto v : g[u]) {
				if (v == f)continue;
				dfs(v, u);
				sz[u] += sz[v];
			}
            pos[u] = str.size(); str += s[u];
		};
		dfs(1, 0);
        std::cout << str << "\n";
		std::vector<u64>hashValue(n + 5), reverseHashValue(n + 5);
		u64 x = 233; std::vector<u64>px(n + 1);
		px[0] = 1; for (i64 i = 1; i <= n; i++)px[i] = px[i - 1] * x;
		for (i64 i = 1; i <= n; i++) {
			hashValue[i] = hashValue[i - 1] * x + str[i];
		}
		for (i64 i = n; i >= 1; i--) {
			reverseHashValue[i] = reverseHashValue[i + 1] * x + str[i];
		}
		auto judge = [&](i64 l, i64 r)->bool {
			u64 v1 = hashValue[r] - hashValue[l - 1] * px[r - l + 1];
			u64 v2 = reverseHashValue[l] - reverseHashValue[r + 1] * px[r - l + 1];
			return v1 == v2;
		};
		for (i64 i = 0; i < n; i++) {
			i64 cur = i + 1;
			res[i] = judge(pos[cur] - sz[cur] + 1, pos[cur]);
		}
		return res;
	}
};