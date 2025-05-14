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
constexpr f64 eps = 1e-7;


int main() {
	i64 n, t;
	std::cin >> n >> t;
	std::vector<i64>stk;
	std::vector<i64>a(n + 1);
	for (i64 i = 1; i <= n; i++)std::cin >> a[i];
	std::vector nxt(n + 1, std::vector<i64>(25, 0));
	std::vector w(n + 1, std::vector<i64>(25, 0));
	for (i64 i = 1; i <= n; i++) {
		while (stk.size() and a[stk.back()] < a[i]) {
			nxt[stk.back()][0] = i;
			w[stk.back()][0] = a[i] + (i - stk.back() - 1) * a[stk.back()];
			stk.pop_back();
		}
		stk.push_back(i);
	}
	for (i64 i = 1; i <= 24; i++) {
		for (i64 j = n; j >= 1; j--) {
			if (nxt[j][i - 1]) {
				nxt[j][i] = nxt[nxt[j][i - 1]][i - 1];
				w[j][i] = w[nxt[j][i - 1]][i - 1] + w[j][i - 1];
			}
		}
	}
	i64 prev = 0;
	while (t--) {
		i64 u, v; std::cin >> u >> v;
		i64 l = 1 + (u ^ prev) % n;
		i64 q = 1 + (v ^ (prev + 1)) % (n - l + 1);
		i64 cur = l;
		i64 ans = a[l];
		for (i64 i = 24; i >= 0; i--) {
			if (not nxt[cur][i])continue;
			if (nxt[cur][i] <= l + q - 1)ans += w[cur][i], cur = nxt[cur][i];
		}
		ans += (l + q - 1 - cur) * a[cur];
		std::cout << ans << "\n";
		prev = ans;
	}
}