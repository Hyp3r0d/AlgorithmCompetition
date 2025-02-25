
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
	long long findMaximumElegance(vector<vector<int>>& items, int k) {
		int n = items.size();
		sort(items.begin(), items.end(), [&](vector<int>x, vector<int>y)->bool{
			return x[0] > y[0];
		});
		vector<int>ws; i64 tot = 0; std::set<int>st;
		i64 ans = 0;
		auto cal = [&]() {
			return (i64)(st.size() * st.size() + tot);
		};
		for (int i = 0; i < n; i++) {
			int p = items[i][0], c = items[i][1];
			if (i < k) {
				tot += p; if (st.count(c))ws.push_back(p); st.insert(c);
			} else {
				if (ws.size() and not st.count(c)) {
					tot -= ws.back(); tot += p; ws.pop_back();
					st.insert(c);
				}
			}
			ans = max(ans, cal());
		}
		return ans;
	}
};