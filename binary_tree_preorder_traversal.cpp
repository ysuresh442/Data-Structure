/*
LeetCode 144: Binary Tree Preorder Traversal
Difficulty: Easy
Companies: Amazon, Google, Microsoft

Problem:
Given the root of a binary tree, return the preorder traversal of its nodes' values.
Preorder traversal: Root -> Left -> Right

Example:
Input: root = [1,null,2,3]
Output: [1,2,3]

Time Complexity: O(n) where n is the number of nodes
Space Complexity: O(h) where h is the height of the tree
*/

#include <iostream>
#include <vector>
#include <stack>
#include <functional>
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
    // Approach 1: Recursive (most intuitive)
    // Time: O(n), Space: O(h)
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        preorderRecursive(root, result);
        return result;
    }
    
private:
    void preorderRecursive(TreeNode* root, vector<int>& result) {
        if (!root) return;
        
        result.push_back(root->val);            // Root
        preorderRecursive(root->left, result);  // Left
        preorderRecursive(root->right, result); // Right
    }
    
public:
    // Approach 2: Iterative using stack (classic)
    // Time: O(n), Space: O(h)
    vector<int> preorderTraversalIterative(TreeNode* root) {
        if (!root) return {};
        
        vector<int> result;
        stack<TreeNode*> stk;
        stk.push(root);
        
        while (!stk.empty()) {
            TreeNode* node = stk.top();
            stk.pop();
            
            result.push_back(node->val); // Process root
            
            // Push right first, then left (stack is LIFO)
            if (node->right) stk.push(node->right);
            if (node->left) stk.push(node->left);
        }
        
        return result;
    }
    
    // Approach 3: Morris Traversal (constant space)
    // Time: O(n), Space: O(1)
    vector<int> preorderTraversalMorris(TreeNode* root) {
        vector<int> result;
        TreeNode* current = root;
        
        while (current) {
            if (!current->left) {
                // No left child, process current and go right
                result.push_back(current->val);
                current = current->right;
            } else {
                // Find the rightmost node in left subtree
                TreeNode* predecessor = current->left;
                while (predecessor->right && predecessor->right != current) {
                    predecessor = predecessor->right;
                }
                
                if (!predecessor->right) {
                    // Create link and process current (preorder: root first)
                    result.push_back(current->val);
                    predecessor->right = current;
                    current = current->left;
                } else {
                    // Remove link and go right
                    predecessor->right = nullptr;
                    current = current->right;
                }
            }
        }
        
        return result;
    }
    
    // Approach 4: Iterative with explicit control
    // Time: O(n), Space: O(h)
    vector<int> preorderTraversalExplicit(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> stk;
        TreeNode* current = root;
        
        while (current || !stk.empty()) {
            if (current) {
                result.push_back(current->val); // Process root
                stk.push(current);
                current = current->left; // Go left
            } else {
                current = stk.top();
                stk.pop();
                current = current->right; // Go right
            }
        }
        
        return result;
    }
    
    // Approach 5: Using lambda (modern C++)
    // Time: O(n), Space: O(h)
    vector<int> preorderTraversalLambda(TreeNode* root) {
        vector<int> result;
        
        function<void(TreeNode*)> preorder = [&](TreeNode* node) {
            if (!node) return;
            result.push_back(node->val);
            preorder(node->left);
            preorder(node->right);
        };
        
        preorder(root);
        return result;
    }
    
    // Approach 6: Using stack with pairs
    // Time: O(n), Space: O(h)
    vector<int> preorderTraversalPairs(TreeNode* root) {
        if (!root) return {};
        
        vector<int> result;
        stack<pair<TreeNode*, bool>> stk; // pair<node, visited>
        stk.push({root, false});
        
        while (!stk.empty()) {
            auto [node, visited] = stk.top();
            stk.pop();
            
            if (visited) {
                result.push_back(node->val);
            } else {
                // Push in reverse order: right, left, root
                if (node->right) stk.push({node->right, false});
                if (node->left) stk.push({node->left, false});
                stk.push({node, true}); // Mark as visited
            }
        }
        
        return result;
    }
};

// Helper function to create test tree
TreeNode* createTestTree() {
    // Tree: [1,null,2,3]
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->left = new TreeNode(3);
    return root;
}

// Helper function to create complex test tree
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

// Helper function to print vector
void printVector(const vector<int>& vec, const string& approach) {
    cout << approach << ": [";
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i];
        if (i < vec.size() - 1) cout << ",";
    }
    cout << "]" << endl;
}

int main() {
    Solution sol;
    TreeNode* root1 = createTestTree();
    TreeNode* root2 = createComplexTree();
    
    cout << "Simple tree [1,null,2,3]:" << endl;
    printVector(sol.preorderTraversal(root1), "Recursive");
    printVector(sol.preorderTraversalIterative(root1), "Iterative");
    printVector(sol.preorderTraversalMorris(root1), "Morris");
    
    cout << "\nComplex tree [1,2,3,4,5,6,7]:" << endl;
    printVector(sol.preorderTraversalExplicit(root2), "Explicit");
    printVector(sol.preorderTraversalLambda(root2), "Lambda");
    printVector(sol.preorderTraversalPairs(root2), "Pairs");
    
    return 0;
}

/*
Key Insights:
1. Preorder traversal: Root -> Left -> Right
2. Root is processed BEFORE its children (unlike inorder)
3. Iterative approach: push right child first, then left (due to stack LIFO)
4. Morris traversal for preorder is simpler than inorder
5. Natural for tree copying, expression tree evaluation

Comparison of Approaches:
1. Recursive: Most intuitive, matches definition exactly
2. Iterative: Standard approach, uses stack to simulate recursion
3. Morris: Constant space, modifies tree temporarily
4. Explicit: Alternative iterative style
5. Lambda: Modern C++, clean syntax
6. Pairs: Uses visited flag, unified template for all traversals

Applications:
- Tree copying/cloning
- Expression tree evaluation (prefix notation)
- Tree serialization
- Directory traversal (process directory before contents)
- Syntax tree processing

Interview Tips:
- Start with recursive (shows understanding of concept)
- Move to iterative (demonstrates stack usage)
- Key insight: for stack-based approach, push right before left
- Mention that preorder is naturally easier than inorder iteratively
- Explain Morris traversal for O(1) space solution

Edge Cases:
- Empty tree: return empty vector
- Single node: return [node.val]
- Left-skewed tree: [root, left_child, left_grandchild, ...]
- Right-skewed tree: [root, right_child, right_grandchild, ...]

Comparison with other traversals:
- Preorder: Root, Left, Right (good for copying)
- Inorder: Left, Root, Right (good for BST - gives sorted order)
- Postorder: Left, Right, Root (good for deletion, calculating size)

Common Mistakes:
- Wrong order when pushing to stack (should be right first, then left)
- Processing node after popping instead of before pushing
- Incorrect Morris traversal link management
- Forgetting to handle null nodes

Memory Optimization:
- Recursive: O(h) stack space
- Iterative: O(h) explicit stack
- Morris: O(1) space but modifies tree temporarily
- Choose based on constraints and requirements

Related Problems:
- Binary Tree Inorder Traversal
- Binary Tree Postorder Traversal
- N-ary Tree Preorder Traversal
- Construct Binary Tree from Preorder and Inorder
*/