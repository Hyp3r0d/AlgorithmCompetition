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
    T cnt1; T cnt2; int b;
    i64 l; i64 r;
  };

  vector<Node>tr;

  SegmentTree(i64 n): tr(4 * n + 10) {}

  void pushUp(i64 p) {
    tr[p].cnt1 = tr[p << 1].cnt1 + tr[p << 1 | 1].cnt1;
    tr[p].cnt2 = tr[p << 1].cnt2 + tr[p << 1 | 1].cnt2;
  }

  void build(i64 p, i64 l, i64 r) {
    tr[p].l = l; tr[p].r = r; tr[p].cnt1 = tr[p].cnt2 = 0;
    if (l == r) {
      tr[p].cnt2 = 1; return;
    }
    i64 mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushUp(p);
  }
  void pushDown(i64 p) {
    if (tr[p].b) {
      tr[p].b ^= 1;
      tr[p << 1].b ^= 1; tr[p << 1 | 1].b ^= 1;
      swap(tr[p << 1].cnt1, tr[p << 1].cnt2);
      swap(tr[p << 1 | 1].cnt1, tr[p << 1 | 1].cnt2);
    }
  }
  void modify(i64 p, i64 l, i64 r) {
    if (tr[p].l >= l and tr[p].r <= r) {
      tr[p].b ^= 1;
      swap(tr[p].cnt1, tr[p].cnt2);
      return;
    }
    pushDown(p);
    i64 mid = (tr[p].l + tr[p].r) >> 1;
    if (l <= mid)
      modify(p << 1, l, r);
    if (r > mid)
      modify(p << 1 | 1, l, r);
    pushUp(p);
  }

  i64 query(i64 p, i64 l, i64 r) {
    if (tr[p].l >= l and tr[p].r <= r) {
      return tr[p].cnt1;
    }
    pushDown(p);
    i64 ret = 0; i64 mid = (tr[p].l + tr[p].r) >> 1;
    if (l <= mid)ret += query(p << 1, l, r);
    if (r > mid)ret += query(p << 1 | 1, l, r);
    return ret;
  }
};


int main() {
  i64 n, m; std::cin >> n >> m;
  SegmentTree<i64>tr(n);
  tr.build(1, 1, n);
  while (m--) {
    i64 c, l, r; std::cin >> c >> l >> r;
    if (c == 0) {
      tr.modify(1, l, r);
    } else {
      std::cout << tr.query(1, l, r) << "\n";
    }
  }
  return 0;
}