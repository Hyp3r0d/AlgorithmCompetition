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
constexpr i64 maxn = 3e4 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;
i64 n, k;
struct Squre {
public:
    i64 ux, uy, dx, dy; bool use;
    int get() {
        if (not use)return 0;
        return (dx - ux) * (uy - dy);
    }
    void add(int x, int y) {
        if (not use) {
            ux = x; uy = y; dx = x; dy = y;
            use = 1;
            return;
        }
        if (ux > x)ux = x;
        if (dx < x)dx = x;
        if (uy < y)uy = y;
        if (dy > y)dy = y;
    }
    bool isInSqure(int x, int y) {
        if (x < ux or x > dx or y > uy or y < dy)return false;
        return true;
    }
    bool cross(Squre u) {
        if (not use or not u.use)return false;
        return u.isInSqure(dx, dy) or u.isInSqure(dx, uy) or u.isInSqure(ux, dy) or u.isInSqure(ux, uy);
    }
} g[5];


bool notCross() {
    for (i64 i = 1; i <= k; i++) {
        for (i64 j = i + 1; j <= k; j++) {
            if (g[i].cross(g[j]) or g[j].cross(g[i]))return false;
        }
    }
    return true;
}

pair<i64, i64>w[100];
i64 ans = inf;
void dfs(i64 area, i64 cur) {
    if (cur > n) {
        if (notCross())ans = std::min(ans, area);
        return;
    }
    Squre tmp;
    for (i64 i = 1; i <= k; i++) {
        tmp = g[i];
        g[i].add(w[cur].first, w[cur].second);
        if (notCross()) {
            if (area - tmp.get() + g[i].get() < ans) {
                dfs(area - tmp.get() + g[i].get(), cur + 1);
            }
        }
        g[i] = tmp;
    }
}
int main() {
    std::cin >> n >> k;
    for (i64 i = 1; i <= n; i++) {
        std::cin >> w[i].first >> w[i].second;
    }
    dfs(0, 1);
    std::cout << ans << "\n";
    return 0;
}