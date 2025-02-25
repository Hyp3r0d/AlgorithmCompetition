

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
const i64 maxn = 1e7 + 5;
const i64 inf = 0x3f3f3f3f3f3f3f3f;


struct Node {
    i64 to[2]; i64 cnt = 0;
};
std::vector<Node>tr;

int main() {
    tr.push_back(Node());
    i64 n, k; std::cin >> n >> k;
    std::vector<i64>a(n + 5);
    for (i64 i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    auto insert = [&](i64 x) {
        i64 u = 0;
        for (i64 i = 21; i >= 0; i--) {
            i64 cur = ((x >> i) & 1);
            if (not tr[u].to[cur]) {
                tr[u].to[cur] = tr.size();
                tr.push_back(Node());
            }
            u = tr[u].to[cur];
            tr[u].cnt++;
        }
    };
    auto query = [&](i64 x) {
        i64 ret = 0; i64 u = 0; bool flag = false;
        for (i64 i = 21; i >= 0; i--) {
            i64 cur = (x >> i) & 1;
            i64 t = (k >> i) & 1;
            if (t == 1)if (tr[u].to[cur])ret += tr[tr[u].to[cur]].cnt;
            if (not tr[u].to[cur ^ t]) {
                flag = true; break;
            }
            u = tr[u].to[cur ^ t];
        }
        if (not flag)
            ret += tr[u].cnt;
        return ret;
    };
    for (i64 i = 1; i <= n; i++)insert(a[i]);
    i64 ans = 0;
    for (i64 i = 0; i <= 3000000; i++) {
        ans = std::max(ans, query(i));
    }
    std::cout << ans << "\n";
    return 0;
}