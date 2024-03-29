struct TreeNode {
	T key;
	TreeNode* left;
	TreeNode* right;
	// 维护其他信息，如高度，节点数量等
	i64 size;   // 当前节点为根的子树大小
	i64 count;  // 当前节点的重复数量
	TreeNode(i64 value)
		: key(value), size(1), count(1), left(nullptr), right(nullptr) {}
};



template<typename T>
struct BinarySearchTree {
public:
	TreeNode<T>* root = nullptr;
	void inorderTraversal(TreeNode<T>* cur) {
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
	bool search(TreeNode<T>* cur, T target) {
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
	TreeNode<T>* insert(TreeNode<T>* cur, T value) {
		if (cur == nullptr) {
			return new TreeNode<T>(value);
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
	TreeNode<T>* findMinNode(TreeNode<T>* v) {
		TreeNode<T> *cur = v;
		while (cur->left != nullptr) {
			cur = cur->left;
		}
		return cur;
	}


// 此处返回值为删除 value 后的新 cur
	TreeNode<T>* remove(TreeNode<T>* cur, T value) {
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
					TreeNode<T>* temp = cur->right;
					delete cur;
					return temp;
				} else if (cur->right == nullptr) {
					TreeNode<T>* temp = cur->left;
					delete cur;
					return temp;
				} else {
					TreeNode<T>* successor = findMinNode(cur->right);
					cur->key = successor->key;
					cur->count = successor->count;  // 更新重复数量
					cur->right = remove(cur->right, successor->key);
				}
			}
		}
		return cur;
	}

	void remove(T value) {
		root = remove(root, value);
	}
	i64 queryRank(TreeNode<T>* cur, T v) {
		if (cur == nullptr) return 0;
		if (cur->key == v) return (cur->left ? cur->left->size : 0) + 1;
		if (cur->key > v) return queryRank(cur->left, v);
		return queryRank(cur->right, v) + (cur->left ? cur->left->size : 0) +
		       cur->count;
	}

	i64 queryRank(T v) {
		return queryRank(root, v);
	}

	i64 queryValue(TreeNode<T>* cur, T k) {
		if (cur == nullptr) return -1;  // 或者根据需求返回其他合适的值
		if (cur->left) {
			if (cur->left->size >= k) return queryValue(cur->left, k);
			if (cur->left->size + cur->count >= k) return cur->key;
		} else {
			if (k == 1) return cur->key;
		}
		return queryValue(cur->right,
		                  k - (cur->left ? cur->left->size : 0) - cur->count);
	}

	i64 queryValue(T v) {
		return queryValue(root, v);
	}
};