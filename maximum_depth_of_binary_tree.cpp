/*
LeetCode 104: Maximum Depth of Binary Tree
Difficulty: Easy
Companies: Amazon, Google, Microsoft

Problem:
Given the root of a binary tree, return its maximum depth.
A binary tree's maximum depth is the number of nodes along the longest path 
from the root node down to the farthest leaf node.

Example:
Input: root = [3,9,20,null,null,15,7]
Output: 3

Time Complexity: O(n) where n is the number of nodes
Space Complexity: O(h) where h is the height of the tree (O(log n) for balanced, O(n) for skewed)
*/

#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

// Definition for a binary tree node
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
    // Approach 1: Recursive DFS (Most intuitive)
    // Time: O(n), Space: O(h)
    int maxDepth(TreeNode* root) {
        if (!root) return 0;
        return 1 + max(maxDepth(root->left), maxDepth(root->right));
    }
    
    // Approach 2: Iterative BFS (Level order traversal)
    // Time: O(n), Space: O(w) where w is maximum width of tree
    int maxDepthBFS(TreeNode* root) {
        if (!root) return 0;
        
        queue<TreeNode*> q;
        q.push(root);
        int depth = 0;
        
        while (!q.empty()) {
            int levelSize = q.size();
            depth++;
            
            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front();
                q.pop();
                
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
        
        return depth;
    }
    
    // Approach 3: Iterative DFS using stack with pair<node, depth>
    // Time: O(n), Space: O(h)
    int maxDepthIterativeDFS(TreeNode* root) {
        if (!root) return 0;
        
        stack<pair<TreeNode*, int>> stk;
        stk.push({root, 1});
        int maxDepth = 0;
        
        while (!stk.empty()) {
            auto [node, depth] = stk.top();
            stk.pop();
            
            maxDepth = max(maxDepth, depth);
            
            if (node->right) stk.push({node->right, depth + 1});
            if (node->left) stk.push({node->left, depth + 1});
        }
        
        return maxDepth;
    }
};

// Helper function to create test tree
TreeNode* createTestTree() {
    // Creating tree: [3,9,20,null,null,15,7]
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);
    return root;
}

int main() {
    Solution sol;
    TreeNode* root = createTestTree();
    
    cout << "Maximum Depth (Recursive): " << sol.maxDepth(root) << endl;
    cout << "Maximum Depth (BFS): " << sol.maxDepthBFS(root) << endl;
    cout << "Maximum Depth (Iterative DFS): " << sol.maxDepthIterativeDFS(root) << endl;
    
    return 0;
}

/*
Key Insights:
1. Recursive approach is most intuitive - depth of tree = 1 + max depth of subtrees
2. BFS naturally processes level by level, counting levels gives depth
3. For balanced trees, all approaches have similar performance
4. BFS uses more space for wide trees, DFS uses more space for deep trees
5. This is a fundamental tree problem that tests basic tree traversal understanding

Follow-up Questions:
- How would you modify to find minimum depth?
- What if tree nodes can have more than 2 children?
- How to find depth of a specific node?
*/