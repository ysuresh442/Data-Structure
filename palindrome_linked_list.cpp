/*
 * LeetCode 234: Palindrome Linked List
 * 
 * Given the head of a singly linked list, return true if it is a palindrome 
 * or false otherwise.
 * 
 * Example 1:
 * Input: head = [1,2,2,1]
 * Output: true
 * 
 * Example 2:
 * Input: head = [1,2]
 * Output: false
 * 
 * Follow up: Could you do it in O(n) time and O(1) space?
 * 
 * Companies: Amazon, Google, Microsoft, Facebook, Apple
 * Difficulty: Easy
 * Pattern: Two Pointers, Stack, Linked List Reversal
 */

#include "linked_list_common.h"

class Solution {
public:
    /*
     * Approach 1: Array/Vector Conversion
     * 
     * Algorithm:
     * 1. Copy all values to an array
     * 2. Use two pointers to check if array is palindrome
     * 
     * Time Complexity: O(n)
     * Space Complexity: O(n)
     */
    bool isPalindromeArray(ListNode* head) {
        vector<int> values;
        
        // Copy values to array
        ListNode* current = head;
        while (current) {
            values.push_back(current->val);
            current = current->next;
        }
        
        // Check palindrome using two pointers
        int left = 0, right = values.size() - 1;
        while (left < right) {
            if (values[left] != values[right]) {
                return false;
            }
            left++;
            right--;
        }
        
        return true;
    }
    
    /*
     * Approach 2: Stack-based Solution
     * 
     * Algorithm:
     * 1. Push first half of values onto stack
     * 2. Compare second half with popped values
     * 
     * Time Complexity: O(n)
     * Space Complexity: O(n/2) = O(n)
     */
    bool isPalindromeStack(ListNode* head) {
        if (!head || !head->next) return true;
        
        // Find the middle using slow/fast pointers
        ListNode* slow = head;
        ListNode* fast = head;
        stack<int> firstHalf;
        
        while (fast && fast->next) {
            firstHalf.push(slow->val);
            slow = slow->next;
            fast = fast->next->next;
        }
        
        // Skip middle element for odd length lists
        if (fast) {
            slow = slow->next;
        }
        
        // Compare second half with first half (from stack)
        while (slow) {
            if (firstHalf.empty() || firstHalf.top() != slow->val) {
                return false;
            }
            firstHalf.pop();
            slow = slow->next;
        }
        
        return true;
    }
    
    /*
     * Approach 3: Reverse Second Half (O(1) Space)
     * 
     * Algorithm:
     * 1. Find the middle of the list
     * 2. Reverse the second half
     * 3. Compare first half with reversed second half
     * 4. Restore the list (optional)
     * 
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    bool isPalindrome(ListNode* head) {
        if (!head || !head->next) return true;
        
        // Step 1: Find the middle of the list
        ListNode* firstHalfEnd = getFirstHalfEnd(head);
        
        // Step 2: Reverse the second half
        ListNode* secondHalfStart = reverseList(firstHalfEnd->next);
        
        // Step 3: Compare both halves
        bool isPalin = true;
        ListNode* p1 = head;
        ListNode* p2 = secondHalfStart;
        
        while (isPalin && p2) {
            if (p1->val != p2->val) {
                isPalin = false;
            }
            p1 = p1->next;
            p2 = p2->next;
        }
        
        // Step 4: Restore the list (optional but good practice)
        firstHalfEnd->next = reverseList(secondHalfStart);
        
        return isPalin;
    }
    
    /*
     * Approach 4: Recursive Solution
     * 
     * Algorithm:
     * 1. Use recursion to reach the end
     * 2. Compare values while unwinding
     * 3. Use a global pointer to track front
     * 
     * Time Complexity: O(n)
     * Space Complexity: O(n) due to recursion stack
     */
    bool isPalindromeRecursive(ListNode* head) {
        frontPointer = head;
        return recursiveCheck(head);
    }

private:
    ListNode* frontPointer;
    
    // Helper function to find the end of first half
    ListNode* getFirstHalfEnd(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        
        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        return slow;
    }
    
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
    
    // Recursive helper function
    bool recursiveCheck(ListNode* currentNode) {
        if (currentNode) {
            if (!recursiveCheck(currentNode->next)) {
                return false;
            }
            if (currentNode->val != frontPointer->val) {
                return false;
            }
            frontPointer = frontPointer->next;
        }
        return true;
    }
};

// Test cases
void testPalindromeLinkedList() {
    Solution solution;
    
    // Test case 1: [1,2,2,1] -> true
    vector<int> nums1 = {1, 2, 2, 1};
    ListNode* head1 = createLinkedList(nums1);
    
    cout << "Test 1:" << endl;
    cout << "List: ";
    printLinkedList(head1);
    cout << "Is palindrome (O(1) space): " << (solution.isPalindrome(head1) ? "true" : "false") << endl;
    cout << "Restored list: ";
    printLinkedList(head1);
    cout << endl;
    
    // Test case 2: [1,2] -> false
    vector<int> nums2 = {1, 2};
    ListNode* head2 = createLinkedList(nums2);
    
    cout << "Test 2:" << endl;
    cout << "List: ";
    printLinkedList(head2);
    cout << "Is palindrome (Array): " << (solution.isPalindromeArray(head2) ? "true" : "false") << endl;
    cout << endl;
    
    // Test case 3: [1,2,3,2,1] -> true (odd length)
    vector<int> nums3 = {1, 2, 3, 2, 1};
    ListNode* head3 = createLinkedList(nums3);
    
    cout << "Test 3:" << endl;
    cout << "List: ";
    printLinkedList(head3);
    cout << "Is palindrome (Stack): " << (solution.isPalindromeStack(head3) ? "true" : "false") << endl;
    cout << endl;
    
    // Test case 4: [1] -> true (single element)
    vector<int> nums4 = {1};
    ListNode* head4 = createLinkedList(nums4);
    
    cout << "Test 4:" << endl;
    cout << "List: ";
    printLinkedList(head4);
    cout << "Is palindrome: " << (solution.isPalindrome(head4) ? "true" : "false") << endl;
    cout << endl;
    
    // Test case 5: [] -> true (empty list)
    ListNode* head5 = nullptr;
    
    cout << "Test 5:" << endl;
    cout << "List: null" << endl;
    cout << "Is palindrome: " << (solution.isPalindrome(head5) ? "true" : "false") << endl;
    cout << endl;
    
    // Test case 6: [1,2,3,4,5] -> false
    vector<int> nums6 = {1, 2, 3, 4, 5};
    ListNode* head6 = createLinkedList(nums6);
    
    cout << "Test 6:" << endl;
    cout << "List: ";
    printLinkedList(head6);
    cout << "Is palindrome (Recursive): " << (solution.isPalindromeRecursive(head6) ? "true" : "false") << endl;
    cout << endl;
    
    // Test case 7: [1,1,2,1] -> false (almost palindrome)
    vector<int> nums7 = {1, 1, 2, 1};
    ListNode* head7 = createLinkedList(nums7);
    
    cout << "Test 7:" << endl;
    cout << "List: ";
    printLinkedList(head7);
    cout << "Is palindrome: " << (solution.isPalindrome(head7) ? "true" : "false") << endl;
    cout << endl;
}

int main() {
    testPalindromeLinkedList();
    return 0;
}

/*
 * Algorithm Analysis:
 * 
 * 1. Array Approach:
 *    - Pros: Simple to implement and understand
 *    - Cons: Uses O(n) extra space
 *    - Best for: When space is not a constraint
 * 
 * 2. Stack Approach:
 *    - Pros: Only uses O(n/2) space, elegant solution
 *    - Cons: Still linear space complexity
 *    - Best for: When you want to demonstrate stack usage
 * 
 * 3. Reverse Second Half:
 *    - Pros: O(1) space, optimal solution
 *    - Cons: More complex, temporarily modifies the list
 *    - Best for: Interview optimization questions
 * 
 * 4. Recursive Approach:
 *    - Pros: Elegant and demonstrates recursion
 *    - Cons: O(n) space due to call stack
 *    - Best for: Academic purposes, recursive thinking
 * 
 * Key Insights:
 * 
 * Finding the Middle:
 * - For even length: slow pointer stops at end of first half
 * - For odd length: slow pointer stops at middle element
 * - The condition fast->next && fast->next->next ensures proper positioning
 * 
 * Palindrome Patterns:
 * Even length: 1 -> 2 -> 2 -> 1
 * Odd length:  1 -> 2 -> 3 -> 2 -> 1
 * 
 * Edge Cases:
 * - Empty list (considered palindrome)
 * - Single element (always palindrome)
 * - Two elements (check if both are same)
 * - Lists with duplicate values
 * 
 * Common Mistakes:
 * - Incorrect middle finding for odd/even lengths
 * - Not handling empty or single element lists
 * - Forgetting to restore the list after reversing
 * - Off-by-one errors in loop conditions
 * 
 * Interview Tips:
 * 1. Start with the simple array approach
 * 2. Optimize to O(1) space when asked
 * 3. Mention that you can restore the original list
 * 4. Discuss trade-offs between approaches
 * 5. Handle edge cases explicitly
 * 
 * Step-by-Step O(1) Space Algorithm:
 * 
 * Original: 1 -> 2 -> 3 -> 2 -> 1
 * 
 * Step 1: Find middle
 * First half: 1 -> 2 -> 3
 * Second half: 2 -> 1
 * 
 * Step 2: Reverse second half
 * First half: 1 -> 2 -> 3
 * Reversed second: 1 -> 2
 * 
 * Step 3: Compare
 * Compare 1,2,3 with 1,2 (stop when shorter list ends)
 * 
 * Step 4: Restore (optional)
 * Reverse the second half back to original
 * 
 * Related Problems:
 * - Valid Palindrome (string version)
 * - Palindrome Number (number version)
 * - Longest Palindromic Substring
 * - Reverse Linked List (building block)
 * 
 * Time Complexity Summary:
 * - All approaches: O(n) time
 * - Space varies: O(n), O(n/2), O(1), O(n) respectively
 * 
 * Follow-up Questions:
 * - "What if we can't modify the original list?" (Use stack/array)
 * - "What if the list is very large?" (O(1) space approach)
 * - "How would you handle a doubly linked list?" (Easier with prev pointers)
 */