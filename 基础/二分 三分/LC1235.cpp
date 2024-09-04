class Solution {
public:
    int jobScheduling(vector<int> &startTime, vector<int> &endTime, vector<int> &profit) {
        int n = startTime.size();
        vector<vector<int>> jobs(n + 1);
        jobs[0] = {0, 0 , 0};
        for (int i = 1; i <= n; i++) {
            jobs[i] = vector<int> {startTime[i - 1], endTime[i - 1], profit[i - 1]};
        }
        std::sort(jobs.begin() + 1, jobs.end(), [](const vector<int> &job1, const vector<int> &job2) -> bool {
            return job1[1] < job2[1];
        });
        vector<int> dp(n + 1);
        int res = 0;
        for (int i = 1; i <= n; i++) {
            int l = 0, r  = i;
            while (l < r) {
                int mid = (l + r + 1) >> 1;
                if (jobs[mid][1] <= jobs[i][0]) {
                    l = mid;
                }
                else r = mid - 1;
            }
            if (jobs[l][1] <= jobs[i][0])
                dp[i] = max(dp[i - 1], dp[l] + jobs[i][2]);
        }
        return dp[n];
    }
};





#include<bits/stdc++.h>
#include<sys/stat.h>
#include<fcntl.h>
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
const i64 mod = 1e9 + 7;
const i64 maxn = 1e6 + 5;
const i64 inf = 0x3f3f3f3f3f3f3f3f;




/* 不满足单调栈上二分的性质, 不能单调栈上二分 */
class Solution {
public:
    i64 tr[maxn];

    void add(i64 idx, i64 v) {
        for (; idx <= 100000; idx += (idx & -idx))tr[idx] = std::max(tr[idx], v);
    }

    i64 query(i64 idx) {
        i64 ret = 0;
        for (; idx >= 1; idx -= (idx & -idx))ret = std::max(ret, tr[idx]);
        return ret;
    }
    int jobScheduling(vector<int> &startTime, vector<int> &endTime, vector<int> &profit) {
        i64 n = startTime.size();
        std::vector<array<i64, 3>>z(1);
        for (i64 i = 0; i < n; i++) {
            z.push_back({startTime[i], endTime[i], profit[i]});
        }
        std::sort(z.begin() + 1, z.begin() + 1 + n, [&](auto x, auto y)->bool{
            return x[1] < y[1];
        });
        vector<i64>dp(n + 5);
        for (i64 i = 1; i <= n; i++) {
            i64 start = z[i][0];
            i64 idx = lower_bound(z.begin(), z.begin() + i, start, [&](array<i64, 3>x, i64 y) -> bool{
                return x[1] <= y;
            }) - z.begin() - 1;
            dp[i] = std::max(dp[i], query(idx) + z[i][2]);
            add(i, dp[i]);
        }
        return query(n);
    }
};


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

constexpr i64 mod = 1e5 + 3;
constexpr i64 maxn = 1e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


/* 不满足单调栈上二分的性质, 不能单调栈上二分 */
class Solution {
public:


  i64 tr[maxn];

  void add(i64 idx, i64 v) {
    for (; idx <= 5e4; idx += idx & -idx)tr[idx] = std::max(tr[idx], v);
  }

  i64 query(i64 idx) {
    i64 ret = 0;
    for (; idx >= 1; idx -= idx & -idx)ret = std::max(ret, tr[idx]);
    return ret;
  }
  int jobScheduling(vector<int> &startTime, vector<int> &endTime, vector<int> &profit) {
    
    i64 n = startTime.size();
    
    std::vector<array<i64, 3>>z(n + 1);
    

    z[0] = {0, 0, 0};
    for (i64 i = 1; i <= n; i++) {
      z[i] = {startTime[i - 1], endTime[i - 1], profit[i - 1]};
    }
    std::sort(z.begin() + 1, z.begin() + 1 + n, [&](array<i64, 3> x, array<i64, 3> y)->bool {
      return  x[1] < y[1];
    });
    for(i64  i = 0;i <= 4e5;i ++) tr[i] = -inf;
    std::vector<i64>dp(n + 1, 0);
    for (i64 i = 1; i <= n; i ++) {
      dp[i] = z[i][2];
      i64 l = 0, r = i; i64 ans = 0;
      i64 v = z[i][0];
      while (l < r) {
        i64 mid = (l + r + 1) >> 1;
        if (z[mid][1] <= v)l = mid, ans = mid;
        else r = mid - 1;
      }
      /*
      i64 l = 0, r = i - 1;
      while(l <= r) {
        i64 mid = (l + r) >> 1;
        if(z[mid][1] <= v) l = mid + 1, ans = mid;
        else r = mid - 1;
      }
      */
      std::cout << ans << "\n";
      i64 q = query(ans);
      dp[i] = std::max(dp[i], q + z[i][2]);
      add(i, dp[i]);
    }
    return (int)query(n);
  }
};




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

constexpr i64 mod = 1e5 + 3;
constexpr i64 maxn = 1e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


/* 不满足单调栈上二分的性质, 不能单调栈上二分 */
class Solution {
public:


  i64 tr[maxn];

  void add(i64 idx, i64 v) {
    for (; idx <= 5e4; idx += idx & -idx)tr[idx] = std::max(tr[idx], v);
  }

  i64 query(i64 idx) {
    i64 ret = 0;
    for (; idx >= 1; idx -= idx & -idx)ret = std::max(ret, tr[idx]);
    return ret;
  }
  int jobScheduling(vector<int> &startTime, vector<int> &endTime, vector<int> &profit) {
    
    i64 n = startTime.size();
    
    std::vector<array<i64, 3>>z(n + 1);
    

    z[0] = {0, 0, 0};
    for (i64 i = 1; i <= n; i++) {
      z[i] = {startTime[i - 1], endTime[i - 1], profit[i - 1]};
    }
    std::sort(z.begin() + 1, z.begin() + 1 + n, [&](array<i64, 3> x, array<i64, 3> y)->bool {
      return  x[1] < y[1];
    });
    for(i64  i = 0;i <= 4e5;i ++) tr[i] = -inf;
    std::vector<i64>dp(n + 1, 0);
    for (i64 i = 1; i <= n; i ++) {
      dp[i] = z[i][2];
      i64 v = z[i][0];
      i64 ans = upper_bound(z.begin() + 1, z.end(), array<i64, 3>{0 ,v, 0 }, [&](array<i64, 3>x,array<i64, 3>y)->bool{
        return x[1] < y[1];
      }) - z.begin() - 1;
      std::cout << ans << "\n";
      i64 q = query(ans);
      dp[i] = std::max(dp[i], q + z[i][2]);
      add(i, dp[i]);
    }
    return (int)query(n);
  }
};