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

i64 tr[maxn];

std::vector<i64>a(1);


void add(i64 idx, i64 v) {
	for (; idx <= 1e6; idx += idx & -idx)tr[idx] += v;
}

i64 query(i64 idx) {
	i64 ret = 0;
	for (; idx >= 1; idx -= idx & -idx)ret += tr[idx];
	return ret;
}

std::map<i64, i64>f;
int main() {

	i64 n;
	std::cin >> n;
	std::vector<array<i64, 2>>w(n + 1);
	for (i64 i = 1; i <= n; i++) {
		std::cin >> w[i][0] >> w[i][1];
		if (w[i][0] == 1) {
			a.push_back(w[i][1]);
		}
	}
	sort(a.begin() + 1, a.end());

	i64 len = unique(a.begin() + 1, a.end()) - a.begin() - 1;

	auto get = [&](i64 val) {
		return  lower_bound(a.begin() + 1, a.begin() + 1 + len, val) - a.begin();
	};
	for (i64 i = 1; i <= n; i++) {
		auto [op1, op2] = w[i];
		if (op1 == 1) {
			add(get(op2), 1);
			f[op2] += 1;
		} else if (op1 == 2) {
			f[op2] -= 1; if (f[op2] == 0)f.erase(op2);

			add(get(op2), -1);
		} else if (op1 == 3) {
			i64 p = lower_bound(a.begin() + 1, a.begin() + 1 + len, op2) - a.begin() - 1;
			std::cout << query(p) + 1 << "\n";
		} else if (op1 == 4) {
			i64 l = 1, r = len; i64 ans = -1;
			while (l <= r) {
				i64 mid = (l + r) >> 1;
				if (query(mid) >= op2) {
					r = mid - 1; ans = mid;

				} else l = mid + 1;
			}

			
			std::cout << a[ans] << "\n";

		} else if (op1 == 5) {
			auto p = f.lower_bound(op2);
			p--; std::cout << (p->first) << "\n";
		} else {
			auto p = f.upper_bound(op2);
			std::cout << (p->first) << "\n";
		}
	}
	return 0;
}