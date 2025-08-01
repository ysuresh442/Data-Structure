/*
LeetCode 112: Path Sum
Difficulty: Easy
Companies: Amazon, Google, Microsoft

Problem:
Given the root of a binary tree and an integer targetSum, return true if the tree 
has a root-to-leaf path such that adding up all the values along the path equals targetSum.

A leaf is a node with no children.

Example:
Input: root = [5,4,8,11,null,13,4,7,2,null,null,null,1], targetSum = 22
Output: true (path: 5 + 4 + 11 + 2 = 22)

Time Complexity: O(n) where n is the number of nodes
Space Complexity: O(h) where h is the height of the tree
*/

#include <iostream>
#include <stack>
#include <queue>
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
    // Approach 1: Recursive DFS (Top-down)
    // Time: O(n), Space: O(h)
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (!root) return false;
        
        // If we reach a leaf node, check if remaining sum equals node value
        if (!root->left && !root->right) {
            return targetSum == root->val;
        }
        
        // Recurse on children with reduced target sum
        int remainingSum = targetSum - root->val;
        return hasPathSum(root->left, remainingSum) || 
               hasPathSum(root->right, remainingSum);
    }
    
    // Approach 2: Iterative DFS using stack with pairs
    // Time: O(n), Space: O(h)
    bool hasPathSumIterative(TreeNode* root, int targetSum) {
        if (!root) return false;
        
        stack<pair<TreeNode*, int>> stk;
        stk.push({root, targetSum});
        
        while (!stk.empty()) {
            auto [node, sum] = stk.top();
            stk.pop();
            
            // If leaf node, check if sum equals node value
            if (!node->left && !node->right) {
                if (sum == node->val) return true;
                continue;
            }
            
            // Add children with updated sum
            if (node->right) {
                stk.push({node->right, sum - node->val});
            }
            if (node->left) {
                stk.push({node->left, sum - node->val});
            }
        }
        
        return false;
    }
    
    // Approach 3: BFS using queue
    // Time: O(n), Space: O(w) where w is maximum width
    bool hasPathSumBFS(TreeNode* root, int targetSum) {
        if (!root) return false;
        
        queue<pair<TreeNode*, int>> q;
        q.push({root, targetSum});
        
        while (!q.empty()) {
            auto [node, sum] = q.front();
            q.pop();
            
            // If leaf node, check if sum equals node value
            if (!node->left && !node->right) {
                if (sum == node->val) return true;
                continue;
            }
            
            // Add children with updated sum
            if (node->left) {
                q.push({node->left, sum - node->val});
            }
            if (node->right) {
                q.push({node->right, sum - node->val});
            }
        }
        
        return false;
    }
    
    // Approach 4: Accumulative approach (bottom-up thinking)
    bool hasPathSumAccumulative(TreeNode* root, int targetSum) {
        return dfsAccumulative(root, 0, targetSum);
    }
    
private:
    bool dfsAccumulative(TreeNode* root, int currentSum, int targetSum) {
        if (!root) return false;
        
        currentSum += root->val;
        
        // If leaf node, check if current sum equals target
        if (!root->left && !root->right) {
            return currentSum == targetSum;
        }
        
        return dfsAccumulative(root->left, currentSum, targetSum) ||
               dfsAccumulative(root->right, currentSum, targetSum);
    }
};

// Helper function to create test tree
TreeNode* createTestTree() {
    // Creating tree: [5,4,8,11,null,13,4,7,2,null,null,null,1]
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(4);
    root->right = new TreeNode(8);
    root->left->left = new TreeNode(11);
    root->left->left->left = new TreeNode(7);
    root->left->left->right = new TreeNode(2);
    root->right->left = new TreeNode(13);
    root->right->right = new TreeNode(4);
    root->right->right->right = new TreeNode(1);
    return root;
}

int main() {
    Solution sol;
    TreeNode* root = createTestTree();
    int targetSum = 22;
    
    cout << "Has path sum " << targetSum << " (Recursive): " 
         << (sol.hasPathSum(root, targetSum) ? "Yes" : "No") << endl;
    cout << "Has path sum " << targetSum << " (Iterative): " 
         << (sol.hasPathSumIterative(root, targetSum) ? "Yes" : "No") << endl;
    cout << "Has path sum " << targetSum << " (BFS): " 
         << (sol.hasPathSumBFS(root, targetSum) ? "Yes" : "No") << endl;
    cout << "Has path sum " << targetSum << " (Accumulative): " 
         << (sol.hasPathSumAccumulative(root, targetSum) ? "Yes" : "No") << endl;
    
    return 0;
}

/*
Key Insights:
1. Must check ONLY root-to-leaf paths (not just any path)
2. A leaf is defined as a node with no children
3. Can use either subtractive (reduce target) or accumulative (add current) approach
4. Early termination possible when path is found
5. All traversal methods work, but DFS is more natural for path problems

Common Mistakes:
- Forgetting to check if node is a leaf before validating sum
- Including internal nodes in path sum validation
- Not handling negative numbers properly
- Forgetting edge case of empty tree

Edge Cases:
- Empty tree: return false
- Single node tree: check if node value equals target
- Tree with negative values: algorithm still works
- Target sum of 0: valid case to handle

Follow-up Variations:
- Path Sum II: Find all root-to-leaf paths with given sum
- Path Sum III: Find any path (not necessarily root-to-leaf) with given sum
- Binary Tree Maximum Path Sum: Find path with maximum sum
*/