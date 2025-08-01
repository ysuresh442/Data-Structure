/*
 * LeetCode 217: Contains Duplicate
 * 
 * Problem: Given an integer array nums, return true if any value appears at least twice 
 * in the array, and return false if every element is distinct.
 * 
 * Examples:
 * Input: nums = [1,2,3,1]
 * Output: true
 * 
 * Input: nums = [1,2,3,4]
 * Output: false
 * 
 * Input: nums = [1,1,1,3,3,4,3,2,4,2]
 * Output: true
 * 
 * Companies: Amazon, Google, Microsoft, Apple
 * Difficulty: Easy
 * Pattern: Hash Table, Hash Set
 */

#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <chrono>

class Solution {
public:
    // Approach 1: Hash Set (Optimal)
    // Time: O(n), Space: O(n)
    bool containsDuplicate(std::vector<int>& nums) {
        std::unordered_set<int> seen;
        
        for (int num : nums) {
            if (seen.find(num) != seen.end()) {
                return true;  // Found duplicate
            }
            seen.insert(num);
        }
        
        return false;
    }
    
    // Approach 2: Hash Set - Size Comparison
    // Time: O(n), Space: O(n)
    bool containsDuplicateSet(std::vector<int>& nums) {
        std::unordered_set<int> uniqueNums(nums.begin(), nums.end());
        return uniqueNums.size() != nums.size();
    }
    
    // Approach 3: Hash Map (Frequency Count)
    // Time: O(n), Space: O(n)
    bool containsDuplicateMap(std::vector<int>& nums) {
        std::unordered_map<int, int> frequency;
        
        for (int num : nums) {
            frequency[num]++;
            if (frequency[num] > 1) {
                return true;
            }
        }
        
        return false;
    }
    
    // Approach 4: Sorting
    // Time: O(n log n), Space: O(1)
    bool containsDuplicateSort(std::vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == nums[i-1]) {
                return true;
            }
        }
        
        return false;
    }
    
    // Approach 5: Brute Force (for comparison)
    // Time: O(n²), Space: O(1)
    bool containsDuplicateBrute(std::vector<int>& nums) {
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums[i] == nums[j]) {
                    return true;
                }
            }
        }
        return false;
    }
    
    // Approach 6: Early Termination with Hash Set
    // Time: O(n) average, Space: O(n)
    bool containsDuplicateOptimized(std::vector<int>& nums) {
        if (nums.size() <= 1) return false;
        
        std::unordered_set<int> seen;
        seen.reserve(nums.size()); // Pre-allocate for better performance
        
        for (const int& num : nums) {
            if (!seen.insert(num).second) {
                return true; // insert returns pair<iterator, bool>
            }
        }
        
        return false;
    }
};

/*
 * Complexity Analysis:
 * 
 * Approach 1 (Hash Set):
 * - Time: O(n) - single pass through array
 * - Space: O(n) - hash set can store up to n elements
 * 
 * Approach 2 (Hash Set Size):
 * - Time: O(n) - constructor iterates through all elements
 * - Space: O(n) - hash set stores unique elements
 * 
 * Approach 3 (Hash Map):
 * - Time: O(n) - single pass with early termination
 * - Space: O(n) - hash map stores frequencies
 * 
 * Approach 4 (Sorting):
 * - Time: O(n log n) - sorting dominates
 * - Space: O(1) - in-place sorting
 * 
 * Approach 5 (Brute Force):
 * - Time: O(n²) - nested loops
 * - Space: O(1) - no extra space
 * 
 * Hash Table Optimization Tricks:
 * 1. Use unordered_set for O(1) average lookup
 * 2. Early termination on first duplicate found
 * 3. Reserve capacity for better performance
 * 4. Use insert().second for one-operation check and insert
 * 5. Pass by reference to avoid copies
 */

// Test helper functions
void testContainsDuplicate() {
    Solution solution;
    
    // Test case 1: Contains duplicate
    std::vector<int> nums1 = {1, 2, 3, 1};
    std::cout << "Test 1 - [1,2,3,1]: " << std::boolalpha 
              << solution.containsDuplicate(nums1) << std::endl;
    
    // Test case 2: No duplicates
    std::vector<int> nums2 = {1, 2, 3, 4};
    std::cout << "Test 2 - [1,2,3,4]: " << std::boolalpha 
              << solution.containsDuplicate(nums2) << std::endl;
    
    // Test case 3: Multiple duplicates
    std::vector<int> nums3 = {1, 1, 1, 3, 3, 4, 3, 2, 4, 2};
    std::cout << "Test 3 - [1,1,1,3,3,4,3,2,4,2]: " << std::boolalpha 
              << solution.containsDuplicate(nums3) << std::endl;
    
    // Edge case: Empty array
    std::vector<int> nums4;
    std::cout << "Test 4 - []: " << std::boolalpha 
              << solution.containsDuplicate(nums4) << std::endl;
    
    // Edge case: Single element
    std::vector<int> nums5 = {1};
    std::cout << "Test 5 - [1]: " << std::boolalpha 
              << solution.containsDuplicate(nums5) << std::endl;
    
    // Edge case: Two identical elements
    std::vector<int> nums6 = {1, 1};
    std::cout << "Test 6 - [1,1]: " << std::boolalpha 
              << solution.containsDuplicate(nums6) << std::endl;
    
    // Performance comparison
    std::cout << "\nPerformance comparison:" << std::endl;
    
    // Large array with duplicate at end
    std::vector<int> largeNums(100000);
    for (int i = 0; i < 99999; i++) {
        largeNums[i] = i;
    }
    largeNums[99999] = 50000; // Duplicate near the end
    
    auto start = std::chrono::high_resolution_clock::now();
    bool hashResult = solution.containsDuplicate(largeNums);
    auto end = std::chrono::high_resolution_clock::now();
    auto hashTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    start = std::chrono::high_resolution_clock::now();
    bool sortResult = solution.containsDuplicateSort(largeNums);
    end = std::chrono::high_resolution_clock::now();
    auto sortTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Hash Set approach: " << hashTime.count() << " μs, result: " 
              << std::boolalpha << hashResult << std::endl;
    std::cout << "Sorting approach: " << sortTime.count() << " μs, result: " 
              << std::boolalpha << sortResult << std::endl;
    std::cout << "Speedup: " << (double)sortTime.count() / hashTime.count() << "x" << std::endl;
    
    // Test different approaches for correctness
    std::cout << "\nCorrectness verification:" << std::endl;
    std::vector<int> testNums = {1, 5, 3, 1};
    std::cout << "Test array: [1,5,3,1]" << std::endl;
    std::cout << "Hash Set: " << solution.containsDuplicate(testNums) << std::endl;
    std::cout << "Size comparison: " << solution.containsDuplicateSet(testNums) << std::endl;
    std::cout << "Hash Map: " << solution.containsDuplicateMap(testNums) << std::endl;
    std::cout << "Optimized: " << solution.containsDuplicateOptimized(testNums) << std::endl;
}

int main() {
    testContainsDuplicate();
    return 0;
}