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
constexpr i64 maxn = 1e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


i64 lp[maxn];
bool flag = false;
void init() {
	if (flag)return;
	flag = true;
	for (i64 i = 2; i <= 1e6; i++) {
		if (not lp[i]) {
			lp[i] = i;
			for (i64 j = i + i; j <= 1e6; j += i) {
				if (not lp[j])lp[j] = i;
			}
		}
	}
}

class Solution {
public:
	int minOperations(vector<int>& nums) {
		init(); i64 n = nums.size();
        for(i64 i = 2;i <= 1000;i ++) {
            std::cout << lp[i] << "\n";
        }
		std::vector<i64>dp(2, inf);
		dp[0] = 0;
        if(nums[0] != 1)dp[1] = 1;
		for (i64 i = 1; i < nums.size(); i++) {
			i64 x = nums[i]; std::vector<i64>ndp(2, inf);
			if (x >= nums[i - 1]) {
				ndp[0] = std::min(ndp[0], dp[0]);
			}
			if (x >= lp[nums[i - 1]] and nums[i - 1] != 1)ndp[0] = std::min(ndp[0], dp[1]);
			
			x = lp[x];
			if (x >= nums[i - 1])ndp[1] = std::min(ndp[1], dp[0] + 1);
			if (x >= lp[nums[i - 1]] and nums[i - 1] != 1)ndp[1] = std::min(ndp[1], dp[1] + 1);
			dp = ndp;
		}
		if (dp[0] == inf and dp[1] == inf)return -1;
		return std::min(dp[0], dp[1]);
	}
};