# Trees: Top LeetCode Questions

This repository contains comprehensive solutions to the most important tree-related LeetCode problems frequently asked in technical interviews at top companies like Amazon, Google, and Facebook.

## Problem Overview

| # | Title | Companies | Pattern | Difficulty | Solution |
|---|-------|-----------|---------|------------|----------|
| 1 | Maximum Depth of Binary Tree | Amazon, Google | DFS/BFS | Easy | [maximum_depth_of_binary_tree.cpp](maximum_depth_of_binary_tree.cpp) |
| 2 | Validate Binary Search Tree | Amazon, Google | Inorder Traversal | Medium | [validate_binary_search_tree.cpp](validate_binary_search_tree.cpp) |
| 3 | Binary Tree Level Order Traversal | Amazon, Google, Facebook | BFS | Medium | [binary_tree_level_order_traversal.cpp](binary_tree_level_order_traversal.cpp) |
| 4 | Invert Binary Tree | Google, Facebook | DFS | Easy | [invert_binary_tree.cpp](invert_binary_tree.cpp) |
| 5 | Lowest Common Ancestor of BST | Amazon, Google | BST Properties | Medium | [lowest_common_ancestor_of_bst.cpp](lowest_common_ancestor_of_bst.cpp) |
| 6 | Path Sum | Amazon, Google | DFS | Easy | [path_sum.cpp](path_sum.cpp) |
| 7 | Construct Binary Tree from Preorder and Inorder | Amazon, Google | Tree Construction | Medium | [construct_binary_tree_from_preorder_and_inorder.cpp](construct_binary_tree_from_preorder_and_inorder.cpp) |
| 8 | Serialize and Deserialize Binary Tree | Amazon, Google | Tree Serialization | Hard | [serialize_and_deserialize_binary_tree.cpp](serialize_and_deserialize_binary_tree.cpp) |
| 9 | Binary Tree Maximum Path Sum | Amazon, Google | DFS | Hard | [binary_tree_maximum_path_sum.cpp](binary_tree_maximum_path_sum.cpp) |
| 10 | Same Tree | Amazon, Google | Tree Comparison | Easy | [same_tree.cpp](same_tree.cpp) |
| 11 | Symmetric Tree | Amazon, Google | DFS | Easy | [symmetric_tree.cpp](symmetric_tree.cpp) |
| 12 | Binary Tree Zigzag Level Order Traversal | Amazon, Google | BFS | Medium | [zigzag_level_order_traversal.cpp](zigzag_level_order_traversal.cpp) |
| 13 | Populating Next Right Pointers in Each Node | Amazon, Google | BFS | Medium | [populating_next_right_pointers.cpp](populating_next_right_pointers.cpp) |
| 14 | Flatten Binary Tree to Linked List | Amazon, Google | DFS | Medium | [flatten_binary_tree_to_linked_list.cpp](flatten_binary_tree_to_linked_list.cpp) |
| 15 | Binary Tree Right Side View | Amazon, Google | BFS | Medium | [binary_tree_right_side_view.cpp](binary_tree_right_side_view.cpp) |
| 16 | Balanced Binary Tree | Amazon, Google | DFS | Easy | [balanced_binary_tree.cpp](balanced_binary_tree.cpp) |
| 17 | Minimum Depth of Binary Tree | Amazon, Google | BFS | Easy | [minimum_depth_of_binary_tree.cpp](minimum_depth_of_binary_tree.cpp) |
| 18 | Path Sum II | Amazon, Google | DFS, Backtracking | Medium | [path_sum_ii.cpp](path_sum_ii.cpp) |
| 19 | Sum Root to Leaf Numbers | Amazon, Google | DFS | Medium | [sum_root_to_leaf_numbers.cpp](sum_root_to_leaf_numbers.cpp) |
| 20 | Binary Tree Inorder Traversal | Amazon, Google | DFS, Stack | Easy | [binary_tree_inorder_traversal.cpp](binary_tree_inorder_traversal.cpp) |
| 21 | Binary Tree Preorder Traversal | Amazon, Google | DFS, Stack | Easy | [binary_tree_preorder_traversal.cpp](binary_tree_preorder_traversal.cpp) |
| 22 | Binary Tree Postorder Traversal | Amazon, Google | DFS, Stack | Easy | [binary_tree_postorder_traversal.cpp](binary_tree_postorder_traversal.cpp) |
| 23 | Recover Binary Search Tree | Amazon, Google | Inorder Traversal | Hard | [recover_binary_search_tree.cpp](recover_binary_search_tree.cpp) |
| 24 | Kth Smallest Element in a BST | Amazon, Google | Inorder Traversal | Medium | [kth_smallest_element_bst.cpp](kth_smallest_element_bst.cpp) |
| 25 | Count Complete Tree Nodes | Amazon, Google | DFS | Medium | [count_complete_tree_nodes.cpp](count_complete_tree_nodes.cpp) |
| 26 | Binary Tree Paths | Amazon, Google | DFS, Backtracking | Easy | [binary_tree_paths.cpp](binary_tree_paths.cpp) |
| 27 | Sum of Left Leaves | Amazon, Google | DFS | Easy | [sum_of_left_leaves.cpp](sum_of_left_leaves.cpp) |
| 28 | Diameter of Binary Tree | Amazon, Google | DFS | Easy | [diameter_of_binary_tree.cpp](diameter_of_binary_tree.cpp) |
| 29 | Convert Sorted Array to BST | Amazon, Google | Recursion | Easy | [convert_sorted_array_to_bst.cpp](convert_sorted_array_to_bst.cpp) |
| 30 | Convert Sorted List to BST | Amazon, Google | Recursion | Medium | [convert_sorted_list_to_bst.cpp](convert_sorted_list_to_bst.cpp) |
| 31 | Binary Tree Vertical Order Traversal | Amazon, Google | BFS, Hash Map | Medium | [binary_tree_vertical_order_traversal.cpp](binary_tree_vertical_order_traversal.cpp) |
| 32 | Binary Tree Maximum Width | Amazon, Google | BFS | Medium | [binary_tree_maximum_width.cpp](binary_tree_maximum_width.cpp) |
| 33 | House Robber III | Amazon, Google | DP on Trees | Medium | [house_robber_iii.cpp](house_robber_iii.cpp) |
| 34 | Closest Binary Search Tree Value | Amazon, Google | BST | Easy | [closest_bst_value.cpp](closest_bst_value.cpp) |
| 35 | Closest Leaf in a Binary Tree | Amazon, Google | BFS | Medium | [closest_leaf_in_binary_tree.cpp](closest_leaf_in_binary_tree.cpp) |
| 36 | Find Duplicate Subtrees | Amazon, Google | Hashing | Medium | [find_duplicate_subtrees.cpp](find_duplicate_subtrees.cpp) |
| 37 | All Nodes Distance K in Binary Tree | Amazon, Google | BFS, DFS | Medium | [all_nodes_distance_k.cpp](all_nodes_distance_k.cpp) |
| 38 | Binary Tree Cameras | Amazon, Google | DP on Trees | Hard | [binary_tree_cameras.cpp](binary_tree_cameras.cpp) |
| 39 | Smallest Subtree with all the Deepest Nodes | Amazon, Google | DFS | Medium | [smallest_subtree_with_all_deepest.cpp](smallest_subtree_with_all_deepest.cpp) |
| 40 | Maximum Binary Tree | Amazon, Google | Stack | Medium | [maximum_binary_tree.cpp](maximum_binary_tree.cpp) |
| 41 | Binary Search Tree Iterator | Amazon, Google | Stack | Medium | [bst_iterator.cpp](bst_iterator.cpp) |

## Key Patterns

### 1. **Tree Traversal**
- **DFS (Depth-First Search)**: Preorder, Inorder, Postorder
- **BFS (Breadth-First Search)**: Level order traversal

### 2. **Binary Search Tree Properties**
- Leveraging the sorted property of BSTs
- Inorder traversal gives sorted sequence

### 3. **Tree Construction**
- Building trees from traversal sequences
- Converting between different data structures

### 4. **Tree Modification**
- Inverting, flattening, connecting nodes
- Path-based operations

### 5. **Tree Analysis**
- Height, depth, balance calculations
- Path sums and tree properties

## Compilation and Testing

To compile any solution:
```bash
g++ -o solution_name solution_name.cpp
./solution_name
```

Each solution includes:
- Multiple approaches (where applicable)
- Time and space complexity analysis
- Detailed comments explaining the approach
- Test cases and examples

## Tips for Tree Problems

1. **Always consider both recursive and iterative approaches**
2. **Master the three DFS traversals**: preorder, inorder, postorder
3. **Use BFS for level-by-level operations**
4. **Leverage BST properties** when dealing with binary search trees
5. **Consider edge cases**: empty trees, single nodes, unbalanced trees
6. **Practice tree construction** from different input formats

Happy coding! 🌳
