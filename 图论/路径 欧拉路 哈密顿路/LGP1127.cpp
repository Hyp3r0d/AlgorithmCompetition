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
const i64 mod = 666623333;
const i64 maxn = 1e6 + 5;
const i64 inf = 0x3f3f3f3f3f3f3f3f;
/*无向图找欧拉通路 / 欧拉回路*/




vector<pair<i64, i64>>g[30];

void addedge(i64 u, i64 v, i64 z) {
    g[u].push_back({v, z});
}

int main() {
    i64 n; std::cin >> n; std::vector<std::string>s(n + 5);
    std::vector<i64>ind(30), rnd(30); //入度 出度

    for (int i = 1; i <= n; i++) {
        std::cin >> s[i]; ++rnd[s[i][0] - 'a' + 1];
        ++ind[s[i].back() - 'a' + 1];
        i64 u = s[i][0] - 'a' + 1;
        i64 v = s[i].back() - 'a' + 1;
        addedge(u, v, i);
    }
    i64 cnt1 = 0, cnt2 = 0;


    for (i64 i = 1; i <= 26; i++) {
        if (ind[i] == rnd[i] + 1)cnt1++;
        else if (rnd[i] == ind[i] + 1)cnt2++;
        else if (ind[i] != rnd[i]) {
            puts("***"); return 0;
        }
    }

    if (not ((cnt1 == 1 and cnt2 == 1) or (cnt1 == 0 and cnt2 == 0))) {
        puts("***"); return 0;
    }

    for (i64 i = 1; i <= 26; i++) {
        std::sort(g[i].begin(), g[i].end(), [&](auto x, auto y)->bool{
            return s[x.second] < s[y.second];
        });
    }

    // 有向图中欧拉路出现的两种情况
    bool f = (cnt1 == 1 and cnt2 == 1) ? 1 : 0;
    std::vector<bool>vis(n + 1, false);
    std::function<void(i64, string, i64)>dfs = [&](i64 u, string cur, i64 cnt) {
        if (cnt == n) {
            cur.pop_back();
            std::cout << cur;
            std::exit(0);
        }
        for (auto [v, idx] : g[u]) {
            if (not vis[idx]) {
                vis[idx] = true;
                dfs(v, cur + s[idx] + '.', cnt + 1);
                vis[idx] = false;
            }
        }
    };

    if (f) {
        bool z = true;
        for (i64 i = 1; i <= 26; i++) {

            if (rnd[i] == ind[i] + 1) {
                z = false;
                dfs(i, "", 0);
            }
            if (not z) {
                puts("***"); return 0;
            }
        }
    } else {
        bool z = true;
        for (i64 i = 1; i <= 26; i++) {
            if (rnd[i] and ind[i]) {
                z = false;
                dfs(i, "", 0);
            }
           if (not z) {
                puts("***"); return 0;
            }
        }
    }

    puts("***");
    return 0;
}