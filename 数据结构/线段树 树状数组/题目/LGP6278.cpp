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

constexpr i64 mod = 1e9 + 7;
constexpr i64 maxn = 5e2 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

template<typename T>
struct FenwickTree {

public:
	std::vector<T>tr; int n;

	FenwickTree(int n): tr(n + 5), n(n) {}

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
	int n; std::cin >> n;
	std::vector<int>a(n + 1);
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i]; a[i] += 1;
	}
	std::vector<i64>cnt(n + 5);
	FenwickTree<i64>tr(n + 5);
	for (i64 i = 1; i <= n; i++) {
		cnt[a[i]] += i - 1 - tr.query(a[i]);
		tr.modify(a[i], 1);
	}
	i64 ans = 0;
	for (i64 i = 1; i <= n; i++) {
		std::cout << ans << "\n";
		ans += t[i];
	}
	return 0;
}