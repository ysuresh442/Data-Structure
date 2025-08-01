/*
 * LeetCode 141: Linked List Cycle
 * 
 * Given head, the head of a linked list, determine if the linked list has a cycle in it.
 * There is a cycle in a linked list if there is some node in the list that can be reached 
 * again by continuously following the next pointer.
 * 
 * Return true if there is a cycle in the linked list. Otherwise, return false.
 * 
 * Example 1:
 * Input: head = [3,2,0,-4], pos = 1
 * Output: true
 * Explanation: There is a cycle in the linked list, where the tail connects to the 1st node (0-indexed).
 * 
 * Example 2:
 * Input: head = [1,2], pos = 0
 * Output: true
 * Explanation: There is a cycle in the linked list, where the tail connects to the 0th node.
 * 
 * Example 3:
 * Input: head = [1], pos = -1
 * Output: false
 * Explanation: There is no cycle in the linked list.
 * 
 * Companies: Amazon, Google, Microsoft, Facebook, Apple, Bloomberg
 * Difficulty: Easy
 * Pattern: Two Pointers (Floyd's Cycle Detection), Fast-Slow Pointers
 */

#include "linked_list_common.h"

class Solution {
public:
    /*
     * Approach 1: Floyd's Cycle Detection Algorithm (Tortoise and Hare)
     * 
     * Algorithm:
     * 1. Use two pointers: slow (moves 1 step) and fast (moves 2 steps)
     * 2. If there's a cycle, fast will eventually meet slow
     * 3. If there's no cycle, fast will reach the end (null)
     * 
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    bool hasCycle(ListNode *head) {
        if (!head || !head->next) {
            return false;
        }
        
        ListNode* slow = head;
        ListNode* fast = head->next;
        
        while (slow != fast) {
            if (!fast || !fast->next) {
                return false;  // Reached end, no cycle
            }
            slow = slow->next;
            fast = fast->next->next;
        }
        
        return true;  // Pointers met, cycle detected
    }
    
    /*
     * Approach 2: Hash Set Solution
     * 
     * Algorithm:
     * 1. Traverse the list and store visited nodes in a set
     * 2. If we encounter a node already in the set, there's a cycle
     * 3. If we reach the end, there's no cycle
     * 
     * Time Complexity: O(n)
     * Space Complexity: O(n)
     */
    bool hasCycleHashSet(ListNode *head) {
        unordered_set<ListNode*> visited;
        
        while (head) {
            if (visited.count(head)) {
                return true;  // Node already visited, cycle detected
            }
            visited.insert(head);
            head = head->next;
        }
        
        return false;  // Reached end, no cycle
    }
    
    /*
     * Approach 3: Floyd's Algorithm with same starting point
     * 
     * Algorithm:
     * 1. Both pointers start from head
     * 2. Move slow by 1 and fast by 2 in each iteration
     * 3. Check for meeting after each move
     * 
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    bool hasCycleAlternative(ListNode *head) {
        ListNode* slow = head;
        ListNode* fast = head;
        
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            
            if (slow == fast) {
                return true;
            }
        }
        
        return false;
    }
    
    /*
     * Approach 4: Modifying node values (destructive)
     * 
     * Algorithm:
     * 1. Mark visited nodes by changing their values
     * 2. If we encounter a marked node, there's a cycle
     * 
     * Note: This approach modifies the original list
     * 
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    bool hasCycleDestructive(ListNode *head) {
        const int VISITED = INT_MAX;
        
        while (head) {
            if (head->val == VISITED) {
                return true;  // Already visited this node
            }
            head->val = VISITED;
            head = head->next;
        }
        
        return false;
    }
};

// Test cases
void testLinkedListCycle() {
    Solution solution;
    
    // Test case 1: [3,2,0,-4] with cycle at position 1
    vector<int> nums1 = {3, 2, 0, -4};
    ListNode* head1 = createLinkedList(nums1);
    createCycle(head1, 1);  // Create cycle where tail connects to node at index 1
    
    cout << "Test 1: [3,2,0,-4] with cycle at position 1" << endl;
    cout << "Has cycle (Floyd's): " << (solution.hasCycle(head1) ? "true" : "false") << endl;
    cout << endl;
    
    // Test case 2: [1,2] with cycle at position 0
    vector<int> nums2 = {1, 2};
    ListNode* head2 = createLinkedList(nums2);
    createCycle(head2, 0);  // Create cycle where tail connects to head
    
    cout << "Test 2: [1,2] with cycle at position 0" << endl;
    cout << "Has cycle (Alternative): " << (solution.hasCycleAlternative(head2) ? "true" : "false") << endl;
    cout << endl;
    
    // Test case 3: [1] with no cycle
    vector<int> nums3 = {1};
    ListNode* head3 = createLinkedList(nums3);
    
    cout << "Test 3: [1] with no cycle" << endl;
    cout << "Has cycle: " << (solution.hasCycle(head3) ? "true" : "false") << endl;
    cout << endl;
    
    // Test case 4: [] (empty list)
    ListNode* head4 = nullptr;
    
    cout << "Test 4: Empty list" << endl;
    cout << "Has cycle: " << (solution.hasCycle(head4) ? "true" : "false") << endl;
    cout << endl;
    
    // Test case 5: [1,2,3,4,5] with no cycle (using hash set method)
    vector<int> nums5 = {1, 2, 3, 4, 5};
    ListNode* head5 = createLinkedList(nums5);
    
    cout << "Test 5: [1,2,3,4,5] with no cycle" << endl;
    cout << "Original list: ";
    printLinkedList(head5);
    cout << "Has cycle (Hash Set): " << (solution.hasCycleHashSet(head5) ? "true" : "false") << endl;
    cout << endl;
}

int main() {
    testLinkedListCycle();
    return 0;
}

/*
 * Floyd's Cycle Detection Algorithm Explanation:
 * 
 * Why does it work?
 * - If there's no cycle, fast pointer will reach the end
 * - If there's a cycle, both pointers will eventually be inside the cycle
 * - Since fast moves 2 steps and slow moves 1 step, fast gains 1 step on slow each iteration
 * - In a cycle of length k, fast will catch up to slow in at most k iterations
 * 
 * Mathematical proof:
 * - Let's say slow pointer has traveled 'd' distance when they meet
 * - Fast pointer has traveled '2d' distance
 * - The difference '2d - d = d' must be a multiple of cycle length
 * - This guarantees they will meet within the cycle
 * 
 * Key Points:
 * 1. Floyd's algorithm is optimal: O(1) space, O(n) time
 * 2. Hash set approach is intuitive but uses O(n) space
 * 3. Handle edge cases: null head, single node
 * 4. Fast pointer should check both fast and fast->next for null
 * 
 * Edge Cases:
 * - Empty list (head = null)
 * - Single node with no cycle
 * - Single node with self-cycle
 * - Two nodes with cycle
 * - Long list with cycle at the end
 * 
 * Common Mistakes:
 * - Not checking if fast->next is null before accessing fast->next->next
 * - Starting both pointers at the same position without proper loop condition
 * - Infinite loop when there is a cycle (wrong termination condition)
 * 
 * Related Problems:
 * - Linked List Cycle II (find the start of cycle)
 * - Happy Number (applying cycle detection to number sequences)
 * - Find the Duplicate Number (using cycle detection in array)
 */