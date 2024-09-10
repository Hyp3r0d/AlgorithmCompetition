class Solution {
public:
    int lengthOfLongestSubsequence(vector<int>& nums, int target) {
        int n = nums.size();
        vector dp(n + 1, vector<int>(target + 1, -0x3f3f3f3f));
        dp[0][0] = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= target; j++) {
                if (dp[i - 1][j] != -0x3f3f3f3f)dp[i][j] = max(dp[i][j], dp[i - 1][j]);
            }
            for (int j = 0; j <= target; j++) {
                if (j >= nums[i - 1]) {
                    if (dp[i - 1][j - nums[i - 1]] != -0x3f3f3f3f)dp[i][j] = max(dp[i][j], dp[i - 1][j - nums[i - 1]] + 1);
                }
            }
        }
        if (dp[n][target] == -0x3f3f3f3f)return -1;
        return dp[n][target];
    }
};