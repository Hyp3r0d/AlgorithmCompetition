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
// 基于随机算法的质因数分解


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
        TreeNode * root = new TreeNode(preorder.front());
        i64 n = postorder.size();
        std::vector<i64>pos(n + 1);
        for (i64 i = 0; i < n; i++) {
            pos[postorder[i]] = i;
        }
        std::function<void(TreeNode *, i64 , i64, i64, i64)>dfs = [&](TreeNode * cur, i64 l1, i64 r1, i64 l2, i64 r2) {
            if (r1 - l1 + 1 == 1) return;
            i64 mid = pos[preorder[l1 + 1]];
            i64 len1 = mid - l2 + 1;
            i64 len2 = r2 - mid - 1;
            if (len1) {
                TreeNode * lef = new TreeNode(preorder[l1 + 1]);
                cur->left = lef;
                dfs(cur->left, l1 + 1, l1 + len1, l2, l2 + len1 - 1);
            }
            if (len2) {
                TreeNode * righ = new TreeNode(preorder[l1 + len1 + 1]);
                cur->right = righ;
                dfs(cur->right, l1 + len1 + 1, r1, l2 + len1, r2 - 1);
            }
        };
        dfs(root, 0, n - 1, 0 , n - 1);
        return root;
    }
};