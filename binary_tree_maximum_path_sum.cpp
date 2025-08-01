/*
LeetCode 124: Binary Tree Maximum Path Sum
Difficulty: Hard
Companies: Amazon, Google, Facebook

Problem:
A path in a binary tree is a sequence of nodes where each pair of adjacent nodes 
has an edge connecting them. A node can only appear in the sequence at most once.
The path does not need to pass through the root.

The path sum of a path is the sum of the node's values in the path.
Given the root of a binary tree, return the maximum path sum of any non-empty path.

Example:
Input: root = [1,2,3]
Output: 6 (path: 2 -> 1 -> 3)

Input: root = [-10,9,20,null,null,15,7]
Output: 42 (path: 15 -> 20 -> 7)

Time Complexity: O(n) where n is the number of nodes
Space Complexity: O(h) where h is the height of the tree
*/

#include <iostream>
#include <algorithm>
#include <climits>
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
private:
    int maxSum;
    
public:
    // Approach 1: Recursive DFS with global maximum (most common)
    // Time: O(n), Space: O(h)
    int maxPathSum(TreeNode* root) {
        maxSum = INT_MIN;
        maxPathSumHelper(root);
        return maxSum;
    }
    
private:
    // Returns maximum path sum starting from current node going down
    int maxPathSumHelper(TreeNode* node) {
        if (!node) return 0;
        
        // Get maximum path sum from left and right subtrees
        // Use max with 0 to ignore negative paths
        int leftSum = max(0, maxPathSumHelper(node->left));
        int rightSum = max(0, maxPathSumHelper(node->right));
        
        // Maximum path sum passing through current node
        int currentMaxPath = node->val + leftSum + rightSum;
        
        // Update global maximum
        maxSum = max(maxSum, currentMaxPath);
        
        // Return maximum path sum starting from current node
        // Can only choose one direction (left or right) when going up
        return node->val + max(leftSum, rightSum);
    }
    
public:
    // Approach 2: Using reference parameter instead of global variable
    // Time: O(n), Space: O(h)
    int maxPathSumRef(TreeNode* root) {
        int maxSum = INT_MIN;
        maxPathSumHelperRef(root, maxSum);
        return maxSum;
    }
    
private:
    int maxPathSumHelperRef(TreeNode* node, int& maxSum) {
        if (!node) return 0;
        
        int leftSum = max(0, maxPathSumHelperRef(node->left, maxSum));
        int rightSum = max(0, maxPathSumHelperRef(node->right, maxSum));
        
        // Path through current node
        int currentMaxPath = node->val + leftSum + rightSum;
        maxSum = max(maxSum, currentMaxPath);
        
        // Return path from current node going down one direction
        return node->val + max(leftSum, rightSum);
    }
    
public:
    // Approach 3: Using pair to return both values
    // Time: O(n), Space: O(h)
    int maxPathSumPair(TreeNode* root) {
        auto result = maxPathSumHelperPair(root);
        return result.second;
    }
    
private:
    // Returns pair<maxDownPath, maxGlobalPath>
    pair<int, int> maxPathSumHelperPair(TreeNode* node) {
        if (!node) return {0, INT_MIN};
        
        auto left = maxPathSumHelperPair(node->left);
        auto right = maxPathSumHelperPair(node->right);
        
        // Maximum path going down from current node
        int maxDown = node->val + max({0, left.first, right.first});
        
        // Maximum path through current node (can use both children)
        int maxThrough = node->val + max(0, left.first) + max(0, right.first);
        
        // Maximum path in entire subtree
        int maxGlobal = max({maxThrough, left.second, right.second});
        
        return {maxDown, maxGlobal};
    }
    
public:
    // Approach 4: Iterative with explicit stack (complex but educational)
    // Time: O(n), Space: O(n)
    int maxPathSumIterative(TreeNode* root) {
        if (!root) return 0;
        
        unordered_map<TreeNode*, int> maxDown; // Max path sum going down from node
        unordered_map<TreeNode*, bool> visited; // Whether node has been processed
        stack<TreeNode*> stk;
        
        stk.push(root);
        int result = INT_MIN;
        
        while (!stk.empty()) {
            TreeNode* node = stk.top();
            
            if (visited[node]) {
                stk.pop();
                
                // Calculate max path sum through this node
                int leftSum = node->left ? max(0, maxDown[node->left]) : 0;
                int rightSum = node->right ? max(0, maxDown[node->right]) : 0;
                
                // Max path through current node
                int pathThrough = node->val + leftSum + rightSum;
                result = max(result, pathThrough);
                
                // Max path going down from current node
                maxDown[node] = node->val + max({0, leftSum, rightSum});
            } else {
                visited[node] = true;
                
                // Push children first
                if (node->right) stk.push(node->right);
                if (node->left) stk.push(node->left);
            }
        }
        
        return result;
    }
    
    // Approach 5: With path tracking (for debugging/understanding)
    // Time: O(n), Space: O(h)
    int maxPathSumWithPath(TreeNode* root) {
        vector<TreeNode*> maxPath;
        int maxSum = INT_MIN;
        maxPathSumWithPathHelper(root, maxSum, maxPath);
        
        cout << "Maximum path: ";
        for (TreeNode* node : maxPath) {
            cout << node->val << " ";
        }
        cout << endl;
        
        return maxSum;
    }
    
private:
    int maxPathSumWithPathHelper(TreeNode* node, int& maxSum, vector<TreeNode*>& maxPath) {
        if (!node) return 0;
        
        int leftSum = max(0, maxPathSumWithPathHelper(node->left, maxSum, maxPath));
        int rightSum = max(0, maxPathSumWithPathHelper(node->right, maxSum, maxPath));
        
        int currentMaxPath = node->val + leftSum + rightSum;
        
        if (currentMaxPath > maxSum) {
            maxSum = currentMaxPath;
            
            // Reconstruct path (simplified - just store current node)
            maxPath.clear();
            maxPath.push_back(node);
        }
        
        return node->val + max(leftSum, rightSum);
    }
    
public:
    // Approach 6: Handle edge case variations
    // Time: O(n), Space: O(h)
    int maxPathSumRobust(TreeNode* root) {
        if (!root) return 0; // Handle empty tree
        
        int maxSum = root->val; // Initialize with root value instead of INT_MIN
        maxPathSumRobustHelper(root, maxSum);
        return maxSum;
    }
    
private:
    int maxPathSumRobustHelper(TreeNode* node, int& maxSum) {
        if (!node) return 0;
        
        int leftSum = maxPathSumRobustHelper(node->left, maxSum);
        int rightSum = maxPathSumRobustHelper(node->right, maxSum);
        
        // Consider all possible paths:
        // 1. Only current node
        // 2. Current + left subtree
        // 3. Current + right subtree  
        // 4. Current + both subtrees
        int currentOnly = node->val;
        int currentWithLeft = node->val + leftSum;
        int currentWithRight = node->val + rightSum;
        int currentWithBoth = node->val + leftSum + rightSum;
        
        // Update global maximum with best path through current node
        maxSum = max(maxSum, max({currentOnly, currentWithLeft, currentWithRight, currentWithBoth}));
        
        // Return best path extending from current node upward
        return max(currentOnly, max(currentWithLeft, currentWithRight));
    }
};

// Helper functions for testing
TreeNode* createTestTree1() {
    // Tree: [1,2,3] - max path sum = 6 (2->1->3)
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    return root;
}

TreeNode* createTestTree2() {
    // Tree: [-10,9,20,null,null,15,7] - max path sum = 42 (15->20->7)
    TreeNode* root = new TreeNode(-10);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);
    return root;
}

TreeNode* createTestTree3() {
    // Tree: [-3] - max path sum = -3 (single node)
    TreeNode* root = new TreeNode(-3);
    return root;
}

TreeNode* createTestTree4() {
    // Tree: [2,-1] - max path sum = 2 (just root)
    TreeNode* root = new TreeNode(2);
    root->left = new TreeNode(-1);
    return root;
}

int main() {
    Solution sol;
    
    TreeNode* tree1 = createTestTree1();
    TreeNode* tree2 = createTestTree2();
    TreeNode* tree3 = createTestTree3();
    TreeNode* tree4 = createTestTree4();
    
    cout << "Tree [1,2,3]:" << endl;
    cout << "Max path sum (recursive): " << sol.maxPathSum(tree1) << endl;
    cout << "Max path sum (reference): " << sol.maxPathSumRef(tree1) << endl;
    cout << "Max path sum (pair): " << sol.maxPathSumPair(tree1) << endl;
    
    cout << "\nTree [-10,9,20,null,null,15,7]:" << endl;
    cout << "Max path sum (iterative): " << sol.maxPathSumIterative(tree2) << endl;
    cout << "Max path sum (with path): " << sol.maxPathSumWithPath(tree2) << endl;
    
    cout << "\nTree [-3]:" << endl;
    cout << "Max path sum (robust): " << sol.maxPathSumRobust(tree3) << endl;
    
    cout << "\nTree [2,-1]:" << endl;
    cout << "Max path sum (robust): " << sol.maxPathSumRobust(tree4) << endl;
    
    return 0;
}

/*
Key Insights:
1. Path can start and end at any nodes (not necessarily root)
2. At each node, we can either extend path from children or start new path
3. When going up, we can only choose one direction (left or right)
4. When calculating max at current node, we can use both directions
5. Negative paths should be ignored (use max(0, pathSum))

Algorithm Explanation:
1. For each node, calculate max path sum going down in each direction
2. Max path through current node = node.val + left_path + right_path
3. Update global maximum with path through current node
4. Return path going up = node.val + max(left_path, right_path)
5. Use max(0, path) to ignore negative contributions

Common Mistakes:
- Forgetting that path can start/end anywhere (not just at leaves)
- Not handling negative values correctly
- Trying to return path through current node (should only return path going up)
- Not updating global maximum at each node
- Confusing path "through" node vs path "from" node

Edge Cases:
- All negative values: return the maximum single node value
- Empty tree: typically return 0 or handle as error
- Single node: return node value
- Tree with mix of positive and negative values

Interview Tips:
- Explain the difference between "path through node" and "path from node"
- Mention that at each node we consider two things:
  1. Best path using this node as the "peak" (update global max)
  2. Best path extending from this node upward (return value)
- Handle negative values by using max(0, sum)
- Discuss space complexity: O(h) for recursion stack

Variations:
- Path with minimum sum
- Path with maximum product
- Longest path in tree
- Path with specific sum
- Path between two specific nodes

Time/Space Complexity:
- Time: O(n) - visit each node exactly once
- Space: O(h) - recursion stack depth
- h can be O(log n) for balanced tree, O(n) for skewed tree

Related Problems:
- Path Sum (easier version)
- Path Sum II (all paths with target sum)
- Path Sum III (any path with target sum)
- Diameter of Binary Tree (similar recursive structure)
- Maximum Sum BST in Binary Tree

Applications:
- Finding optimal routes in networks
- Maximum gain in decision trees
- Resource allocation in hierarchical systems
- Game theory in tree-structured games
*/