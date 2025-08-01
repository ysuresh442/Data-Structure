/*
LeetCode 101: Symmetric Tree
Difficulty: Easy
Companies: Amazon, Google, Microsoft

Problem:
Given the root of a binary tree, check whether it is a mirror of itself 
(i.e., symmetric around its center).

Example:
Input: root = [1,2,2,3,4,4,3]
Output: true

Input: root = [1,2,2,null,3,null,3]
Output: false

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
    // Approach 1: Recursive DFS (Most intuitive)
    // Time: O(n), Space: O(h)
    bool isSymmetric(TreeNode* root) {
        if (!root) return true;
        return isMirror(root->left, root->right);
    }
    
private:
    bool isMirror(TreeNode* left, TreeNode* right) {
        // Both null - symmetric
        if (!left && !right) return true;
        
        // One null, other not - not symmetric
        if (!left || !right) return false;
        
        // Both non-null: check value and recurse
        // Left's left should mirror Right's right
        // Left's right should mirror Right's left
        return (left->val == right->val) &&
               isMirror(left->left, right->right) &&
               isMirror(left->right, right->left);
    }

public:
    // Approach 2: Iterative using queue (BFS style)
    // Time: O(n), Space: O(w) where w is maximum width
    bool isSymmetricIterativeQueue(TreeNode* root) {
        if (!root) return true;
        
        queue<TreeNode*> q;
        q.push(root->left);
        q.push(root->right);
        
        while (!q.empty()) {
            TreeNode* left = q.front(); q.pop();
            TreeNode* right = q.front(); q.pop();
            
            // Both null - continue
            if (!left && !right) continue;
            
            // One null or values different - not symmetric
            if (!left || !right || left->val != right->val) {
                return false;
            }
            
            // Add children in mirror order
            q.push(left->left);
            q.push(right->right);
            q.push(left->right);
            q.push(right->left);
        }
        
        return true;
    }
    
    // Approach 3: Iterative using stack (DFS style)
    // Time: O(n), Space: O(h)
    bool isSymmetricIterativeStack(TreeNode* root) {
        if (!root) return true;
        
        stack<TreeNode*> stk;
        stk.push(root->left);
        stk.push(root->right);
        
        while (!stk.empty()) {
            TreeNode* right = stk.top(); stk.pop();
            TreeNode* left = stk.top(); stk.pop();
            
            // Both null - continue
            if (!left && !right) continue;
            
            // One null or values different - not symmetric
            if (!left || !right || left->val != right->val) {
                return false;
            }
            
            // Add children in mirror order
            stk.push(left->left);
            stk.push(right->right);
            stk.push(left->right);
            stk.push(right->left);
        }
        
        return true;
    }
    
    // Approach 4: Using inorder traversal with level tracking
    // Time: O(n), Space: O(n)
    bool isSymmetricInorder(TreeNode* root) {
        if (!root) return true;
        
        vector<vector<int>> leftTraversal, rightTraversal;
        inorderLeft(root->left, 0, leftTraversal);
        inorderRight(root->right, 0, rightTraversal);
        
        if (leftTraversal.size() != rightTraversal.size()) return false;
        
        for (int i = 0; i < leftTraversal.size(); i++) {
            if (leftTraversal[i] != rightTraversal[i]) return false;
        }
        
        return true;
    }
    
private:
    void inorderLeft(TreeNode* node, int level, vector<vector<int>>& result) {
        if (!node) {
            if (result.size() <= level) result.resize(level + 1);
            result[level].push_back(INT_MIN); // marker for null
            return;
        }
        
        if (result.size() <= level) result.resize(level + 1);
        
        inorderLeft(node->left, level + 1, result);
        result[level].push_back(node->val);
        inorderLeft(node->right, level + 1, result);
    }
    
    void inorderRight(TreeNode* node, int level, vector<vector<int>>& result) {
        if (!node) {
            if (result.size() <= level) result.resize(level + 1);
            result[level].push_back(INT_MIN); // marker for null
            return;
        }
        
        if (result.size() <= level) result.resize(level + 1);
        
        inorderRight(node->right, level + 1, result);
        result[level].push_back(node->val);
        inorderRight(node->left, level + 1, result);
    }
};

// Helper functions for testing
TreeNode* createSymmetricTree() {
    // Tree: [1,2,2,3,4,4,3]
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(2);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(4);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(3);
    return root;
}

TreeNode* createAsymmetricTree() {
    // Tree: [1,2,2,null,3,null,3]
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(2);
    root->left->right = new TreeNode(3);
    root->right->right = new TreeNode(3);
    return root;
}

int main() {
    Solution sol;
    
    TreeNode* symmetric = createSymmetricTree();
    TreeNode* asymmetric = createAsymmetricTree();
    
    cout << "Symmetric tree test:" << endl;
    cout << "Recursive: " << (sol.isSymmetric(symmetric) ? "Yes" : "No") << endl;
    cout << "Iterative Queue: " << (sol.isSymmetricIterativeQueue(symmetric) ? "Yes" : "No") << endl;
    cout << "Iterative Stack: " << (sol.isSymmetricIterativeStack(symmetric) ? "Yes" : "No") << endl;
    
    cout << "\nAsymmetric tree test:" << endl;
    cout << "Recursive: " << (sol.isSymmetric(asymmetric) ? "Yes" : "No") << endl;
    cout << "Iterative Queue: " << (sol.isSymmetricIterativeQueue(asymmetric) ? "Yes" : "No") << endl;
    cout << "Iterative Stack: " << (sol.isSymmetricIterativeStack(asymmetric) ? "Yes" : "No") << endl;
    
    return 0;
}

/*
Key Insights:
1. A tree is symmetric if left subtree is mirror of right subtree
2. For mirror comparison: left.left mirrors right.right, left.right mirrors right.left
3. Must check both structure (null positions) and values
4. Can use any traversal method as long as mirror property is maintained
5. Recursive solution is most elegant and intuitive

Comparison of Approaches:
1. Recursive: Clean, easy to understand, natural recursion
2. Iterative Queue: Level-by-level comparison, good for wide trees
3. Iterative Stack: Depth-first approach, good for deep trees
4. Inorder traversal: More complex but demonstrates alternative thinking

Edge Cases:
- Empty tree: symmetric by definition
- Single node: symmetric
- Trees where structure is symmetric but values aren't
- Trees where values are symmetric but structure isn't

Interview Tips:
- Start with recursive approach (most intuitive)
- Emphasize the key insight: left subtree mirrors right subtree
- Mention that this is similar to "Same Tree" but with mirror logic
- Discuss space complexity differences between approaches

Common Mistakes:
- Comparing left subtree with right subtree directly (should be mirror comparison)
- Forgetting to handle null nodes properly
- Incorrect pairing of children in mirror comparison
- Not considering both structure and values

Variations:
- Check if two different trees are mirrors of each other
- Find the line of symmetry in a tree
- Check symmetry in n-ary trees
*/