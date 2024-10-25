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


struct cmp {
	bool operator()(const int&x, const int&y)const {
		return x < y;
	}
};

class Solution {
public:

	int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
		stations.push_back(vector<int> {target, 0});
		int ans = 0, pre = 0;
		std::priority_queue<int, vector<int>, cmp>pq;
		for (auto station : stations) {
			i64 x = station[0], y = station[1];
			startFuel -= x - pre;
			pre = x;
			while (pq.size() and startFuel < 0) {
				startFuel += pq.top();
				pq.pop();
				ans++;
			}
			if (startFuel < 0) {
				return -1;
			}
			pq.push(y);
		}
		return ans;
	}
};