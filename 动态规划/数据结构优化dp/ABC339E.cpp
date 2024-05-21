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


template<typename T>
struct SegmentTree {

public:
	/*双懒惰标记线段树*/
	struct Node {
		i64 l; i64 r; T mx;
	};

	std::vector<Node>tr; i64 n;

	SegmentTree(i64 n): tr(4 * n + 10), n(n) {}

	void pushUp(i64 p) {
		tr[p].mx = std::max(tr[p << 1].mx, tr[p << 1 | 1].mx);
	}

	void build(i64 p, i64 l, i64 r, std::vector<T>&a) {
		tr[p].l = l; tr[p].r = r;
		tr[p].mx = 0;
		if (l == r) {
			tr[p].mx = a[l];
			return;
		}
		i64 mid = (l + r) >> 1;
		build(p << 1, l, mid, a);
		build(p << 1 | 1, mid + 1, r, a);
		pushUp(p);
	}


	void modify(i64 p, i64 idx, T val) { // 修改为 x
		if (tr[p].l == tr[p].r) {
			tr[p].mx = max(tr[p].mx, val);
			return;
		}
		i64 mid = (tr[p].l + tr[p].r) >> 1;
		if (idx > mid) {
			modify(p << 1 | 1, idx, val);
		}
		if (idx <= mid) {
			modify(p << 1, idx, val);
		}
		pushUp(p);
	}



	T query(i64 p, i64 l, i64 r) {
		if (tr[p].l >= l and tr[p].r <= r) {
			return tr[p].mx;
		}
		T ret = -inf; i64 mid = (tr[p].l + tr[p].r) >> 1;
		if (r > mid) {
			ret = std::max(ret, query(p << 1 | 1, l, r));
		}
		if (l <= mid) {
			ret = std::max(ret, query(p << 1, l, r));
		}
		return ret;
	}

};

int main() {
	i64 n, d; std::cin >> n >> d;
	std::vector<i64>a(n + 1);
	for (i64 i = 1; i <= n; i++) {
		std::cin >> a[i];
	}
	i64 mx = *std::max_element(a.begin() + 1, a.begin() + 1 + n);
	SegmentTree<i64>tr(mx + 5);
	vector<i64>z(mx + 1, 0);
	tr.build(1, 1, mx, z);
	i64 ans = 1;
	tr.modify(1, a[1], 1);
	for (i64 i = 2; i <= n; i++) {
		i64 l = max(1ll, a[i] - d);
		i64 r = min(mx, a[i] + d);
		i64 v = tr.query(1, l, r);
		ans = std::max(ans, v + 1);
		tr.modify(1, a[i], v + 1);
	}
	std::cout << ans << "\n";
}