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

constexpr i64 mod = 1e9 + 7;
constexpr i64 maxn = 2e7 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


auto qpow(i64 x, i64 y) {
    i64 ret = 1;
    while (y) {
        if (y & 1)ret = ret * x % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return ret % mod;
}


auto inv(i64 x)  {
    return qpow(x, mod - 2) % mod;
}

struct Matrix {
public:
    i64 n; std::vector<std::vector<i64>>a;
    Matrix(i64 len): n(len), a(n) {
        for (i64 i = 0; i < this->n; i++) {
            a[i].assign(n, 0);
        }
    }
    void init() {
        for (i64 i = 0; i < n; i++)a[i][i] = 1;
    }

    friend Matrix operator*(const Matrix &x, const Matrix &y) {
        Matrix ret(x.n);
        for (i64 i = 0; i < x.n; i++) {
            for (i64 j = 0; j < x.n; j++) {
                for (i64 k = 0; k < x.n; k++) {
                    ret.a[i][j] = (ret.a[i][j] % mod + x.a[i][k] % mod * y.a[k][j]) % mod;
                }
            }
        }
        return ret;
    }

    friend Matrix quickPower(Matrix x, i64 y) {
        Matrix ret(x.n); ret.init();
        while (y) {
            if (y & 1)ret = ret * x;
            x = x * x;
            y >>= 1;
        }
        return ret;
    }
};





int main() {
    i64 n, k; std::cin >> n >> k;
    Matrix x(n), y(n);
    for (i64 i = 0; i < n; i++)std::cin >> x.a[0][i];
    for (i64 j = 0; j < n; j++)for (i64 i = 0; i <= j; i++)y.a[i][j] = 1;
    x = x * quickPower(y, k);
    for (i64 i = 0; i < n; i++) {
        std::cout << x.a[0][i] % mod << " \n"[i == n - 1];
    }
    return 0;
}