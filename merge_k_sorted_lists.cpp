/*
 * LeetCode 23: Merge k Sorted Lists
 * 
 * You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.
 * Merge all the linked-lists into one sorted linked-list and return it.
 * 
 * Example 1:
 * Input: lists = [[1,4,5],[1,3,4],[2,6]]
 * Output: [1,1,2,3,4,4,5,6]
 * Explanation: The linked-lists are:
 * [
 *   1->4->5,
 *   1->3->4,
 *   2->6
 * ]
 * merging them into one sorted list:
 * 1->1->2->3->4->4->5->6
 * 
 * Example 2:
 * Input: lists = []
 * Output: []
 * 
 * Example 3:
 * Input: lists = [[]]
 * Output: []
 * 
 * Companies: Amazon, Google, Microsoft, Facebook, Uber, Airbnb
 * Difficulty: Hard
 * Pattern: Heap/Priority Queue, Divide and Conquer, Merge
 */

#include "linked_list_common.h"

class Solution {
public:
    /*
     * Approach 1: Min-Heap / Priority Queue
     * 
     * Algorithm:
     * 1. Add the first node of each non-empty list to a min-heap
     * 2. Extract the minimum node and add it to result
     * 3. If the extracted node has a next, add it to heap
     * 4. Repeat until heap is empty
     * 
     * Time Complexity: O(N log k) where N is total nodes, k is number of lists
     * Space Complexity: O(k) for the heap
     */
    struct Compare {
        bool operator()(ListNode* a, ListNode* b) {
            return a->val > b->val;  // Min heap
        }
    };
    
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, Compare> pq;
        
        // Add first node of each non-empty list to heap
        for (ListNode* list : lists) {
            if (list) {
                pq.push(list);
            }
        }
        
        ListNode dummy(0);
        ListNode* current = &dummy;
        
        while (!pq.empty()) {
            // Get the node with minimum value
            ListNode* minNode = pq.top();
            pq.pop();
            
            // Add to result
            current->next = minNode;
            current = current->next;
            
            // If this node has a next, add it to heap
            if (minNode->next) {
                pq.push(minNode->next);
            }
        }
        
        return dummy.next;
    }
    
    /*
     * Approach 2: Divide and Conquer
     * 
     * Algorithm:
     * 1. Pair up k lists and merge each pair
     * 2. After first round, k lists are merged into k/2 lists
     * 3. Repeat until only one list remains
     * 
     * Time Complexity: O(N log k) where N is total nodes
     * Space Complexity: O(log k) for recursion stack
     */
    ListNode* mergeKListsDivideConquer(vector<ListNode*>& lists) {
        if (lists.empty()) return nullptr;
        
        while (lists.size() > 1) {
            vector<ListNode*> mergedLists;
            
            // Pair up and merge lists
            for (int i = 0; i < lists.size(); i += 2) {
                ListNode* l1 = lists[i];
                ListNode* l2 = (i + 1 < lists.size()) ? lists[i + 1] : nullptr;
                mergedLists.push_back(mergeTwoLists(l1, l2));
            }
            
            lists = mergedLists;
        }
        
        return lists[0];
    }
    
    /*
     * Approach 3: Merge Lists One by One
     * 
     * Algorithm:
     * 1. Start with the first list
     * 2. Merge it with the second list
     * 3. Merge the result with the third list
     * 4. Continue until all lists are merged
     * 
     * Time Complexity: O(N * k) where N is total nodes
     * Space Complexity: O(1)
     */
    ListNode* mergeKListsSequential(vector<ListNode*>& lists) {
        if (lists.empty()) return nullptr;
        
        ListNode* result = lists[0];
        
        for (int i = 1; i < lists.size(); i++) {
            result = mergeTwoLists(result, lists[i]);
        }
        
        return result;
    }
    
    /*
     * Approach 4: Recursive Divide and Conquer
     * 
     * Time Complexity: O(N log k)
     * Space Complexity: O(log k)
     */
    ListNode* mergeKListsRecursive(vector<ListNode*>& lists) {
        return mergeHelper(lists, 0, lists.size() - 1);
    }

private:
    // Helper function to merge two sorted lists
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
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
    
    // Recursive helper for divide and conquer
    ListNode* mergeHelper(vector<ListNode*>& lists, int start, int end) {
        if (start > end) return nullptr;
        if (start == end) return lists[start];
        
        int mid = start + (end - start) / 2;
        ListNode* left = mergeHelper(lists, start, mid);
        ListNode* right = mergeHelper(lists, mid + 1, end);
        
        return mergeTwoLists(left, right);
    }
};

// Test cases
void testMergeKSortedLists() {
    Solution solution;
    
    // Test case 1: [[1,4,5],[1,3,4],[2,6]]
    vector<int> nums1 = {1, 4, 5};
    vector<int> nums2 = {1, 3, 4};
    vector<int> nums3 = {2, 6};
    
    vector<ListNode*> lists1 = {
        createLinkedList(nums1),
        createLinkedList(nums2),
        createLinkedList(nums3)
    };
    
    cout << "Test 1 (Priority Queue):" << endl;
    cout << "Input lists:" << endl;
    for (int i = 0; i < lists1.size(); i++) {
        cout << "List " << i + 1 << ": ";
        printLinkedList(lists1[i]);
    }
    
    ListNode* result1 = solution.mergeKLists(lists1);
    cout << "Merged: ";
    printLinkedList(result1);
    cout << endl;
    
    // Test case 2: [] (empty input)
    vector<ListNode*> lists2 = {};
    
    cout << "Test 2 (Empty input):" << endl;
    ListNode* result2 = solution.mergeKListsDivideConquer(lists2);
    cout << "Merged: ";
    if (result2) {
        printLinkedList(result2);
    } else {
        cout << "null" << endl;
    }
    cout << endl;
    
    // Test case 3: [[]] (single empty list)
    vector<ListNode*> lists3 = {nullptr};
    
    cout << "Test 3 (Single empty list):" << endl;
    ListNode* result3 = solution.mergeKListsSequential(lists3);
    cout << "Merged: ";
    if (result3) {
        printLinkedList(result3);
    } else {
        cout << "null" << endl;
    }
    cout << endl;
    
    // Test case 4: Multiple lists with different lengths
    vector<int> nums4 = {1, 2, 3};
    vector<int> nums5 = {4, 5};
    vector<int> nums6 = {6};
    vector<int> nums7 = {};
    
    vector<ListNode*> lists4 = {
        createLinkedList(nums4),
        createLinkedList(nums5),
        createLinkedList(nums6),
        nums7.empty() ? nullptr : createLinkedList(nums7)
    };
    
    cout << "Test 4 (Recursive Divide & Conquer):" << endl;
    cout << "Input lists:" << endl;
    for (int i = 0; i < lists4.size(); i++) {
        cout << "List " << i + 1 << ": ";
        if (lists4[i]) {
            printLinkedList(lists4[i]);
        } else {
            cout << "null" << endl;
        }
    }
    
    ListNode* result4 = solution.mergeKListsRecursive(lists4);
    cout << "Merged: ";
    printLinkedList(result4);
    cout << endl;
}

int main() {
    testMergeKSortedLists();
    return 0;
}

/*
 * Algorithm Analysis:
 * 
 * 1. Priority Queue Approach:
 *    - Best for when k is small
 *    - Consistent O(log k) for each insertion/deletion
 *    - Memory efficient: only stores k nodes at a time
 * 
 * 2. Divide and Conquer:
 *    - Most efficient overall: O(N log k)
 *    - Works well for large k
 *    - Uses the merge two lists pattern efficiently
 * 
 * 3. Sequential Merging:
 *    - Simple to implement
 *    - Less efficient: O(N * k)
 *    - Good for small k or educational purposes
 * 
 * Key Points:
 * 1. Handle empty lists and null pointers carefully
 * 2. Priority queue approach is intuitive and efficient
 * 3. Divide and conquer is optimal for large inputs
 * 4. Reuse the merge two lists function
 * 
 * Edge Cases:
 * - Empty input vector
 * - All lists are empty
 * - Single list (empty or non-empty)
 * - Lists with different lengths
 * - Duplicate values across lists
 * 
 * Common Mistakes:
 * - Not handling empty lists in priority queue
 * - Forgetting to add next node to heap after extraction
 * - Incorrect base cases in recursive approach
 * - Memory management issues
 * 
 * Space Optimization:
 * - Can modify input lists instead of creating new nodes
 * - Priority queue only needs to store k nodes maximum
 * - Recursive approach uses O(log k) stack space
 * 
 * Related Problems:
 * - Merge Two Sorted Lists
 * - Merge Sorted Array
 * - Kth Smallest Element in a Sorted Matrix
 * - Find K Pairs with Smallest Sums
 */