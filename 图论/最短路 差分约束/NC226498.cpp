/* dijkstra模板 */
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

constexpr i64 mod = 1e5 + 3;
constexpr i64 maxn = 1e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


struct cmp {
    bool operator()(const pair<i64, i64>&x, const pair<i64, i64>&y) {
        return x.first > y.first;
    }
};

std::priority_queue<std::pair<i64, i64>, vector<pair<i64, i64>>, cmp>q;
i64 dis[maxn]; bool vis[maxn];
std::vector<std::pair<i64, i64>>e[maxn + 5];
void solve() {
    i64 n, m; std::cin >> n >> m;
    memset(dis, 0x3f, sizeof(dis));

    for (i64 i = 1; i <= m; i++) {
        i64 u, v, w; std::cin >> u >> v >> w;
        e[u].push_back({v, w});
        e[v].push_back({u, w});
    }

    q.push({0, 1}); dis[1] = 0;

    while (q.size()) {
        auto [d, u] = q.top();
        q.pop();
        if (vis[u])continue;
        vis[u] = true;
        for (auto [v, w] : e[u]) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                if (not vis[v]) {
                    q.push({dis[v], v});
                }
            }
        }
    }
    std::cout << (dis[n] == inf ? -1 : dis[n]);
}
int main() {
    solve();
    return 0;
}





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

constexpr i64 mod = 1e5 + 3;
constexpr i64 maxn = 1e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;
/*Bei64man - ford算法*/

/*spfa优化*/
i64 dis[maxn]; bool vis[maxn];
std::vector<std::pair<i64, i64>>g[maxn + 5];
int main() {
    i64 n, m; std::cin >> n >> m;
    memset(dis, 0x3f, sizeof(dis));

    for (i64 i = 1; i <= m; i++) {
        i64 u, v, w; std::cin >> u >> v >> w;
        e[u].push_back({v, w});
        e[v].push_back({u, w});
    }
    dis[1] = 0, vis[1] = 1;
    std::vector<i64>cnt(n + 1);
    queue<i64>q; q.push(s);
    while (q.size()) {
        i64 u = q.front(); q.pop();
        vis[u] = 0;
        for (auto [v, w] : g[u]) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                //cnt[v] = cnt[u] + 1;
                //if (cnt[v] >= n)return 0;
                if (not vis[v]) {
                    q.push(v), vis[v] = 1;
                }
            }
        }
    }
    std::cout << (dis[n] == inf ? -1 : dis[n]);
}




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

constexpr i64 mod = 1e5 + 3;
constexpr i64 maxn = 1e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;
/*Bei64man - ford算法*/

/*spfa优化*/
i64 dis[maxn]; bool vis[maxn];
std::vector<std::pair<i64, i64>>g[maxn + 5];
int main() {
    i64 n, m; std::cin >> n >> m;
    memset(dis, 0x3f, sizeof(dis));

    for (i64 i = 1; i <= m; i++) {
        i64 u, v, w; std::cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    dis[1] = 0, vis[1] = 1;
    std::vector<i64>cnt(n + 1);
    queue<i64>q; q.push(1);
    while (q.size()) {
        i64 u = q.front(); q.pop();
        vis[u] = 0;
        for (auto [v, w] : g[u]) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                //cnt[v] = cnt[u] + 1;
                //if (cnt[v] >= n)return 0;
                if (not vis[v]) {
                    q.push(v), vis[v] = 1;
                }
            }
        }
    }
    std::cout << (dis[n] == inf ? -1 : dis[n]);
}