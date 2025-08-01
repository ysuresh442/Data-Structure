/*
 * LeetCode 19: Remove Nth Node From End of List
 * 
 * Given the head of a linked list, remove the nth node from the end of the list 
 * and return its head.
 * 
 * Example 1:
 * Input: head = [1,2,3,4,5], n = 2
 * Output: [1,2,3,5]
 * 
 * Example 2:
 * Input: head = [1], n = 1
 * Output: []
 * 
 * Example 3:
 * Input: head = [1,2], n = 1
 * Output: [1]
 * 
 * Companies: Amazon, Google, Microsoft, Facebook
 * Difficulty: Medium
 * Pattern: Two Pointers, Fast-Slow Pointers
 */

#include "linked_list_common.h"

class Solution {
public:
    /*
     * Approach 1: Two-Pass Algorithm
     * 
     * Algorithm:
     * 1. First pass: Count the total number of nodes
     * 2. Second pass: Remove the (length - n + 1)th node from the beginning
     * 
     * Time Complexity: O(L) where L is the length of the list
     * Space Complexity: O(1)
     */
    ListNode* removeNthFromEndTwoPass(ListNode* head, int n) {
        // Count the length of the list
        int length = 0;
        ListNode* current = head;
        while (current) {
            length++;
            current = current->next;
        }
        
        // Handle edge case: removing the head
        if (n == length) {
            ListNode* newHead = head->next;
            delete head;
            return newHead;
        }
        
        // Find the node before the one to be removed
        current = head;
        for (int i = 0; i < length - n - 1; i++) {
            current = current->next;
        }
        
        // Remove the nth node from end
        ListNode* nodeToRemove = current->next;
        current->next = nodeToRemove->next;
        delete nodeToRemove;
        
        return head;
    }
    
    /*
     * Approach 2: One-Pass Algorithm with Two Pointers
     * 
     * Algorithm:
     * 1. Use dummy head to handle edge cases
     * 2. Place fast pointer n+1 steps ahead of slow pointer
     * 3. Move both pointers until fast reaches end
     * 4. Slow pointer will be at the node before the one to remove
     * 
     * Time Complexity: O(L)
     * Space Complexity: O(1)
     */
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode dummy(0);
        dummy.next = head;
        ListNode* slow = &dummy;
        ListNode* fast = &dummy;
        
        // Move fast pointer n+1 steps ahead
        for (int i = 0; i <= n; i++) {
            fast = fast->next;
        }
        
        // Move both pointers until fast reaches end
        while (fast) {
            slow = slow->next;
            fast = fast->next;
        }
        
        // Remove the nth node from end
        ListNode* nodeToRemove = slow->next;
        slow->next = slow->next->next;
        delete nodeToRemove;
        
        return dummy.next;
    }
    
    /*
     * Approach 3: Recursive Solution
     * 
     * Algorithm:
     * 1. Recursively traverse to the end
     * 2. Count nodes on the way back
     * 3. Remove node when count equals n
     * 
     * Time Complexity: O(L)
     * Space Complexity: O(L) due to recursion stack
     */
    ListNode* removeNthFromEndRecursive(ListNode* head, int n) {
        int count = 0;
        return removeHelper(head, n, count);
    }
    
private:
    ListNode* removeHelper(ListNode* head, int n, int& count) {
        if (!head) return nullptr;
        
        head->next = removeHelper(head->next, n, count);
        count++;
        
        if (count == n) {
            ListNode* nodeToDelete = head;
            delete nodeToDelete;
            return head->next;
        }
        
        return head;
    }
};

// Test cases
void testRemoveNthNode() {
    Solution solution;
    
    // Test case 1: [1,2,3,4,5], n = 2 -> [1,2,3,5]
    vector<int> nums1 = {1, 2, 3, 4, 5};
    ListNode* head1 = createLinkedList(nums1);
    
    cout << "Test 1:" << endl;
    cout << "Original: ";
    printLinkedList(head1);
    
    ListNode* result1 = solution.removeNthFromEnd(head1, 2);
    cout << "After removing 2nd from end: ";
    printLinkedList(result1);
    cout << endl;
    
    // Test case 2: [1], n = 1 -> []
    vector<int> nums2 = {1};
    ListNode* head2 = createLinkedList(nums2);
    
    cout << "Test 2:" << endl;
    cout << "Original: ";
    printLinkedList(head2);
    
    ListNode* result2 = solution.removeNthFromEnd(head2, 1);
    cout << "After removing 1st from end: ";
    if (result2) {
        printLinkedList(result2);
    } else {
        cout << "null" << endl;
    }
    cout << endl;
    
    // Test case 3: [1,2], n = 1 -> [1]
    vector<int> nums3 = {1, 2};
    ListNode* head3 = createLinkedList(nums3);
    
    cout << "Test 3:" << endl;
    cout << "Original: ";
    printLinkedList(head3);
    
    ListNode* result3 = solution.removeNthFromEnd(head3, 1);
    cout << "After removing 1st from end: ";
    printLinkedList(result3);
    cout << endl;
    
    // Test case 4: [1,2], n = 2 -> [2] (remove head)
    vector<int> nums4 = {1, 2};
    ListNode* head4 = createLinkedList(nums4);
    
    cout << "Test 4:" << endl;
    cout << "Original: ";
    printLinkedList(head4);
    
    ListNode* result4 = solution.removeNthFromEnd(head4, 2);
    cout << "After removing 2nd from end: ";
    printLinkedList(result4);
    cout << endl;
}

int main() {
    testRemoveNthNode();
    return 0;
}

/*
 * Key Points:
 * 1. Two-pointer technique is optimal for one-pass solution
 * 2. Use dummy head to handle edge cases (removing head node)
 * 3. Make sure fast pointer is exactly n+1 steps ahead
 * 4. Handle memory deallocation properly
 * 
 * Edge Cases:
 * - Removing the head node (n equals list length)
 * - Single node list
 * - n = 1 (removing last node)
 * - List with duplicate values
 * 
 * Common Mistakes:
 * - Off-by-one errors in pointer positioning
 * - Not handling the case where head needs to be removed
 * - Memory leaks (not deleting removed node)
 * 
 * Follow-up Questions:
 * - What if n is greater than the list length?
 * - Can you do it without calculating the list length?
 * - How would you handle a doubly linked list?
 */