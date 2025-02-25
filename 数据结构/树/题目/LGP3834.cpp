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
constexpr i64 maxn = 1e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

struct Node {
	i64 lson, rson;
	i64 sum;
} tr[maxn << 5];

i64 sum[maxn << 5];

i64 tot = 0;
i64 build(i64 l, i64 r) {
	i64 p = ++tot;
	if (l == r)return p;
	i64 mid = (l + r) >> 1;
	tr[p].lson = build(l, mid);
	tr[p].rson = build(mid + 1, r);
	return p;
}

i64 update(i64 p, i64 k, i64 l, i64 r) {
	i64 dir = ++tot; // 沿着路径复制一颗线段树, 只复制修改过的点
	tr[dir].lson = tr[p].lson, tr[dir].rson = tr[p].rson;
	tr[dir].sum = tr[p].sum + 1;
	if (l == r)return dir;
	i64 mid = (l + r) >> 1;
	if (k <= mid)
		tr[dir].lson = update(tr[p].lson, k, l, mid);
	else
		tr[dir].rson = update(tr[p].rson, k, mid + 1, r);
	return dir;
}

i64 query(i64 u, i64 v, i64 l, i64 r, i64 k) {
	i64 mid = (l + r) >> 1;
	// 两个版本的数量差即为该区间内该范围数据的多少
	i64 x = tr[tr[v].lson].sum - tr[tr[u].lson].sum;
	if (l == r)return l;
	if (k <= x) {
		return query(tr[u].lson, tr[v].lson, l, mid, k);
	} else {
		return query(tr[u].rson, tr[v].rson, mid + 1, r, k - x);
	}

}
i64 rt[maxn];

int main() {
	i64 n, m; std::cin >> n >> m;
	std::vector<i64>a(n + 1);
	for (i64 i = 1; i <= n; i++) {
		std::cin >> a[i];
	}
	auto z = a;
	std::sort(z.begin() + 1, z.begin() + 1 + n);
	i64 len = unique(z.begin() + 1, z.begin() + 1 + n) - z.begin() - 1;
	auto get = [&](i64 val) {
		return lower_bound(z.begin() + 1, z.begin() + 1 + len, val) - z.begin();
	};
	rt[0] = build(1, len);
	for (i64 i = 1; i <= n; i++) {
		rt[i] = update(rt[i - 1], get(a[i]), 1, len);
	}
	while (m--) {
		i64 l, r, k; std::cin >> l >> r >> k;
		std::cout << z[query(rt[l - 1], rt[r], 1, len, k)] << "\n";
	}
	return 0;
}
