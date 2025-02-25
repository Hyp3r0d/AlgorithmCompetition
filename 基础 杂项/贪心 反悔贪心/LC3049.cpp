
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
	int earliestSecondToMarkIndices(vector<int>& nums, vector<int>& changeIndices) {
		int n = nums.size();
		int m = changeIndices.size();
		i64 total = n + accumulate(nums.begin(), nums.end(), 0ll);
		std::vector<i64>f(n, -1);
		for (i64 t = m - 1; t >= 0; t--) {
			f[changeIndices[t] - 1] = t;
		}
		auto check = [&](i64 x) {
			i64 cnt = 0;
			i64 slow = total;
			priority_queue<int, std::vector<int>, greater<>>pq;
			for (i64 t = x - 1; t >= 0; t--) {
				i64 i = changeIndices[t] - 1;
				i64 v = nums[i];
				if (v <= 1 or t != f[i]) {
					cnt++; continue;
				}
				if (cnt == 0) {
					if (pq.empty() or v <= pq.top()) {
						cnt++; continue;
					}
					slow += pq.top() + 1;
					pq.pop(); cnt += 2;
				}
				slow -= v + 1;
				cnt--; pq.push(v);
			}
			return cnt >= slow;
		};
		i64 l = n - 1, r = m + 1;
		while (l < r) {
			i64 mid = (l + r) >> 1;
			if (check(mid))r = mid;
			else l = mid + 1;
		}
		return r > m ? -1 : r;
	}
};