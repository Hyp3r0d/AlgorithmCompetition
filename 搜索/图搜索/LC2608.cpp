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
    int findShortestCycle(int n, vector<vector<int>>& edges) {
        vector<vector<i64>>g(n + 1);
        for (auto e : edges) {
            g[e[0] + 1].push_back(e[1] + 1);
            g[e[1] + 1].push_back(e[0] + 1);
        }
        std::vector<i64>dis(n + 1 - 1);
        auto bfs = [&](i64 x) {
            i64 ret = inf;
            std::fill(dis + 1, dis + 1 + n, -1);
            dis[x] = 0;
            queue<pair<i64, i64>>q;
            q.push({x, -1});
            while (q.size()) {
                auto [u, fa] = q.front(); q.pop();
                for (auto v : g[u]) {
                    if (dis[v] < 0) {
                        dis[v] = dis[u] + 1;
                        q.push({v, u});
                    } else if (v != fa) {
                        ret = std::min(ret, dis[u] + dis[v] + 1);
                    }
                }
            }
            return ret;
        };
        i64 ans = inf;
        for (i64 i = 1; i <= n; i++) {
            ans = std::min(ans, bfs(i));
        }
        return ans == inf ? ans : -1;
    }
};