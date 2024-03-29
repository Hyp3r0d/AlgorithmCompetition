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
constexpr i64 maxn = 2e5 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;



int n, q; string s;
struct node {
	int sum, tag;
} tree[maxn << 2];

void pushup(int ip) {
	tree[ip].sum = tree[ip << 1].sum + tree[ip << 1 | 1].sum;
}

void pushdown(int ip, int l, int r) {
	if (tree[ip].tag) {
		int m = l + r >> 1;
		tree[ip << 1].sum = m - l + 1 - tree[ip << 1].sum;
		tree[ip << 1].tag ^= 1;
		tree[ip << 1 | 1].sum = r - m - tree[ip << 1 | 1].sum;
		tree[ip << 1 | 1].tag ^= 1;
		tree[ip].tag = 0;
	}
}

void update(int ip, int nl, int nr, int l, int r) {
	if (l <= nl && nr <= r) {
		tree[ip].sum = nr - nl + 1 - tree[ip].sum;
		tree[ip].tag ^= 1;
		return;
	}
	int m = nl + nr >> 1;
	pushdown(ip, nl, nr);
	if (l <= m) update(ip << 1, nl, m, l, r);
	if (r > m) update(ip << 1 | 1, m + 1, nr, l, r);
	pushup(ip);
}

int query(int ip, int nl, int nr, int l, int r) {
	if (l <= nl && nr <= r) return tree[ip].sum;
	int m = nl + nr >> 1;
	int sum = 0;
	pushdown(ip, nl, nr);
	if (l <= m) sum = query(ip << 1, nl, m, l, r);
	if (r > m) sum += query(ip << 1 | 1, m + 1, nr, l, r);
	return sum;
}

int main() {
	std::cin >> n >> q;
	std::cin >> s; s = " " + s;
	for (int i = 1; i <= n; ++i)
		if (s[i] == '0' && (i & 1) || s[i] == '1' && (i & 1) == 0) update(1, 1, n, i, i);
	while (q--) {
		int op, l, r;
		scanf("%d%d%d", &op, &l, &r);
		if (op == 1) update(1, 1, n, l, r);
		else {
			int sum = query(1, 1, n, l, r);
			if (sum == 0 || sum == r - l + 1) puts("Yes");
			else puts("No");
		}
	}
	return 0;
}