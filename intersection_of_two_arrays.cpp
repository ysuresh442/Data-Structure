/*
 * LeetCode 349: Intersection of Two Arrays
 * 
 * Problem: Given two integer arrays nums1 and nums2, return an array of their intersection. 
 * Each element in the result must be unique and you may return the result in any order.
 * 
 * Examples:
 * Input: nums1 = [1,2,2,1], nums2 = [2,2]
 * Output: [2]
 * 
 * Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
 * Output: [9,4] or [4,9]
 * 
 * Companies: Amazon, Google, Microsoft
 * Difficulty: Easy
 * Pattern: Hash Table, Hash Set, Two Pointers
 */

#include <iostream>
#include <vector>
#include <unordered_set>
#include <set>
#include <algorithm>
#include <chrono>

class Solution {
public:
    // Approach 1: Hash Set (Optimal)
    // Time: O(m + n), Space: O(min(m, n))
    std::vector<int> intersection(std::vector<int>& nums1, std::vector<int>& nums2) {
        std::unordered_set<int> set1(nums1.begin(), nums1.end());
        std::unordered_set<int> result;
        
        for (int num : nums2) {
            if (set1.find(num) != set1.end()) {
                result.insert(num);
            }
        }
        
        return std::vector<int>(result.begin(), result.end());
    }
    
    // Approach 2: Optimized Hash Set (smaller set first)
    // Time: O(m + n), Space: O(min(m, n))
    std::vector<int> intersectionOptimized(std::vector<int>& nums1, std::vector<int>& nums2) {
        // Use smaller array for the set to save space
        if (nums1.size() > nums2.size()) {
            return intersectionOptimized(nums2, nums1);
        }
        
        std::unordered_set<int> set1(nums1.begin(), nums1.end());
        std::unordered_set<int> result;
        
        for (int num : nums2) {
            if (set1.count(num)) {
                result.insert(num);
            }
        }
        
        return std::vector<int>(result.begin(), result.end());
    }
    
    // Approach 3: Two Hash Sets
    // Time: O(m + n), Space: O(m + n)
    std::vector<int> intersectionTwoSets(std::vector<int>& nums1, std::vector<int>& nums2) {
        std::unordered_set<int> set1(nums1.begin(), nums1.end());
        std::unordered_set<int> set2(nums2.begin(), nums2.end());
        std::vector<int> result;
        
        for (int num : set1) {
            if (set2.count(num)) {
                result.push_back(num);
            }
        }
        
        return result;
    }
    
    // Approach 4: Sorting + Two Pointers
    // Time: O(m log m + n log n), Space: O(1) if not counting output
    std::vector<int> intersectionSorted(std::vector<int>& nums1, std::vector<int>& nums2) {
        std::sort(nums1.begin(), nums1.end());
        std::sort(nums2.begin(), nums2.end());
        
        std::vector<int> result;
        int i = 0, j = 0;
        
        while (i < nums1.size() && j < nums2.size()) {
            if (nums1[i] < nums2[j]) {
                i++;
            } else if (nums1[i] > nums2[j]) {
                j++;
            } else {
                // Found intersection
                if (result.empty() || result.back() != nums1[i]) {
                    result.push_back(nums1[i]);
                }
                i++;
                j++;
            }
        }
        
        return result;
    }
    
    // Approach 5: Using STL set_intersection
    // Time: O(m log m + n log n), Space: O(m + n)
    std::vector<int> intersectionSTL(std::vector<int>& nums1, std::vector<int>& nums2) {
        std::set<int> set1(nums1.begin(), nums1.end());
        std::set<int> set2(nums2.begin(), nums2.end());
        std::vector<int> result;
        
        std::set_intersection(set1.begin(), set1.end(),
                             set2.begin(), set2.end(),
                             std::back_inserter(result));
        
        return result;
    }
    
    // Approach 6: Binary Search
    // Time: O(m log n) or O(n log m), Space: O(min(m, n))
    std::vector<int> intersectionBinarySearch(std::vector<int>& nums1, std::vector<int>& nums2) {
        // Use smaller array for searching to optimize
        if (nums1.size() > nums2.size()) {
            return intersectionBinarySearch(nums2, nums1);
        }
        
        std::sort(nums2.begin(), nums2.end());
        std::unordered_set<int> result;
        
        for (int num : nums1) {
            if (std::binary_search(nums2.begin(), nums2.end(), num)) {
                result.insert(num);
            }
        }
        
        return std::vector<int>(result.begin(), result.end());
    }
};

/*
 * Complexity Analysis:
 * 
 * Approach 1 (Hash Set):
 * - Time: O(m + n) where m, n are array sizes
 * - Space: O(min(m, n)) for the smaller set
 * 
 * Approach 2 (Optimized Hash Set):
 * - Time: O(m + n) - same as approach 1
 * - Space: O(min(m, n)) - guaranteed to use smaller array
 * 
 * Approach 3 (Two Hash Sets):
 * - Time: O(m + n) - convert both to sets
 * - Space: O(m + n) - both sets stored
 * 
 * Approach 4 (Sorting + Two Pointers):
 * - Time: O(m log m + n log n) - sorting dominates
 * - Space: O(1) not counting output space
 * 
 * Approach 5 (STL set_intersection):
 * - Time: O(m log m + n log n) - set creation
 * - Space: O(m + n) - both sets
 * 
 * Approach 6 (Binary Search):
 * - Time: O(m log n) or O(n log m) - search in sorted array
 * - Space: O(min(m, n)) - result set
 * 
 * Hash Table Optimization Tricks:
 * 1. Always use the smaller array for the hash set
 * 2. Use unordered_set for O(1) average lookup
 * 3. Insert directly into result set to avoid duplicates
 * 4. Consider sorting when arrays are already sorted or small
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

void testIntersection() {
    Solution solution;
    
    // Test case 1
    std::vector<int> nums1_1 = {1, 2, 2, 1};
    std::vector<int> nums2_1 = {2, 2};
    auto result1 = solution.intersection(nums1_1, nums2_1);
    std::cout << "Test 1 - ";
    printVector(nums1_1);
    std::cout << " ∩ ";
    printVector(nums2_1);
    std::cout << " = ";
    printVector(result1);
    std::cout << std::endl;
    
    // Test case 2
    std::vector<int> nums1_2 = {4, 9, 5};
    std::vector<int> nums2_2 = {9, 4, 9, 8, 4};
    auto result2 = solution.intersection(nums1_2, nums2_2);
    std::cout << "Test 2 - ";
    printVector(nums1_2);
    std::cout << " ∩ ";
    printVector(nums2_2);
    std::cout << " = ";
    printVector(result2);
    std::cout << std::endl;
    
    // Edge case: No intersection
    std::vector<int> nums1_3 = {1, 2, 3};
    std::vector<int> nums2_3 = {4, 5, 6};
    auto result3 = solution.intersection(nums1_3, nums2_3);
    std::cout << "Test 3 - ";
    printVector(nums1_3);
    std::cout << " ∩ ";
    printVector(nums2_3);
    std::cout << " = ";
    printVector(result3);
    std::cout << std::endl;
    
    // Edge case: Empty arrays
    std::vector<int> nums1_4 = {};
    std::vector<int> nums2_4 = {1, 2, 3};
    auto result4 = solution.intersection(nums1_4, nums2_4);
    std::cout << "Test 4 - ";
    printVector(nums1_4);
    std::cout << " ∩ ";
    printVector(nums2_4);
    std::cout << " = ";
    printVector(result4);
    std::cout << std::endl;
    
    // Performance comparison
    std::cout << "\nPerformance comparison:" << std::endl;
    
    // Large arrays
    std::vector<int> large1(10000);
    std::vector<int> large2(10000);
    for (int i = 0; i < 10000; i++) {
        large1[i] = i;
        large2[i] = i + 5000; // Half overlap
    }
    
    auto start = std::chrono::high_resolution_clock::now();
    auto hashResult = solution.intersection(large1, large2);
    auto end = std::chrono::high_resolution_clock::now();
    auto hashTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    start = std::chrono::high_resolution_clock::now();
    auto sortedResult = solution.intersectionSorted(large1, large2);
    end = std::chrono::high_resolution_clock::now();
    auto sortedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Hash Set approach: " << hashTime.count() << " μs, result size: " 
              << hashResult.size() << std::endl;
    std::cout << "Sorted approach: " << sortedTime.count() << " μs, result size: " 
              << sortedResult.size() << std::endl;
    std::cout << "Speedup: " << (double)sortedTime.count() / hashTime.count() << "x" << std::endl;
    
    // Correctness verification
    std::cout << "\nCorrectness verification:" << std::endl;
    std::vector<int> test1 = {1, 2, 2, 1};
    std::vector<int> test2 = {2, 2};
    std::cout << "Test arrays: ";
    printVector(test1);
    std::cout << " and ";
    printVector(test2);
    std::cout << std::endl;
    
    auto hash_res = solution.intersection(test1, test2);
    auto opt_res = solution.intersectionOptimized(test1, test2);
    auto two_res = solution.intersectionTwoSets(test1, test2);
    auto sort_res = solution.intersectionSorted(test1, test2);
    auto stl_res = solution.intersectionSTL(test1, test2);
    auto bin_res = solution.intersectionBinarySearch(test1, test2);
    
    std::cout << "Hash Set: "; printVector(hash_res); std::cout << std::endl;
    std::cout << "Optimized: "; printVector(opt_res); std::cout << std::endl;
    std::cout << "Two Sets: "; printVector(two_res); std::cout << std::endl;
    std::cout << "Sorted: "; printVector(sort_res); std::cout << std::endl;
    std::cout << "STL: "; printVector(stl_res); std::cout << std::endl;
    std::cout << "Binary Search: "; printVector(bin_res); std::cout << std::endl;
}

int main() {
    testIntersection();
    return 0;
}