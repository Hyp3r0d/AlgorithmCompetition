struct RangeTable {
public:
	i64 n; std::vector<std::vector<i64>>st;
	RangeTable(i64 n): n(n), st(n + 1) {
		for (i64 i = 1; i <= n; i++) {
			st[i].resize(31, 0);
		}
	}
	void init(const std::vector<i64>&a) {
		for (i64 i = 1; i <= n; i++)st[i][0] = a[i];
		for (i64 len = 1; (1 << len) <= n; len++) {
			for (i64 i = 1; i + (1 << len) - 1 <= n; i++) {
				st[i][len] = std::max(st[i][len - 1], st[i + (1 << (len - 1))][len - 1]);
			}
		}
	}
};