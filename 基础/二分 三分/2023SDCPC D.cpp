#include<bits/stdc++.h>
using namespace std;
typedef double db;
using i64 = long long;
typedef long double lb;
const i64 maxn = 1e6 + 5;
const i64 inf = 0x3f3f3f3f3f3f3f3f;
const i64 mod = 233;
struct sq {
	i64 u; i64 w; i64 idx;
};
void solve() {
	i64 n; std::cin >> n;
	vector<sq>st(n + 5), st2(n + 5);
	i64 mv = inf;
	for (i64 i = 1; i <= n; i++) {
		std::cin >> st[i].u >> st[i].w;
		st2[i] = st[i];
	}
	std::sort(st.begin() + 1, st.begin() + 1 + n, [&](sq x, sq y)->bool{
		return x.u + x.w > y.u + y.w;
	});
	std::sort(st2.begin() + 1, st2.begin() + 1 + n, [&](sq x, sq y)->bool{
		return x.w > y.w;
	});
	auto check = [&](i64 x) {
		vector<i64>p, q;
		for (i64 i = 1; i <= n; i++)if (st[i].u >= x)p.push_back(st[i].u + st[i].w);
		for (i64 i = 1; i <= n; i++)if (st2[i].u < x)q.push_back(st2[i].w);
		if (p.size() < q.size())return false;
		for (i64 i = 0; i < q.size(); i++) {
			if (p[i] - q[i] < x)return false;
		}
		return true;
	};
	i64 l = 0, r = 1e15, ans = 0;
	while (l < r) {
		i64 mid = (l + r + 1) >> 1;
		if (check(mid)) {
			l = mid;
		} else {
			r = mid - 1;
		}
	}
	std::cout  << l << "\n";
;
}
int main() {
	i64 T; std::cin >> T;
	while (T--)solve();
}