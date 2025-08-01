/*
 * LeetCode 206: Reverse Linked List
 * 
 * Given the head of a singly linked list, reverse the list, and return the reversed list.
 * 
 * Example 1:
 * Input: head = [1,2,3,4,5]
 * Output: [5,4,3,2,1]
 * 
 * Example 2:
 * Input: head = [1,2]
 * Output: [2,1]
 * 
 * Example 3:
 * Input: head = []
 * Output: []
 * 
 * Companies: Amazon, Google, Facebook, Microsoft, Apple, Netflix
 * Difficulty: Easy
 * Pattern: Linked List Reversal, Three Pointers
 */

#include "linked_list_common.h"

class Solution {
public:
    /*
     * Approach 1: Iterative Solution (Three Pointers)
     * 
     * Algorithm:
     * 1. Use three pointers: prev, current, next
     * 2. For each node, reverse the link to point to previous
     * 3. Move all pointers one step forward
     * 4. Continue until current becomes null
     * 
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* current = head;
        
        while (current) {
            ListNode* next = current->next;  // Store next node
            current->next = prev;            // Reverse the link
            prev = current;                  // Move prev forward
            current = next;                  // Move current forward
        }
        
        return prev;  // prev is the new head
    }
    
    /*
     * Approach 2: Recursive Solution
     * 
     * Algorithm:
     * 1. Base case: if head is null or head->next is null, return head
     * 2. Recursively reverse the rest of the list
     * 3. Reverse the current link
     * 4. Set current->next to null to avoid cycles
     * 
     * Time Complexity: O(n)
     * Space Complexity: O(n) due to recursion stack
     */
    ListNode* reverseListRecursive(ListNode* head) {
        // Base case
        if (!head || !head->next) {
            return head;
        }
        
        // Recursively reverse the rest
        ListNode* newHead = reverseListRecursive(head->next);
        
        // Reverse current connection
        head->next->next = head;
        head->next = nullptr;
        
        return newHead;
    }
    
    /*
     * Approach 3: Stack-based Solution
     * 
     * Algorithm:
     * 1. Push all nodes onto a stack
     * 2. Pop nodes and rebuild the list in reverse order
     * 
     * Time Complexity: O(n)
     * Space Complexity: O(n) for the stack
     */
    ListNode* reverseListStack(ListNode* head) {
        if (!head) return nullptr;
        
        stack<ListNode*> nodeStack;
        ListNode* current = head;
        
        // Push all nodes onto stack
        while (current) {
            nodeStack.push(current);
            current = current->next;
        }
        
        // Pop nodes to build reversed list
        ListNode* newHead = nodeStack.top();
        nodeStack.pop();
        current = newHead;
        
        while (!nodeStack.empty()) {
            current->next = nodeStack.top();
            nodeStack.pop();
            current = current->next;
        }
        
        current->next = nullptr;  // Important: set last node's next to null
        return newHead;
    }
    
    /*
     * Approach 4: Two-pointer technique with array
     * 
     * Time Complexity: O(n)
     * Space Complexity: O(n) for storing node pointers
     */
    ListNode* reverseListArray(ListNode* head) {
        if (!head) return nullptr;
        
        vector<ListNode*> nodes;
        ListNode* current = head;
        
        // Store all nodes in array
        while (current) {
            nodes.push_back(current);
            current = current->next;
        }
        
        // Rebuild list in reverse order
        for (int i = nodes.size() - 1; i > 0; i--) {
            nodes[i]->next = nodes[i - 1];
        }
        nodes[0]->next = nullptr;
        
        return nodes.back();
    }
};

// Test cases
void testReverseLinkedList() {
    Solution solution;
    
    // Test case 1: [1,2,3,4,5] -> [5,4,3,2,1]
    vector<int> nums1 = {1, 2, 3, 4, 5};
    ListNode* head1 = createLinkedList(nums1);
    
    cout << "Test 1 (Iterative):" << endl;
    cout << "Original: ";
    printLinkedList(head1);
    
    ListNode* result1 = solution.reverseList(head1);
    cout << "Reversed: ";
    printLinkedList(result1);
    cout << endl;
    
    // Test case 2: [1,2] -> [2,1]
    vector<int> nums2 = {1, 2};
    ListNode* head2 = createLinkedList(nums2);
    
    cout << "Test 2 (Recursive):" << endl;
    cout << "Original: ";
    printLinkedList(head2);
    
    ListNode* result2 = solution.reverseListRecursive(head2);
    cout << "Reversed: ";
    printLinkedList(result2);
    cout << endl;
    
    // Test case 3: [] -> []
    ListNode* head3 = nullptr;
    
    cout << "Test 3 (Empty list):" << endl;
    cout << "Original: null" << endl;
    
    ListNode* result3 = solution.reverseList(head3);
    cout << "Reversed: ";
    if (result3) {
        printLinkedList(result3);
    } else {
        cout << "null" << endl;
    }
    cout << endl;
    
    // Test case 4: [42] -> [42] (single node)
    vector<int> nums4 = {42};
    ListNode* head4 = createLinkedList(nums4);
    
    cout << "Test 4 (Single node, Stack method):" << endl;
    cout << "Original: ";
    printLinkedList(head4);
    
    ListNode* result4 = solution.reverseListStack(head4);
    cout << "Reversed: ";
    printLinkedList(result4);
    cout << endl;
}

int main() {
    testReverseLinkedList();
    return 0;
}

/*
 * Key Points:
 * 1. Three-pointer iterative approach is most efficient
 * 2. Recursive solution is elegant but uses O(n) space
 * 3. Be careful about null pointers and cycles
 * 4. The last node's next must be set to null
 * 
 * Edge Cases:
 * - Empty list (null head)
 * - Single node list
 * - Two node list
 * 
 * Common Mistakes:
 * - Forgetting to store next pointer before reversing
 * - Not setting the last node's next to null
 * - Mixing up the order of pointer updates
 * - Not handling null input
 * 
 * Visualization of Iterative Process:
 * Initial:  null <- 1 -> 2 -> 3 -> 4 -> 5 -> null
 *           prev  curr
 * 
 * Step 1:   null <- 1    2 -> 3 -> 4 -> 5 -> null
 *                  prev  curr
 * 
 * Step 2:   null <- 1 <- 2    3 -> 4 -> 5 -> null
 *                         prev curr
 * 
 * Continue until curr becomes null...
 * 
 * Extensions:
 * - Reverse linked list in groups of k
 * - Reverse between positions m and n
 * - Check if linked list is palindrome (using reversal)
 */