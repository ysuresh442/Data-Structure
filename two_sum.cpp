/*
 * LeetCode 1: Two Sum
 * 
 * Problem: Given an array of integers nums and an integer target, return indices of the 
 * two numbers such that they add up to target. You may assume that each input would have 
 * exactly one solution, and you may not use the same element twice.
 * 
 * Examples:
 * Input: nums = [2,7,11,15], target = 9
 * Output: [0,1]
 * 
 * Input: nums = [3,2,4], target = 6
 * Output: [1,2]
 * 
 * Input: nums = [3,3], target = 6
 * Output: [0,1]
 * 
 * Companies: Amazon, Google, Facebook, Microsoft, Apple, Netflix
 * Difficulty: Easy
 * Pattern: Hash Table
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <chrono>

class Solution {
public:
    // Approach 1: Hash Table - One Pass
    // Time: O(n), Space: O(n)
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        std::unordered_map<int, int> numToIndex;
        
        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            
            // Check if complement exists in hash table
            if (numToIndex.find(complement) != numToIndex.end()) {
                return {numToIndex[complement], i};
            }
            
            // Store current number and its index
            numToIndex[nums[i]] = i;
        }
        
        return {}; // Should never reach here given problem constraints
    }
    
    // Approach 2: Hash Table - Two Pass
    // Time: O(n), Space: O(n)
    std::vector<int> twoSumTwoPass(std::vector<int>& nums, int target) {
        std::unordered_map<int, int> numToIndex;
        
        // First pass: store all numbers and their indices
        for (int i = 0; i < nums.size(); i++) {
            numToIndex[nums[i]] = i;
        }
        
        // Second pass: find complement
        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            if (numToIndex.find(complement) != numToIndex.end() && 
                numToIndex[complement] != i) {
                return {i, numToIndex[complement]};
            }
        }
        
        return {};
    }
    
    // Approach 3: Brute Force (for comparison)
    // Time: O(n²), Space: O(1)
    std::vector<int> twoSumBruteForce(std::vector<int>& nums, int target) {
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums[i] + nums[j] == target) {
                    return {i, j};
                }
            }
        }
        return {};
    }
    
    // Approach 4: Sorting + Two Pointers (modified for indices)
    // Time: O(n log n), Space: O(n)
    std::vector<int> twoSumSorted(std::vector<int>& nums, int target) {
        std::vector<std::pair<int, int>> indexedNums;
        for (int i = 0; i < nums.size(); i++) {
            indexedNums.push_back({nums[i], i});
        }
        
        std::sort(indexedNums.begin(), indexedNums.end());
        
        int left = 0, right = indexedNums.size() - 1;
        while (left < right) {
            int sum = indexedNums[left].first + indexedNums[right].first;
            if (sum == target) {
                return {indexedNums[left].second, indexedNums[right].second};
            } else if (sum < target) {
                left++;
            } else {
                right--;
            }
        }
        
        return {};
    }
};

/*
 * Complexity Analysis:
 * 
 * Approach 1 (Hash Table - One Pass):
 * - Time: O(n) - single pass through array
 * - Space: O(n) - hash table can store up to n elements
 * 
 * Approach 2 (Hash Table - Two Pass):
 * - Time: O(n) - two passes through array
 * - Space: O(n) - hash table stores all elements
 * 
 * Approach 3 (Brute Force):
 * - Time: O(n²) - nested loops
 * - Space: O(1) - no extra space
 * 
 * Approach 4 (Sorting + Two Pointers):
 * - Time: O(n log n) - sorting dominates
 * - Space: O(n) - for indexed pairs
 * 
 * Hash Table Optimization Tricks:
 * 1. One-pass approach is optimal - check for complement before inserting
 * 2. Use unordered_map for O(1) average lookup time
 * 3. Handle duplicates correctly by checking index
 * 4. Early termination when solution found
 */

// Test helper functions
void printVector(const std::vector<int>& vec) {
    std::cout << "[";
    for (int i = 0; i < vec.size(); i++) {
        std::cout << vec[i];
        if (i < vec.size() - 1) std::cout << ", ";
    }
    std::cout << "]";
}

void testTwoSum() {
    Solution solution;
    
    // Test case 1
    std::vector<int> nums1 = {2, 7, 11, 15};
    int target1 = 9;
    auto result1 = solution.twoSum(nums1, target1);
    std::cout << "Test 1 - nums: ";
    printVector(nums1);
    std::cout << ", target: " << target1 << " -> ";
    printVector(result1);
    std::cout << std::endl;
    
    // Test case 2
    std::vector<int> nums2 = {3, 2, 4};
    int target2 = 6;
    auto result2 = solution.twoSum(nums2, target2);
    std::cout << "Test 2 - nums: ";
    printVector(nums2);
    std::cout << ", target: " << target2 << " -> ";
    printVector(result2);
    std::cout << std::endl;
    
    // Test case 3
    std::vector<int> nums3 = {3, 3};
    int target3 = 6;
    auto result3 = solution.twoSum(nums3, target3);
    std::cout << "Test 3 - nums: ";
    printVector(nums3);
    std::cout << ", target: " << target3 << " -> ";
    printVector(result3);
    std::cout << std::endl;
    
    // Edge case: negative numbers
    std::vector<int> nums4 = {-1, -2, -3, -4, -5};
    int target4 = -8;
    auto result4 = solution.twoSum(nums4, target4);
    std::cout << "Test 4 - nums: ";
    printVector(nums4);
    std::cout << ", target: " << target4 << " -> ";
    printVector(result4);
    std::cout << std::endl;
    
    // Performance comparison
    std::cout << "\nPerformance comparison for large array:" << std::endl;
    std::vector<int> largeNums(10000);
    for (int i = 0; i < 10000; i++) {
        largeNums[i] = i;
    }
    int largeTarget = 19999;
    
    auto start = std::chrono::high_resolution_clock::now();
    auto hashResult = solution.twoSum(largeNums, largeTarget);
    auto end = std::chrono::high_resolution_clock::now();
    auto hashTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    start = std::chrono::high_resolution_clock::now();
    auto bruteResult = solution.twoSumBruteForce(largeNums, largeTarget);
    end = std::chrono::high_resolution_clock::now();
    auto bruteTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Hash Table approach: " << hashTime.count() << " μs" << std::endl;
    std::cout << "Brute Force approach: " << bruteTime.count() << " μs" << std::endl;
    std::cout << "Speedup: " << (double)bruteTime.count() / hashTime.count() << "x" << std::endl;
}

int main() {
    testTwoSum();
    return 0;
}