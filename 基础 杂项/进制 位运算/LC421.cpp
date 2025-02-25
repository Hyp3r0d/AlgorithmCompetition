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
	int findMaximumXOR(vector<int>& nums) {
		std::unordered_set<int>st;
		int ans = 0, msk = 0;
		for (int i = 30; i >= 0; i--) {
			msk |= (1 << i);
			st.clear();
			int nxt = (ans | (1 << i));
			for (auto x : nums) {
				x &= msk;
				if (st.count(x ^ nxt)) {
					ans = nxt; break;
				}
				st.insert(x);
			}
		}
		return ans;
	}
};