#include<bits/extc++.h>


using i64 = signed long long;

using namespace std;

constexpr i64 maxn = 4e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


int main() {
	i64 n; std::cin >> n;
	std::map<array<i64, 3>, i64>dp;
	string s = to_string(n); i64 m = s.size();
	i64 mod = 1;
	std::function<i64(i64, i64, i64, i64, i64)>dfs = [&](i64 idx, i64 stt, i64 now, i64 isnum, i64 islimit) {
		if (idx == m) {
			return (i64)(isnum and (stt == mod) and now == 0);
		}
		if (not islimit and isnum and dp.count({idx, stt, now}))return dp[ {idx, stt, now}];
		i64 res = 0;
		if (not isnum)res += dfs(idx + 1, stt, now, false, false);
		i64 low = isnum ? 0 : 1;
		i64 up = islimit ? s[idx] - '0' : 9;
		for (i64 d = low; d <= up; d++) {
			res += dfs(idx + 1, stt + d, (now * 10 + d) % mod, true, islimit and d == up);
		}
		if (not islimit and isnum)dp[ {idx, stt, now}] = res;
		return res;
	};
	i64 ret = 0;
	for (mod = 1; mod <= 9 * m; mod++) {
		dp.clear();
		ret += dfs(0, 0, 0, false, true);
	}
	std::cout << ret << "\n";
}
