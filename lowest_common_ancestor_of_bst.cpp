/*
LeetCode 235: Lowest Common Ancestor of a Binary Search Tree
Difficulty: Medium
Companies: Amazon, Google, Microsoft

Problem:
Given a binary search tree (BST), find the lowest common ancestor (LCA) of two given nodes.
The LCA is defined as the lowest node that has both p and q as descendants 
(where we allow a node to be a descendant of itself).

Example:
Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
Output: 6

Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
Output: 2

Time Complexity: O(h) where h is the height of the tree
Space Complexity: O(h) for recursive approach, O(1) for iterative
*/

#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set> // Added for Approach 4
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    // Approach 1: Recursive using BST property (most elegant)
    // Time: O(h), Space: O(h)
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root) return nullptr;
        
        // If both p and q are smaller than root, LCA is in left subtree
        if (p->val < root->val && q->val < root->val) {
            return lowestCommonAncestor(root->left, p, q);
        }
        
        // If both p and q are greater than root, LCA is in right subtree  
        if (p->val > root->val && q->val > root->val) {
            return lowestCommonAncestor(root->right, p, q);
        }
        
        // If p and q are on different sides (or one is root), current node is LCA
        return root;
    }
    
    // Approach 2: Iterative using BST property (optimal space)
    // Time: O(h), Space: O(1)
    TreeNode* lowestCommonAncestorIterative(TreeNode* root, TreeNode* p, TreeNode* q) {
        while (root) {
            // Both nodes are in left subtree
            if (p->val < root->val && q->val < root->val) {
                root = root->left;
            }
            // Both nodes are in right subtree
            else if (p->val > root->val && q->val > root->val) {
                root = root->right;
            }
            // Nodes are on different sides or one is the root
            else {
                return root;
            }
        }
        return nullptr; // Should never reach here if p and q exist in tree
    }
    
    // Approach 3: Path-based approach (works for any binary tree)
    // Time: O(h), Space: O(h)
    TreeNode* lowestCommonAncestorPath(TreeNode* root, TreeNode* p, TreeNode* q) {
        vector<TreeNode*> pathP, pathQ;
        
        if (!findPath(root, p, pathP) || !findPath(root, q, pathQ)) {
            return nullptr; // One of the nodes doesn't exist
        }
        
        TreeNode* lca = nullptr;
        int minLen = min(pathP.size(), pathQ.size());
        
        for (int i = 0; i < minLen; i++) {
            if (pathP[i] == pathQ[i]) {
                lca = pathP[i];
            } else {
                break;
            }
        }
        
        return lca;
    }
    
private:
    bool findPath(TreeNode* root, TreeNode* target, vector<TreeNode*>& path) {
        if (!root) return false;
        
        path.push_back(root);
        
        if (root == target) return true;
        
        // For BST, we can use BST property to decide direction
        if (target->val < root->val) {
            if (findPath(root->left, target, path)) return true;
        } else {
            if (findPath(root->right, target, path)) return true;
        }
        
        path.pop_back(); // Backtrack
        return false;
    }
    
public:
    // Approach 4: Using parent pointers (if available)
    // Time: O(h), Space: O(h)
    TreeNode* lowestCommonAncestorParent(TreeNode* root, TreeNode* p, TreeNode* q) {
        // First, traverse to find p and q and set their parent pointers
        // This approach assumes we can modify the tree or have parent pointers
        
        // Find path to p and store all ancestors
        unordered_set<TreeNode*> ancestors;
        TreeNode* current = p;
        
        // Traverse from p to root using BST property
        current = root;
        while (current != p) {
            ancestors.insert(current);
            if (p->val < current->val) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        ancestors.insert(p);
        
        // Traverse from q to root and find first common ancestor
        current = root;
        while (current != q) {
            if (ancestors.count(current)) {
                return current;
            }
            if (q->val < current->val) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        
        return q; // q is ancestor of itself
    }
    
    // Approach 5: Generic LCA approach (works for any binary tree)
    // Time: O(n), Space: O(h)
    TreeNode* lowestCommonAncestorGeneric(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || root == p || root == q) return root;
        
        TreeNode* left = lowestCommonAncestorGeneric(root->left, p, q);
        TreeNode* right = lowestCommonAncestorGeneric(root->right, p, q);
        
        // If both left and right are non-null, current node is LCA
        if (left && right) return root;
        
        // Return non-null child (or null if both are null)
        return left ? left : right;
    }
    
    // Approach 6: Optimized BST approach with value comparison
    // Time: O(h), Space: O(1)
    TreeNode* lowestCommonAncestorOptimized(TreeNode* root, TreeNode* p, TreeNode* q) {
        // Ensure p has smaller value for easier comparison
        if (p->val > q->val) swap(p, q);
        
        while (root) {
            if (q->val < root->val) {
                // Both are in left subtree
                root = root->left;
            } else if (p->val > root->val) {
                // Both are in right subtree
                root = root->right;
            } else {
                // p <= root <= q, so root is LCA
                return root;
            }
        }
        
        return nullptr;
    }
};

// Helper functions for testing
TreeNode* createBST() {
    // BST: [6,2,8,0,4,7,9,null,null,3,5]
    TreeNode* root = new TreeNode(6);
    root->left = new TreeNode(2);
    root->right = new TreeNode(8);
    root->left->left = new TreeNode(0);
    root->left->right = new TreeNode(4);
    root->right->left = new TreeNode(7);
    root->right->right = new TreeNode(9);
    root->left->right->left = new TreeNode(3);
    root->left->right->right = new TreeNode(5);
    return root;
}

TreeNode* findNode(TreeNode* root, int val) {
    if (!root) return nullptr;
    if (root->val == val) return root;
    if (val < root->val) return findNode(root->left, val);
    return findNode(root->right, val);
}

int main() {
    Solution sol;
    TreeNode* root = createBST();
    
    TreeNode* p1 = findNode(root, 2);
    TreeNode* q1 = findNode(root, 8);
    TreeNode* p2 = findNode(root, 2);
    TreeNode* q2 = findNode(root, 4);
    
    cout << "BST: [6,2,8,0,4,7,9,null,null,3,5]" << endl;
    
    cout << "\nLCA of 2 and 8:" << endl;
    cout << "Recursive: " << sol.lowestCommonAncestor(root, p1, q1)->val << endl;
    cout << "Iterative: " << sol.lowestCommonAncestorIterative(root, p1, q1)->val << endl;
    cout << "Path-based: " << sol.lowestCommonAncestorPath(root, p1, q1)->val << endl;
    
    cout << "\nLCA of 2 and 4:" << endl;
    cout << "Optimized: " << sol.lowestCommonAncestorOptimized(root, p2, q2)->val << endl;
    cout << "Generic: " << sol.lowestCommonAncestorGeneric(root, p2, q2)->val << endl;
    
    return 0;
}

/*
Key Insights:
1. BST property: left < root < right for all nodes
2. LCA is the first node where paths to p and q diverge
3. If both nodes are smaller/greater than current, go left/right
4. If nodes are on different sides, current node is LCA
5. BST allows O(h) solution vs O(n) for general binary tree

Comparison of Approaches:
1. Recursive BST: Clean, leverages BST property naturally
2. Iterative BST: Optimal space O(1), same logic as recursive
3. Path-based: More general, works for any binary tree
4. Parent pointers: Alternative approach when available
5. Generic LCA: Standard approach for any binary tree
6. Optimized: Slight improvement with value ordering

Why BST is Special:
- BST property allows us to eliminate half the tree at each step
- No need to search both subtrees like in general binary tree
- Can determine direction to search based on node values
- Guarantees O(h) time complexity instead of O(n)

Interview Tips:
- Start with BST-specific approach (shows understanding of BST properties)
- Explain why BST allows more efficient solution than general tree
- Mention iterative solution for optimal space complexity
- Discuss how this extends to general binary tree LCA
- Handle edge cases: nodes not in tree, same node, root cases

Edge Cases:
- One or both nodes not in tree
- One node is ancestor of the other
- Both nodes are the same
- Tree is empty
- Tree has only one node

Common Mistakes:
- Not utilizing BST property (treating it like general binary tree)
- Incorrect handling when one node is ancestor of other
- Not considering that a node can be ancestor of itself
- Forgetting to handle edge cases

Variations:
- LCA in Binary Tree (general case)
- LCA of Deepest Leaves
- LCA with parent pointers
- LCA in N-ary tree
- Multiple LCA queries

Time Complexity Analysis:
- BST approaches: O(h) where h is height
  * Best case (balanced): O(log n)
  * Worst case (skewed): O(n)
- General tree approach: O(n) always

Space Complexity:
- Recursive: O(h) for call stack
- Iterative: O(1) constant space
- Path-based: O(h) for storing paths

Related Problems:
- Lowest Common Ancestor of Binary Tree (LC 236)
- Lowest Common Ancestor of Deepest Leaves (LC 1123)
- Kth Ancestor of Tree Node (LC 1483)
- Distance Between BST Nodes (using LCA)
*/