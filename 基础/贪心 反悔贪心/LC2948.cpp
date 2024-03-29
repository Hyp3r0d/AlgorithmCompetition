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

constexpr i64 mod = 999911659;
constexpr i64 maxn = 2e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

class Solution {
public:
	vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
		int n = nums.size();
		std::vector<int>idx(n);
		std::iota(idx.begin(), idx.end(), 0);
		std::sort(idx.begin(), idx.end(), [&](int x, int y)->bool{
			return nums[x] < nums[y];
		});
		std::vector<int>ans(n);
		for (int i = 0; i < n;) {
			int st = i; i++;
			while (i < n && nums[idx[i]] - nums[idx[i - 1]] <= limit)i++;
			std::vector<int>id(idx.begin() + st, idx.begin() + i);
			std::sort(id.begin(), id.end());
			for (int j = 0; j < id.size(); j++) {
				ans[id[j]] = nums[idx[st + j]];
			}
		}
		return ans;
	}
};