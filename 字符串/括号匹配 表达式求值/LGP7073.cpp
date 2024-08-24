


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
constexpr i64 maxn = 2e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

char s[maxn]; i64 c[maxn];

std::vector<i64>g[maxn];
int main() {

	fgets(s, 1000005, stdin);

	i64 len = strlen(s);

	std::vector<string>e(1);
	for (i64 i = 0; i < len; i++) {
		if (s[i] == 'x') {
			i64 p = 0;
			i64 k = i + 1;
			while (k < len and isdigit(s[k])) {
				p = (p * 10 + s[k] - '0');
				k++;
			}
			i = k;
			e.push_back(to_string(p));
		} else if (s[i] == '&' or s[i] == '|' or s[i] == '!') {
			string z = ""; z.push_back(s[i]);
			e.push_back(z);
		}
	}
	i64 n; std::cin >> n;
	std::vector<i64>v(n + 1);
	for (i64 i = 1; i <= n; i++)std::cin >> v[i];

	std::vector<i64>w(n + 1);
	/*逆波兰表达式直接建树*/
	std::function<pair<i64, i64>(i64)>dfs = [&](i64 u) {
		if (isdigit(e[u][0])) {
			w[stoi(e[u])] = u;
			return (pair<i64, i64>) {v[stoi(e[u])], 1};
		}
		if (e[u][0] == '&' or e[u][0] == '|') {
			auto ret1 = dfs(u - 1);
			i64 v1 = ret1.first, len1 = ret1.second;
			auto ret2 = dfs(u - 1 - len1);
			i64 v2 = ret2.first, len2 = ret2.second;
			g[u].push_back(u - 1);
			g[u].push_back(u - 1 - len1);
			if (e[u][0] == '&') {
				if (v1 == 0)c[u - 1 - len1] = 1;
				if (v2 == 0)c[u - 1] = 1;
				return (pair<i64, i64>) {v1&v2, len1 + len2 + 1};
			} else {
				if (v1 == 1)c[u - 1 - len1] = 1;
				if (v2 == 1)c[u - 1] = 1;
				return (pair<i64, i64>) {v1 | v2, len1 + len2 + 1};
			}
		} else {
			auto ret1 = dfs(u - 1);
			i64 v1 = ret1.first, len1 = ret1.second;
			g[u].push_back(u - 1);
			return (pair<i64, i64>) {!v1, len1 + 1};
		}
	};


	std::function<void(i64)>dfs2 = [&](i64 u) {
		if (isdigit(e[u][0])) {
			return;
		}
		for (auto v : g[u]) {

			c[v] |= c[u]; dfs2(v);
		}
	};
	auto ret = dfs(e.size() - 1);
	i64 ans = ret.first;
	dfs2(e.size() - 1);
	i64 q; std::cin >> q;
	while (q--) {
		i64 idx; std::cin >> idx;
		if (c[w[idx]]) {
			std::cout << ans << "\n";
		} else std::cout << (!ans) << "\n";
	}

}


/* 通过栈来对逆波兰表达式建树*/







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

char s[maxn]; i64 c[maxn];

std::vector<i64>g[maxn];

i64 v[maxn];

int main() {
	fgets(s, 1000005, stdin);

	std::vector<i64>stk;
	std::vector<string>eva(1); i64 len = strlen(s);

	std::vector<vector<i64>>g(len + 1);
	for (i64 i = 0; i < len; i++) {
		if (s[i] == 'x') {
			i64 p = 0;
			i64 k = i + 1;
			while (k < len and isdigit(s[k])) {
				p = (p * 10 + s[k] - '0');
				k++;
			}
			i = k;
			eva.push_back(to_string(p));
		} else if (s[i] == '&' or s[i] == '|' or s[i] == '!') {
			string z = ""; z.push_back(s[i]);
			eva.push_back(z);
		}
	}
	i64 n; std::cin >> n;

	for (i64 i = 1; i <= n; i++) {
		std::cin >> v[i];
	}

	for (i64 i = 1; i < eva.size(); i++) {
		if (isdigit(eva[i][0])) {
			stk.push_back(i);
		} else if (eva[i] == "&") {
			i64 x = stk.back(); stk.pop_back();
			i64 y = stk.back(); stk.pop_back();
			stk.push_back(i);
			g[i].push_back(x);
			g[i].push_back(y);
		} else if (eva[i] == "|") {
			i64 x = stk.back(); stk.pop_back();
			i64 y = stk.back(); stk.pop_back();
			stk.push_back(i);
			g[i].push_back(x); g[i].push_back(y);
		} else if (eva[i] == "!") {
			i64 x = stk.back(); stk.pop_back();
			stk.push_back(i);
			g[i].push_back(x);
		}
	}

	std::vector<i64>w(n + 1);

	std::function<i64(i64)>dfs = [&](i64 u) {
		if (isdigit(eva[u][0])) {
			w[stoi(eva[u])] = u;
			return v[stoi(eva[u])];
		}
		if (eva[u] == "&") {
			i64 x = dfs(g[u][0]);
			i64 y = dfs(g[u][1]);
			if (x == 0)c[g[u][1]] = 1;
			if (y == 0)c[g[u][0]] = 1;
			return x & y;
		} else if (eva[u] == "|") {
			i64 x = dfs(g[u][0]);
			i64 y = dfs(g[u][1]);
			if (x == 1)c[g[u][1]] = 1;
			if (y == 1)c[g[u][0]] = 1;
			return x | y;
		} else {
			i64 x = dfs(g[u][0]);
			return (i64)!x;
		}
	};

	i64 ret = dfs(eva.size() - 1);
	std::function<void(i64)>dfs2 = [&](i64 u) {
		if (isdigit(eva[u][0])) {
			return;
		}
		for (auto v : g[u]) {
			c[v] |= c[u];
			dfs2(v);
		}
	};
	dfs2(eva.size() - 1);
	i64 q; std::cin >> q;
	while (q--) {
		i64 idx; std::cin >> idx;
		std::cout << (c[w[idx]] ? ret : !ret) << "\n";
	}

	return 0;

}