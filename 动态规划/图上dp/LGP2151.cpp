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
const i64 mod = 45989;
const i64 maxn = 1e6 + 5;
const i64 inf = 0x3f3f3f3f3f3f3f3f;


struct Matrix {
public:
	i64 n, m;
	vector<vector<i64>>a;
	Matrix(i64 n, i64 m): n(n), m(m) {
		a.resize(n);
		for (i64 i = 0; i < n; i++) {
			a[i].resize(m, 0);
		}
	}
	friend Matrix operator*(Matrix x, Matrix y) {
		Matrix ret(x.n, y.m);
		for (i64 i = 0; i < x.n; i++) {
			for (i64 j = 0; j < y.m; j++) {
				for (i64 k = 0; k < x.m; k++) {
					ret.a[i][j] = (ret.a[i][j] % mod + x.a[i][k] % mod * y.a[k][j] % mod) % mod;
				}
			}
		}
		return ret;
	}
	friend Matrix operator+(Matrix x, Matrix y) {
		Matrix ret(x.n, x.m);
		for (i64 i = 0; i < x.n; i++) {
			for (i64 j = 0; j < x.m; j++) {
				ret.a[i][j] = (ret.a[i][j] % mod + x.a[i][j] % mod + y.a[i][j] % mod) % mod;
			}
		}
		return ret;
	}
	friend Matrix quickPower(Matrix x, i64 y) {
		Matrix ret(x.n, x.n);
		for (i64 i = 0; i < x.n; i++)ret.a[i][i] = 1;
		while (y) {
			if (y & 1)ret = ret * x;
			x = x * x;
			y >>= 1;
		}
		return ret;
	}
};


struct edge {
	i64 v, nxt;
} e[maxn]; i64 cnt = 0;
i64 head[maxn];
void addEdge(i64 u, i64 v) {
	e[cnt].v = v; e[cnt].nxt = head[u]; head[u] = cnt++;
}

int main() {
	memset(head, -1, sizeof(head));
	i64 n, m, t, a, b; std::cin >> n >> m >> t >> a >> b;
	for (i64 i = 1; i <= m; i++) {
		i64 u, v; std::cin >> u >> v;
		addEdge(u, v); addEdge(v, u);
	}
	Matrix g(cnt, cnt);
	for (i64 z = head[a]; z != -1; z = e[z].nxt) {
		g.a[0][z] = 1;
	}
	Matrix trans(cnt, cnt);
	for (i64 i = 0; i < cnt; i++) {
		i64 v = e[i].v;
		for (i64 j = head[v]; j != -1; j = e[j].nxt) {
			if ((j ^ 1) != i) {
				trans.a[i][j] += 1;
				trans.a[i][j] %= mod;
			}
		}
	}

	g = g * quickPower(trans, t - 1);

	i64 ans = 0;
	for (i64 i = head[b]; i != -1; i = e[i].nxt) {
		ans = (ans % mod + g.a[0][i ^ 1]) % mod;
	}
	std::cout << ans % mod << "\n";
	return 0;
}