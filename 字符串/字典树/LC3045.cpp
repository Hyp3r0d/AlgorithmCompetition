/*与概率递推不同,本题应当先算出各种情况的种数量,结合古典概型进行运算*/
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



class Solution {
public:
	vector<int> zFunction(string &s) {
		int n = (int)s.size();
		std::vector<int>z(n);
		for (int i = 1, l = 0, r = 0; i < n; i++) {
			if (i <= r and z[i - l] < r - i + 1) {
				z[i] = z[i - l];
			} else {
				z[i] = std::max(0, r - i + 1);
				while (i + z[i] < n and s[z[i]] == s[i + z[i]])++z[i];
			}
			if (i + z[i] - 1 > r) {
				l = i, r = i + z[i] - 1;
			}
		}
		return z;
	}
	struct Node {
		int to[30]; int cnt = 0;
	};
	i64 tot = 1;
	long long countPrefixSuffixPairs(vector<string>& words) {
		std::vector<Node>tr;
		tr.push_back(Node());
		auto insert = [&](string s) {

			auto z = zFunction(s);

			int n = s.size(); int u = 0;

			for (int i = 0; i < n; i++) {
				int cur = s[i] - 'a';
				if (not tr[u].to[cur]) {
					tr[u].to[cur] = tot;
					tr.push_back(Node()); tot++;
				}
				u = tr[u].to[cur];
				int len = i + 1;
				if (z[n - len] == len or len == n) {
					tr[u].cnt++;
				}
			}
		};
		int m = words.size();
		auto query = [&](string s) {
			int u = 0;
			int n = s.size();
			for (int i = 0; i < n; i++) {
				int cur = s[i] - 'a';
				if (not tr[u].to[cur])return 0;
				u = tr[u].to[cur];
			}
			return tr[u].cnt;
		};
		i64 ans = 0;
		for (int i = m - 1; i >= 0; i--) {
			auto s = words[i];
			ans += query(s);
			insert(s);
		}
		return ans;
	}
};
