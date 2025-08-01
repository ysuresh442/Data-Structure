/*
 * LeetCode 347: Top K Frequent Elements
 * 
 * Problem: Given an integer array nums and an integer k, return the k most frequent elements. 
 * You may return the answer in any order.
 * 
 * Examples:
 * Input: nums = [1,1,1,2,2,3], k = 2
 * Output: [1,2]
 * 
 * Input: nums = [1], k = 1
 * Output: [1]
 * 
 * Companies: Amazon, Google, Facebook, Microsoft
 * Difficulty: Medium
 * Pattern: Hash Table + Heap, Bucket Sort, Quick Select
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <chrono>

class Solution {
public:
    // Approach 1: Hash Map + Min Heap
    // Time: O(n log k), Space: O(n + k)
    std::vector<int> topKFrequent(std::vector<int>& nums, int k) {
        // Count frequencies
        std::unordered_map<int, int> freq;
        for (int num : nums) {
            freq[num]++;
        }
        
        // Min heap to keep top k elements
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, 
                           std::greater<std::pair<int, int>>> minHeap;
        
        for (const auto& p : freq) {
            minHeap.push({p.second, p.first});
            if (minHeap.size() > k) {
                minHeap.pop();
            }
        }
        
        std::vector<int> result;
        while (!minHeap.empty()) {
            result.push_back(minHeap.top().second);
            minHeap.pop();
        }
        
        return result;
    }
    
    // Approach 2: Hash Map + Max Heap
    // Time: O(n log n), Space: O(n)
    std::vector<int> topKFrequentMaxHeap(std::vector<int>& nums, int k) {
        std::unordered_map<int, int> freq;
        for (int num : nums) {
            freq[num]++;
        }
        
        // Max heap based on frequency
        std::priority_queue<std::pair<int, int>> maxHeap;
        for (const auto& p : freq) {
            maxHeap.push({p.second, p.first});
        }
        
        std::vector<int> result;
        for (int i = 0; i < k; i++) {
            result.push_back(maxHeap.top().second);
            maxHeap.pop();
        }
        
        return result;
    }
    
    // Approach 3: Bucket Sort
    // Time: O(n), Space: O(n)
    std::vector<int> topKFrequentBucket(std::vector<int>& nums, int k) {
        std::unordered_map<int, int> freq;
        for (int num : nums) {
            freq[num]++;
        }
        
        // Bucket sort by frequency
        std::vector<std::vector<int>> buckets(nums.size() + 1);
        for (const auto& p : freq) {
            buckets[p.second].push_back(p.first);
        }
        
        std::vector<int> result;
        for (int i = buckets.size() - 1; i >= 0 && result.size() < k; i--) {
            for (int num : buckets[i]) {
                result.push_back(num);
                if (result.size() == k) break;
            }
        }
        
        return result;
    }
    
    // Approach 4: Quick Select Algorithm
    // Time: O(n) average, O(n²) worst case, Space: O(n)
    std::vector<int> topKFrequentQuickSelect(std::vector<int>& nums, int k) {
        std::unordered_map<int, int> freq;
        for (int num : nums) {
            freq[num]++;
        }
        
        std::vector<std::pair<int, int>> freqPairs;
        for (const auto& p : freq) {
            freqPairs.push_back({p.second, p.first});
        }
        
        int n = freqPairs.size();
        quickSelect(freqPairs, 0, n - 1, n - k);
        
        std::vector<int> result;
        for (int i = n - k; i < n; i++) {
            result.push_back(freqPairs[i].second);
        }
        
        return result;
    }
    
    // Approach 5: STL nth_element
    // Time: O(n) average, Space: O(n)
    std::vector<int> topKFrequentSTL(std::vector<int>& nums, int k) {
        std::unordered_map<int, int> freq;
        for (int num : nums) {
            freq[num]++;
        }
        
        std::vector<std::pair<int, int>> freqPairs;
        for (const auto& p : freq) {
            freqPairs.push_back({p.second, p.first});
        }
        
        std::nth_element(freqPairs.begin(), 
                        freqPairs.begin() + freqPairs.size() - k,
                        freqPairs.end());
        
        std::vector<int> result;
        for (int i = freqPairs.size() - k; i < freqPairs.size(); i++) {
            result.push_back(freqPairs[i].second);
        }
        
        return result;
    }
    
    // Approach 6: Optimized for small k
    // Time: O(n + k log k), Space: O(n)
    std::vector<int> topKFrequentOptimized(std::vector<int>& nums, int k) {
        if (k == nums.size()) {
            std::unordered_set<int> unique(nums.begin(), nums.end());
            return std::vector<int>(unique.begin(), unique.end());
        }
        
        std::unordered_map<int, int> freq;
        for (int num : nums) {
            freq[num]++;
        }
        
        if (k == 1) {
            int maxFreq = 0, result = 0;
            for (const auto& p : freq) {
                if (p.second > maxFreq) {
                    maxFreq = p.second;
                    result = p.first;
                }
            }
            return {result};
        }
        
        // Use min heap for small k
        return topKFrequent(nums, k);
    }

private:
    void quickSelect(std::vector<std::pair<int, int>>& freqPairs, int left, int right, int k) {
        if (left >= right) return;
        
        int pivot = partition(freqPairs, left, right);
        
        if (pivot == k) {
            return;
        } else if (pivot < k) {
            quickSelect(freqPairs, pivot + 1, right, k);
        } else {
            quickSelect(freqPairs, left, pivot - 1, k);
        }
    }
    
    int partition(std::vector<std::pair<int, int>>& freqPairs, int left, int right) {
        int pivotFreq = freqPairs[right].first;
        int i = left;
        
        for (int j = left; j < right; j++) {
            if (freqPairs[j].first < pivotFreq) {
                std::swap(freqPairs[i], freqPairs[j]);
                i++;
            }
        }
        
        std::swap(freqPairs[i], freqPairs[right]);
        return i;
    }
};

/*
 * Complexity Analysis:
 * 
 * Approach 1 (Hash Map + Min Heap):
 * - Time: O(n log k) - n elements, maintain heap of size k
 * - Space: O(n + k) - hash map + heap
 * 
 * Approach 2 (Hash Map + Max Heap):
 * - Time: O(n log n) - all elements in heap
 * - Space: O(n) - hash map + heap
 * 
 * Approach 3 (Bucket Sort):
 * - Time: O(n) - linear scan and bucket fill
 * - Space: O(n) - buckets array
 * 
 * Approach 4 (Quick Select):
 * - Time: O(n) average, O(n²) worst - partition algorithm
 * - Space: O(n) - frequency pairs
 * 
 * Approach 5 (STL nth_element):
 * - Time: O(n) average - optimized quick select
 * - Space: O(n) - frequency pairs
 * 
 * Hash Table Optimization Tricks:
 * 1. Use min heap of size k to avoid sorting all elements
 * 2. Bucket sort is optimal when frequency range is small
 * 3. Quick select avoids full sorting
 * 4. Early termination for edge cases (k=1, k=n)
 * 5. Consider input size when choosing algorithm
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

void testTopKFrequent() {
    Solution solution;
    
    // Test case 1
    std::vector<int> nums1 = {1, 1, 1, 2, 2, 3};
    int k1 = 2;
    auto result1 = solution.topKFrequent(nums1, k1);
    std::cout << "Test 1 - nums: ";
    printVector(nums1);
    std::cout << ", k: " << k1 << " -> ";
    printVector(result1);
    std::cout << std::endl;
    
    // Test case 2
    std::vector<int> nums2 = {1};
    int k2 = 1;
    auto result2 = solution.topKFrequent(nums2, k2);
    std::cout << "Test 2 - nums: ";
    printVector(nums2);
    std::cout << ", k: " << k2 << " -> ";
    printVector(result2);
    std::cout << std::endl;
    
    // Test case 3: All elements have same frequency
    std::vector<int> nums3 = {1, 2, 3, 4, 5};
    int k3 = 3;
    auto result3 = solution.topKFrequent(nums3, k3);
    std::cout << "Test 3 - nums: ";
    printVector(nums3);
    std::cout << ", k: " << k3 << " -> ";
    printVector(result3);
    std::cout << std::endl;
    
    // Test case 4: Negative numbers
    std::vector<int> nums4 = {-1, -1, -2, -2, -2, 3};
    int k4 = 2;
    auto result4 = solution.topKFrequent(nums4, k4);
    std::cout << "Test 4 - nums: ";
    printVector(nums4);
    std::cout << ", k: " << k4 << " -> ";
    printVector(result4);
    std::cout << std::endl;
    
    // Performance comparison
    std::cout << "\nPerformance comparison:" << std::endl;
    
    // Large array with varying frequencies
    std::vector<int> largeNums;
    for (int i = 0; i < 100000; i++) {
        int freq = (i % 100) + 1; // Frequency from 1 to 100
        for (int j = 0; j < freq; j++) {
            largeNums.push_back(i);
        }
    }
    int largeK = 50;
    
    auto start = std::chrono::high_resolution_clock::now();
    auto minHeapResult = solution.topKFrequent(largeNums, largeK);
    auto end = std::chrono::high_resolution_clock::now();
    auto minHeapTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    start = std::chrono::high_resolution_clock::now();
    auto bucketResult = solution.topKFrequentBucket(largeNums, largeK);
    end = std::chrono::high_resolution_clock::now();
    auto bucketTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    start = std::chrono::high_resolution_clock::now();
    auto quickSelectResult = solution.topKFrequentQuickSelect(largeNums, largeK);
    end = std::chrono::high_resolution_clock::now();
    auto quickSelectTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    start = std::chrono::high_resolution_clock::now();
    auto stlResult = solution.topKFrequentSTL(largeNums, largeK);
    end = std::chrono::high_resolution_clock::now();
    auto stlTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Min Heap approach: " << minHeapTime.count() << " μs, result size: " 
              << minHeapResult.size() << std::endl;
    std::cout << "Bucket Sort approach: " << bucketTime.count() << " μs, result size: " 
              << bucketResult.size() << std::endl;
    std::cout << "Quick Select approach: " << quickSelectTime.count() << " μs, result size: " 
              << quickSelectResult.size() << std::endl;
    std::cout << "STL nth_element: " << stlTime.count() << " μs, result size: " 
              << stlResult.size() << std::endl;
    
    // Edge case testing
    std::cout << "\nEdge case testing:" << std::endl;
    
    // k = 1
    std::vector<int> edgeNums = {4, 1, -1, 2, -1, 2, 3};
    auto edge1 = solution.topKFrequent(edgeNums, 1);
    std::cout << "k=1: ";
    printVector(edge1);
    std::cout << std::endl;
    
    // k = all unique elements
    auto edge2 = solution.topKFrequent(edgeNums, 4);
    std::cout << "k=all: ";
    printVector(edge2);
    std::cout << std::endl;
    
    // Correctness verification
    std::cout << "\nCorrectness verification:" << std::endl;
    std::vector<int> testNums = {1, 1, 1, 2, 2, 3};
    int testK = 2;
    std::cout << "Test array: ";
    printVector(testNums);
    std::cout << ", k=" << testK << std::endl;
    
    auto min_heap = solution.topKFrequent(testNums, testK);
    auto max_heap = solution.topKFrequentMaxHeap(testNums, testK);
    auto bucket = solution.topKFrequentBucket(testNums, testK);
    auto quick_sel = solution.topKFrequentQuickSelect(testNums, testK);
    auto stl_nth = solution.topKFrequentSTL(testNums, testK);
    
    std::cout << "Min Heap: "; printVector(min_heap); std::cout << std::endl;
    std::cout << "Max Heap: "; printVector(max_heap); std::cout << std::endl;
    std::cout << "Bucket Sort: "; printVector(bucket); std::cout << std::endl;
    std::cout << "Quick Select: "; printVector(quick_sel); std::cout << std::endl;
    std::cout << "STL nth_element: "; printVector(stl_nth); std::cout << std::endl;
}

int main() {
    testTopKFrequent();
    return 0;
}