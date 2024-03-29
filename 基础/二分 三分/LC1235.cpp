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