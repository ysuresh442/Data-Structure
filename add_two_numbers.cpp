/*
 * LeetCode 2: Add Two Numbers
 * 
 * You are given two non-empty linked lists representing two non-negative integers.
 * The digits are stored in reverse order, and each of their nodes contains a single digit.
 * Add the two numbers and return the sum as a linked list.
 * 
 * You may assume the two numbers do not contain any leading zero, except the number 0 itself.
 * 
 * Example 1:
 * Input: l1 = [2,4,3], l2 = [5,6,4]
 * Output: [7,0,8]
 * Explanation: 342 + 465 = 807.
 * 
 * Example 2:
 * Input: l1 = [0], l2 = [0]
 * Output: [0]
 * 
 * Example 3:
 * Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
 * Output: [8,9,9,9,0,0,0,1]
 * 
 * Companies: Amazon, Google, Microsoft, Bloomberg, Adobe
 * Difficulty: Medium
 * Pattern: Linked List Traversal, Math
 */

#include "linked_list_common.h"

class Solution {
public:
    /*
     * Approach 1: Elementary Math with Linked List Traversal
     * 
     * Algorithm:
     * 1. Initialize a dummy head to simplify edge cases
     * 2. Keep track of carry from previous addition
     * 3. Traverse both lists simultaneously
     * 4. For each position, add corresponding digits + carry
     * 5. Create new node with sum % 10, update carry = sum / 10
     * 6. Continue until both lists are exhausted and carry is 0
     * 
     * Time Complexity: O(max(m, n)) where m and n are lengths of the two lists
     * Space Complexity: O(max(m, n)) for the result list
     */
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* current = &dummy;
        int carry = 0;
        
        while (l1 || l2 || carry) {
            int sum = carry;
            
            if (l1) {
                sum += l1->val;
                l1 = l1->next;
            }
            
            if (l2) {
                sum += l2->val;
                l2 = l2->next;
            }
            
            carry = sum / 10;
            current->next = new ListNode(sum % 10);
            current = current->next;
        }
        
        return dummy.next;
    }
    
    /*
     * Approach 2: Recursive Solution
     * 
     * Time Complexity: O(max(m, n))
     * Space Complexity: O(max(m, n)) due to recursion stack
     */
    ListNode* addTwoNumbersRecursive(ListNode* l1, ListNode* l2) {
        return addHelper(l1, l2, 0);
    }
    
private:
    ListNode* addHelper(ListNode* l1, ListNode* l2, int carry) {
        if (!l1 && !l2 && carry == 0) {
            return nullptr;
        }
        
        int sum = carry;
        if (l1) {
            sum += l1->val;
            l1 = l1->next;
        }
        if (l2) {
            sum += l2->val;
            l2 = l2->next;
        }
        
        ListNode* result = new ListNode(sum % 10);
        result->next = addHelper(l1, l2, sum / 10);
        
        return result;
    }
};

// Test cases
void testAddTwoNumbers() {
    Solution solution;
    
    // Test case 1: [2,4,3] + [5,6,4] = [7,0,8]
    vector<int> nums1 = {2, 4, 3};
    vector<int> nums2 = {5, 6, 4};
    ListNode* l1 = createLinkedList(nums1);
    ListNode* l2 = createLinkedList(nums2);
    
    cout << "Test 1:" << endl;
    cout << "L1: ";
    printLinkedList(l1);
    cout << "L2: ";
    printLinkedList(l2);
    
    ListNode* result = solution.addTwoNumbers(l1, l2);
    cout << "Sum: ";
    printLinkedList(result);
    cout << endl;
    
    // Test case 2: [0] + [0] = [0]
    vector<int> nums3 = {0};
    vector<int> nums4 = {0};
    ListNode* l3 = createLinkedList(nums3);
    ListNode* l4 = createLinkedList(nums4);
    
    cout << "Test 2:" << endl;
    cout << "L1: ";
    printLinkedList(l3);
    cout << "L2: ";
    printLinkedList(l4);
    
    ListNode* result2 = solution.addTwoNumbers(l3, l4);
    cout << "Sum: ";
    printLinkedList(result2);
    cout << endl;
    
    // Test case 3: [9,9,9,9,9,9,9] + [9,9,9,9] = [8,9,9,9,0,0,0,1]
    vector<int> nums5 = {9, 9, 9, 9, 9, 9, 9};
    vector<int> nums6 = {9, 9, 9, 9};
    ListNode* l5 = createLinkedList(nums5);
    ListNode* l6 = createLinkedList(nums6);
    
    cout << "Test 3:" << endl;
    cout << "L1: ";
    printLinkedList(l5);
    cout << "L2: ";
    printLinkedList(l6);
    
    ListNode* result3 = solution.addTwoNumbers(l5, l6);
    cout << "Sum: ";
    printLinkedList(result3);
    cout << endl;
}

int main() {
    testAddTwoNumbers();
    return 0;
}

/*
 * Key Points:
 * 1. Handle different length lists gracefully
 * 2. Don't forget the final carry
 * 3. Use dummy head to simplify code
 * 4. Process digits from least significant to most significant
 * 
 * Edge Cases:
 * - Lists of different lengths
 * - Carry at the end (e.g., 999 + 1 = 1000)
 * - Single digit numbers
 * - Zero cases
 * 
 * Similar Problems:
 * - Add Two Numbers II (digits stored in normal order)
 * - Multiply Strings
 * - Plus One
 */