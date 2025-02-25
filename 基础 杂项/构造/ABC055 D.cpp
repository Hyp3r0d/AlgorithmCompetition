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
	i64 n; std::cin >> n;
	string s; std::cin >> s; s = " " + s;
	string ans(n + 1, ' ');
	auto check = [&](vector<int>v) {
		//  1 sheep 0 wolf
		for (int i = 2; i <= n - 1; i++) {
			if (s[i] == 'o') {
				if (v[i] == 1) {
					v[i + 1] = v[i - 1];
				} else {
					v[i + 1] = 1 - v[i - 1];
				}
			} else {
				if (v[i] == 1) {
					v[i + 1] = 1 - v[i - 1];
				} else {
					v[i + 1] = v[i - 1];
				}
			}
		}
		bool f = true;
		if (v[0] == 1) {
			if (s[1] == 'o') {
				if (v[2] != v[n])f = false;
			} else {
				if (v[2] == v[n])f = false;
			}
		} else {
			if (s[1] == 'o') {
				if (v[2] == v[n])f = false;
			} else {
				if (v[2] != v[n])f = false;
			}
		}
		if (v[n] == 1) {
			if (s[n] == 'o') {
				if (v[n - 1] != v[1])f = false;
			} else {
				if (v[n - 1] == v[1])f = false;
			}
		} else {
			if (s[n] == 'o') {
				if (v[n - 1] == v[1])f = false;
			} else {
				if (v[n - 1] != v[1])f = false;
			}
		}
		if (f) {
			string res = "";
			for (int i = 1; i <= n; i++) {
				if (v[i] == 1)res += 'S';
				else res += 'W';
			}
			std::cout << res << "\n";
			exit(0);
		}
	};
	std::vector<int>v(n + 1);
	v[1] = 0; v[2] = 0;
	check(v);
	v[1] = 0; v[2] = 1;
	check(v);
	v[1] = 1; v[2] = 0;
	check(v);
	v[1] = 1; v[2] = 1;
	check(v);
	puts("-1");
	return 0;
}