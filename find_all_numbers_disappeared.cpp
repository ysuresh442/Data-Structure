/*
 * LeetCode 448: Find All Numbers Disappeared in an Array
 * 
 * Problem: Given an array nums of n integers where nums[i] is in the range [1, n], 
 * return an array of all the integers in the range [1, n] that do not appear in nums.
 * 
 * Examples:
 * Input: nums = [4,3,2,7,8,2,3,1]
 * Output: [5,6]
 * 
 * Input: nums = [1,1]
 * Output: [2]
 * 
 * Companies: Amazon, Google
 * Difficulty: Easy
 * Pattern: Hash Set, Array Marking
 */

#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <chrono>

class Solution {
public:
    // Approach 1: Hash Set
    // Time: O(n), Space: O(n)
    std::vector<int> findDisappearedNumbers(std::vector<int>& nums) {
        std::unordered_set<int> numSet(nums.begin(), nums.end());
        std::vector<int> result;
        
        for (int i = 1; i <= nums.size(); i++) {
            if (numSet.find(i) == numSet.end()) {
                result.push_back(i);
            }
        }
        
        return result;
    }
    
    // Approach 2: Array marking (optimal space)
    // Time: O(n), Space: O(1) - not counting output
    std::vector<int> findDisappearedNumbersMarking(std::vector<int>& nums) {
        // Mark numbers as seen by negating values at corresponding indices
        for (int i = 0; i < nums.size(); i++) {
            int index = std::abs(nums[i]) - 1; // Convert to 0-based index
            if (nums[index] > 0) {
                nums[index] = -nums[index];
            }
        }
        
        std::vector<int> result;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] > 0) {
                result.push_back(i + 1);
            }
        }
        
        // Restore original array
        for (int i = 0; i < nums.size(); i++) {
            nums[i] = std::abs(nums[i]);
        }
        
        return result;
    }
    
    // Approach 3: Boolean array
    // Time: O(n), Space: O(n)
    std::vector<int> findDisappearedNumbersBool(std::vector<int>& nums) {
        std::vector<bool> seen(nums.size() + 1, false);
        
        for (int num : nums) {
            seen[num] = true;
        }
        
        std::vector<int> result;
        for (int i = 1; i <= nums.size(); i++) {
            if (!seen[i]) {
                result.push_back(i);
            }
        }
        
        return result;
    }
    
    // Approach 4: Cyclic sort approach
    // Time: O(n), Space: O(1)
    std::vector<int> findDisappearedNumbersCyclic(std::vector<int>& nums) {
        int i = 0;
        while (i < nums.size()) {
            int correctIndex = nums[i] - 1;
            if (nums[i] != nums[correctIndex]) {
                std::swap(nums[i], nums[correctIndex]);
            } else {
                i++;
            }
        }
        
        std::vector<int> result;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != i + 1) {
                result.push_back(i + 1);
            }
        }
        
        return result;
    }
    
    // Approach 5: Adding n to mark presence
    // Time: O(n), Space: O(1)
    std::vector<int> findDisappearedNumbersAddN(std::vector<int>& nums) {
        int n = nums.size();
        
        // Add n to mark presence
        for (int i = 0; i < n; i++) {
            int index = (nums[i] - 1) % n;
            nums[index] += n;
        }
        
        std::vector<int> result;
        for (int i = 0; i < n; i++) {
            if (nums[i] <= n) {
                result.push_back(i + 1);
            }
        }
        
        // Restore original array
        for (int i = 0; i < n; i++) {
            nums[i] = (nums[i] - 1) % n + 1;
        }
        
        return result;
    }
};

/*
 * Complexity Analysis:
 * 
 * Approach 1 (Hash Set):
 * - Time: O(n) - set creation + linear scan
 * - Space: O(n) - hash set storage
 * 
 * Approach 2 (Array Marking):
 * - Time: O(n) - two passes through array
 * - Space: O(1) - in-place marking using sign
 * 
 * Approach 3 (Boolean Array):
 * - Time: O(n) - mark presence + find missing
 * - Space: O(n) - boolean array
 * 
 * Approach 4 (Cyclic Sort):
 * - Time: O(n) - each element moved at most once
 * - Space: O(1) - in-place sorting
 * 
 * Approach 5 (Add N):
 * - Time: O(n) - mark by adding n, check by comparing
 * - Space: O(1) - in-place using modulo arithmetic
 * 
 * Hash Table Optimization Tricks:
 * 1. Use unordered_set for O(1) average lookup
 * 2. In-place marking avoids extra space
 * 3. Cyclic sort naturally places elements in correct positions
 * 4. Mathematical properties (sign, modulo) for marking
 * 5. Consider problem constraints for optimization opportunities
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

void testFindDisappearedNumbers() {
    Solution solution;
    
    // Test case 1
    std::vector<int> nums1 = {4, 3, 2, 7, 8, 2, 3, 1};
    auto result1 = solution.findDisappearedNumbers(nums1);
    std::cout << "Test 1 - nums: ";
    printVector(nums1);
    std::cout << " -> ";
    printVector(result1);
    std::cout << " (expected: [5,6])" << std::endl;
    
    // Test case 2
    std::vector<int> nums2 = {1, 1};
    auto result2 = solution.findDisappearedNumbers(nums2);
    std::cout << "Test 2 - nums: ";
    printVector(nums2);
    std::cout << " -> ";
    printVector(result2);
    std::cout << " (expected: [2])" << std::endl;
    
    // Edge case: All numbers present
    std::vector<int> nums3 = {1, 2, 3, 4, 5};
    auto result3 = solution.findDisappearedNumbers(nums3);
    std::cout << "Test 3 - nums: ";
    printVector(nums3);
    std::cout << " -> ";
    printVector(result3);
    std::cout << " (expected: [])" << std::endl;
    
    // Edge case: Single element
    std::vector<int> nums4 = {1};
    auto result4 = solution.findDisappearedNumbers(nums4);
    std::cout << "Test 4 - nums: ";
    printVector(nums4);
    std::cout << " -> ";
    printVector(result4);
    std::cout << " (expected: [])" << std::endl;
    
    // Performance comparison
    std::cout << "\nPerformance comparison:" << std::endl;
    
    // Large array
    std::vector<int> largeNums(100000);
    for (int i = 0; i < 100000; i++) {
        largeNums[i] = (i % 50000) + 1; // Missing second half
    }
    
    auto start = std::chrono::high_resolution_clock::now();
    auto hashResult = solution.findDisappearedNumbers(largeNums);
    auto end = std::chrono::high_resolution_clock::now();
    auto hashTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    start = std::chrono::high_resolution_clock::now();
    auto markingResult = solution.findDisappearedNumbersMarking(largeNums);
    end = std::chrono::high_resolution_clock::now();
    auto markingTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    start = std::chrono::high_resolution_clock::now();
    auto cyclicResult = solution.findDisappearedNumbersCyclic(largeNums);
    end = std::chrono::high_resolution_clock::now();
    auto cyclicTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Hash Set approach: " << hashTime.count() << " μs, result size: " 
              << hashResult.size() << std::endl;
    std::cout << "Array Marking: " << markingTime.count() << " μs, result size: " 
              << markingResult.size() << std::endl;
    std::cout << "Cyclic Sort: " << cyclicTime.count() << " μs, result size: " 
              << cyclicResult.size() << std::endl;
    
    // Correctness verification
    std::cout << "\nCorrectness verification:" << std::endl;
    std::vector<int> testNums = {1, 3, 5, 3, 1};
    std::cout << "Test array: ";
    printVector(testNums);
    std::cout << std::endl;
    
    auto hash_res = solution.findDisappearedNumbers(testNums);
    auto bool_res = solution.findDisappearedNumbersBool(testNums);
    auto marking_res = solution.findDisappearedNumbersMarking(testNums);
    auto cyclic_res = solution.findDisappearedNumbersCyclic(testNums);
    auto addN_res = solution.findDisappearedNumbersAddN(testNums);
    
    std::cout << "Hash Set: "; printVector(hash_res); std::cout << std::endl;
    std::cout << "Boolean Array: "; printVector(bool_res); std::cout << std::endl;
    std::cout << "Array Marking: "; printVector(marking_res); std::cout << std::endl;
    std::cout << "Cyclic Sort: "; printVector(cyclic_res); std::cout << std::endl;
    std::cout << "Add N: "; printVector(addN_res); std::cout << std::endl;
}

int main() {
    testFindDisappearedNumbers();
    return 0;
}