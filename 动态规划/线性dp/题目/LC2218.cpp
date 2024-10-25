class Solution {
public:
    int maxValueOfCoins(vector<vector<int>>& piles, int k) {
        vector<int> f(k + 1);
        int sum_n = 0;
        for (auto& pile : piles) {
            int n = pile.size();
            pile.insert(pile.begin(), 0);
            for (int i = 1; i <= n; i++) {
                pile[i] += pile[i - 1]; // pile 前缀和
            }
            sum_n = min(sum_n + n, k); 
            for (int j = sum_n; j >= 0; j--) {
                for (int w = 0; w <= min(n, j); w++) {
                    f[j] = max(f[j], f[j - w] + pile[w]);
                }
            }
        }
        return f[k];
    }
};

