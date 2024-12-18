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
    struct cmp {
        bool operator()(const int&x, const int&y)const {
            return x < y;
        }
    };
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int k) {
        std::vector<pair<int, int>>g;
        i64 n = quality.size();
        for (int i = 0; i < n; i++) {
            g.push_back(pair<int, int> {quality[i], wage[i]});
        }
        std::sort(g.begin(), g.end(), [&](pair<int, int>x, pair<int, int>y)->bool {
            return (x.second + 0.0) / x.first < (y.second + 0.0) / y.first;
        });
        double sum = 0;
        std::priority_queue<int, vector<int>, cmp>pq;
        for (int i = 0; i < k; i++) {
            pq.push(g[i].first); sum += g[i].first;
        }
        double ans = sum * g[k - 1].second / (g[k - 1].first + 0.0);
        for (int i = k; i < n; i++) {
            int q = g[i].first;
            if (q < pq.top()) {
                sum -= pq.top(); sum += q;
                pq.pop(); pq.push(q);
                ans = std::min(ans, (double)sum * g[i].second / (g[i].first + 0.0));
            }
        }
        return ans;
    }
};