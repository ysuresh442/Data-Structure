/*
 * LeetCode 21: Merge Two Sorted Lists
 * 
 * You are given the heads of two sorted linked lists list1 and list2.
 * Merge the two lists in a sorted manner and return the head of the merged linked list.
 * The list should be made by splicing together the nodes of the first two lists.
 * 
 * Example 1:
 * Input: list1 = [1,2,4], list2 = [1,3,4]
 * Output: [1,1,2,3,4,4]
 * 
 * Example 2:
 * Input: list1 = [], list2 = []
 * Output: []
 * 
 * Example 3:
 * Input: list1 = [], list2 = [0]
 * Output: [0]
 * 
 * Companies: Amazon, Microsoft, Google, Facebook, Apple
 * Difficulty: Easy
 * Pattern: Linked List Merge, Two Pointers
 */

#include "linked_list_common.h"

class Solution {
public:
    /*
     * Approach 1: Iterative Solution
     * 
     * Algorithm:
     * 1. Use dummy head to simplify edge cases
     * 2. Compare values from both lists
     * 3. Always pick the smaller value and advance that pointer
     * 4. Append remaining nodes when one list is exhausted
     * 
     * Time Complexity: O(m + n) where m and n are lengths of the lists
     * Space Complexity: O(1)
     */
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode dummy(0);
        ListNode* current = &dummy;
        
        while (list1 && list2) {
            if (list1->val <= list2->val) {
                current->next = list1;
                list1 = list1->next;
            } else {
                current->next = list2;
                list2 = list2->next;
            }
            current = current->next;
        }
        
        // Append remaining nodes
        current->next = list1 ? list1 : list2;
        
        return dummy.next;
    }
    
    /*
     * Approach 2: Recursive Solution
     * 
     * Algorithm:
     * 1. Base cases: if one list is empty, return the other
     * 2. Compare first elements and recursively merge
     * 3. The smaller element becomes current head
     * 
     * Time Complexity: O(m + n)
     * Space Complexity: O(m + n) due to recursion stack
     */
    ListNode* mergeTwoListsRecursive(ListNode* list1, ListNode* list2) {
        // Base cases
        if (!list1) return list2;
        if (!list2) return list1;
        
        if (list1->val <= list2->val) {
            list1->next = mergeTwoListsRecursive(list1->next, list2);
            return list1;
        } else {
            list2->next = mergeTwoListsRecursive(list1, list2->next);
            return list2;
        }
    }
    
    /*
     * Approach 3: In-place Merge (modifying original lists)
     * 
     * Time Complexity: O(m + n)
     * Space Complexity: O(1)
     */
    ListNode* mergeTwoListsInPlace(ListNode* list1, ListNode* list2) {
        if (!list1) return list2;
        if (!list2) return list1;
        
        // Ensure list1 has the smaller first element
        if (list1->val > list2->val) {
            swap(list1, list2);
        }
        
        ListNode* head = list1;
        
        while (list1->next && list2) {
            if (list1->next->val <= list2->val) {
                list1 = list1->next;
            } else {
                ListNode* temp = list1->next;
                list1->next = list2;
                list2 = temp;
                list1 = list1->next;
            }
        }
        
        if (list2) {
            list1->next = list2;
        }
        
        return head;
    }
};

// Test cases
void testMergeTwoSortedLists() {
    Solution solution;
    
    // Test case 1: [1,2,4] and [1,3,4] -> [1,1,2,3,4,4]
    vector<int> nums1 = {1, 2, 4};
    vector<int> nums2 = {1, 3, 4};
    ListNode* list1 = createLinkedList(nums1);
    ListNode* list2 = createLinkedList(nums2);
    
    cout << "Test 1:" << endl;
    cout << "List1: ";
    printLinkedList(list1);
    cout << "List2: ";
    printLinkedList(list2);
    
    ListNode* result1 = solution.mergeTwoLists(list1, list2);
    cout << "Merged: ";
    printLinkedList(result1);
    cout << endl;
    
    // Test case 2: [] and [] -> []
    ListNode* list3 = nullptr;
    ListNode* list4 = nullptr;
    
    cout << "Test 2:" << endl;
    cout << "List1: null" << endl;
    cout << "List2: null" << endl;
    
    ListNode* result2 = solution.mergeTwoLists(list3, list4);
    cout << "Merged: ";
    if (result2) {
        printLinkedList(result2);
    } else {
        cout << "null" << endl;
    }
    cout << endl;
    
    // Test case 3: [] and [0] -> [0]
    vector<int> nums5 = {};
    vector<int> nums6 = {0};
    ListNode* list5 = nums5.empty() ? nullptr : createLinkedList(nums5);
    ListNode* list6 = createLinkedList(nums6);
    
    cout << "Test 3:" << endl;
    cout << "List1: null" << endl;
    cout << "List2: ";
    printLinkedList(list6);
    
    ListNode* result3 = solution.mergeTwoLists(list5, list6);
    cout << "Merged: ";
    printLinkedList(result3);
    cout << endl;
    
    // Test case 4: Different lengths [1,2,3,4,5] and [6]
    vector<int> nums7 = {1, 2, 3, 4, 5};
    vector<int> nums8 = {6};
    ListNode* list7 = createLinkedList(nums7);
    ListNode* list8 = createLinkedList(nums8);
    
    cout << "Test 4 (Recursive):" << endl;
    cout << "List1: ";
    printLinkedList(list7);
    cout << "List2: ";
    printLinkedList(list8);
    
    ListNode* result4 = solution.mergeTwoListsRecursive(list7, list8);
    cout << "Merged: ";
    printLinkedList(result4);
    cout << endl;
}

int main() {
    testMergeTwoSortedLists();
    return 0;
}

/*
 * Key Points:
 * 1. Handle empty lists gracefully
 * 2. Use dummy head to simplify code
 * 3. Remember to append remaining nodes
 * 4. Recursive solution is elegant but uses more space
 * 
 * Edge Cases:
 * - One or both lists are empty
 * - Lists of different lengths
 * - All elements in one list are smaller
 * - Duplicate values
 * 
 * Common Mistakes:
 * - Forgetting to handle null lists
 * - Not appending remaining nodes
 * - Using >= instead of <= (affects stability)
 * 
 * Extensions:
 * - Merge k sorted lists
 * - Merge sorted arrays
 * - Merge intervals
 * 
 * Pattern Recognition:
 * This is a fundamental merge operation used in:
 * - Merge sort
 * - External sorting
 * - Database join operations
 */