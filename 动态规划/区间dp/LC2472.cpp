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
    int maxPalindromes(string s, int k) {
        i64 n = s.size();
        s = " " + s;
        std::vector isPalindrome(n + 1, std::vector<bool>(n + 1, false));
        for (i64 i = 1; i <= n; i++) {
            isPalindrome[i][i] = true;
            if (i <= n - 1 and s[i] == s[i + 1]) {
                isPalindrome[i][i + 1] = true;
            }
        }
        for (i64 len = 3; len <= n; len++) {
            for (i64 i = 1; i + len - 1 <= n; i++) {
                isPalindrome[i][i + len - 1] = isPalindrome[i + 1][i + len - 2] && (s[i] == s[i + len - 1]);
            }
        }
        std::vector<i64>dp(n + 1);
        for (i64 i = 1; i <= n; i++) {
            dp[i] = std::max(dp[i], dp[i - 1]);
            for (i64 j = i - k; j >= 0; j--) {
                if (isPalindrome[j + 1][i] == true) {
                    dp[i] = std::max(dp[i], dp[j] + 1);
                }
            }
        }
        return dp[n];
    }
};