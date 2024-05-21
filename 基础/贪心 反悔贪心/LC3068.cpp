/*Tarjan缩点求SCC*/
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
  long long maximumValueSum(vector<int>& nums, int k, vector<vector<int>>& edges) {
    i64 n = nums.size();

    std::vector<vector<i64>>g(n + 1);

    for (i64 i = 0; i < edges.size(); i++) {
      g[edges[i][0] + 1].push_back(edges[i][1] + 1);
      g[edges[i][1] + 1].push_back(edges[i][0] + 1);
    }

    nums.insert(nums.begin(), 0);
    std::vector dp(n + 1, std::array<i64, 2>{0ll, -inf});
    std::function<void(i64, i64)>dfs = [&](i64 u, i64 f) {
      for (auto v : g[u]) {
        if (v == f)continue;
        dfs(v, u);
        array<i64, 2>nxt;
        for (i64 i = 0; i <= 1; i++) {
          nxt[i] = std::max(dp[u][i] + max(dp[v][0], dp[v][1]), dp[u][1 - i] + max(dp[v][0] + (nums[v] ^ k) - nums[v], dp[v][1] + nums[v] - (nums[v] ^ k)));
        }
        dp[u] = nxt;
      }
      dp[u][0] += nums[u]; dp[u][1] += (nums[u] ^ k);
    };

    dfs(1, 0);

    return std::max(dp[1][0], dp[1][1]);
  }
};