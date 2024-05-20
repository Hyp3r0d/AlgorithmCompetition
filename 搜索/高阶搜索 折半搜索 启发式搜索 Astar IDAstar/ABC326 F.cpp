/*折半搜索*/
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
constexpr i64 maxn = 2e2 + 10;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


/*  折半搜索 + 双指针*/

int main() {
    i64 n, X, Y; std::cin >> n >> X >> Y;
    vector<i64>a(n + 1);
    for (i64 i = 1; i <= n; i++)std::cin >> a[i];

    vector<i64>f1, f2;


    for (i64 i = 1; i <= n; i++) {
        if (i & 1)f2.push_back(a[i]);
        else f1.push_back(a[i]);
    }

    vector<vector<pair<i64, string>>>h1(2), h2(2);


    // 正为 0, 负为 1
    std::function<void(vector<i64>, vector<pair<i64, string>>&, i64, i64, i64, i64, string)>dfs = [&](vector<i64>x, vector<pair<i64, string>>&y, i64 len, i64 pad, i64 idx, i64 sum, string path) {
        if (idx == len) {
            y.push_back({sum, path}); return;
        }
        dfs(x, y, len, pad, idx + 1, sum + x[pad + idx], path + "0");
        dfs(x, y, len, pad, idx + 1, sum - x[pad + idx], path + "1");
    };

    i64 len1 = f1.size() / 2, len2 = f1.size() - len1;

    dfs(f1, h1[0], len1, 0, 0, 0, "");
    dfs(f1, h1[1], len2, len1, 0, 0, "");
    len1 = f2.size() / 2, len2 = f2.size() - len1;
    dfs(f2, h2[0], len1, 0, 0, 0, "");
    dfs(f2, h2[1], len2, len1, 0, 0, "");


    // 双指针

    bool flag1 = false, flag2 = false;

    auto cmp = [&](pair<i64, string>x, pair<i64, string>y)->bool{
        return x.first < y.first;
    };
    string ans1, ans2;
    if (h1[0].size() == 0)h1[0].push_back({0, ""});
    std::sort(h1[0].begin(), h1[0].end(), cmp);
    if (h1[1].size() == 0)h1[1].push_back({0, ""});
    std::sort(h1[1].begin(), h1[1].end(), cmp);
    if (h2[0].size() == 0)h2[0].push_back({0, ""});
    std::sort(h2[0].begin(), h2[0].end(), cmp);
    if (h2[1].size() == 0)h2[1].push_back({0, ""});
    std::sort(h2[1].begin(), h2[1].end(), cmp);
    for (i64 i = 0; i < h1[0].size(); i++) {
        i64 idx = lower_bound(h1[1].begin(), h1[1].end(), X - h1[0][i].first, [&](pair<i64, string>x, i64 y)->bool{
            return x.first < y;
        }) - h1[1].begin();
        if (idx >= 0 and idx < h1[1].size()) {
            if (h1[1][idx].first + h1[0][i].first == X) {
                ans1 = h1[1][idx].second + h1[0][i].second;
                flag1 = true; break;
            }
        }
    }


    for (i64 i = 0; i < h2[0].size(); i++) {
        i64 idx = lower_bound(h2[1].begin(), h2[1].end(), Y - h2[0][i].first, [&](pair<i64, string>x, i64 y)->bool{
            return x.first < y;
        }) - h2[1].begin();
        if (idx >= 0 and idx < h2[1].size()) {
            if (h2[1][idx].first + h2[0][i].first == Y) {
                ans2 = h2[1][idx].second + h2[0][i].second;
                flag2 = true; break;
            }
        }
    }


    string tot = "";
    for (i64 i = 0; i < ans2.size(); i++) {
        tot += ans2[i];
        if (i < ans1.size())tot += ans1[i];
    }
    //std::cout << tot << "\n";
    string p = "";
    int pre = 0;
    for (i64 i = 0; i < tot.size(); i++) {
        i64 cur = tot[i] - '0';
        if (i % 2 == 0) {
            p += ((cur ^ pre) == 0) ? 'L' : 'R';
        } else {
            p += ((cur ^ pre) == 0) ? 'R' : 'L';
        }
        pre = cur;
    }

    if (flag1 and flag2) {
        puts("Yes");


        std::cout << p << "\n";
    } else puts("No");
}