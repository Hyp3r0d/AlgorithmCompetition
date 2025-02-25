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
constexpr i64 maxn = 4e7 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


/*可持久化权值线段树(主席树) 模板*/
struct Node {
	i64 lson, rson, val;
} tr[maxn];
i64 top = 0; i64 a[1000005];
i64 clone(i64 p) {
	tr[++top] = tr[p];
	return top;
}

i64 build(i64 p, i64 l, i64 r) {
	if (not p)p = ++top;
	if (l == r) {
		tr[p].val = a[l];
		return p;
	}
	i64 mid = (l + r) >> 1;
	tr[p].lson = build(tr[p].lson, l, mid);
	tr[p].rson = build(tr[p].rson, mid + 1, r);
	return p;
}

i64 update(i64 p, i64 l, i64 r, i64 idx, i64 val) {
	p = clone(p);
	if (l == r) {
		tr[p].val = val;
	} else {
		i64 mid = (l + r) >> 1;
		if (idx <= mid) {
			tr[p].lson = update(tr[p].lson, l, mid, idx, val);
		} else {
			tr[p].rson = update(tr[p].rson, mid + 1, r, idx, val);
		}
	}
	return p;
}

i64 query(i64 p, i64 l, i64 r, i64 x) {
	if (l == r) {
		return tr[p].val;
	} else {
		i64 mid = (l + r) >> 1;
		if (x <= mid) {
			return query(tr[p].lson, l, mid, x);
		} else {
			return query(tr[p].rson, mid + 1, r, x);
		}
	}
}
i64 root[1000005];
int main() {
	i64 n, m; std::cin >> n >> m;
	for (i64 i = 1; i <= n; i++) {
		std::cin >> a[i];
	}
	root[0] = build(0, 1, n);
	for (i64 i = 1; i <= m; i++) {
		i64 rt, mode, x; std::cin >> rt >> mode >> x;
		if (mode == 1) {
			i64 y; std::cin >> y;
			root[i] = update(root[rt], 1, n, x, y);
		} else {
			std::cout << query(root[rt], 1, n, x) << "\n";
			root[i] = root[rt];
		}
	}
}