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
constexpr i64 maxn = 4e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

class Solution {
public:
	long long incremovableSubarrayCount(vector<int>& nums) {
		i64 n = nums.size();
		nums.insert(nums.begin(), 0);
		i64 l = 1, r = n;
		while (l + 1 <= n and nums[l + 1] > nums[l])l++;
		while (r - 1 >= 1 and nums[r - 1] < nums[r])r--;


		if (r == 1) {
			return (1 + n) * n / 2;
		}

		i64 ans = 0;
		for (i64 i = 0; i <= l; i++) {

			i64 idx = upper_bound(nums.begin() + r, nums.begin() + 1 + n, nums[i]) - nums.begin();
			ans += (n - idx + 2);
		}
		
		return ans;
	}
};