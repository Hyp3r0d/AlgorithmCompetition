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

constexpr i64 mod = 45989;
constexpr i64 maxn = 2e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

std::unordered_set<i64>st[maxn];

struct Node {
	i64 nxt[30];
};

std::vector<Node>Trie;


void insert(string s, i64 idx) {
	i64 len = s.size();
	i64 u = 0;
	for (i64 i = 0; i < len; i++) {
		i64 c = s[i] - 'a';
		if (not Trie[u].nxt[c]) {
			Trie[u].nxt[c] = Trie.size();
			Trie.push_back(Node());
		}
		u = Trie[u].nxt[c];
		st[u].insert(idx);
	}
}


i64 query(string s, i64 idx) {
	i64 len = s.size(); i64 u = 0, ret = 0;
	for (i64 i = 0; i < len; i++) {
		i64 c = s[i] - 'a';
		if (st[Trie[u].nxt[c]].size() != 1) {
			ret++; u = Trie[u].nxt[c];
		} else {
			return ret;
		}
	}
	return ret;
}

int main() {
	i64 n; std::cin >> n;
	std::vector<string>z(n + 1);
	Trie.push_back(Node());
	for (i64 i = 1; i <= n; i++)std::cin >> z[i];
	for (i64 i = 1; i <= n; i++) {
		insert(z[i], i);
	}
	for (i64 i = 1; i <= n; i++) {
		std::cout << query(z[i], i) << "\n";
	}
	return 0;
}