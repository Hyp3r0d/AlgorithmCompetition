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

constexpr i64 mod = 45989;
constexpr i64 maxn = 5e4 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


class Solution {
public:
	vector<int> countVisitedNodes(vector<int>& edges) {
		int n = edges.size();
		vector<int>ret(n);
		std::vector<int>d(n);
		vector<vector<int>>g(n);
		for (int i = 0; i < n; i++) {
			d[edges[i]]++;
			g[edges[i]].push_back(i);
		}
		queue<int>q; vector<bool>vis(n);
		for (int i = 0; i < n; i++) {
			if (not d[i])q.push(i), vis[i] = true;
		}
		while (q.size()) {
			auto u = q.front(); q.pop();
			i64 nxt = edges[u];
			d[nxt]--;
			if (not d[nxt]) {
				vis[nxt] = true; q.push(nxt);
			}
		}
		auto bfs = [&](i64 u, i64 sz) {
			ret[u] = sz;
			q.push(u);
			while (q.size()) {
				auto u = q.front(); q.pop();
				for (auto v : g[u]) {
					if (not vis[v])continue;
					if (ret[v])continue;
					ret[v] = ret[u] + 1;
					q.push(v);
				}
			}
		};
        std::vector<bool>vis2(n);
		for (i64 i = 0; i < n; i++) {
			if (not vis[i] and not vis2[i]) {
				i64 cur = i; int sz = 1;vis2[cur] = true;
				while (1) {
					cur = edges[cur];
					if (cur == i)break;
                    vis2[cur] = true;
					sz++; 
				}
                cur = i;bfs(cur, sz);
                while(1) {
                    cur = edges[cur];
                    if(cur == i)break;
                    bfs(cur, sz);
                }
			}
		}
		return ret;
	}
};