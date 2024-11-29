class Solution {
    public int dfs(int i,int j, int[][] memo) {
        if(i == 0 || j == 0)return 0;
        if(memo[i][j] != 0) return memo[i][j];
        return dfs(i - 1, j, memo) + dfs(i - 1, j - 1, memo) + 1;
    }
    public int superEggDrop(int k, int n) {
        int [][] memo = new int[n + 1][];
        for(int i = 1;  ;i ++) {
            memo[i] = new int[k + 1];
            if(this.dfs(i, k, memo) >= n) return i;
        }
       // return 0;
    }
}