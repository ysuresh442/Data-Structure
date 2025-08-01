/*
LeetCode 100: Same Tree
Difficulty: Easy
Companies: Amazon, Google, Facebook

Problem:
Given the roots of two binary trees p and q, write a function to check if they are the same or not.
Two binary trees are considered the same if they are structurally identical, 
and the nodes have the same value.

Example:
Input: p = [1,2,3], q = [1,2,3]
Output: true

Input: p = [1,2], q = [1,null,2]
Output: false

Time Complexity: O(min(m,n)) where m and n are the number of nodes in trees
Space Complexity: O(min(m,n)) for recursion stack
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
    // Time: O(min(m,n)), Space: O(min(m,n))
    bool isSameTree(TreeNode* p, TreeNode* q) {
        // Base case: both null
        if (!p && !q) return true;
        
        // One is null, other is not
        if (!p || !q) return false;
        
        // Both non-null: check value and recurse on children
        return (p->val == q->val) && 
               isSameTree(p->left, q->left) && 
               isSameTree(p->right, q->right);
    }
    
    // Approach 2: Iterative using stack (preorder traversal)
    // Time: O(min(m,n)), Space: O(min(m,n))
    bool isSameTreeIterative(TreeNode* p, TreeNode* q) {
        stack<pair<TreeNode*, TreeNode*>> stk;
        stk.push({p, q});
        
        while (!stk.empty()) {
            auto [node1, node2] = stk.top();
            stk.pop();
            
            // Both null - continue
            if (!node1 && !node2) continue;
            
            // One null, other not - different
            if (!node1 || !node2) return false;
            
            // Different values - different
            if (node1->val != node2->val) return false;
            
            // Add children to stack
            stk.push({node1->right, node2->right});
            stk.push({node1->left, node2->left});
        }
        
        return true;
    }
    
    // Approach 3: BFS using queue (level order comparison)
    // Time: O(min(m,n)), Space: O(min(m,n))
    bool isSameTreeBFS(TreeNode* p, TreeNode* q) {
        queue<pair<TreeNode*, TreeNode*>> que;
        que.push({p, q});
        
        while (!que.empty()) {
            auto [node1, node2] = que.front();
            que.pop();
            
            // Both null - continue
            if (!node1 && !node2) continue;
            
            // One null, other not - different
            if (!node1 || !node2) return false;
            
            // Different values - different
            if (node1->val != node2->val) return false;
            
            // Add children to queue
            que.push({node1->left, node2->left});
            que.push({node1->right, node2->right});
        }
        
        return true;
    }
    
    // Approach 4: Using serialization (alternative approach)
    // Time: O(m+n), Space: O(m+n)
    bool isSameTreeSerialization(TreeNode* p, TreeNode* q) {
        string s1 = serialize(p);
        string s2 = serialize(q);
        return s1 == s2;
    }
    
private:
    string serialize(TreeNode* root) {
        if (!root) return "null,";
        return to_string(root->val) + "," + 
               serialize(root->left) + 
               serialize(root->right);
    }
};

// Helper functions for testing
TreeNode* createTree1() {
    // Tree: [1,2,3]
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    return root;
}

TreeNode* createTree2() {
    // Tree: [1,2,3] (same as tree1)
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    return root;
}

TreeNode* createTree3() {
    // Tree: [1,null,2]
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    return root;
}

int main() {
    Solution sol;
    
    TreeNode* p1 = createTree1();
    TreeNode* q1 = createTree2();
    TreeNode* p2 = createTree1();
    TreeNode* q2 = createTree3();
    
    cout << "Tree1 and Tree2 same (Recursive): " 
         << (sol.isSameTree(p1, q1) ? "Yes" : "No") << endl;
    cout << "Tree1 and Tree2 same (Iterative): " 
         << (sol.isSameTreeIterative(p1, q1) ? "Yes" : "No") << endl;
    cout << "Tree1 and Tree2 same (BFS): " 
         << (sol.isSameTreeBFS(p1, q1) ? "Yes" : "No") << endl;
    
    cout << "\nTree1 and Tree3 same (Recursive): " 
         << (sol.isSameTree(p2, q2) ? "Yes" : "No") << endl;
    cout << "Tree1 and Tree3 same (Serialization): " 
         << (sol.isSameTreeSerialization(p2, q2) ? "Yes" : "No") << endl;
    
    return 0;
}

/*
Key Insights:
1. Two trees are same if structure and values are identical
2. Early termination when difference is found
3. Must check both structure (null positions) and values
4. Any traversal order works since we compare corresponding nodes
5. Recursive solution is most elegant and intuitive

Comparison of Approaches:
1. Recursive: Most readable, natural recursion
2. Iterative DFS: Avoids recursion stack, explicit stack management
3. BFS: Level-by-level comparison, good for wide trees
4. Serialization: Convert to strings and compare, higher space complexity

Edge Cases:
- Both trees null: return true
- One tree null, other not: return false
- Trees with different structures but same values
- Trees with same structure but different values
- Single node trees

Interview Tips:
- Start with recursive approach (easiest to explain)
- Mention the early termination optimization
- Discuss space complexity trade-offs
- This problem tests basic tree traversal and comparison logic

Common Mistakes:
- Forgetting to check structure (null positions)
- Not handling the case when both nodes are null
- Incorrect order of conditions in base cases
*/