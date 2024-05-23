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
const i64 mod = 1e9 + 7;
const i64 maxn = 1e6 + 5;
const i64 inf = 0x3f3f3f3f3f3f3f3f;


i64 a[maxn];
struct SegmentTree {
    struct Node {
        i64 l; i64 r;
        i64 mx; i64 laz;
    };
    vector<Node>tr;
    SegmentTree(i64 n): tr(4 * n + 10) {}
    void pushup(i64 p) {
        tr[p].mx = max(tr[p << 1].mx, tr[p << 1 | 1].mx);
    }
    void pushdown(i64 p) {
        if (tr[p].laz) {
            i64 laz = tr[p].laz;
            tr[p].laz = 0;
            tr[p << 1].laz += laz;
            tr[p << 1].mx += laz;
            tr[p << 1 | 1].laz += laz;
            tr[p << 1 | 1].mx += laz;
        }
    }
    void build(i64 p, i64 l, i64 r, vector<i64>f) {
        tr[p].l = l; tr[p].r = r; tr[p].mx = tr[p].laz = 0;
        if (l == r) {
            tr[p].mx = f[l];
            return;
        }
        i64 mid = (l + r) >> 1;
        build(p << 1, l, mid, f);
        build(p << 1 | 1, mid + 1, r, f);
        pushup(p);
    }
    void modify(i64 p, i64 l, i64 r, i64 v) {
        if (l > r)return;
        if (tr[p].l >= l and tr[p].r <= r) {
            tr[p].mx += v; tr[p].laz += v;
            return;
        }
        i64 mid = (tr[p].l + tr[p].r) >> 1;
        pushdown(p);
        if (l <= mid)modify(p << 1, l, r, v);
        if (r > mid)modify(p << 1 | 1, l, r, v);
        pushup(p);
    }
    i64 query(i64 p, i64 l, i64 r) {
        if (l > r)return 0ll;
        if (tr[p].l >= l and tr[p].r <= r) {
            return tr[p].mx;
        }
        i64 ret = 0;
        pushdown(p);
        i64 mid = (tr[p].l + tr[p].r) >> 1;
        if (l <= mid)ret = max(ret, query(p << 1, l, r));
        if (r > mid)ret = max(ret, query(p << 1 | 1, l, r));
        return ret;
    }
};
void solve() {
    i64 n, k; std::cin >> n >> k;

    for (i64 i = 1; i <= n; i++)std::cin >> a[i];
    vector<i64>p(n + 5), pre(n + 5);
    for (i64 i = 1; i <= n; i++) {
        pre[i] = p[a[i]];
        p[a[i]] = i;
    }

    SegmentTree tr(n);
    vector<i64>dp(n + 1);
    for (i64 i = 1; i <= k; i++) {
        tr.build(1, 1, n, dp); std::vector<i64>ndp(n + 1, 0);
        i64 zero = 0;
        for (i64 j = 1; j <= n; j++) {
            i64 cur = pre[j];
            if (cur == 0) {
                zero += 1;
                tr.modify(1, 1, j - 1, 1);
                ndp[j] = std::max(ndp[j], zero);
                ndp[j] = std::max(ndp[j], tr.query(1, 1, j - 1));
            } else {
                tr.modify(1, cur, j - 1, 1);
                ndp[j] = std::max(ndp[j], zero);
                ndp[j] = std::max(ndp[j], tr.query(1, 1, j - 1));
            }
        }
        dp = ndp;
    }
    std::cout << dp[n] << "\n";


}
int main() {
    solve();
}