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


int main() {
	std::vector<i64>z;
	i64 n; std::cin >> n;
	for (i64 i = 0; i < n; i++) {
		i64 v; std::cin >> v;
		z.push_back(v);
	}

	// 异或过后数组中最大值可能的最小值
	std::function<i64(i64, vector<i64>)>dfs = [&](i64 cur, vector<i64>v)->i64 {
		if (cur == -1)return 0ll;
		vector<i64>s, t;
		for (auto w : v) {
			if ((w >> cur) & 1)s.push_back(w);
			else t.push_back(w);
		}
		// 贪心策略，尽量让该位为 0
		if (not s.size())return dfs(cur - 1, t); // 该位可以为0
		else if (not t.size())return dfs(cur - 1, s);
		else{
			return std::min(dfs(cur - 1, s), dfs(cur - 1, t)) | (1 << cur); // 前边的位确定了, 这一位必须为1 ,选择比较小的那一个决策方案
		}
	};
	std::cout << dfs(30, z) << "\n";
}