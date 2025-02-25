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
const i64 mod = 998244353;
const i64 maxn = 2e5 + 5;
const i64 inf = 0x3f3f3f3f3f3f3f3f;


int main() {
	i64 n; std::cin >> n;
	std::vector<i64>A(n + 1), pre(n + 1);

	for (i64 i = 1; i <= n; i++) {
		std::cin >> A[i]; pre[i] = A[i] ^ pre[i - 1];
	}

	std::vector sum(35, std::array<i64, 2> {0, 0});
	for (i64 i = 0; i <= 31; i++)sum[i][0] += 1;
	i64 ans = 0;
	for (i64 i = 2; i <= n; i++) {
		for (i64 j = 0; j <= 31; j++) {
			i64 z = (pre[i] >> j) & 1;
			i64 cnt = sum[j][z ^ 1];
			ans += (1ll << j) * cnt;
			z = (pre[i - 1] >> j) & 1;
			sum[j][z] += 1;
		}
	}
	std::cout << ans << "\n";
}