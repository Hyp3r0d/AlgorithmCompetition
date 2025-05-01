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


// 莫比乌斯反演结论



//莫比乌斯函数
i64 Mobius[maxn]; i64 cnt = 0, prime[maxn];
bool vis[maxn];

int main() {
	Mobius[1] = 1;
	//预处理莫比乌斯函数
	for (i64 i = 2; i <= 1e5; i++) {
		if (not vis[i])prime[++cnt] = i, Mobius[i] = -1;
		for (i64 j = 1; j <= cnt and prime[j]*i <= 1e5; j++) {
			vis[prime[j]*i] = true;
			if (i % prime[j] == 0) {
				Mobius[i * prime[j]] = 0;
				break;
			} else {
				Mobius[i * prime[j]] = Mobius[i] * (-1);
			}
		}
	}
	for (i64 i = 2; i <= 1e5; i++)Mobius[i] += Mobius[i - 1];
	i64 T; std::cin >> T;
	while (T--) {
		i64 a, b, d; std::cin >> a >> b >> d;
		a = a / d, b = b / d; i64 ans = 0;
		for (i64 i = 1; i <= std::max(a, b);) {
			i64 r1 = 0, r2 = 0;
			if (i > a)r1 = std::max(a, b);
			else r1 = (a) / (a / i);
			if (i > b)r2 = std::max(a, b);
			else r2 = b / (b / i);
			i64 r = std::min(r1, r2);
			ans += (Mobius[r] - Mobius[i - 1]) * (a / i) * (b / i);
			i = r + 1;
		}
		std::cout << ans << "\n";
	}
	return 0;
}