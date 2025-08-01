/*
LeetCode 297: Serialize and Deserialize Binary Tree
Difficulty: Hard
Companies: Amazon, Google, Facebook

Problem:
Serialization is the process of converting a data structure into a string
so that it can be stored or transmitted and reconstructed later.

Design an algorithm to serialize and deserialize a binary tree.

Example:
Input: root = [1,2,3,null,null,4,5]
Output: [1,2,3,null,null,4,5]

Note: The format doesn't have to be exactly as shown. You can use any format as long as
it can correctly deserialize back to the original tree structure.

Time Complexity: O(n) for both serialize and deserialize
Space Complexity: O(n) for the serialized string and recursion stack
*/

#include <iostream>
#include <string>
#include <queue>
#include <sstream>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Approach 1: Preorder traversal (most common)
class Codec {
public:
    // Encodes a tree to a single string using preorder traversal
    // Time: O(n), Space: O(n)
    string serialize(TreeNode* root) {
        string result;
        serializeHelper(root, result);
        return result;
    }
    
private:
    void serializeHelper(TreeNode* node, string& result) {
        if (!node) {
            result += "null,";
            return;
        }
        
        result += to_string(node->val) + ",";
        serializeHelper(node->left, result);
        serializeHelper(node->right, result);
    }
    
public:
    // Decodes your encoded data to tree using preorder traversal
    // Time: O(n), Space: O(n)
    TreeNode* deserialize(string data) {
        queue<string> tokens;
        stringstream ss(data);
        string token;
        
        while (getline(ss, token, ',')) {
            tokens.push(token);
        }
        
        return deserializeHelper(tokens);
    }
    
private:
    TreeNode* deserializeHelper(queue<string>& tokens) {
        if (tokens.empty()) return nullptr;
        
        string val = tokens.front();
        tokens.pop();
        
        if (val == "null") return nullptr;
        
        TreeNode* node = new TreeNode(stoi(val));
        node->left = deserializeHelper(tokens);
        node->right = deserializeHelper(tokens);
        
        return node;
    }
};

// Approach 2: Level order traversal (BFS)
class CodecBFS {
public:
    string serialize(TreeNode* root) {
        if (!root) return "";
        
        string result;
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            
            if (node) {
                result += to_string(node->val) + ",";
                q.push(node->left);
                q.push(node->right);
            } else {
                result += "null,";
            }
        }
        
        return result;
    }
    
    TreeNode* deserialize(string data) {
        if (data.empty()) return nullptr;
        
        vector<string> tokens;
        stringstream ss(data);
        string token;
        
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        
        TreeNode* root = new TreeNode(stoi(tokens[0]));
        queue<TreeNode*> q;
        q.push(root);
        
        int i = 1;
        while (!q.empty() && i < tokens.size()) {
            TreeNode* node = q.front();
            q.pop();
            
            // Process left child
            if (i < tokens.size() && tokens[i] != "null") {
                node->left = new TreeNode(stoi(tokens[i]));
                q.push(node->left);
            }
            i++;
            
            // Process right child
            if (i < tokens.size() && tokens[i] != "null") {
                node->right = new TreeNode(stoi(tokens[i]));
                q.push(node->right);
            }
            i++;
        }
        
        return root;
    }
};

// Approach 3: Postorder traversal
class CodecPostorder {
public:
    string serialize(TreeNode* root) {
        string result;
        serializeHelper(root, result);
        return result;
    }
    
private:
    void serializeHelper(TreeNode* node, string& result) {
        if (!node) {
            result += "null,";
            return;
        }
        
        serializeHelper(node->left, result);
        serializeHelper(node->right, result);
        result += to_string(node->val) + ",";
    }
    
public:
    TreeNode* deserialize(string data) {
        queue<string> tokens;
        stringstream ss(data);
        string token;
        
        while (getline(ss, token, ',')) {
            tokens.push(token);
        }
        
        // Convert queue to vector for easier access from end
        vector<string> vec;
        while (!tokens.empty()) {
            vec.push_back(tokens.front());
            tokens.pop();
        }
        
        int idx = vec.size() - 1;
        return deserializeHelper(vec, idx);
    }
    
private:
    TreeNode* deserializeHelper(vector<string>& tokens, int& idx) {
        if (idx < 0 || tokens[idx] == "null") {
            idx--;
            return nullptr;
        }
        
        TreeNode* node = new TreeNode(stoi(tokens[idx--]));
        node->right = deserializeHelper(tokens, idx); // Right first in postorder
        node->left = deserializeHelper(tokens, idx);
        
        return node;
    }
};

// Approach 4: Using stringstream for cleaner parsing
class CodecStringStream {
public:
    string serialize(TreeNode* root) {
        ostringstream out;
        serializeHelper(root, out);
        return out.str();
    }
    
private:
    void serializeHelper(TreeNode* node, ostringstream& out) {
        if (!node) {
            out << "# ";
            return;
        }
        
        out << node->val << " ";
        serializeHelper(node->left, out);
        serializeHelper(node->right, out);
    }
    
public:
    TreeNode* deserialize(string data) {
        istringstream in(data);
        return deserializeHelper(in);
    }
    
private:
    TreeNode* deserializeHelper(istringstream& in) {
        string val;
        in >> val;
        
        if (val == "#") return nullptr;
        
        TreeNode* node = new TreeNode(stoi(val));
        node->left = deserializeHelper(in);
        node->right = deserializeHelper(in);
        
        return node;
    }
};

// Approach 5: Compact representation for complete trees
class CodecCompact {
public:
    string serialize(TreeNode* root) {
        if (!root) return "";
        
        vector<string> result;
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            
            if (node) {
                result.push_back(to_string(node->val));
                q.push(node->left);
                q.push(node->right);
            } else {
                result.push_back("#");
            }
        }
        
        // Remove trailing nulls for compact representation
        while (!result.empty() && result.back() == "#") {
            result.pop_back();
        }
        
        string serialized;
        for (int i = 0; i < result.size(); i++) {
            serialized += result[i];
            if (i < result.size() - 1) serialized += ",";
        }
        
        return serialized;
    }
    
    TreeNode* deserialize(string data) {
        if (data.empty()) return nullptr;
        
        vector<string> tokens;
        stringstream ss(data);
        string token;
        
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        
        if (tokens.empty()) return nullptr;
        
        TreeNode* root = new TreeNode(stoi(tokens[0]));
        queue<TreeNode*> q;
        q.push(root);
        
        int i = 1;
        while (!q.empty() && i < tokens.size()) {
            TreeNode* node = q.front();
            q.pop();
            
            if (i < tokens.size() && tokens[i] != "#") {
                node->left = new TreeNode(stoi(tokens[i]));
                q.push(node->left);
            }
            i++;
            
            if (i < tokens.size() && tokens[i] != "#") {
                node->right = new TreeNode(stoi(tokens[i]));
                q.push(node->right);
            }
            i++;
        }
        
        return root;
    }
};

// Helper functions for testing
TreeNode* createTestTree() {
    // Tree: [1,2,3,null,null,4,5]
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(5);
    return root;
}

void printInorder(TreeNode* root) {
    if (!root) return;
    printInorder(root->left);
    cout << root->val << " ";
    printInorder(root->right);
}

int main() {
    TreeNode* root = createTestTree();
    
    cout << "Original tree (inorder): ";
    printInorder(root);
    cout << endl;
    
    // Test Preorder approach
    Codec codec1;
    string serialized1 = codec1.serialize(root);
    cout << "\nPreorder serialized: " << serialized1 << endl;
    TreeNode* deserialized1 = codec1.deserialize(serialized1);
    cout << "Deserialized (inorder): ";
    printInorder(deserialized1);
    cout << endl;
    
    // Test BFS approach
    CodecBFS codec2;
    string serialized2 = codec2.serialize(root);
    cout << "\nBFS serialized: " << serialized2 << endl;
    TreeNode* deserialized2 = codec2.deserialize(serialized2);
    cout << "Deserialized (inorder): ";
    printInorder(deserialized2);
    cout << endl;
    
    // Test StringStream approach
    CodecStringStream codec3;
    string serialized3 = codec3.serialize(root);
    cout << "\nStringStream serialized: " << serialized3 << endl;
    TreeNode* deserialized3 = codec3.deserialize(serialized3);
    cout << "Deserialized (inorder): ";
    printInorder(deserialized3);
    cout << endl;
    
    return 0;
}

/*
Key Insights:
1. Serialization must capture both structure and values
2. Null nodes must be explicitly represented to maintain structure
3. Different traversal orders lead to different serialization formats
4. Deserialization must reconstruct exact same tree structure
5. Choice of delimiter and null representation affects parsing

Comparison of Approaches:
1. Preorder: Natural recursive structure, easy to implement
2. Level order (BFS): Intuitive level-by-level representation
3. Postorder: Less common but demonstrates algorithmic flexibility
4. StringStream: Cleaner parsing using C++ streams
5. Compact: Optimized representation removing trailing nulls

Serialization Formats:
- Preorder: "1,2,null,null,3,4,null,null,5,null,null,"
- Level order: "1,2,3,null,null,4,5,"
- Each has trade-offs in terms of size and parsing complexity

Interview Tips:
- Start with preorder approach (most common and intuitive)
- Explain why null markers are necessary
- Discuss alternative approaches (BFS, postorder)
- Handle edge cases: empty tree, single node
- Consider space optimization techniques

Edge Cases:
- Empty tree: return empty string or special marker
- Single node tree: just the node value
- Complete binary tree: more compact representation possible
- Skewed tree: many null markers needed

Common Mistakes:
- Forgetting to handle null nodes properly
- Incorrect parsing of serialized string
- Not maintaining exact tree structure during deserialization
- Issues with delimiter choice (spaces, commas, special characters)

Design Considerations:
1. Format choice: human-readable vs compact
2. Delimiter selection: avoid conflicts with data
3. Null representation: "null", "#", "N", etc.
4. Error handling: malformed input, invalid trees
5. Memory efficiency: streaming vs buffering

Applications:
- Database storage of tree structures
- Network transmission of trees
- Caching tree computations
- Tree comparison and hashing
- File format design for hierarchical data

Optimization Techniques:
- Remove trailing nulls for compact representation
- Use single character markers (#, N) instead of "null"
- Binary serialization instead of text
- Compression for large trees
- Streaming for very large trees

Related Problems:
- Serialize and Deserialize BST (LC 449)
- Serialize and Deserialize N-ary Tree (LC 428)
- Find Duplicate Subtrees (uses serialization)
- Encode and Decode Strings (LC 271)

Performance Analysis:
- Time: O(n) for both serialize and deserialize
- Space: O(n) for serialized string + O(h) for recursion
- BFS uses O(w) space during processing
- DFS uses O(h) space during processing
*/