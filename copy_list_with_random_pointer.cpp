/*
 * LeetCode 138: Copy List with Random Pointer
 * 
 * A linked list of length n is given such that each node contains an additional random pointer,
 * which could point to any node in the list, or null.
 * 
 * Construct a deep copy of the list. The deep copy should consist of exactly n brand new nodes,
 * where each new node has its value set to the value of its corresponding original node.
 * Both the next and random pointers of the new nodes should point to new nodes in the copied list
 * such that the pointers in the original list and copied list represent the same list state.
 * None of the pointers in the new list should point to nodes in the original list.
 * 
 * Example 1:
 * Input: head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
 * Output: [[7,null],[13,0],[11,4],[10,2],[1,0]]
 * 
 * Example 2:
 * Input: head = [[1,1],[2,1]]
 * Output: [[1,1],[2,1]]
 * 
 * Example 3:
 * Input: head = [[3,null],[3,0],[3,null]]
 * Output: [[3,null],[3,0],[3,null]]
 * 
 * Companies: Amazon, Google, Microsoft, Facebook, Uber
 * Difficulty: Medium
 * Pattern: Hash Table, Linked List Manipulation
 */

#include "linked_list_common.h"

class Solution {
public:
    /*
     * Approach 1: Hash Table / Map
     * 
     * Algorithm:
     * 1. First pass: Create all new nodes and store mapping old -> new
     * 2. Second pass: Set next and random pointers using the mapping
     * 
     * Time Complexity: O(n)
     * Space Complexity: O(n) for the hash map
     */
    Node* copyRandomList(Node* head) {
        if (!head) return nullptr;
        
        unordered_map<Node*, Node*> nodeMap;
        
        // First pass: Create all nodes and store mapping
        Node* current = head;
        while (current) {
            nodeMap[current] = new Node(current->val);
            current = current->next;
        }
        
        // Second pass: Set next and random pointers
        current = head;
        while (current) {
            if (current->next) {
                nodeMap[current]->next = nodeMap[current->next];
            }
            if (current->random) {
                nodeMap[current]->random = nodeMap[current->random];
            }
            current = current->next;
        }
        
        return nodeMap[head];
    }
    
    /*
     * Approach 2: Interweaving Nodes (Constant Space)
     * 
     * Algorithm:
     * 1. Create new nodes and interweave them with original nodes
     * 2. Set random pointers for new nodes
     * 3. Separate the two lists
     * 
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    Node* copyRandomListConstantSpace(Node* head) {
        if (!head) return nullptr;
        
        // Step 1: Create new nodes and interweave them
        Node* current = head;
        while (current) {
            Node* newNode = new Node(current->val);
            newNode->next = current->next;
            current->next = newNode;
            current = newNode->next;
        }
        
        // Step 2: Set random pointers for new nodes
        current = head;
        while (current) {
            if (current->random) {
                current->next->random = current->random->next;
            }
            current = current->next->next;
        }
        
        // Step 3: Separate the two lists
        Node* dummy = new Node(0);
        Node* copyPrev = dummy;
        current = head;
        
        while (current) {
            Node* copyNode = current->next;
            current->next = copyNode->next;
            copyPrev->next = copyNode;
            copyPrev = copyNode;
            current = current->next;
        }
        
        Node* result = dummy->next;
        delete dummy;
        return result;
    }
    
    /*
     * Approach 3: Recursive with Memoization
     * 
     * Algorithm:
     * 1. Use recursion to clone nodes
     * 2. Use memoization to avoid cloning the same node twice
     * 
     * Time Complexity: O(n)
     * Space Complexity: O(n) for recursion stack and memoization
     */
    Node* copyRandomListRecursive(Node* head) {
        if (!head) return nullptr;
        
        unordered_map<Node*, Node*> memo;
        return cloneNode(head, memo);
    }

private:
    Node* cloneNode(Node* node, unordered_map<Node*, Node*>& memo) {
        if (!node) return nullptr;
        
        // If already cloned, return the clone
        if (memo.find(node) != memo.end()) {
            return memo[node];
        }
        
        // Create new node
        Node* clone = new Node(node->val);
        memo[node] = clone;
        
        // Recursively clone next and random
        clone->next = cloneNode(node->next, memo);
        clone->random = cloneNode(node->random, memo);
        
        return clone;
    }
};

// Helper functions for testing
Node* createRandomList(vector<int>& vals, vector<int>& randomIndices) {
    if (vals.empty()) return nullptr;
    
    vector<Node*> nodes;
    
    // Create all nodes
    for (int val : vals) {
        nodes.push_back(new Node(val));
    }
    
    // Set next pointers
    for (int i = 0; i < nodes.size() - 1; i++) {
        nodes[i]->next = nodes[i + 1];
    }
    
    // Set random pointers
    for (int i = 0; i < randomIndices.size(); i++) {
        if (randomIndices[i] != -1) {
            nodes[i]->random = nodes[randomIndices[i]];
        }
    }
    
    return nodes[0];
}

void printRandomList(Node* head) {
    Node* current = head;
    int index = 0;
    
    while (current) {
        cout << "[" << current->val << ",";
        if (current->random) {
            // Find index of random node
            Node* temp = head;
            int randomIndex = 0;
            while (temp && temp != current->random) {
                temp = temp->next;
                randomIndex++;
            }
            cout << randomIndex;
        } else {
            cout << "null";
        }
        cout << "]";
        
        if (current->next) cout << " -> ";
        current = current->next;
        index++;
    }
    cout << endl;
}

// Test cases
void testCopyRandomList() {
    Solution solution;
    
    // Test case 1: [[7,null],[13,0],[11,4],[10,2],[1,0]]
    vector<int> vals1 = {7, 13, 11, 10, 1};
    vector<int> random1 = {-1, 0, 4, 2, 0};  // -1 means null
    Node* head1 = createRandomList(vals1, random1);
    
    cout << "Test 1 (Hash Table):" << endl;
    cout << "Original: ";
    printRandomList(head1);
    
    Node* copy1 = solution.copyRandomList(head1);
    cout << "Copied:   ";
    printRandomList(copy1);
    cout << endl;
    
    // Test case 2: [[1,1],[2,1]]
    vector<int> vals2 = {1, 2};
    vector<int> random2 = {1, 1};
    Node* head2 = createRandomList(vals2, random2);
    
    cout << "Test 2 (Constant Space):" << endl;
    cout << "Original: ";
    printRandomList(head2);
    
    Node* copy2 = solution.copyRandomListConstantSpace(head2);
    cout << "Copied:   ";
    printRandomList(copy2);
    cout << endl;
    
    // Test case 3: [[3,null],[3,0],[3,null]]
    vector<int> vals3 = {3, 3, 3};
    vector<int> random3 = {-1, 0, -1};
    Node* head3 = createRandomList(vals3, random3);
    
    cout << "Test 3 (Recursive):" << endl;
    cout << "Original: ";
    printRandomList(head3);
    
    Node* copy3 = solution.copyRandomListRecursive(head3);
    cout << "Copied:   ";
    printRandomList(copy3);
    cout << endl;
    
    // Test case 4: Empty list
    Node* head4 = nullptr;
    
    cout << "Test 4 (Empty list):" << endl;
    cout << "Original: null" << endl;
    
    Node* copy4 = solution.copyRandomList(head4);
    cout << "Copied:   ";
    if (copy4) {
        printRandomList(copy4);
    } else {
        cout << "null" << endl;
    }
    cout << endl;
}

int main() {
    testCopyRandomList();
    return 0;
}

/*
 * Algorithm Analysis:
 * 
 * 1. Hash Table Approach:
 *    - Most intuitive and easy to implement
 *    - Two pass solution with clear separation of concerns
 *    - Extra space for the hash map
 * 
 * 2. Interweaving Approach:
 *    - Space optimal: O(1) extra space
 *    - More complex but demonstrates advanced linked list manipulation
 *    - Three distinct phases: interweave, set random, separate
 * 
 * 3. Recursive Approach:
 *    - Clean and elegant solution
 *    - Natural memoization prevents infinite loops
 *    - May hit stack overflow for very long lists
 * 
 * Key Points:
 * 1. Handle null pointers carefully (both next and random)
 * 2. Ensure no pointers in copy point to original nodes
 * 3. Hash table approach is most commonly asked in interviews
 * 4. Constant space approach shows deep understanding
 * 
 * Edge Cases:
 * - Empty list (null head)
 * - Single node with self-pointing random
 * - All random pointers are null
 * - Circular random pointer references
 * - Random pointers forming cycles
 * 
 * Common Mistakes:
 * - Forgetting to handle null random pointers
 * - Creating shallow copy instead of deep copy
 * - Memory leaks in test creation
 * - Off-by-one errors in interweaving approach
 * 
 * Interweaving Visualization:
 * Original: A -> B -> C -> null
 * Step 1:   A -> A' -> B -> B' -> C -> C' -> null
 * Step 2:   Set A'->random, B'->random, C'->random
 * Step 3:   A -> B -> C -> null and A' -> B' -> C' -> null
 * 
 * Interview Tips:
 * 1. Start with hash table approach (easier to implement correctly)
 * 2. Mention constant space approach to show algorithmic knowledge
 * 3. Discuss trade-offs between space and complexity
 * 4. Handle edge cases explicitly
 * 
 * Related Problems:
 * - Clone Graph
 * - Copy Binary Tree with Random Pointer
 * - Deep Copy of Doubly Linked List
 */