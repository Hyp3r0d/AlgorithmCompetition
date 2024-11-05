'#include<bits/stdc++.h>
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
constexpr i64 maxn = 2e5 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


class Solution {
public:
	void solveSudoku(vector<vector<char>>& board) {
		std::vector<std::pair<i64, i64>>stk;
		std::vector q1(10, std::vector<bool>(10, false));
		auto q2 = q1;
		std::vector t(3, std::vector(3, std::vector<bool>(10, false)));
		for (i64 i = 0; i < 9; i++) {
			for (i64 j = 0; j < 9; j++) {
				if (board[i][j] == '.') {
					stk.push_back({i, j}); continue;
				}
				q1[i][board[i][j] - '0'] = true;
				q2[j][board[i][j] - '0'] = true;
				t[i / 3][j / 3][board[i][j] - '0'] = true;
			}
		}
		std::function<bool(i64)>dfs = [&](i64 idx) {
			if (idx == stk.size())return true;
			auto [x, y] = stk[idx];
			for (i64 i = 1; i <= 9; i++) {
				if (q1[x][i] or q2[y][i] or t[x / 3][y / 3][i])continue;
				q1[x][i] = q2[y][i] = t[x / 3][y / 3][i] = true;
                board[x][y] = i + '0';
				bool f = dfs(idx + 1);
				if (f)return true;
				q1[x][i] = q2[y][i] = t[x / 3][y / 3][i] = false;
                board[x][y] = '.';
            }
			return false;
		};
		dfs(0);
	}
};'