/*
LeetCode 111: Minimum Depth of Binary Tree
Difficulty: Easy
Companies: Amazon, Google, Facebook

Problem:
Given a binary tree, find its minimum depth.
The minimum depth is the number of nodes along the shortest path 
from the root node down to the nearest leaf node.

Note: A leaf is a node with no children.

Example:
Input: root = [3,9,20,null,null,15,7]
Output: 2

Input: root = [2,null,3,null,4,null,5,null,6]
Output: 5

Time Complexity: O(n) where n is the number of nodes
Space Complexity: O(h) where h is the height of the tree
*/

#include <iostream>
#include <queue>
#include <algorithm>
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
    // Approach 1: Recursive DFS (careful with logic)
    // Time: O(n), Space: O(h)
    int minDepth(TreeNode* root) {
        if (!root) return 0;
        
        // If one child is missing, return depth of the other child + 1
        if (!root->left) return 1 + minDepth(root->right);
        if (!root->right) return 1 + minDepth(root->left);
        
        // Both children exist, return minimum of both + 1
        return 1 + min(minDepth(root->left), minDepth(root->right));
    }
    
    // Approach 2: BFS (optimal for minimum depth - early termination)
    // Time: O(n) worst case, but often better, Space: O(w) where w is max width
    int minDepthBFS(TreeNode* root) {
        if (!root) return 0;
        
        queue<TreeNode*> q;
        q.push(root);
        int depth = 1;
        
        while (!q.empty()) {
            int levelSize = q.size();
            
            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front();
                q.pop();
                
                // If we find a leaf, this is the minimum depth
                if (!node->left && !node->right) {
                    return depth;
                }
                
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            
            depth++;
        }
        
        return depth;
    }
    
    // Approach 3: DFS with early termination optimization
    // Time: O(n), Space: O(h)
    int minDepthOptimized(TreeNode* root) {
        if (!root) return 0;
        return dfsMinDepth(root);
    }
    
private:
    int dfsMinDepth(TreeNode* root) {
        if (!root) return INT_MAX; // Not a valid path
        
        // If leaf node, return 1
        if (!root->left && !root->right) return 1;
        
        // Get minimum depth from children
        int leftDepth = dfsMinDepth(root->left);
        int rightDepth = dfsMinDepth(root->right);
        
        return 1 + min(leftDepth, rightDepth);
    }
    
public:
    // Approach 4: Iterative DFS using stack
    // Time: O(n), Space: O(h)
    int minDepthIterativeDFS(TreeNode* root) {
        if (!root) return 0;
        
        stack<pair<TreeNode*, int>> stk;
        stk.push({root, 1});
        int minDepth = INT_MAX;
        
        while (!stk.empty()) {
            auto [node, depth] = stk.top();
            stk.pop();
            
            // If leaf node, update minimum depth
            if (!node->left && !node->right) {
                minDepth = min(minDepth, depth);
                continue;
            }
            
            // Pruning: if current depth >= minDepth, skip
            if (depth >= minDepth) continue;
            
            if (node->right) stk.push({node->right, depth + 1});
            if (node->left) stk.push({node->left, depth + 1});
        }
        
        return minDepth;
    }
    
    // Approach 5: Simple recursive (less optimal)
    // Time: O(n), Space: O(h)
    int minDepthSimple(TreeNode* root) {
        if (!root) return 0;
        
        int left = minDepthSimple(root->left);
        int right = minDepthSimple(root->right);
        
        // Key insight: if one subtree is empty, we must use the other
        if (left == 0 || right == 0) {
            return 1 + left + right; // One will be 0, so this gives 1 + non-zero depth
        }
        
        return 1 + min(left, right);
    }
};

// Helper functions for testing
TreeNode* createTestTree1() {
    // Tree: [3,9,20,null,null,15,7] - min depth = 2
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);
    return root;
}

TreeNode* createTestTree2() {
    // Tree: [2,null,3,null,4,null,5,null,6] - min depth = 5 (skewed tree)
    TreeNode* root = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->right = new TreeNode(4);
    root->right->right->right = new TreeNode(5);
    root->right->right->right->right = new TreeNode(6);
    return root;
}

int main() {
    Solution sol;
    
    TreeNode* tree1 = createTestTree1();
    TreeNode* tree2 = createTestTree2();
    
    cout << "Tree 1 minimum depth:" << endl;
    cout << "Recursive: " << sol.minDepth(tree1) << endl;
    cout << "BFS: " << sol.minDepthBFS(tree1) << endl;
    cout << "Optimized: " << sol.minDepthOptimized(tree1) << endl;
    cout << "Iterative DFS: " << sol.minDepthIterativeDFS(tree1) << endl;
    cout << "Simple: " << sol.minDepthSimple(tree1) << endl;
    
    cout << "\nTree 2 minimum depth:" << endl;
    cout << "Recursive: " << sol.minDepth(tree2) << endl;
    cout << "BFS: " << sol.minDepthBFS(tree2) << endl;
    cout << "Optimized: " << sol.minDepthOptimized(tree2) << endl;
    cout << "Iterative DFS: " << sol.minDepthIterativeDFS(tree2) << endl;
    cout << "Simple: " << sol.minDepthSimple(tree2) << endl;
    
    return 0;
}

/*
Key Insights:
1. Minimum depth is distance to the NEAREST LEAF, not any node
2. If one child is null, you MUST go through the other child
3. BFS is often better for minimum problems due to early termination
4. Different from maximum depth - can't just take min of children
5. Must handle the case where one or both children are missing

Comparison of Approaches:
1. Recursive: Clean logic, handles edge cases well
2. BFS: Best for finding minimum due to level-by-level processing
3. Optimized DFS: Uses INT_MAX for invalid paths
4. Iterative DFS: Stack-based with pruning optimization
5. Simple recursive: Alternative logic using sum property

Edge Cases:
- Empty tree: return 0
- Single node: return 1
- Skewed tree (like linked list): minimum depth = number of nodes
- Tree with one child missing at some nodes

Interview Tips:
- Clarify that we need path to a LEAF node
- Explain why we can't just take min when one child is null
- BFS is often optimal for minimum depth problems
- Mention early termination advantages

Common Mistakes:
- Taking min of children when one is null (wrong!)
- Forgetting that path must end at a leaf
- Not handling the null child cases properly
- Confusing with maximum depth logic

Optimization Notes:
- BFS terminates early when first leaf is found
- DFS with pruning can skip unnecessary branches
- For very wide trees, DFS might be better (less space)
- For very deep trees, BFS might be better (early termination)

Related Problems:
- Maximum Depth of Binary Tree
- Binary Tree Level Order Traversal  
- Path Sum (similar path-to-leaf logic)
*/