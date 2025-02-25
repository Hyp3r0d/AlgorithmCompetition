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

struct Node {
	int l; int r; int c; int x;
};


struct SegmentTree {

public:

	std::vector<Node>tr; int n;

	SegmentTree(int n): tr(4 * n + 4), n(n) {}
	/*摩尔投票算法求绝对众数*/
	void pushUp(int p) {
		if (tr[p << 1].x == tr[p << 1 | 1].x) {
			tr[p].x = tr[p << 1].x;
			tr[p].c = tr[p << 1].c + tr[p << 1 | 1].c;
		} else if (tr[p << 1].c < tr[p << 1 | 1].c) {
			tr[p].x = tr[p << 1 | 1].x;
			tr[p].c = tr[p << 1 | 1].c - tr[p << 1].c;
		} else {
			tr[p].x = tr[p << 1].x;
			tr[p].c = tr[p << 1].c - tr[p << 1 | 1].c;
		}
	}

	Node merge(Node f, Node g) {
		Node ret;
		if (f.x == g.x) {
			ret.x = f.x;
			ret.c = f.c + g.c;
		} else if (f.c < g.c) {
			ret.x = g.x;
			ret.c = g.c - f.c;
		} else {
			ret.x = f.x;
			ret.c = f.c - g.c;
		}
		return ret;
	}

	void build(int p, int l, int r, std::vector<int>&a) {
		tr[p].l = l; tr[p].r = r;
		if (l == r) {
			tr[p].x = a[l]; tr[p].c = 1;
			return;
		}
		int mid = (l + r) >> 1;
		build(p << 1, l, mid, a);
		build(p << 1 | 1, mid + 1, r, a);
		pushUp(p);
	}


	Node query(int p, int l, int r) {
		if (tr[p].l >= l and tr[p].r <= r) {
			return tr[p];
		}
		Node ret;
		int mid = (tr[p].l + tr[p].r) >> 1;
		if (r > mid) {
			ret = merge(ret, query(p << 1 | 1, l, r));
		}
		if (l <= mid) {
			ret = merge(ret, query(p << 1, l, r));
		}
		return ret;
	}

};



class MajorityChecker {
public:
	std::vector<int>a;
	SegmentTree tr;
	std::vector<int>loc[20005];
	MajorityChecker(vector<int>& arr): tr(arr.size()) {
		int n = arr.size();
		a.assign(n + 1, 0);
		for (int i = 1; i <= n; i++) {
			a[i] = arr[i - 1];
		}
		for (int i = 0; i < n; i++) {
			loc[arr[i]].push_back(i);
		}
		tr.build(1, 1, n, a);
	}

	int query(int left, int right, int threshold) {
		Node ans = tr.query(1, left + 1, right + 1);
		std::vector<int>pos = loc[ans.x];
		int res = upper_bound(pos.begin(), pos.end(), right) - lower_bound(pos.begin(), pos.end(), left);
		return res >= threshold ? ans.x : -1;
	}
};