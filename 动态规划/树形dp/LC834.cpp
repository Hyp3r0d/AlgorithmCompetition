class Solution {
public:

	vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
		vector<int>tr[n + 5];
		for (int i = 0; i < n; i++)tr[i].clear();
		for (auto c : edges) {
			int a = c[0], b = c[1];
			tr[a].push_back(b);
			tr[b].push_back(a);
		}
		vector<int>dp(n + 5, 0), sz(n + 5);
		function<void(int, int)>dfs = [&](int u, int f) {
			sz[u] = 1;
			for (auto v : tr[u]) {
				if (v == f)continue;
				dfs(v, u);
				dp[u] += dp[v] + sz[v];
				sz[u] += sz[v];
			}
		};
		dfs(0, -1);
      // 换根: dp1 固定根的答案 dp2 当前节点为根的答案
        std::vector<int>dp2(n);
		
        dp2[0] = dp[0];
        function<void(int, int)>tarjan = [&](int u, int f) {
			for (auto v : tr[u]) {
				if (v == f)continue;
				dp2[v] = dp2[u] - (dp[v] + sz[v]) + (n - sz[v]) + dp[v];  
                tarjan(v, u);
			}
		};
		tarjan(0, -1);
		return dp2;
	}
};