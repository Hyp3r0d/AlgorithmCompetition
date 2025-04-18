/*线段树优化dp*/
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

constexpr i64 mod = 998244353;
constexpr i64 maxn = 1e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;
class Solution {
public:
    struct Node {
        i64 mx; i64 l; i64 r; i64 laz;
    } tr [maxn];
    void pushUp(i64 p) {
        tr[p].mx = max(tr[p << 1].mx, tr[p << 1 | 1].mx);
    }

    void pushDown(i64 p) {
        if (tr[p].laz != -inf) {
            i64 k = tr[p].laz; tr[p].laz = -inf;
            tr[p << 1].mx = std::max(tr[p << 1].mx, k);
            tr[p << 1].laz = std::max(tr[p << 1].laz, k);
            tr[p << 1 | 1].mx = std::max(tr[p << 1 | 1].mx, k);
            tr[p << 1 | 1].laz = std::max(tr[p << 1 | 1].laz, k);
        }
    }
    /*带懒标记区间修改*/
    void update(i64 p, i64 l, i64 r, i64 v) {
        if (tr[p].l == tr[p].r) {
            tr[p].mx = max(tr[p].mx, v);
            tr[p].laz = std::max(tr[p].laz, v);
            return;
        }
        pushDown(p);
        i64 mid = (tr[p].l + tr[p].r) >> 1;
        if (r > mid)update(p << 1 | 1, l, r, v);
        if (l <= mid)update(p << 1, l, r, v);
        pushUp(p);
    }
    void build(i64 p, i64 l, i64 r) {
        tr[p].l = l; tr[p].r = r;
        tr[p].laz = -inf;
        if (l == r) {
            return;
        }
        i64 mid = (l + r) >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        pushUp(p);
    }
    i64 query(i64 p, i64 l, i64 r) {
        if (tr[p].l >= l and tr[p].r <= r) {
            return tr[p].mx;
        }
        pushDown(p);
        i64 ret = 0; i64 mid = (tr[p].l + tr[p].r) >> 1;
        if (r > mid)
            ret = max(ret, query(p << 1 | 1, l, r));
        if (l <= mid)ret = max(ret, query(p << 1, l, r));
        return ret;
    }
    int lengthOfLIS(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int>dp(n + 5, 1);
        auto ver = nums;
        ver.insert(ver.begin(), 0);
        std::sort(ver.begin() + 1, ver.begin() + 1 + n);
        i64 len = unique(ver.begin() + 1, ver.begin() + 1 + n) - ver.begin() - 1;
        build(1, 1, len);
        auto get = [&](i64 x) {
            return lower_bound(ver.begin() + 1, ver.begin() + 1 + len, x) - ver.begin();
        };
        for (int i = 1; i <= n; i++) {
            i64 l = get(nums[i - 1] - k); i64 r = get(nums[i - 1]) - 1;
            int q = query(1, l, r);
            dp[i] = max(dp[i], q + 1); int idx = get(nums[i - 1]);
            update(1, idx, idx, dp[i]);
        }
        int ans = 0;
        for (int i = 1; i <= n; i++)ans = max(ans, dp[i]);
        return ans;
    }
};



/*线段树优化dp*/
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

constexpr i64 mod = 998244353;
constexpr i64 maxn = 4e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;
class Solution {
public:
	struct sq {
		int mx; int l; int r;
	} tr[maxn];
	void pushUp(int p) {
		tr[p].mx = max(tr[p << 1].mx, tr[p << 1 | 1].mx);
	}
	//单点修改
	void update(int p, int l, int r, int v) {
		if (tr[p].l == tr[p].r) {
			tr[p].mx = max(tr[p].mx, v);
			return;
		}
		int mid = (tr[p].l + tr[p].r) >> 1;
		if (r > mid)update(p << 1 | 1, l, r, v);
		if (l <= mid)update(p << 1, l, r, v);
		pushUp(p);
	}
	void build(int p, int l, int r) {
		tr[p].l = l; tr[p].r = r;
		if (l == r) {
			tr[p].mx = 0; return;
		}
		int mid = (l + r) >> 1;
		build(p << 1, l, mid);
		build(p << 1 | 1, mid + 1, r);
		pushUp(p);
	}
	int query(int p, int l, int r) {
		if (tr[p].l >= l and tr[p].r <= r) {
			return tr[p].mx;
		}
		int ret = 0; int mid = (tr[p].l + tr[p].r) >> 1;
		if (r > mid)
			ret = max(ret, query(p << 1 | 1, l, r));
		if (l <= mid)ret = max(ret, query(p << 1, l, r));
		return ret;
	}
	int lengthOfLIS(vector<int>& nums, int k) {
		int n = nums.size();
		vector<int>dp(n + 5, 0);
		std::fill(dp.begin() + 1, dp.begin() + 1 + n, 1);
		build(1, 1, 1e5);
		for (int i = 1; i <= n; i++) {
			int q = query(1, max(1, nums[i - 1] - k), nums[i - 1] - 1);
			dp[i] = max(dp[i], q + 1);
			update(1, nums[i - 1], nums[i - 1], dp[i]);
		}
		int ans = 0;
		for (int i = 1; i <= n; i++)ans = max(ans, dp[i]);
		return ans;
	}
};