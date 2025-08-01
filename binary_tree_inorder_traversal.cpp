/*
LeetCode 94: Binary Tree Inorder Traversal
Difficulty: Easy
Companies: Amazon, Google, Microsoft

Problem:
Given the root of a binary tree, return the inorder traversal of its nodes' values.
Inorder traversal: Left -> Root -> Right

Example:
Input: root = [1,null,2,3]
Output: [1,3,2]

Follow up: Recursive solution is trivial, could you do it iteratively?

Time Complexity: O(n) where n is the number of nodes
Space Complexity: O(h) where h is the height of the tree
*/

#include <iostream>
#include <vector>
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
    // Approach 1: Recursive (trivial but good to know)
    // Time: O(n), Space: O(h)
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        inorderRecursive(root, result);
        return result;
    }
    
private:
    void inorderRecursive(TreeNode* root, vector<int>& result) {
        if (!root) return;
        
        inorderRecursive(root->left, result);   // Left
        result.push_back(root->val);            // Root
        inorderRecursive(root->right, result);  // Right
    }
    
public:
    // Approach 2: Iterative using stack (classic approach)
    // Time: O(n), Space: O(h)
    vector<int> inorderTraversalIterative(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> stk;
        TreeNode* current = root;
        
        while (current || !stk.empty()) {
            // Go to leftmost node
            while (current) {
                stk.push(current);
                current = current->left;
            }
            
            // Current is null, so pop from stack
            current = stk.top();
            stk.pop();
            result.push_back(current->val);
            
            // Move to right subtree
            current = current->right;
        }
        
        return result;
    }
    
    // Approach 3: Morris Traversal (constant space)
    // Time: O(n), Space: O(1)
    vector<int> inorderTraversalMorris(TreeNode* root) {
        vector<int> result;
        TreeNode* current = root;
        
        while (current) {
            if (!current->left) {
                // No left child, visit current and go right
                result.push_back(current->val);
                current = current->right;
            } else {
                // Find inorder predecessor
                TreeNode* predecessor = current->left;
                while (predecessor->right && predecessor->right != current) {
                    predecessor = predecessor->right;
                }
                
                if (!predecessor->right) {
                    // Make current the right child of its inorder predecessor
                    predecessor->right = current;
                    current = current->left;
                } else {
                    // Revert the changes made - remove the link
                    predecessor->right = nullptr;
                    result.push_back(current->val);
                    current = current->right;
                }
            }
        }
        
        return result;
    }
    
    // Approach 4: Using lambda with recursion (modern C++)
    // Time: O(n), Space: O(h)
    vector<int> inorderTraversalLambda(TreeNode* root) {
        vector<int> result;
        
        function<void(TreeNode*)> inorder = [&](TreeNode* node) {
            if (!node) return;
            inorder(node->left);
            result.push_back(node->val);
            inorder(node->right);
        };
        
        inorder(root);
        return result;
    }
    
    // Approach 5: Using stack with pairs (alternative iterative)
    // Time: O(n), Space: O(h)
    vector<int> inorderTraversalPairs(TreeNode* root) {
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
                // Push in reverse order: right, root, left
                if (node->right) stk.push({node->right, false});
                stk.push({node, true}); // Mark as visited
                if (node->left) stk.push({node->left, false});
            }
        }
        
        return result;
    }
    
    // Approach 6: Threaded Binary Tree approach (educational)
    // Time: O(n), Space: O(1) but modifies tree structure temporarily
    vector<int> inorderTraversalThreaded(TreeNode* root) {
        vector<int> result;
        TreeNode* current = root;
        
        while (current) {
            if (!current->left) {
                result.push_back(current->val);
                current = current->right;
            } else {
                // Find the rightmost node in left subtree
                TreeNode* rightmost = current->left;
                while (rightmost->right && rightmost->right != current) {
                    rightmost = rightmost->right;
                }
                
                if (!rightmost->right) {
                    // Create thread
                    rightmost->right = current;
                    current = current->left;
                } else {
                    // Remove thread and process current
                    rightmost->right = nullptr;
                    result.push_back(current->val);
                    current = current->right;
                }
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
    TreeNode* root = createTestTree();
    
    printVector(sol.inorderTraversal(root), "Recursive");
    printVector(sol.inorderTraversalIterative(root), "Iterative");
    printVector(sol.inorderTraversalMorris(root), "Morris");
    printVector(sol.inorderTraversalLambda(root), "Lambda");
    printVector(sol.inorderTraversalPairs(root), "Pairs");
    printVector(sol.inorderTraversalThreaded(root), "Threaded");
    
    return 0;
}

/*
Key Insights:
1. Inorder traversal visits nodes in sorted order for BST
2. Pattern: Left -> Root -> Right
3. Iterative approach simulates recursion using stack
4. Morris traversal achieves O(1) space by using tree structure itself
5. Understanding all approaches shows mastery of tree traversal

Comparison of Approaches:
1. Recursive: Most intuitive, clean code
2. Iterative with stack: Standard iterative approach, good for interview
3. Morris: Constant space, more complex but elegant
4. Lambda: Modern C++ style, clean syntax
5. Pairs: Alternative iterative, uses visited flag
6. Threaded: Educational, shows how threading works

Space Complexity Analysis:
- Recursive: O(h) for recursion stack
- Iterative: O(h) for explicit stack
- Morris: O(1) constant space
- Others: O(h) for stack storage

Interview Tips:
- Start with recursive (show you understand the concept)
- Move to iterative (shows you can avoid recursion)
- Mention Morris for bonus points (O(1) space solution)
- Explain the key insight: process left first, then current, then right

Edge Cases:
- Empty tree: return empty vector
- Single node: return [node.val]
- Linear tree (left-skewed or right-skewed)
- Balanced tree

Applications:
- BST validation (inorder should be sorted)
- Converting BST to sorted array
- Finding kth smallest element in BST
- Tree serialization/deserialization

Common Mistakes:
- Wrong order in iterative approach
- Not handling null nodes properly
- Forgetting to move to right child after processing
- Incorrect Morris traversal link management

Follow-up Questions:
- How would you modify for preorder/postorder?
- How to do reverse inorder traversal?
- How to find inorder successor/predecessor?
*/