/*
 * LeetCode 143: Reorder List
 * 
 * You are given the head of a singly linked-list. The list can be represented as:
 * L0 → L1 → … → Ln - 1 → Ln
 * 
 * Reorder the list to be on the following form:
 * L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
 * 
 * You may not modify the values in the list's nodes. Only nodes themselves may be changed.
 * 
 * Example 1:
 * Input: head = [1,2,3,4]
 * Output: [1,4,2,3]
 * 
 * Example 2:
 * Input: head = [1,2,3,4,5]
 * Output: [1,5,2,4,3]
 * 
 * Companies: Amazon, Google, Microsoft, Facebook, Bloomberg
 * Difficulty: Medium
 * Pattern: Two Pointers, Linked List Reversal, Merge
 */

#include "linked_list_common.h"

class Solution {
public:
    /*
     * Approach 1: Find Middle + Reverse + Merge
     * 
     * Algorithm:
     * 1. Find the middle of the linked list using slow/fast pointers
     * 2. Reverse the second half of the list
     * 3. Merge the first half and reversed second half alternately
     * 
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    void reorderList(ListNode* head) {
        if (!head || !head->next) return;
        
        // Step 1: Find the middle of the list
        ListNode* slow = head;
        ListNode* fast = head;
        ListNode* prev = nullptr;
        
        while (fast && fast->next) {
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        
        // Cut the list into two halves
        prev->next = nullptr;
        
        // Step 2: Reverse the second half
        ListNode* secondHalf = reverseList(slow);
        
        // Step 3: Merge the two halves alternately
        ListNode* firstHalf = head;
        mergeAlternately(firstHalf, secondHalf);
    }
    
    /*
     * Approach 2: Using Array/Vector
     * 
     * Algorithm:
     * 1. Store all nodes in an array
     * 2. Use two pointers from start and end to reorder
     * 
     * Time Complexity: O(n)
     * Space Complexity: O(n) for the array
     */
    void reorderListArray(ListNode* head) {
        if (!head || !head->next) return;
        
        // Store all nodes in vector
        vector<ListNode*> nodes;
        ListNode* current = head;
        
        while (current) {
            nodes.push_back(current);
            current = current->next;
        }
        
        // Reorder using two pointers
        int left = 0, right = nodes.size() - 1;
        
        while (left < right) {
            nodes[left]->next = nodes[right];
            left++;
            
            if (left >= right) break;
            
            nodes[right]->next = nodes[left];
            right--;
        }
        
        nodes[left]->next = nullptr;
    }
    
    /*
     * Approach 3: Recursive Solution
     * 
     * Algorithm:
     * 1. Use recursion to reach the end
     * 2. Reorder from the end back to the beginning
     * 
     * Time Complexity: O(n)
     * Space Complexity: O(n) due to recursion stack
     */
    void reorderListRecursive(ListNode* head) {
        if (!head || !head->next) return;
        
        int length = getLength(head);
        reorderHelper(head, length);
    }

private:
    // Helper function to reverse a linked list
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* current = head;
        
        while (current) {
            ListNode* next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        
        return prev;
    }
    
    // Helper function to merge two lists alternately
    void mergeAlternately(ListNode* first, ListNode* second) {
        while (first && second) {
            ListNode* firstNext = first->next;
            ListNode* secondNext = second->next;
            
            first->next = second;
            second->next = firstNext;
            
            first = firstNext;
            second = secondNext;
        }
    }
    
    // Helper function for recursive approach
    ListNode* reorderHelper(ListNode* head, int length) {
        if (length == 1) {
            ListNode* tail = head->next;
            head->next = nullptr;
            return tail;
        }
        
        if (length == 2) {
            ListNode* tail = head->next;
            head->next = nullptr;
            return tail;
        }
        
        ListNode* tail = reorderHelper(head->next, length - 2);
        ListNode* nextTail = tail->next;
        tail->next = head->next;
        head->next = tail;
        
        return nextTail;
    }
};

// Test cases
void testReorderList() {
    Solution solution;
    
    // Test case 1: [1,2,3,4] -> [1,4,2,3]
    vector<int> nums1 = {1, 2, 3, 4};
    ListNode* head1 = createLinkedList(nums1);
    
    cout << "Test 1:" << endl;
    cout << "Original: ";
    printLinkedList(head1);
    
    solution.reorderList(head1);
    cout << "Reordered: ";
    printLinkedList(head1);
    cout << endl;
    
    // Test case 2: [1,2,3,4,5] -> [1,5,2,4,3]
    vector<int> nums2 = {1, 2, 3, 4, 5};
    ListNode* head2 = createLinkedList(nums2);
    
    cout << "Test 2 (Array approach):" << endl;
    cout << "Original: ";
    printLinkedList(head2);
    
    solution.reorderListArray(head2);
    cout << "Reordered: ";
    printLinkedList(head2);
    cout << endl;
    
    // Test case 3: [1,2] -> [1,2]
    vector<int> nums3 = {1, 2};
    ListNode* head3 = createLinkedList(nums3);
    
    cout << "Test 3:" << endl;
    cout << "Original: ";
    printLinkedList(head3);
    
    solution.reorderList(head3);
    cout << "Reordered: ";
    printLinkedList(head3);
    cout << endl;
    
    // Test case 4: [1] -> [1]
    vector<int> nums4 = {1};
    ListNode* head4 = createLinkedList(nums4);
    
    cout << "Test 4 (Single node):" << endl;
    cout << "Original: ";
    printLinkedList(head4);
    
    solution.reorderList(head4);
    cout << "Reordered: ";
    printLinkedList(head4);
    cout << endl;
    
    // Test case 5: [1,2,3,4,5,6] -> [1,6,2,5,3,4]
    vector<int> nums5 = {1, 2, 3, 4, 5, 6};
    ListNode* head5 = createLinkedList(nums5);
    
    cout << "Test 5 (Recursive approach):" << endl;
    cout << "Original: ";
    printLinkedList(head5);
    
    solution.reorderListRecursive(head5);
    cout << "Reordered: ";
    printLinkedList(head5);
    cout << endl;
}

int main() {
    testReorderList();
    return 0;
}

/*
 * Algorithm Breakdown:
 * 
 * The key insight is to split the problem into three steps:
 * 1. Find the middle point to split the list
 * 2. Reverse the second half
 * 3. Merge the two halves alternately
 * 
 * Detailed Steps:
 * 
 * Original: 1 -> 2 -> 3 -> 4 -> 5 -> 6
 * 
 * Step 1: Find middle and split
 * First half:  1 -> 2 -> 3
 * Second half: 4 -> 5 -> 6
 * 
 * Step 2: Reverse second half
 * First half:  1 -> 2 -> 3
 * Second half: 6 -> 5 -> 4
 * 
 * Step 3: Merge alternately
 * Result: 1 -> 6 -> 2 -> 5 -> 3 -> 4
 * 
 * Key Points:
 * 1. Use slow/fast pointers to find the middle in one pass
 * 2. Be careful with odd vs even length lists
 * 3. Properly cut the connection between the two halves
 * 4. Handle edge cases: empty list, single node, two nodes
 * 
 * Edge Cases:
 * - Empty list (null head)
 * - Single node
 * - Two nodes
 * - Odd length vs even length lists
 * 
 * Common Mistakes:
 * - Not properly cutting the connection between halves
 * - Off-by-one errors in finding the middle
 * - Incorrect merging logic
 * - Not handling the last node's next pointer
 * 
 * Space-Time Trade-offs:
 * 1. Approach 1: O(1) space, O(n) time - Optimal
 * 2. Approach 2: O(n) space, O(n) time - Easier to understand
 * 3. Approach 3: O(n) space, O(n) time - Recursive elegance
 * 
 * Interview Tips:
 * 1. Start by explaining the three-step approach
 * 2. Implement the optimal O(1) space solution
 * 3. Mention the array approach as an alternative
 * 4. Discuss how to handle edge cases
 * 
 * Pattern Recognition:
 * This problem combines several common linked list patterns:
 * - Finding middle using two pointers
 * - Reversing a linked list
 * - Merging two linked lists
 * 
 * Related Problems:
 * - Palindrome Linked List (similar middle-finding + reversal)
 * - Merge Two Sorted Lists (merging pattern)
 * - Reverse Linked List (reversal pattern)
 * - Middle of the Linked List (finding middle pattern)
 */