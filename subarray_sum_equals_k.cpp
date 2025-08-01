/*
 * LeetCode 560: Subarray Sum Equals K
 * 
 * Problem: Given an array of integers nums and an integer k, return the total number of 
 * continuous subarrays whose sum is equal to k.
 * 
 * Examples:
 * Input: nums = [1,1,1], k = 2
 * Output: 2
 * 
 * Input: nums = [1,2,3], k = 3
 * Output: 2
 * 
 * Companies: Amazon, Google, Facebook
 * Difficulty: Medium
 * Pattern: Hash Map, Prefix Sum
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <chrono>

class Solution {
public:
    // Approach 1: Hash Map with Prefix Sum (Optimal)
    // Time: O(n), Space: O(n)
    int subarraySum(std::vector<int>& nums, int k) {
        std::unordered_map<int, int> prefixSumCount;
        prefixSumCount[0] = 1; // Empty prefix has sum 0
        
        int count = 0;
        int prefixSum = 0;
        
        for (int num : nums) {
            prefixSum += num;
            
            // Check if there exists a prefix with sum (prefixSum - k)
            if (prefixSumCount.find(prefixSum - k) != prefixSumCount.end()) {
                count += prefixSumCount[prefixSum - k];
            }
            
            // Add current prefix sum to map
            prefixSumCount[prefixSum]++;
        }
        
        return count;
    }
    
    // Approach 2: Brute Force (for comparison)
    // Time: O(n²), Space: O(1)
    int subarraySumBrute(std::vector<int>& nums, int k) {
        int count = 0;
        
        for (int i = 0; i < nums.size(); i++) {
            int sum = 0;
            for (int j = i; j < nums.size(); j++) {
                sum += nums[j];
                if (sum == k) {
                    count++;
                }
            }
        }
        
        return count;
    }
    
    // Approach 3: Optimized Brute Force with early termination
    // Time: O(n²) worst case, Space: O(1)
    int subarraySumOptimizedBrute(std::vector<int>& nums, int k) {
        int count = 0;
        
        for (int i = 0; i < nums.size(); i++) {
            int sum = 0;
            for (int j = i; j < nums.size(); j++) {
                sum += nums[j];
                if (sum == k) {
                    count++;
                } else if (sum > k && nums[j] > 0) {
                    // Early termination for positive numbers
                    break;
                }
            }
        }
        
        return count;
    }
    
    // Approach 4: Using cumulative sum array
    // Time: O(n²), Space: O(n)
    int subarraySumCumulative(std::vector<int>& nums, int k) {
        std::vector<int> cumSum(nums.size() + 1, 0);
        
        // Build cumulative sum array
        for (int i = 0; i < nums.size(); i++) {
            cumSum[i + 1] = cumSum[i] + nums[i];
        }
        
        int count = 0;
        
        // Check all possible subarrays
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i; j < nums.size(); j++) {
                if (cumSum[j + 1] - cumSum[i] == k) {
                    count++;
                }
            }
        }
        
        return count;
    }
    
    // Approach 5: Hash Map with running count optimization
    // Time: O(n), Space: O(n)
    int subarraySumOptimized(std::vector<int>& nums, int k) {
        std::unordered_map<int, int> prefixSumCount;
        prefixSumCount.reserve(nums.size()); // Pre-allocate for performance
        
        int count = 0;
        int prefixSum = 0;
        
        for (int num : nums) {
            // Check before adding current element
            if (prefixSum == k) count++;
            
            prefixSum += num;
            
            // Check if (prefixSum - k) exists
            auto it = prefixSumCount.find(prefixSum - k);
            if (it != prefixSumCount.end()) {
                count += it->second;
            }
            
            // Update count for current prefix sum
            prefixSumCount[prefixSum]++;
        }
        
        return count;
    }
    
    // Approach 6: Two-pass solution for better cache locality
    // Time: O(n), Space: O(n)
    int subarraySumTwoPass(std::vector<int>& nums, int k) {
        // First pass: calculate all prefix sums
        std::vector<int> prefixSums(nums.size() + 1, 0);
        for (int i = 0; i < nums.size(); i++) {
            prefixSums[i + 1] = prefixSums[i] + nums[i];
        }
        
        // Second pass: count subarrays using hash map
        std::unordered_map<int, int> sumCount;
        int count = 0;
        
        for (int sum : prefixSums) {
            if (sumCount.count(sum - k)) {
                count += sumCount[sum - k];
            }
            sumCount[sum]++;
        }
        
        return count;
    }
};

/*
 * Complexity Analysis:
 * 
 * Approach 1 (Hash Map + Prefix Sum):
 * - Time: O(n) - single pass through array
 * - Space: O(n) - hash map for prefix sums
 * 
 * Approach 2 (Brute Force):
 * - Time: O(n²) - nested loops
 * - Space: O(1) - no extra space
 * 
 * Approach 3 (Optimized Brute Force):
 * - Time: O(n²) worst case, better average for positive numbers
 * - Space: O(1) - no extra space
 * 
 * Approach 4 (Cumulative Sum):
 * - Time: O(n²) - build cumSum + nested loops
 * - Space: O(n) - cumulative sum array
 * 
 * Hash Table Optimization Tricks:
 * 1. Use prefix sum to convert problem to "two sum" variant
 * 2. Hash map stores frequency of each prefix sum
 * 3. Key insight: sum[i,j] = prefixSum[j] - prefixSum[i-1]
 * 4. Pre-allocate hash map capacity for better performance
 * 5. Consider early termination for positive-only arrays
 * 
 * Mathematical Insight:
 * - If prefixSum[j] - prefixSum[i] = k, then subarray [i+1, j] has sum k
 * - We need to count how many times (prefixSum - k) has appeared before
 * - Initialize with prefixSum[0] = 0 (empty prefix)
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

void testSubarraySum() {
    Solution solution;
    
    // Test case 1
    std::vector<int> nums1 = {1, 1, 1};
    int k1 = 2;
    std::cout << "Test 1 - nums: ";
    printVector(nums1);
    std::cout << ", k: " << k1 << " -> " << solution.subarraySum(nums1, k1) 
              << " (expected: 2)" << std::endl;
    
    // Test case 2
    std::vector<int> nums2 = {1, 2, 3};
    int k2 = 3;
    std::cout << "Test 2 - nums: ";
    printVector(nums2);
    std::cout << ", k: " << k2 << " -> " << solution.subarraySum(nums2, k2) 
              << " (expected: 2)" << std::endl;
    
    // Test case 3: Negative numbers
    std::vector<int> nums3 = {1, -1, 0};
    int k3 = 0;
    std::cout << "Test 3 - nums: ";
    printVector(nums3);
    std::cout << ", k: " << k3 << " -> " << solution.subarraySum(nums3, k3) 
              << " (expected: 3)" << std::endl;
    
    // Test case 4: Single element
    std::vector<int> nums4 = {5};
    int k4 = 5;
    std::cout << "Test 4 - nums: ";
    printVector(nums4);
    std::cout << ", k: " << k4 << " -> " << solution.subarraySum(nums4, k4) 
              << " (expected: 1)" << std::endl;
    
    // Test case 5: No valid subarray
    std::vector<int> nums5 = {1, 2, 3};
    int k5 = 7;
    std::cout << "Test 5 - nums: ";
    printVector(nums5);
    std::cout << ", k: " << k5 << " -> " << solution.subarraySum(nums5, k5) 
              << " (expected: 0)" << std::endl;
    
    // Test case 6: Complex case with duplicates
    std::vector<int> nums6 = {3, 4, 7, 2, -3, 1, 4, 2};
    int k6 = 7;
    std::cout << "Test 6 - nums: ";
    printVector(nums6);
    std::cout << ", k: " << k6 << " -> " << solution.subarraySum(nums6, k6) 
              << " (expected: 4)" << std::endl;
    
    // Performance comparison
    std::cout << "\nPerformance comparison:" << std::endl;
    
    // Large array
    std::vector<int> largeNums(10000);
    for (int i = 0; i < 10000; i++) {
        largeNums[i] = (i % 21) - 10; // Numbers from -10 to 10
    }
    int largeK = 0;
    
    auto start = std::chrono::high_resolution_clock::now();
    int hashMapResult = solution.subarraySum(largeNums, largeK);
    auto end = std::chrono::high_resolution_clock::now();
    auto hashMapTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    start = std::chrono::high_resolution_clock::now();
    int bruteResult = solution.subarraySumBrute(largeNums, largeK);
    end = std::chrono::high_resolution_clock::now();
    auto bruteTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    start = std::chrono::high_resolution_clock::now();
    int optimizedResult = solution.subarraySumOptimized(largeNums, largeK);
    end = std::chrono::high_resolution_clock::now();
    auto optimizedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Hash Map approach: " << hashMapTime.count() << " μs, result: " 
              << hashMapResult << std::endl;
    std::cout << "Brute Force approach: " << bruteTime.count() << " μs, result: " 
              << bruteResult << std::endl;
    std::cout << "Optimized approach: " << optimizedTime.count() << " μs, result: " 
              << optimizedResult << std::endl;
    std::cout << "Speedup: " << (double)bruteTime.count() / hashMapTime.count() << "x" << std::endl;
    
    // Detailed example walkthrough
    std::cout << "\nDetailed walkthrough for [1, -1, 0], k=0:" << std::endl;
    std::vector<int> walkthrough = {1, -1, 0};
    std::unordered_map<int, int> prefixSumCount;
    prefixSumCount[0] = 1;
    
    int count = 0, prefixSum = 0;
    for (int i = 0; i < walkthrough.size(); i++) {
        prefixSum += walkthrough[i];
        std::cout << "i=" << i << ", num=" << walkthrough[i] 
                  << ", prefixSum=" << prefixSum 
                  << ", looking for: " << (prefixSum - 0);
        
        if (prefixSumCount.count(prefixSum - 0)) {
            count += prefixSumCount[prefixSum - 0];
            std::cout << ", found " << prefixSumCount[prefixSum - 0] << " times";
        }
        
        prefixSumCount[prefixSum]++;
        std::cout << ", count=" << count << std::endl;
    }
    
    // Correctness verification
    std::cout << "\nCorrectness verification:" << std::endl;
    std::vector<int> testNums = {-1, -1, 1};
    int testK = 0;
    std::cout << "Test array: ";
    printVector(testNums);
    std::cout << ", k=" << testK << std::endl;
    
    std::cout << "Hash Map: " << solution.subarraySum(testNums, testK) << std::endl;
    std::cout << "Brute Force: " << solution.subarraySumBrute(testNums, testK) << std::endl;
    std::cout << "Cumulative: " << solution.subarraySumCumulative(testNums, testK) << std::endl;
    std::cout << "Optimized: " << solution.subarraySumOptimized(testNums, testK) << std::endl;
    std::cout << "Two Pass: " << solution.subarraySumTwoPass(testNums, testK) << std::endl;
}

int main() {
    testSubarraySum();
    return 0;
}