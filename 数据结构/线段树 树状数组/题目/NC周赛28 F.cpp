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

constexpr i64 mod = 998244353;
constexpr i64 maxn = 4e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

template<typename T>
struct FenwickTree {

public:
	std::vector<T>tr; i64 n;

	FenwickTree(i64 n): tr(n + 5), n(n) {}

	FenwickTree() {}

	void init(int n) {
		this -> n = n; tr.assign(n + 5, 0);
	}

	T query(int idx) {
		T ret = 0;
		for (; idx > 0; idx -= (idx & -idx)) {
			ret += tr[idx];
		}
		return ret;
	}

	void modify(int idx, T v) {
		for (; idx <= this -> n; idx += (idx & -idx)) {
			tr[idx] += v;
		}
	}

	T queryRange(int l, int r) {
		return query(r) - query(l - 1);
	}
};
int main() {
	i64 n, k; std::cin >> n >> k;
	std::vector<i64>a(n + 1);
	for (i64 i = 1; i <= n; i++) {
		std::cin >> a[i];
	}
	for (i64 i = 1; i <= n; i++) {
		a[i] += a[i - 1];
	}
	std::vector<i64>z(1);
	for (i64 i = 0; i <= n; i++) {
		z.push_back(a[i]);
	}
	i64 ans = 0;
	std::sort(z.begin() + 1, z.end());
	z.erase(std::unique(z.begin() + 1, z.end()), z.end());
	FenwickTree<i64>tr(z.size());
	i64 idx = std::lower_bound(z.begin() + 1, z.end(), 0ll) - z.begin();
	tr.modify(idx, 1);
	for (i64 i = 1; i < a.size(); i++) {
		i64 idx = upper_bound(z.begin() + 1, z.end(), a[i] - k) - z.begin();
		ans += tr.query(idx - 1);
		idx = lower_bound(z.begin() + 1, z.end(), a[i]) - z.begin();
		tr.modify(idx, 1);
	}
	std::cout << ans << "\n";
	return 0;
}