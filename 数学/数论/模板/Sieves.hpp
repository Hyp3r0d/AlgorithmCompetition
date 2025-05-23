/*筛法求素数, 欧拉函数*/




struct Sieve {
public:
	std::vector<i64>prime, e;
	std::vector<bool>vis;
	i64 cnt = 0; i64 len;
	Sieve(i64 len = 1e6): len(len), prime(len + 5), e(len + 5), vis(len + 5) {}
	void init() {
		e[1] = 1;
		for (i64 i = 2; i <= len; i++) {
			if (not vis[i]) {
				e[i] = i - 1; prime[++cnt] = i;
			}
			for (i64 j = 1; j <= cnt and i * prime[j] <= len; j++) {
				vis[i * prime[j]] = 1;
				if (i % prime[j]) {
					e[i * prime[j]] = e[prime[j]] * e[i];
				} else {
					e[i * prime[j]] = e[i] * prime[j];
					break;
				}
			}
		}
	}
	void erao() {
		for (i64 i = 2; i <= len; i++) {
			if (not vis[i]) {
				prime[++cnt] = i;
				if (i * i > len)continue;
				for (i64 j = i * i; j <= len; j += i) {
					vis[j] = true;
				}
			}
		}
	}
};


i64 phi(i64 n) {
	i64 res = n;
	for (i64 i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			while (n % i == 0) {
				n /= i;
			}
			res = res / i * (i - 1);
		}
	}
	if (n > 1) {
		res = res / n * (n - 1);
	}
	return res;
};
