/*
LeetCode 98: Validate Binary Search Tree
Difficulty: Medium
Companies: Amazon, Google, Facebook

Problem:
Given the root of a binary tree, determine if it is a valid binary search tree (BST).
A valid BST is defined as follows:
- The left subtree of a node contains only nodes with keys less than the node's key.
- The right subtree of a node contains only nodes with keys greater than the node's key.
- Both the left and right subtrees must also be binary search trees.

Example:
Input: root = [2,1,3]
Output: true

Input: root = [5,1,4,null,null,3,6]
Output: false (3 < 5 but it's in the right subtree)

Time Complexity: O(n) where n is the number of nodes
Space Complexity: O(h) where h is the height of the tree
*/

#include <iostream>
#include <vector>
#include <stack>
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
public:
    // Approach 1: Recursive with range validation (most intuitive)
    // Time: O(n), Space: O(h)
    bool isValidBST(TreeNode* root) {
        return validate(root, LONG_MIN, LONG_MAX);
    }
    
private:
    bool validate(TreeNode* node, long minVal, long maxVal) {
        if (!node) return true;
        
        // Check if current node violates BST property
        if (node->val <= minVal || node->val >= maxVal) {
            return false;
        }
        
        // Recursively validate subtrees with updated bounds
        return validate(node->left, minVal, node->val) &&
               validate(node->right, node->val, maxVal);
    }
    
public:
    // Approach 2: Inorder traversal (elegant solution)
    // Time: O(n), Space: O(h)
    bool isValidBSTInorder(TreeNode* root) {
        long prev = LONG_MIN;
        return inorderValidate(root, prev);
    }
    
private:
    bool inorderValidate(TreeNode* root, long& prev) {
        if (!root) return true;
        
        // Check left subtree
        if (!inorderValidate(root->left, prev)) return false;
        
        // Check current node
        if (root->val <= prev) return false;
        prev = root->val;
        
        // Check right subtree
        return inorderValidate(root->right, prev);
    }
    
public:
    // Approach 3: Iterative inorder traversal
    // Time: O(n), Space: O(h)
    bool isValidBSTIterativeInorder(TreeNode* root) {
        stack<TreeNode*> stk;
        long prev = LONG_MIN;
        TreeNode* current = root;
        
        while (current || !stk.empty()) {
            while (current) {
                stk.push(current);
                current = current->left;
            }
            
            current = stk.top();
            stk.pop();
            
            if (current->val <= prev) return false;
            prev = current->val;
            
            current = current->right;
        }
        
        return true;
    }
    
    // Approach 4: Preorder with bounds (iterative)
    // Time: O(n), Space: O(h)
    bool isValidBSTIterativePreorder(TreeNode* root) {
        if (!root) return true;
        
        stack<tuple<TreeNode*, long, long>> stk;
        stk.push({root, LONG_MIN, LONG_MAX});
        
        while (!stk.empty()) {
            auto [node, minVal, maxVal] = stk.top();
            stk.pop();
            
            if (node->val <= minVal || node->val >= maxVal) {
                return false;
            }
            
            if (node->right) {
                stk.push({node->right, node->val, maxVal});
            }
            if (node->left) {
                stk.push({node->left, minVal, node->val});
            }
        }
        
        return true;
    }
    
    // Approach 5: Using inorder traversal with vector (less efficient)
    // Time: O(n), Space: O(n)
    bool isValidBSTVector(TreeNode* root) {
        vector<int> inorder;
        inorderToVector(root, inorder);
        
        for (int i = 1; i < inorder.size(); i++) {
            if (inorder[i] <= inorder[i-1]) return false;
        }
        
        return true;
    }
    
private:
    void inorderToVector(TreeNode* root, vector<int>& inorder) {
        if (!root) return;
        inorderToVector(root->left, inorder);
        inorder.push_back(root->val);
        inorderToVector(root->right, inorder);
    }
    
public:
    // Approach 6: Post-order with returning min/max info
    // Time: O(n), Space: O(h)
    bool isValidBSTPostorder(TreeNode* root) {
        return postorderValidate(root).isValid;
    }
    
private:
    struct Result {
        bool isValid;
        int minVal;
        int maxVal;
    };
    
    Result postorderValidate(TreeNode* root) {
        if (!root) return {true, INT_MAX, INT_MIN};
        
        auto left = postorderValidate(root->left);
        auto right = postorderValidate(root->right);
        
        bool valid = left.isValid && right.isValid &&
                    (root->left == nullptr || left.maxVal < root->val) &&
                    (root->right == nullptr || right.minVal > root->val);
        
        int minVal = root->left ? left.minVal : root->val;
        int maxVal = root->right ? right.maxVal : root->val;
        
        return {valid, minVal, maxVal};
    }
};

// Helper functions for testing
TreeNode* createValidBST() {
    // Tree: [2,1,3] - valid BST
    TreeNode* root = new TreeNode(2);
    root->left = new TreeNode(1);
    root->right = new TreeNode(3);
    return root;
}

TreeNode* createInvalidBST() {
    // Tree: [5,1,4,null,null,3,6] - invalid BST (3 < 5 but in right subtree)
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(1);
    root->right = new TreeNode(4);
    root->right->left = new TreeNode(3);
    root->right->right = new TreeNode(6);
    return root;
}

TreeNode* createTrickyBST() {
    // Tree: [10,5,15,null,null,6,20] - invalid (6 < 10 but in right subtree)
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(5);
    root->right = new TreeNode(15);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(20);
    return root;
}

int main() {
    Solution sol;
    
    TreeNode* validBST = createValidBST();
    TreeNode* invalidBST = createInvalidBST();
    TreeNode* trickyBST = createTrickyBST();
    
    cout << "Valid BST [2,1,3]:" << endl;
    cout << "Range validation: " << (sol.isValidBST(validBST) ? "Valid" : "Invalid") << endl;
    cout << "Inorder: " << (sol.isValidBSTInorder(validBST) ? "Valid" : "Invalid") << endl;
    cout << "Iterative inorder: " << (sol.isValidBSTIterativeInorder(validBST) ? "Valid" : "Invalid") << endl;
    
    cout << "\nInvalid BST [5,1,4,null,null,3,6]:" << endl;
    cout << "Range validation: " << (sol.isValidBST(invalidBST) ? "Valid" : "Invalid") << endl;
    cout << "Iterative preorder: " << (sol.isValidBSTIterativePreorder(invalidBST) ? "Valid" : "Invalid") << endl;
    cout << "Vector approach: " << (sol.isValidBSTVector(invalidBST) ? "Valid" : "Invalid") << endl;
    
    cout << "\nTricky BST [10,5,15,null,null,6,20]:" << endl;
    cout << "Postorder: " << (sol.isValidBSTPostorder(trickyBST) ? "Valid" : "Invalid") << endl;
    
    return 0;
}

/*
Key Insights:
1. BST property must hold for ALL nodes, not just immediate children
2. Each node has implicit min/max bounds based on ancestors
3. Inorder traversal of valid BST produces sorted sequence
4. Common mistake: only checking immediate parent-child relationships
5. Must handle edge cases with INT_MIN/INT_MAX values

Comparison of Approaches:
1. Range validation: Most intuitive, passes bounds down the tree
2. Inorder traversal: Elegant, leverages BST property directly
3. Iterative inorder: Space-efficient for deep trees
4. Iterative preorder: Alternative iterative approach with bounds
5. Vector approach: Simple but uses more space
6. Postorder: Returns additional info, bottom-up validation

Common Mistakes:
- Only checking immediate parent-child relationships
- Not handling duplicate values correctly (BST typically doesn't allow duplicates)
- Integer overflow issues (use long for bounds)
- Forgetting that left subtree max < root, right subtree min > root

Interview Tips:
- Start with range validation approach (easiest to explain)
- Mention inorder property as elegant alternative
- Discuss space complexity trade-offs
- Handle edge cases (empty tree, single node, duplicates)
- Explain why naive approach (checking only immediate children) fails

Edge Cases:
- Empty tree: valid BST by definition
- Single node: valid BST
- Tree with INT_MIN or INT_MAX values
- Tree with duplicate values
- Large trees that might cause stack overflow

Optimization Notes:
- Early termination when invalid node found
- Choose approach based on tree characteristics:
  * Deep trees: prefer iterative to avoid stack overflow
  * Wide trees: recursive is fine
  * Memory-constrained: use inorder with previous value tracking

Related Problems:
- Recover Binary Search Tree
- Convert Sorted Array to BST  
- Kth Smallest Element in a BST
- Lowest Common Ancestor of BST

Time/Space Analysis:
- All approaches: O(n) time in worst case
- Recursive: O(h) space for call stack
- Iterative: O(h) space for explicit stack
- Vector approach: O(n) space for storing all values
*/