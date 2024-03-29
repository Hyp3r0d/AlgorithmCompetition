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

constexpr i64 mod = 999911659;
constexpr i64 maxn = 1e3 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


struct Node {
	int l; int r; int mx1 = 0, mx2 = 0;
	int cnt1 = 0, cnt2 = 0;
	friend Node operator+(Node a, Node b) {
		Node c;
		if (a.mx1 < b.mx1) {
			std::swap(a, b);
		}
		int mx1 = a.mx1;
		int cnt1 = a.cnt1;
		int mx2 = 0, cnt2 = 0;
		if (a.mx1 == b.mx1) {
			cnt1 += b.cnt1;
			if (a.mx2 < b.mx2) {
				mx2 = b.mx2;
				cnt2 += b.cnt2;
			} else if (a.mx2 == b.mx2) {
				mx2 = b.mx2;
				cnt2 += a.cnt2;
				cnt2 += b.cnt2;
			} else {
				mx2 = a.mx2;
				cnt2 += a.cnt2;
			}
		} else {
			if (a.mx2 < b.mx1) {
				mx2 = b.mx1;
				cnt2 += b.cnt1;
			} else if (a.mx2 == b.mx1) {
				mx2 = b.mx1;
				cnt2 += a.cnt2;
				cnt2 += b.cnt1;
			} else {
				mx2 = a.mx2;
				cnt2 += a.cnt2;
			}
		}
		c.mx1 = mx1;
		c.mx2 = mx2;
		c.cnt1 = cnt1;
		c.cnt2 = cnt2;
		return c;
	}
};


struct SegmentTree {
	/*单懒标记线段树*/
public:



	std::vector<Node>tr; int n;

	SegmentTree(int n): tr(4 * n + 4), n(n) {}


	void build(int p, int l, int r, std::vector<int>&a) {
		tr[p].l = l; tr[p].r = r;
		if (l == r) {
			tr[p].mx1 = a[l]; tr[p].mx2 = 0;
			tr[p].cnt1 = 1;
			return;
		}
		int mid = (l + r) >> 1;
		build(p << 1, l, mid, a);
		build(p << 1 | 1, mid + 1, r, a);
		Node tmp = tr[p << 1] + tr[p << 1 | 1];
		tr[p].mx1 = tmp.mx1;
		tr[p].mx2 = tmp.mx2;
		tr[p].cnt1 = tmp.cnt1;
		tr[p].cnt2 = tmp.cnt2;
	}


	void modify(int p, int idx, int val) {
		if (tr[p].l == tr[p].r) {
			tr[p].mx1 = val;
			tr[p].cnt1 = 1;
			return;
		}
		int mid = (tr[p].l + tr[p].r) >> 1;
		if (idx > mid) {
			modify(p << 1 | 1, idx, val);
		} else if (idx <= mid) {
			modify(p << 1, idx, val);
		}
		Node tmp = tr[p << 1] + tr[p << 1 | 1];
		tr[p].mx1 = tmp.mx1;
		tr[p].mx2 = tmp.mx2;
		tr[p].cnt1 = tmp.cnt1;
		tr[p].cnt2 = tmp.cnt2;
	}
	Node query(int p, int l, int r) {
		if (tr[p].l >= l and tr[p].r <= r) {
			return tr[p];
		}
		int mid = (tr[p].l + tr[p].r) >> 1;
		int mx1 = 0, mx2 = 0; Node L, R, ret;
		L.mx1 = L.mx2 = R.mx1 = R.mx2 = ret.mx1 = ret.mx2 = 0;
		if (l <= mid) {
			L = query(p << 1, l, r);
		}
		if (r > mid) {
			R = query(p << 1 | 1, l, r);
		}
		return (L + R);
	}

};



int main() {
	i64 n, q; std::cin >> n >> q;
	std::vector<int>a(n + 1);
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
	}
	SegmentTree tr(n); tr.build(1, 1, n, a);
	for (int i = 1; i <= q; i++) {
		int opt; std::cin >> opt;
		if (opt == 1) {
			int p, x; std::cin >> p >> x;
			tr.modify(1, p, x); a[p] = x;
		} else {
			int cnt = 0;
			int l, r; std::cin >> l >> r;
			auto g = tr.query(1, l, r);
			for (int i = l; i <= r; i++) {
				if (a[i] == g.mx2)cnt++;
			}
			std::cout << cnt << "\n";
		}
	}
}
