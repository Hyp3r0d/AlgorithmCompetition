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

constexpr i64 mod = 999911659;
constexpr i64 maxn = 2e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

u64 b = 13331;

u64 bw[maxn];


void init() {
	bw[0] = 1; for (i64 i = 1; i <= 2e5; i++)bw[i] = bw[i - 1] * b;
}

struct StringHash {
public:
	std::vector<u64>h;
	void init(string s) {
		i64 n = s.size(); h.assign(n + 5, 0);
		s = " " + s;
		for (i64 i = 1; i <= n; i++) {
			h[i] = h[i - 1] * b + s[i];
		}
	}
	StringHash(string s) {
		init(s);
	}
	u64 get(i64 l, i64 r) {
		return h[r] - h[l - 1] * bw[r - l + 1];
	}
};

int main() {
	i64 n; std::cin >> n; string t; std::cin >> t; string tmp = t;
	init();
	reverse(tmp.begin(), tmp.end());
	StringHash p1(t), p2(tmp);
	for (int i = 0; i <= n; i++) {
		if (p1.get(1, i) == p2.get(n - i + 1, n) and p2.get(1, n - i) == p1.get(2 * n - (n - i) + 1, 2 * n)) {
			string ans = "";
			for (int j = 0; j < i; j++)ans.push_back(t[j]);
			for (int j = n + i; j < 2 * n; j++)ans.push_back(t[j]);
			std::cout << ans << "\n";
			std::cout << i << "\n";
			return 0;
		}
	}
	puts("-1"); return 0;
}


