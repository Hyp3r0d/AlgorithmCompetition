template<typename T>
struct BinarySearchTree {
private:
  struct TreeNode {
    T key;
    TreeNode* left;
    TreeNode* right;
    // 维护其他信息，如高度，节点数量等
    i64 size;   // 当前节点为根的子树大小
    i64 count;  // 当前节点的重复数量
    TreeNode(T value)
      : key(value), size(1), count(1), left(nullptr), right(nullptr) {}
  };

  TreeNode* root = nullptr;

public:
  void inorderTraversal(TreeNode* cur) {
    if (cur == nullptr) {
      return;
    }
    inorderTraversal(cur->left);
    std::cout << cur->key << " ";
    inorderTraversal(cur->right);
  }

  void inorderTraversal() {
    inorderTraversal(root);
  }

  bool search(TreeNode* cur, T target) {
    if (cur == nullptr) {
      return false;
    }
    if (cur->key == target) {
      return true;
    } else if (target < cur->key) {
      return search(cur->left, target);
    } else {
      return search(cur->right, target);
    }
  }

  bool search(T target) {
    return search(root, target);
  }

  TreeNode* insert(TreeNode* cur, T value) {
    if (cur == nullptr) {
      return new TreeNode(value);
    }
    if (value < cur->key) {
      cur->left = insert(cur->left, value);
    } else if (value > cur->key) {
      cur->right = insert(cur->right, value);
    } else {
      cur->count++;  // 节点值相等，增加重复数量
    }
    cur->size = cur->count + (cur->left ? cur->left->size : 0) +
                (cur->right ? cur->right->size : 0);  // 更新节点的子树大小
    return cur;
  }

  void insert(T value) {
    root = insert(root, value);
  }

  // 此处以右子树的最小值为例
  TreeNode* findMinNode(TreeNode* v) {
    TreeNode *cur = v;
    while (cur->left != nullptr) {
      cur = cur->left;
    }
    return cur;
  }

  // 此处返回值为删除 value 后的新 cur
  TreeNode* remove(TreeNode* cur, T value) {
    if (cur == nullptr) {
      return cur;
    }
    if (value < cur->key) {
      cur->left = remove(cur->left, value);
    } else if (value > cur->key) {
      cur->right = remove(cur->right, value);
    } else {
      if (cur->count > 1) {
        cur->count--;  // 节点重复数量大于1，减少重复数量
      } else {
        if (cur->left == nullptr) {
          TreeNode* temp = cur->right;
          delete cur;
          return temp;
        } else if (cur->right == nullptr) {
          TreeNode* temp = cur->left;
          delete cur;
          return temp;
        } else {
          TreeNode* successor = findMinNode(cur->right);
          cur->key = successor->key;
          cur->count = successor->count;  // 更新重复数量
          successor->count = 1;
          cur->right = remove(cur->right, successor->key);
        }
      }
    }
    cur->size = cur ->count + (cur->left ? cur->left->size : 0) +
                (cur->right ? cur->right->size : 0);
    return cur;
  }

  void remove(T value) {
    root = remove(root, value);
  }


  /*查找某个值的排名*/
  i64 queryRank(TreeNode* cur, T v) {
    if (cur == nullptr) return 0;
    if (cur->key == v) return (cur->left ? cur->left->size : 0) + 1;
    if (cur->key > v) return queryRank(cur->left, v);
    return queryRank(cur->right, v) + (cur->left ? cur->left->size : 0) +
           cur->count;
  }

  i64 queryRank(T v) {
    if (not search(v))return -1;
    return queryRank(root, v); // 树中没有该值返回-1
  }

  /*查找排名为k的某个值*/
  T queryValue(TreeNode* cur, T k) {
    if (cur == nullptr) {
      return -1; // 或者抛出异常，表示 k 超出范围
    }
    T leftSize = (cur->left ? cur->left->size : 0);
    if (k <= leftSize) {
      return queryValue(cur->left, k); // 在左子树中查找
    } else if (k <= leftSize + cur->count) {
      return cur->key; // 当前节点就是第 k 大
    } else {
      return queryValue(cur->right, k - leftSize - cur->count); // 在右子树中查找
    }
  }

  T queryValue(T v) {
    return queryValue(root, v);
  }
};