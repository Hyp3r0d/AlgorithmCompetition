u64 b = 13331;

u64 bw[maxn];


void init() {
	bw[0] = 1; for (i64 i = 1; i <= 2e5; i++)bw[i] = bw[i - 1] * b;
}

struct StringHash {
public:
	std::vector<u64>h;
	void init(string s) {
		i64 n = s.size(); h.assign(n + 5, 0);
		s = " " + s;
		for (i64 i = 1; i <= n; i++) {
			h[i] = h[i - 1] * b + s[i];
		}
	}
	StringHash(string s) {
		init(s);
	}
	u64 get(i64 l, i64 r) {
		return h[r] - h[l - 1] * bw[r - l + 1];
	}
};