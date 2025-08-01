/*
LeetCode 110: Balanced Binary Tree
Difficulty: Easy
Companies: Amazon, Google, Facebook

Problem:
Given a binary tree, determine if it is height-balanced.
A height-balanced binary tree is one in which the depth of the two subtrees 
of every node never differ by more than 1.

Example:
Input: root = [3,9,20,null,null,15,7]
Output: true

Input: root = [1,2,2,3,3,null,null,4,4]
Output: false

Time Complexity: O(n) where n is the number of nodes
Space Complexity: O(h) where h is the height of the tree
*/

#include <iostream>
#include <algorithm>
#include <cmath>
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
    // Approach 1: Top-down approach (less efficient)
    // Time: O(n log n) worst case, Space: O(h)
    bool isBalanced(TreeNode* root) {
        if (!root) return true;
        
        // Check if current node is balanced
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);
        
        if (abs(leftHeight - rightHeight) > 1) return false;
        
        // Recursively check subtrees
        return isBalanced(root->left) && isBalanced(root->right);
    }
    
    // Approach 2: Bottom-up approach (optimal)
    // Time: O(n), Space: O(h)
    bool isBalancedOptimal(TreeNode* root) {
        return checkBalance(root) != -1;
    }
    
    // Approach 3: Using pair to return both height and balance status
    // Time: O(n), Space: O(h)
    bool isBalancedWithPair(TreeNode* root) {
        auto result = checkBalanceWithPair(root);
        return result.second;
    }
    
private:
    // Helper function for approach 1
    int height(TreeNode* root) {
        if (!root) return 0;
        return 1 + max(height(root->left), height(root->right));
    }
    
    // Helper function for approach 2
    // Returns -1 if unbalanced, otherwise returns height
    int checkBalance(TreeNode* root) {
        if (!root) return 0;
        
        int leftHeight = checkBalance(root->left);
        if (leftHeight == -1) return -1; // Left subtree unbalanced
        
        int rightHeight = checkBalance(root->right);
        if (rightHeight == -1) return -1; // Right subtree unbalanced
        
        // Check if current node is balanced
        if (abs(leftHeight - rightHeight) > 1) return -1;
        
        return 1 + max(leftHeight, rightHeight);
    }
    
    // Helper function for approach 3
    // Returns pair<height, isBalanced>
    pair<int, bool> checkBalanceWithPair(TreeNode* root) {
        if (!root) return {0, true};
        
        auto leftResult = checkBalanceWithPair(root->left);
        if (!leftResult.second) return {-1, false};
        
        auto rightResult = checkBalanceWithPair(root->right);
        if (!rightResult.second) return {-1, false};
        
        bool balanced = abs(leftResult.first - rightResult.first) <= 1;
        int height = 1 + max(leftResult.first, rightResult.first);
        
        return {height, balanced};
    }
    
public:
    // Approach 4: Using global flag (alternative style)
    // Time: O(n), Space: O(h)
    bool isBalancedGlobalFlag(TreeNode* root) {
        bool balanced = true;
        checkBalanceGlobal(root, balanced);
        return balanced;
    }
    
private:
    int checkBalanceGlobal(TreeNode* root, bool& balanced) {
        if (!root || !balanced) return 0;
        
        int leftHeight = checkBalanceGlobal(root->left, balanced);
        int rightHeight = checkBalanceGlobal(root->right, balanced);
        
        if (abs(leftHeight - rightHeight) > 1) {
            balanced = false;
        }
        
        return 1 + max(leftHeight, rightHeight);
    }
};

// Helper functions for testing
TreeNode* createBalancedTree() {
    // Tree: [3,9,20,null,null,15,7] - balanced
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);
    return root;
}

TreeNode* createUnbalancedTree() {
    // Tree: [1,2,2,3,3,null,null,4,4] - unbalanced
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(2);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(3);
    root->left->left->left = new TreeNode(4);
    root->left->left->right = new TreeNode(4);
    return root;
}

int main() {
    Solution sol;
    
    TreeNode* balanced = createBalancedTree();
    TreeNode* unbalanced = createUnbalancedTree();
    
    cout << "Balanced tree tests:" << endl;
    cout << "Top-down: " << (sol.isBalanced(balanced) ? "Yes" : "No") << endl;
    cout << "Bottom-up: " << (sol.isBalancedOptimal(balanced) ? "Yes" : "No") << endl;
    cout << "With pair: " << (sol.isBalancedWithPair(balanced) ? "Yes" : "No") << endl;
    cout << "Global flag: " << (sol.isBalancedGlobalFlag(balanced) ? "Yes" : "No") << endl;
    
    cout << "\nUnbalanced tree tests:" << endl;
    cout << "Top-down: " << (sol.isBalanced(unbalanced) ? "Yes" : "No") << endl;
    cout << "Bottom-up: " << (sol.isBalancedOptimal(unbalanced) ? "Yes" : "No") << endl;
    cout << "With pair: " << (sol.isBalancedWithPair(unbalanced) ? "Yes" : "No") << endl;
    cout << "Global flag: " << (sol.isBalancedGlobalFlag(unbalanced) ? "Yes" : "No") << endl;
    
    return 0;
}

/*
Key Insights:
1. Height-balanced means |left_height - right_height| <= 1 for every node
2. Must check balance at every node, not just root
3. Bottom-up approach is more efficient than top-down
4. Can combine height calculation with balance checking for optimization
5. Early termination possible when imbalance is detected

Comparison of Approaches:
1. Top-down: Intuitive but inefficient O(n log n) due to repeated height calculations
2. Bottom-up: Optimal O(n) by calculating height and checking balance in single pass
3. With pair: Clean code structure, returns both height and balance status
4. Global flag: Alternative style using reference parameter

Edge Cases:
- Empty tree: balanced by definition
- Single node: balanced
- Linear tree (like linked list): unbalanced
- Perfect binary tree: always balanced
- Complete binary tree: always balanced

Interview Tips:
- Start with top-down approach but mention it's not optimal
- Quickly move to bottom-up approach for optimal solution
- Explain the key insight: combine height calculation with balance checking
- Discuss early termination optimization

Common Mistakes:
- Only checking balance at root (must check every node)
- Inefficient repeated height calculations
- Forgetting that empty tree is balanced
- Not handling the -1 return value properly in bottom-up approach

Related Problems:
- Maximum Depth of Binary Tree
- Minimum Depth of Binary Tree
- Diameter of Binary Tree
- AVL Tree operations
*/