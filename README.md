# Linked Lists: Top LeetCode Questions

This repository contains comprehensive solutions to the most important linked list problems from LeetCode. Each solution includes multiple approaches, detailed explanations, time/space complexity analysis, and real-world test cases.

## 📊 Problems Overview

| # | Title | Companies | Pattern | Difficulty | Solution |
|---|-------|-----------|---------|------------|----------|
| 1 | Add Two Numbers | Amazon, Google, Microsoft | Linked List Traversal | Medium | [add_two_numbers.cpp](add_two_numbers.cpp) |
| 2 | Remove Nth Node From End of List | Amazon, Google | Two Pointers | Medium | [remove_nth_node.cpp](remove_nth_node.cpp) |
| 3 | Merge Two Sorted Lists | Amazon, Microsoft | Linked List Merge | Easy | [merge_two_sorted_lists.cpp](merge_two_sorted_lists.cpp) |
| 4 | Reverse Linked List | Amazon, Google, Facebook | Linked List Reversal | Easy | [reverse_linked_list.cpp](reverse_linked_list.cpp) |
| 5 | Linked List Cycle | Amazon, Google | Two Pointers (Floyd's) | Easy | [linked_list_cycle.cpp](linked_list_cycle.cpp) |
| 6 | Merge k Sorted Lists | Amazon, Google | Heap/Priority Queue | Hard | [merge_k_sorted_lists.cpp](merge_k_sorted_lists.cpp) |
| 7 | Copy List with Random Pointer | Amazon, Google | Hash Table | Medium | [copy_list_with_random_pointer.cpp](copy_list_with_random_pointer.cpp) |
| 8 | Reorder List | Amazon, Google | Two Pointers | Medium | [reorder_list.cpp](reorder_list.cpp) |
| 9 | Sort List | Amazon, Google | Merge Sort | Medium | [sort_list.cpp](sort_list.cpp) |
| 10 | Intersection of Two Linked Lists | Amazon, Google | Two Pointers | Easy | [intersection_of_two_linked_lists.cpp](intersection_of_two_linked_lists.cpp) |

## 🎯 Key Patterns and Techniques

### 1. Two Pointers / Fast-Slow Pointers
**When to use:** Finding middle, detecting cycles, removing nodes from end
**Key Problems:** 
- Linked List Cycle (Floyd's Algorithm)
- Remove Nth Node From End
- Finding Middle of Linked List

**Template:**
```cpp
ListNode* slow = head;
ListNode* fast = head;
while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
}
```

### 2. Linked List Reversal
**When to use:** Reversing entire list or parts of it
**Key Problems:**
- Reverse Linked List
- Reverse Nodes in k-Group
- Palindrome Linked List

**Template:**
```cpp
ListNode* prev = nullptr;
ListNode* current = head;
while (current) {
    ListNode* next = current->next;
    current->next = prev;
    prev = current;
    current = next;
}
return prev;
```

### 3. Merge Technique
**When to use:** Combining sorted lists, reordering
**Key Problems:**
- Merge Two Sorted Lists
- Merge k Sorted Lists
- Sort List

**Template:**
```cpp
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
```

### 4. Hash Table for Complex Relationships
**When to use:** Random pointers, detecting intersections, avoiding duplicates
**Key Problems:**
- Copy List with Random Pointer
- Remove Duplicates from Unsorted List

### 5. Dummy Head Technique
**When to use:** Simplifying edge cases, especially when head might change
**Benefits:** Eliminates special handling for head node

```cpp
ListNode dummy(0);
dummy.next = head;
// Work with dummy.next
return dummy.next;
```

## 🚀 Advanced Techniques

### Floyd's Cycle Detection (Tortoise and Hare)
- **Use Case:** Detecting cycles in O(1) space
- **Principle:** Fast pointer gains one position per iteration on slow pointer
- **Extension:** Finding cycle start (Linked List Cycle II)

### Divide and Conquer
- **Use Case:** Merge k sorted lists, sorting linked lists
- **Advantage:** Reduces time complexity from O(n²) to O(n log n)

### Space-Time Trade-offs
1. **Hash Table Approach:** O(n) space for O(1) lookup
2. **Two-Pass Algorithm:** O(1) space but requires multiple traversals
3. **Constant Space Tricks:** Modifying pointers cleverly (e.g., interweaving)

## 💡 Common Pitfalls and Solutions

### 1. Null Pointer Handling
```cpp
// Always check before accessing
if (fast && fast->next) {
    fast = fast->next->next;
}
```

### 2. Memory Management
```cpp
// Don't forget to delete removed nodes
ListNode* nodeToDelete = current->next;
current->next = nodeToDelete->next;
delete nodeToDelete;
```

### 3. Edge Cases to Consider
- Empty list (head = nullptr)
- Single node
- Two nodes
- Cycles in the list
- Lists of different lengths

### 4. Off-by-One Errors
- Finding middle: Use correct loop condition
- N-th node from end: Position fast pointer correctly

## 🏗️ Problem-Solving Framework

### Step 1: Understand the Problem
- What are the constraints?
- What should be returned?
- Are there special cases?

### Step 2: Identify the Pattern
- Two pointers?
- Reversal needed?
- Merge operation?
- Hash table for relationships?

### Step 3: Choose the Approach
- Optimize for time or space?
- Multiple approaches possible?
- Which is most suitable for interview?

### Step 4: Handle Edge Cases
- Null inputs
- Single/two node lists
- Cycles or special structures

## 🔥 Interview Tips

### Most Frequently Asked
1. **Reverse Linked List** - Master both iterative and recursive
2. **Merge Two Sorted Lists** - Foundation for many problems
3. **Linked List Cycle** - Floyd's algorithm is elegant
4. **Remove Nth Node** - Classic two-pointer problem

### What Interviewers Look For
1. **Clean Code:** Use dummy heads, meaningful variable names
2. **Edge Case Handling:** Show you think about corner cases
3. **Multiple Solutions:** Mention time/space trade-offs
4. **Optimization:** Can you improve the solution?

### Common Follow-ups
- "What if the list is doubly linked?"
- "Can you do it in O(1) space?"
- "How would you handle very large lists?"
- "What if there are memory constraints?"

## 📈 Complexity Analysis Summary

| Operation | Time | Space | Notes |
|-----------|------|-------|-------|
| Traversal | O(n) | O(1) | Basic operation |
| Reversal | O(n) | O(1) | Three-pointer technique |
| Cycle Detection | O(n) | O(1) | Floyd's algorithm |
| Merge Two Lists | O(m+n) | O(1) | Linear merge |
| Merge k Lists | O(N log k) | O(1) or O(k) | N = total nodes |
| Find Middle | O(n) | O(1) | Two-pointer technique |

## 🛠️ How to Use This Repository

### Compilation
```bash
# Compile any solution
g++ -std=c++17 -o solution problem_name.cpp

# Run with test cases
./solution
```

### Study Guide
1. Start with **Easy** problems to build fundamentals
2. Focus on **patterns** rather than memorizing solutions
3. Practice **without looking** at solutions first
4. **Time yourself** to simulate interview conditions
5. **Explain your approach** out loud

### Common Header File
All solutions include `linked_list_common.h` which provides:
- Standard includes and utilities
- ListNode definition
- Helper functions for testing
- Node definitions for special cases (random pointer, multilevel)

## 🎓 Learning Path

### Beginner (Start Here)
1. Reverse Linked List
2. Merge Two Sorted Lists
3. Remove Duplicates from Sorted List
4. Middle of the Linked List

### Intermediate
1. Remove Nth Node From End
2. Linked List Cycle
3. Intersection of Two Linked Lists
4. Add Two Numbers

### Advanced
1. Merge k Sorted Lists
2. Copy List with Random Pointer
3. Reorder List
4. Sort List
5. Reverse Nodes in k-Group

### Expert Level
1. LRU Cache (using doubly linked list)
2. Design Browser History
3. All O(1) Data Structure
4. Flatten Multilevel Doubly Linked List

## 🤝 Contributing

Feel free to contribute by:
- Adding new problems
- Optimizing existing solutions
- Improving documentation
- Adding test cases
- Fixing bugs

## 📚 Additional Resources

- [LeetCode Linked List Problems](https://leetcode.com/tag/linked-list/)
- [GeeksforGeeks Linked List](https://www.geeksforgeeks.org/data-structures/linked-list/)
- [Cracking the Coding Interview - Chapter 2](https://www.amazon.com/Cracking-Coding-Interview-Programming-Questions/dp/0984782850)

---

**Happy Coding! 🚀**

*Remember: The key to mastering linked lists is understanding the patterns, not memorizing solutions.*
