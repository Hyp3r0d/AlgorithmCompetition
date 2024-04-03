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


std::vector<i64> PrefixFunction(string s) {
	i64 len = s.size();
	std::vector<i64>p(len + 5, 0);
	for (i64 i = 1; i < len; i++) {
		i64 j = p[i - 1];
		while (j > 0 and s[i] != s[j])j = p[j - 1];
		if (s[i] == s[j])j++;
		p[i] = j;
	}//KMP函数板题
	return p;
}

int main() {
	i64 n; string t; std::cin >> n >> t;
	string tmp = t; reverse(tmp.begin(), tmp.end());
	string tmp1 = t + tmp;
	auto prefix1 = PrefixFunction(tmp1);
	string tmp2 = tmp + t;
	auto prefix2 = PrefixFunction(tmp2);
	string ans = "";
	for (int i = 0; i <= n; i++) {
		if (prefix1[3 * n - 1] >= i and prefix2[3 * n - 1] >= n - i) {
			for (int j = 0; j < i; j++)ans.push_back(t[j]);
			for (int j = n + i; j < n * 2; j++)ans.push_back(t[j]);
			std::cout << ans << "\n";
			std::cout << i << "\n";
			return 0;
		}
	}
	puts("-1");
	return 0;
}