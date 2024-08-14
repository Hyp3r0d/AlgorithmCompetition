
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
constexpr i64 maxn = 4e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

int main() {
	string s; std::cin >> s;
	i64 len = s.size();
	vector<i64>a; vector<char>opt;
	std::map<char, i64>pr;
	pr['+'] = pr['-'] = 1;
	pr['*'] = pr['/'] = 2;
	auto eval = [&]() {
		char op = opt.back(); opt.pop_back();
		i64 c2 = a.back(); a.pop_back();
		i64 c1 = a.back(); a.pop_back();
		if (op == '+') {
			a.push_back(c1 + c2);
		} else if (op == '-') {
			a.push_back(c1 - c2);
		} else if (op == '*') {
			a.push_back(c1 * c2);
		} else if (op == '/') {
			a.push_back(c1 / c2);
		}
	};
	char prev = '(';
	for (i64 i = 0; i < len; i++) {
		if (s[i] == ' ')continue;
		if (isdigit(s[i])) {
			i64 cur = 0;
			while (i < len and isdigit(s[i])) {
				cur = cur * 10 + s[i] - '0';
				i++;
			}
			i--; a.push_back(cur);
		} else if (s[i] == '(' or s[i] == '[' or s[i] == '{') {
			opt.push_back('(');
			s[i] = '(';
		} else if (s[i] == ')' or s[i] == ']' or s[i] == '}') {
			while (opt.size() and opt.back() != '(') eval();
			opt.pop_back();
			s[i] = ')';
		} else {
			if (prev == '(') {//单目运算符的特判
				a.push_back(0);
			}
			char c = s[i];
			while (opt.size() and pr[opt.back()] >= pr[c]) {
				eval();
			}
			opt.push_back(s[i]);
		}
		prev = s[i];
	}
	while (a.size() >= 2)
		eval();
	std::cout << a.back();
}