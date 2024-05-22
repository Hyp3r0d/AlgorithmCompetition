/*二维树状数组: 第二种满足区间操作的轻量级数据结构*/
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

void solve() {
	i64 n, m;
	std::cin >> n >> m; vector<i64>A(n + 5, 0);
	for (i64 i = 1; i <= n; i++)std::cin >> A[i];
	vector<i64>tr1(n + 5, 0);
	vector<i64>tr2(n + 5, 0);
	auto add1 = [&](i64 idx, i64 v) {
		for (; idx <= n; idx += (idx & -idx)) {
			tr1[idx] += v;
		}
	};
	auto add2 = [&](i64 idx, i64 v) {
		i64 s = idx * v;
		for (; idx <= n; idx += (idx & -idx)) {
			tr2[idx] += s;
		}
	};
	auto query1 = [&](i64 idx) {
		i64 ret = 0;
		for (; idx >= 1; idx -= (idx & -idx)) {
			ret += tr1[idx];
		}
		return ret;
	};
	auto query2 = [&](i64 idx) {
		i64 ret = 0;
		for (; idx >= 1; idx -= (idx & -idx)) {
			ret += tr2[idx];
		}
		return ret;
	};
	auto modify = [&](i64 l, i64 r, i64 v) {
		add1(l, v); add1(r + 1, -v);
		add2(l, v); add2(r + 1, -v);
	};
	auto query = [&](i64 l, i64 r) {
		l--;
		return (r + 1) * query1(r) - query2(r) - (l + 1) * query1(l) + query2(l);
	};
	for (i64 i = 1; i <= n; i++) {
		add1(i, A[i] - A[i - 1]);
		add2(i, A[i] - A[i - 1]);
	}
	while (m--) {
		string opt; std::cin >> opt;
		if (opt == "C") {
			i64 l, r, d; std::cin >> l >> r >> d;
			modify(l, r, d);
		} else {
			i64 l; std::cin >> l;
			std::cout  << query(l, l) << "\n";
			;
		}
	}
}
int main() {
	solve();
}








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
	struct Node {
		T add; T sum;
		i64 l; i64 r;
	};

	vector<Node>tr;

	SegmentTree(i64 n): tr(4 * n + 10) {}

	void pushUp(i64 p) {
		tr[p].sum = tr[p << 1].sum + tr[p << 1 | 1].sum;
	}

	void build(i64 p, i64 l, i64 r, vector<i64>&a) {
		tr[p].l = l; tr[p].r = r; tr[p].add = tr[p].sum = 0;
		if (l == r) {
			tr[p].sum = a[l]; return;
		}
		i64 mid = (l + r) >> 1;
		build(p << 1, l, mid, a);
		build(p << 1 | 1, mid + 1, r, a);
		pushUp(p);
	}
	void pushDown(i64 p) {
		if (tr[p].add) {
			i64 add = tr[p].add;
			tr[p].add = 0;
			tr[p << 1].add += add; tr[p << 1 | 1].add += add;
			tr[p << 1].sum += (tr[p << 1].r - tr[p << 1].l + 1) * add;
			tr[p << 1 | 1].sum += (tr[p << 1 | 1].r - tr[p << 1 | 1].l + 1) * add;
		}
	}
	void modify(i64 p, i64 l, i64 r, i64 v) {
		if (tr[p].l >= l and tr[p].r <= r) {
			tr[p].add += v;
			tr[p].sum += (tr[p].r - tr[p].l + 1) * v;
			return;
		}
		pushDown(p);
		i64 mid = (tr[p].l + tr[p].r) >> 1;
		if (l <= mid)
			modify(p << 1, l, r, v);
		if (r > mid)
			modify(p << 1 | 1, l, r, v);
		pushUp(p);
	}

	i64 query(i64 p, i64 l, i64 r) {
		if (tr[p].l >= l and tr[p].r <= r) {
			return tr[p].sum;
		}
		pushDown(p);
		i64 ret = 0; i64 mid = (tr[p].l + tr[p].r) >> 1;
		if (l <= mid)ret += query(p << 1, l, r);
		if (r > mid)ret += query(p << 1 | 1, l, r);
		return ret;
	}
};


int main() {
	i64 n, m; std::cin >> n >> m; vector<i64>a(n + 1);
	for (i64 i = 1; i <= n; i++)std::cin >> a[i];
	SegmentTree<i64>tr(n);
	tr.build(1, 1, n, a);
	while (m--) {
		string opt; i64 l, r, d;
		std::cin >> opt;
		if (opt == "C") {
			i64 l, r, d;
			std::cin >> l >> r >> d;
			tr.modify(1, l, r, d);
		} else if (opt == "Q") {
			i64 x; std::cin >> x;
			std::cout << tr.query(1, x, x) << "\n";
		}
	}
	return 0;
}