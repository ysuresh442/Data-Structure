/*
LeetCode 102: Binary Tree Level Order Traversal
Difficulty: Medium
Companies: Amazon, Google, Facebook

Problem:
Given the root of a binary tree, return the level order traversal of its nodes' values.
(i.e., from left to right, level by level).

Example:
Input: root = [3,9,20,null,null,15,7]
Output: [[3],[9,20],[15,7]]

Input: root = [1]
Output: [[1]]

Time Complexity: O(n) where n is the number of nodes
Space Complexity: O(w) where w is the maximum width of the tree
*/

#include <iostream>
#include <vector>
#include <queue>
#include <deque>
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
    // Approach 1: BFS with queue (most common approach)
    // Time: O(n), Space: O(w)
    vector<vector<int>> levelOrder(TreeNode* root) {
        if (!root) return {};
        
        vector<vector<int>> result;
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            int levelSize = q.size();
            vector<int> currentLevel;
            
            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front();
                q.pop();
                
                currentLevel.push_back(node->val);
                
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            
            result.push_back(currentLevel);
        }
        
        return result;
    }
    
    // Approach 2: DFS with level tracking (recursive)
    // Time: O(n), Space: O(h)
    vector<vector<int>> levelOrderDFS(TreeNode* root) {
        vector<vector<int>> result;
        dfs(root, 0, result);
        return result;
    }
    
private:
    void dfs(TreeNode* node, int level, vector<vector<int>>& result) {
        if (!node) return;
        
        // Ensure we have enough levels in result
        if (level >= result.size()) {
            result.push_back(vector<int>());
        }
        
        // Add current node to its level
        result[level].push_back(node->val);
        
        // Recursively process children
        dfs(node->left, level + 1, result);
        dfs(node->right, level + 1, result);
    }
    
public:
    // Approach 3: BFS with queue and level markers
    // Time: O(n), Space: O(w)
    vector<vector<int>> levelOrderWithMarker(TreeNode* root) {
        if (!root) return {};
        
        vector<vector<int>> result;
        queue<TreeNode*> q;
        q.push(root);
        q.push(nullptr); // Level marker
        
        vector<int> currentLevel;
        
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            
            if (node == nullptr) {
                // End of current level
                result.push_back(currentLevel);
                currentLevel.clear();
                
                if (!q.empty()) {
                    q.push(nullptr); // Marker for next level
                }
            } else {
                currentLevel.push_back(node->val);
                
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
        
        return result;
    }
    
    // Approach 4: Using two queues
    // Time: O(n), Space: O(w)
    vector<vector<int>> levelOrderTwoQueues(TreeNode* root) {
        if (!root) return {};
        
        vector<vector<int>> result;
        queue<TreeNode*> current, next;
        current.push(root);
        
        while (!current.empty()) {
            vector<int> level;
            
            while (!current.empty()) {
                TreeNode* node = current.front();
                current.pop();
                
                level.push_back(node->val);
                
                if (node->left) next.push(node->left);
                if (node->right) next.push(node->right);
            }
            
            result.push_back(level);
            swap(current, next);
        }
        
        return result;
    }
    
    // Approach 5: BFS with node-level pairs
    // Time: O(n), Space: O(w)
    vector<vector<int>> levelOrderPairs(TreeNode* root) {
        if (!root) return {};
        
        vector<vector<int>> result;
        queue<pair<TreeNode*, int>> q;
        q.push({root, 0});
        
        while (!q.empty()) {
            auto [node, level] = q.front();
            q.pop();
            
            // Ensure we have enough levels
            if (level >= result.size()) {
                result.push_back(vector<int>());
            }
            
            result[level].push_back(node->val);
            
            if (node->left) q.push({node->left, level + 1});
            if (node->right) q.push({node->right, level + 1});
        }
        
        return result;
    }
    
    // Approach 6: Iterative DFS with stack (unusual but possible)
    // Time: O(n), Space: O(h)
    vector<vector<int>> levelOrderIterativeDFS(TreeNode* root) {
        if (!root) return {};
        
        vector<vector<int>> result;
        stack<pair<TreeNode*, int>> stk;
        stk.push({root, 0});
        
        while (!stk.empty()) {
            auto [node, level] = stk.top();
            stk.pop();
            
            // Ensure we have enough levels
            if (level >= result.size()) {
                result.push_back(vector<int>());
            }
            
            result[level].push_back(node->val);
            
            // Push right first, then left (to maintain left-to-right order)
            if (node->right) stk.push({node->right, level + 1});
            if (node->left) stk.push({node->left, level + 1});
        }
        
        // Need to reverse each level since we pushed right first
        for (auto& level : result) {
            reverse(level.begin(), level.end());
        }
        
        return result;
    }
};

// Helper functions for testing
TreeNode* createTestTree() {
    // Tree: [3,9,20,null,null,15,7]
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);
    return root;
}

TreeNode* createComplexTree() {
    // Tree: [1,2,3,4,5,6,7]
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);
    return root;
}

// Helper function to print 2D vector
void print2DVector(const vector<vector<int>>& result, const string& approach) {
    cout << approach << ": [";
    for (int i = 0; i < result.size(); i++) {
        cout << "[";
        for (int j = 0; j < result[i].size(); j++) {
            cout << result[i][j];
            if (j < result[i].size() - 1) cout << ",";
        }
        cout << "]";
        if (i < result.size() - 1) cout << ",";
    }
    cout << "]" << endl;
}

int main() {
    Solution sol;
    TreeNode* tree1 = createTestTree();
    TreeNode* tree2 = createComplexTree();
    
    cout << "Tree [3,9,20,null,null,15,7]:" << endl;
    print2DVector(sol.levelOrder(tree1), "BFS");
    print2DVector(sol.levelOrderDFS(tree1), "DFS");
    print2DVector(sol.levelOrderWithMarker(tree1), "Marker");
    
    cout << "\nTree [1,2,3,4,5,6,7]:" << endl;
    print2DVector(sol.levelOrderTwoQueues(tree2), "Two Queues");
    print2DVector(sol.levelOrderPairs(tree2), "Pairs");
    print2DVector(sol.levelOrderIterativeDFS(tree2), "Iterative DFS");
    
    return 0;
}

/*
Key Insights:
1. Level order traversal is naturally suited for BFS (breadth-first search)
2. Key insight: process all nodes at current level before moving to next
3. Can track level size or use level markers to separate levels
4. DFS with level tracking is an alternative but less intuitive approach
5. This is the foundation for many other tree problems

Comparison of Approaches:
1. BFS with level size: Most common, clean and efficient
2. DFS with level tracking: Uses recursion, good for memory-constrained scenarios
3. BFS with markers: Alternative way to track level boundaries
4. Two queues: Explicit level separation, easier to understand
5. Node-level pairs: Stores level with each node
6. Iterative DFS: Unusual approach, mainly for educational purposes

Space Complexity Analysis:
- BFS approaches: O(w) where w is maximum width (can be O(n) for complete trees)
- DFS approaches: O(h) where h is height (can be O(n) for skewed trees)
- Choose based on tree characteristics

Interview Tips:
- Start with BFS approach (most natural for level order)
- Explain the key insight: process entire level before moving to next
- Mention that level size determines how many nodes to process
- Discuss space complexity trade-offs between BFS and DFS
- Show understanding that this is foundation for many tree problems

Edge Cases:
- Empty tree: return empty vector
- Single node: return [[root.val]]
- Complete binary tree: all levels filled except possibly last
- Skewed tree: essentially a linked list

Applications:
- Tree visualization and printing
- Finding level with maximum sum
- Zigzag level order traversal
- Binary tree right side view
- Populating next right pointers

Common Mistakes:
- Forgetting to track level size in BFS
- Not handling empty tree case
- Confusing level order with other traversals
- Incorrect level tracking in DFS approach

Variations:
- Level Order Traversal II (bottom-up)
- Zigzag Level Order Traversal
- Binary Tree Right Side View
- Average of Levels in Binary Tree
- Maximum Width of Binary Tree

Optimization Notes:
- BFS is naturally optimal for this problem
- For very deep trees, consider iterative approaches to avoid stack overflow
- For very wide trees, DFS uses less space
- Level order traversal visits each node exactly once

Related Problems:
- Binary Tree Zigzag Level Order Traversal (LC 103)
- Binary Tree Level Order Traversal II (LC 107)
- Binary Tree Right Side View (LC 199)
- Average of Levels in Binary Tree (LC 637)
- N-ary Tree Level Order Traversal (LC 429)
*/