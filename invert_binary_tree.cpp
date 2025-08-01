/*
LeetCode 226: Invert Binary Tree
Difficulty: Easy
Companies: Google, Facebook, Apple

Problem:
Given the root of a binary tree, invert the tree, and return its root.
Invert means swap the left and right children of all nodes.

Example:
Input: root = [4,2,7,1,3,6,9]
Output: [4,7,2,9,6,3,1]

Time Complexity: O(n) where n is the number of nodes
Space Complexity: O(h) where h is the height of the tree
*/

#include <iostream>
#include <queue>
#include <stack>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    // Approach 1: Recursive DFS (Most elegant)
    // Time: O(n), Space: O(h)
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return nullptr;
        
        // Swap left and right children
        TreeNode* temp = root->left;
        root->left = root->right;
        root->right = temp;
        
        // Recursively invert subtrees
        invertTree(root->left);
        invertTree(root->right);
        
        return root;
    }
    
    // Approach 2: Recursive DFS (Alternative style)
    TreeNode* invertTreeAlt(TreeNode* root) {
        if (!root) return nullptr;
        
        TreeNode* left = invertTreeAlt(root->left);
        TreeNode* right = invertTreeAlt(root->right);
        
        root->left = right;
        root->right = left;
        
        return root;
    }
    
    // Approach 3: Iterative BFS using queue
    // Time: O(n), Space: O(w) where w is maximum width
    TreeNode* invertTreeBFS(TreeNode* root) {
        if (!root) return nullptr;
        
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            
            // Swap children
            swap(node->left, node->right);
            
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        
        return root;
    }
    
    // Approach 4: Iterative DFS using stack
    // Time: O(n), Space: O(h)
    TreeNode* invertTreeDFS(TreeNode* root) {
        if (!root) return nullptr;
        
        stack<TreeNode*> stk;
        stk.push(root);
        
        while (!stk.empty()) {
            TreeNode* node = stk.top();
            stk.pop();
            
            // Swap children
            swap(node->left, node->right);
            
            if (node->left) stk.push(node->left);
            if (node->right) stk.push(node->right);
        }
        
        return root;
    }
};

// Helper functions for testing
void printInorder(TreeNode* root) {
    if (!root) return;
    printInorder(root->left);
    cout << root->val << " ";
    printInorder(root->right);
}

TreeNode* createTestTree() {
    // Creating tree: [4,2,7,1,3,6,9]
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(7);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(9);
    return root;
}

int main() {
    Solution sol;
    TreeNode* root = createTestTree();
    
    cout << "Original tree (inorder): ";
    printInorder(root);
    cout << endl;
    
    root = sol.invertTree(root);
    
    cout << "Inverted tree (inorder): ";
    printInorder(root);
    cout << endl;
    
    return 0;
}

/*
Key Insights:
1. The problem is about swapping left and right children at every node
2. Can be solved with any tree traversal (preorder, postorder, level-order)
3. Inorder traversal would be trickier since we modify structure during traversal
4. Recursive solution is most intuitive and clean
5. This problem tests basic tree manipulation skills

Interview Tips:
- Start with recursive approach (easiest to explain)
- Mention that you can also do it iteratively
- Discuss space complexity trade-offs between BFS and DFS
- This is a classic problem made famous by Google/Homebrew creator incident

Edge Cases:
- Empty tree (return nullptr)
- Single node (return as is)
- Unbalanced trees work the same way
*/