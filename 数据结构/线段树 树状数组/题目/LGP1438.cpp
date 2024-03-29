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
constexpr i64 maxn = 1e5 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


template<typename T>
struct SegmentTree {
	/*单懒标记线段树*/
public:

	struct Node {
		int l; int r; T sum; T add;
	};

	std::vector<Node>tr; int n;

	SegmentTree(int n): tr(4 * n + 4), n(n) {}

	void pushUp(int p) {
		tr[p].sum = (tr[p << 1].sum + tr[p << 1 | 1].sum);
	}

	void build(int p, int l, int r, std::vector<T>&a) {
		tr[p].l = l; tr[p].r = r;
		if (l == r) {
			tr[p].sum = a[l]; tr[p].add = 0;
			return;
		}
		int mid = (l + r) >> 1;
		build(p << 1, l, mid, a);
		build(p << 1 | 1, mid + 1, r, a);
		pushUp(p);
	}

	void pushDown(int p) {
		int l = tr[p].l, r = tr[p].r;
		int mid = (l + r) >> 1;
		T add = tr[p].add;
		tr[p << 1].sum += add * (mid - l + 1);
		tr[p << 1 | 1].sum += add * (r - mid);
		tr[p << 1].add += add;
		tr[p << 1 | 1].add += add;
		tr[p].add = 0;
	}

	void modify(int p, int l, int r, T val) {
		if (tr[p].l >= l and tr[p].r <= r) {
			tr[p].sum += (tr[p].r - tr[p].l + 1) * val;
			tr[p].add = (tr[p].add + val);
			return;
		}
		pushDown(p);
		int mid = (tr[p].l + tr[p].r) >> 1;
		if (r > mid) {
			modify(p << 1 | 1, l, r, val);
		}
		if (l <= mid) {
			modify(p << 1, l, r, val);
		}
		pushUp(p);
	}

	T query(int p, int l, int r) {
		if (tr[p].l >= l and tr[p].r <= r) {
			return tr[p].sum;
		}
		pushDown(p);
		T ret = 0; int mid = (tr[p].l + tr[p].r) >> 1;
		if (r > mid) {
			ret = (ret + query(p << 1 | 1, l, r));
		}
		if (l <= mid) {
			ret = (ret + query(p << 1, l, r));
		}
		return ret;
	}

};


int main() {
	i64 n, m; std::cin >> n >> m;
	std::vector<i64>a(n + 1);
	std::vector<i64>d(n + 1);
	for (i64 i = 1; i <= n; i++) {
		std::cin >> a[i];
		d[i] = a[i] - a[i - 1];
	}
	SegmentTree<i64>tr(n);
	tr.build(1, 1, n, d);
	while (m--) {
		i64 opt; std::cin >> opt;
		if (opt == 1) {
			i64 l, r, k, x; std::cin >> l >> r >> k >> x;
			tr.modify(1, l, l, k);
			if (r + 1 <= n)tr.modify(1, r + 1, r + 1, -k);
			if (l + 1 <= r)
				tr.modify(1, l + 1, r, x);
			if (r + 1 <= n)tr.modify(1, r + 1, r + 1, -(r - l)*x);
		} else {
			i64 p; std::cin >> p;
			std::cout  << tr.query(1, 1, p) << "\n";;
		}
	}
}