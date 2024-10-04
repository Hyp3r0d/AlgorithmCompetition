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
const i64 mod = 1e9 + 7;
const i64 maxn = 2e5 + 5;
const i64 inf = 0x3f3f3f3f3f3f3f3f;


struct Node {
	i64 id; i64 num;
} a[maxn];



int main() {

	i64 n, m, k; std::cin >> n >> m >> k;
	for (i64 i = 1; i <= n; i++) {
		std::cin >> a[i].num; a[i].id = i;
		k -= a[i].num;
	}
	std::sort(a + 1, a + 1 + n, [&](Node x, Node y)->bool{
		return x.num > y.num;
	});
	std::vector<i64>b(n + 1);
	std::vector<i64>pre(n + 1);
	for (i64 i = 1; i <= n; i++) {
		pre[i] = pre[i - 1] + a[i].num;
		b[i] = a[n - i + 1].num;
	}
	auto check = [&](i64 mid, i64 pos) {
		i64 x = upper_bound(b.begin() + 1, b.begin() + 1 + n, a[pos].num + mid) - b.begin();
		i64 y = n - x + 1; y = std::min(y, m);
		i64 res = (pos > m) ? pre[m] : pre[m + 1] - a[pos].num;
		res -= pre[y];
		res = (m - y) * (a[pos].num + mid + 1) - res;
		return k - mid < res;
	};
	std::vector<i64>res(n + 1);
	for (i64 i = 1; i <= n; i++) {
		i64 l = 0, r = 1e10, ans = -1;
		while (l <= r) {
			i64 mid = (l + r) >> 1;
			if (check(mid, i)) {
				ans = mid; r = mid - 1;
			} else l = mid + 1;
		}
		res[a[i].id] = ans;
	}
	for (i64 i = 1; i <= n; i++) {
		std::cout << res[i] << " \n"[i == n];
	}
	return 0;
}