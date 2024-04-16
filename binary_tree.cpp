#include "common.hpp"

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) { }
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) { }
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) { }
};
void traversalRecurse(TreeNode* cur, vector<int>& vec)
{
    if (cur == nullptr) return;
    vec.push_back(cur->val);
    traversalRecurse(cur->left, vec);
    traversalRecurse(cur->right, vec);
}
vector<int> preorderTraversal(TreeNode* root)
{
    vector<int> vec;
    traversalRecurse(root, vec);
    return vec;
}
int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    cout << "Preorder traversal: " << preorderTraversal(root) << endl;
    return 0;
}