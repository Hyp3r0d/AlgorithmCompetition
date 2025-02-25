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

class MajorityChecker {
public:
	std::vector<int>arr;
	std::unordered_map<int, std::vector<int>>loc;
	mt19937 gen{random_device{}()};
	MajorityChecker(vector<int>& arr): arr(arr) {
		for (int i = 0; i < arr.size(); i++) {
			loc[arr[i]].push_back(i);
		}
	}

	int query(int left, int right, int threshold) {
		int len = right - left + 1;
		uniform_int_distribution<int>dis(left, right);
		for (int i = 0; i < 20; i++) {
			int x = arr[dis(gen)];
			vector<int>pos = loc[x];
			int occ = upper_bound(pos.begin(), pos.end(), right) -
			          lower_bound(pos.begin(), pos.end(), left);
			if (occ >= threshold) {
				return x;
			} else if (occ * 2 >= len) {
				return -1;
			}
		}
		return -1;
	}
};