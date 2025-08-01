/*
 * LeetCode 148: Sort List
 * 
 * Given the head of a linked list, return the list after sorting it in ascending order.
 * 
 * Example 1:
 * Input: head = [4,2,1,3]
 * Output: [1,2,3,4]
 * 
 * Example 2:
 * Input: head = [-1,5,3,4,0]
 * Output: [-1,0,3,4,5]
 * 
 * Example 3:
 * Input: head = []
 * Output: []
 * 
 * Follow up: Can you sort the linked list in O(n logn) time and O(1) memory (i.e. constant space)?
 * 
 * Companies: Amazon, Google, Microsoft, Facebook, Adobe
 * Difficulty: Medium
 * Pattern: Merge Sort, Divide and Conquer
 */

#include "linked_list_common.h"

class Solution {
public:
    /*
     * Approach 1: Merge Sort (Top-Down Recursive)
     * 
     * Algorithm:
     * 1. Find the middle of the list using slow/fast pointers
     * 2. Split the list into two halves
     * 3. Recursively sort both halves
     * 4. Merge the sorted halves
     * 
     * Time Complexity: O(n log n)
     * Space Complexity: O(log n) due to recursion stack
     */
    ListNode* sortList(ListNode* head) {
        if (!head || !head->next) {
            return head;
        }
        
        // Split the list into two halves
        ListNode* mid = getMidAndSplit(head);
        
        // Recursively sort both halves
        ListNode* left = sortList(head);
        ListNode* right = sortList(mid);
        
        // Merge the sorted halves
        return merge(left, right);
    }
    
    /*
     * Approach 2: Merge Sort (Bottom-Up Iterative)
     * 
     * Algorithm:
     * 1. Start with lists of size 1, merge pairs
     * 2. Double the size and repeat until size >= list length
     * 3. Achieve O(1) space complexity
     * 
     * Time Complexity: O(n log n)
     * Space Complexity: O(1)
     */
    ListNode* sortListBottomUp(ListNode* head) {
        if (!head || !head->next) return head;
        
        // Get the length of the list
        int length = getLength(head);
        
        ListNode dummy(0);
        dummy.next = head;
        
        // Start with step size 1, double each iteration
        for (int step = 1; step < length; step *= 2) {
            ListNode* prev = &dummy;
            ListNode* current = dummy.next;
            
            while (current) {
                // Split into two sublists of size 'step'
                ListNode* left = current;
                ListNode* right = split(left, step);
                current = split(right, step);
                
                // Merge the two sublists
                prev = mergeAndConnect(prev, left, right);
            }
        }
        
        return dummy.next;
    }
    
    /*
     * Approach 3: Quick Sort (for comparison, but not optimal for linked lists)
     * 
     * Time Complexity: O(n²) worst case, O(n log n) average
     * Space Complexity: O(log n) due to recursion
     */
    ListNode* sortListQuickSort(ListNode* head) {
        if (!head || !head->next) return head;
        
        ListNode* tail = getTail(head);
        quickSort(head, tail);
        return head;
    }

private:
    // Get middle node and split the list
    ListNode* getMidAndSplit(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        ListNode* prev = nullptr;
        
        while (fast && fast->next) {
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        
        // Split the list
        if (prev) {
            prev->next = nullptr;
        }
        
        return slow;
    }
    
    // Merge two sorted lists
    ListNode* merge(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* current = &dummy;
        
        while (l1 && l2) {
            if (l1->val <= l2->val) {
                current->next = l1;
                l1 = l1->next;
            } else {
                current->next = l2;
                l2 = l2->next;
            }
            current = current->next;
        }
        
        current->next = l1 ? l1 : l2;
        return dummy.next;
    }
    
    // Split list after 'n' nodes and return the remaining part
    ListNode* split(ListNode* head, int n) {
        while (head && --n) {
            head = head->next;
        }
        
        if (!head) return nullptr;
        
        ListNode* next = head->next;
        head->next = nullptr;
        return next;
    }
    
    // Merge two sublists and connect to previous part
    ListNode* mergeAndConnect(ListNode* prev, ListNode* l1, ListNode* l2) {
        ListNode* merged = merge(l1, l2);
        prev->next = merged;
        
        // Move to the end of merged list
        while (prev->next) {
            prev = prev->next;
        }
        
        return prev;
    }
    
    // Quick sort helper functions
    ListNode* getTail(ListNode* head) {
        while (head && head->next) {
            head = head->next;
        }
        return head;
    }
    
    void quickSort(ListNode* head, ListNode* tail) {
        if (!head || head == tail) return;
        
        ListNode* pivot = partition(head, tail);
        quickSort(head, pivot);
        quickSort(pivot->next, tail);
    }
    
    ListNode* partition(ListNode* head, ListNode* tail) {
        int pivot = tail->val;
        ListNode* i = head;
        
        for (ListNode* j = head; j != tail; j = j->next) {
            if (j->val < pivot) {
                swap(i->val, j->val);
                i = i->next;
            }
        }
        
        swap(i->val, tail->val);
        return i;
    }
};

// Test cases
void testSortList() {
    Solution solution;
    
    // Test case 1: [4,2,1,3] -> [1,2,3,4]
    vector<int> nums1 = {4, 2, 1, 3};
    ListNode* head1 = createLinkedList(nums1);
    
    cout << "Test 1 (Merge Sort Recursive):" << endl;
    cout << "Original: ";
    printLinkedList(head1);
    
    ListNode* result1 = solution.sortList(head1);
    cout << "Sorted:   ";
    printLinkedList(result1);
    cout << endl;
    
    // Test case 2: [-1,5,3,4,0] -> [-1,0,3,4,5]
    vector<int> nums2 = {-1, 5, 3, 4, 0};
    ListNode* head2 = createLinkedList(nums2);
    
    cout << "Test 2 (Bottom-Up Merge Sort):" << endl;
    cout << "Original: ";
    printLinkedList(head2);
    
    ListNode* result2 = solution.sortListBottomUp(head2);
    cout << "Sorted:   ";
    printLinkedList(result2);
    cout << endl;
    
    // Test case 3: [] -> []
    ListNode* head3 = nullptr;
    
    cout << "Test 3 (Empty list):" << endl;
    cout << "Original: null" << endl;
    
    ListNode* result3 = solution.sortList(head3);
    cout << "Sorted:   ";
    if (result3) {
        printLinkedList(result3);
    } else {
        cout << "null" << endl;
    }
    cout << endl;
    
    // Test case 4: [1] -> [1]
    vector<int> nums4 = {1};
    ListNode* head4 = createLinkedList(nums4);
    
    cout << "Test 4 (Single element):" << endl;
    cout << "Original: ";
    printLinkedList(head4);
    
    ListNode* result4 = solution.sortList(head4);
    cout << "Sorted:   ";
    printLinkedList(result4);
    cout << endl;
    
    // Test case 5: [3,2,1,0,-1,-2] -> [-2,-1,0,1,2,3]
    vector<int> nums5 = {3, 2, 1, 0, -1, -2};
    ListNode* head5 = createLinkedList(nums5);
    
    cout << "Test 5 (Quick Sort - for comparison):" << endl;
    cout << "Original: ";
    printLinkedList(head5);
    
    ListNode* result5 = solution.sortListQuickSort(head5);
    cout << "Sorted:   ";
    printLinkedList(result5);
    cout << endl;
    
    // Test case 6: Already sorted list
    vector<int> nums6 = {1, 2, 3, 4, 5};
    ListNode* head6 = createLinkedList(nums6);
    
    cout << "Test 6 (Already sorted):" << endl;
    cout << "Original: ";
    printLinkedList(head6);
    
    ListNode* result6 = solution.sortList(head6);
    cout << "Sorted:   ";
    printLinkedList(result6);
    cout << endl;
}

int main() {
    testSortList();
    return 0;
}

/*
 * Algorithm Analysis:
 * 
 * Merge Sort is the optimal choice for linked lists because:
 * 1. Guaranteed O(n log n) time complexity
 * 2. Stable sorting algorithm
 * 3. No random access needed (unlike quicksort)
 * 4. Can be implemented with O(1) space (bottom-up approach)
 * 
 * Why not other sorting algorithms?
 * 
 * 1. Quick Sort:
 *    - Requires random access for efficient partitioning
 *    - O(n²) worst case time complexity
 *    - Not stable
 * 
 * 2. Heap Sort:
 *    - Requires random access to maintain heap property
 *    - Not suitable for linked lists
 * 
 * 3. Bubble/Selection/Insertion Sort:
 *    - O(n²) time complexity
 *    - Only good for small lists or nearly sorted data
 * 
 * Key Insights:
 * 
 * 1. Top-Down Merge Sort:
 *    - More intuitive and easier to implement
 *    - Uses O(log n) space due to recursion
 *    - Classic divide-and-conquer approach
 * 
 * 2. Bottom-Up Merge Sort:
 *    - Achieves O(1) space complexity
 *    - More complex implementation
 *    - Iteratively merges smaller sublists
 * 
 * Step-by-step Bottom-Up Process:
 * 
 * Original: [4, 2, 1, 3, 6, 5]
 * 
 * Step 1 (size = 1): Merge pairs of size 1
 * [2, 4] [1, 3] [5, 6]
 * 
 * Step 2 (size = 2): Merge pairs of size 2
 * [1, 2, 3, 4] [5, 6]
 * 
 * Step 3 (size = 4): Merge pairs of size 4
 * [1, 2, 3, 4, 5, 6]
 * 
 * Edge Cases:
 * - Empty list
 * - Single element
 * - Two elements
 * - Already sorted (best case)
 * - Reverse sorted (worst case for some algorithms)
 * - Duplicate elements
 * 
 * Common Mistakes:
 * - Not properly splitting the list in merge sort
 * - Forgetting to handle null pointers
 * - Incorrect merging logic
 * - Memory leaks in recursive approach
 * 
 * Interview Tips:
 * 1. Start with top-down merge sort (easier to explain)
 * 2. Mention that merge sort is optimal for linked lists
 * 3. Discuss why other sorting algorithms aren't suitable
 * 4. If asked for O(1) space, implement bottom-up approach
 * 5. Handle edge cases explicitly
 * 
 * Related Problems:
 * - Merge Two Sorted Lists (building block)
 * - Merge k Sorted Lists (extension)
 * - Sort Colors (different approach)
 * - Insertion Sort List (simpler O(n²) approach)
 * 
 * Time Complexity Comparison:
 * - Merge Sort: O(n log n) guaranteed
 * - Quick Sort: O(n log n) average, O(n²) worst
 * - Insertion Sort: O(n²) but good for small/nearly sorted lists
 * - Heap Sort: Not suitable for linked lists
 */