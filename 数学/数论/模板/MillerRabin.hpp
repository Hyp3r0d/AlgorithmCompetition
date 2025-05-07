/*素数判定*/
i64 quickPower(i64 a, i64 b, i64 m = mod) {
	i64 res = 1;
	while (b) {
		if (b & 1)res = res * a % m;
		a = a * a % m;
		b >>= 1;
	}
	return res;
}

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