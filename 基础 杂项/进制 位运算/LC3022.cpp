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
class Solution {
public:
	int minOrAfterOperations(vector<int>& nums, int k) {
		i64 ans = 0, mask = 0;
		for (i64 i = 29; i >= 0; i--) {
			mask |= (1 << i);
			i64 cnt = 0, res = (1 << 30) - 1;
			for (auto c : nums) {
				res &= (mask & c);
				if (res) {
					cnt++;
				} else {
					res = (1 << 30) - 1;
				}
			}
			if (cnt > k) {
				ans |= (1 << i);
				mask ^= (1 << i);
			}
		}
		return (int)ans;
	}
};