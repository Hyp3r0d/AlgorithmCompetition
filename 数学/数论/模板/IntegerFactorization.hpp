i64 quickPower(i64 a, i64 b, i64 m = mod) {
	i64 res = 1;
	while (b) {
		if (b & 1)res = res % m * a % m;
		a = a % m * a % m;
		b >>= 1;
	}
	return res;
}

i64 maxFactor = 0; std::unordered_set<i64>st;

bool isPrime(i64 n) {
	if (n < 3 or n % 2 == 0)return n == 2;
	if (n % 3 == 0)return n == 3;
	i64 u = n - 1, t = 0;
	while (u % 2 == 0)u /= 2, t++;
	for (i64 i = 0; i <= 15; i++) {
		i64 a = rand() % (n - 3) + 2, v = quickPower(a, u, n);
		if (v == 1)continue;
		i64 s;
		for (s = 0; s < t; s++) {
			if (v == n - 1)break;
			v = v * v % n;
		}
		if (s == t)return false;
	}
	return true;
}
// sqrt(p)效率下找一个数的非平凡因子
i64 pollardRho(i64 p) {
	i64 s = 0 , t = 0;
	i64 c = (i64)rand() % (p - 1) + 1;
	i64 step = 0, goal = 1;
	i64 val = 1;
	for (goal = 1;; goal *= 2, s = t, val = 1) {
		for (step = 1; step <= goal; ++step) {
			t = (t * t % p + c) % p;
			val = val * abs(t - s) % p;
			if (step % 127 == 0) {
				i64 d = gcd(val, p);
				if (d > 1)return d;
			}
		}
		i64 d = gcd(val, p);
		if (d > 1)return d;
	}
}
// 借助分治找出其所有的素因子
void dfs(i64 n) {
	if (n < 2)return;
	if (isPrime(n)) {
		maxFactor = std::max(maxFactor, n);
		st.insert(n);
		return;
	}
	i64 p = n;
	while (p >= n)p = pollardRho(n);
	while (n % p == 0)n /= p;
	dfs(n); dfs(p);
}

// 进行因式分解 总效率为O(k*sqrt(p) + k*log(n))
std::vector<std::pair<i64, i64>> factorize(i64 n) {
	maxFactor = 0; st.clear();
	dfs(n);
	std::vector<pair<i64, i64>>ret;
	for (auto c : st) {
		std::pair<i64, i64>w;
		w.first = c; i64 ex = 0;
		while (n % c == 0) {
			n /= c; ex++;
		}
		w.second = ex;
		ret.push_back(w);
	}
	return ret;
}