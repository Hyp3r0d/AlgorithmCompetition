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






/*多项式欧几里得*/
int main() {
	auto qpow = [&](i64 u, i64 v, i64 m) {
		i64 ret = 1;
		while (v) {
			if (v & 1)ret = ret % m * u % m;
			u = u % m * u % m;
			v >>= 1;
		}
		return ret % m;
	};
	auto inv = [&](i64 u, i64 m) {
		return qpow(u, m - 2, m) % m;
	};
	i64 cnt = 0;
	i64 n;

	while (std::cin >> n) {

		if (not n)break;

		std::function<deque<i64>(deque<i64>, deque<i64>)>Polygcd = [&](deque<i64>x, deque<i64>y)->deque<i64> {
			if (x.size() < y.size())x.swap(y);
			i64 deg1 = x.size() - 1, deg2 = y.size() - 1;
			if (not y.size())return x;
			else {
				for (i64 i = deg1; i >= deg2; i--) {
					i64 f = x[i] * inv(y[deg2], n) % n;
					i64 dis = i - deg2;
					for (i64 j = i; j >= dis; j--) {
						x[j] -= f * y[j - dis];
						x[j] = (x[j] % n + n) % n;
					}
				}
			}
			while (x.size() and not x.back())x.pop_back();
			for (auto &v : x) {
				v = (v % n + n) % n;
			}
			for (auto &v : y) {
				v = (v % n + n) % n;
			}
			return Polygcd(y, x);
		};

		i64 deg; std::cin >> deg;
		std::deque<i64>x(deg + 1);
		for (i64 i = 0; i <= deg; i++)std::cin >> x[i], x[i] = (x[i] % n);
		std::cin >> deg;
		std::deque<i64>y(deg + 1);
		for (i64 j = 0; j <= deg; j++)std::cin >> y[j], y[j] %= n;
		auto ans = Polygcd(x, y);
		cnt++;
		printf("Case %lld: %lld ", cnt, ans.size() - 1);
		for (i64 i = 0; i < ans.size(); i++) {
			std::cout << ans[i] << " \n"[i == ans.size() - 1];
		}
	}
}