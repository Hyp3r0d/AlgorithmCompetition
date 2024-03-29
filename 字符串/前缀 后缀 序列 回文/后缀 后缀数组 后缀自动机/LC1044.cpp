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


const i64 mod = 1e9 + 7;
const i64 maxn = 3e4 + 5;
const i64 inf = 0x3f3f3f3f3f3f3f3f;


// 维护sa rk height数组
// sa[i] 排名为 i 的后缀编号
// rk[i] 后缀编号为 i 的排名
// height[i] sa[i] 与 sa[i - 1]的最长公共前缀



struct SuffixArray {
public:
    i64 n; std::vector<i64>sa, height, oldrk, rk, id, key1, cnt;
    SuffixArray(i64 n, string s): sa(2 * n + 1), n(n), height(2 * n + 1), oldrk(2 * n + 1), rk(2 * n + 1), id(2 * n + 1), key1(2 * n + 1), cnt(100010) {
        init(s);
    }
    void init(string s) {
        auto cmp = [&](i64 x, i64 y, i64 w) {
            return oldrk[x] == oldrk[y] and oldrk[x + w] == oldrk[y + w];
        };
        /*m 为 字符值的范围 */
        i64 m = 127; i64 p, w, i, j;
        for (i = 1; i <= n; i++)++cnt[rk[i] = s[i]];
        for (i = 1; i <= m; i++)cnt[i] += cnt[i - 1];
        for (i = n; i >= 1; i--)sa[cnt[rk[i]]--] = i;//计数排序
        for (w = 1;; w <<= 1, m = p) {
            for (p = 0, i = n; i > n - w; --i)id[++p] = i;
            for (i = 1; i <= n; i++) {
                if (sa[i] > w)id[++p] = sa[i] - w;
            }
            std::fill(cnt.begin(), cnt.end(), 0);
            for (i = 1; i <= n; i++) {
                ++cnt[key1[i] = rk[id[i]]];
            }
            for (i = 1; i <= m; i++)cnt[i] += cnt[i - 1];
            for (i = n; i >= 1; i--)sa[cnt[key1[i]]--] = id[i];
            for (i = 1; i <= n; i++) {
                oldrk[i] = rk[i];
            }
            for (p = 0, i = 1; i <= n; i++) {
                rk[sa[i]] = cmp(sa[i], sa[i - 1], w) ? p : ++p;
            }
            if (p == n) {
                for (i = 1; i <= n; i++)sa[rk[i]] = i;
                break;
            }
        }
        for (i = 1, j = 0; i <= n; i++) {
            if (j)--j;
            while (s[i + j] == s[sa[rk[i] - 1] + j])++j;
            height[rk[i]] = j;
        }
    }
};


class Solution {
public:
    
    string longestDupSubstring(string s) {
        i64 n = s.size();
        s = " " + s;

        SuffixArray sa(n, s);

        i64 mx = 0; i64 idx = -1;
       
        for (i64 i = 1; i <= n; i++) {
            if (sa.height[i] > mx) {
                mx = sa.height[i];
                idx = sa.sa[i];
            }
        }
        return mx == 0 ? "" : s.substr(idx, mx);
    }
};