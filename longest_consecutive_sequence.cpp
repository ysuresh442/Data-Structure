/*
 * LeetCode 128: Longest Consecutive Sequence
 * 
 * Problem: Given an unsorted array of integers nums, return the length of the longest 
 * consecutive elements sequence. You must write an algorithm that runs in O(n) time.
 * 
 * Examples:
 * Input: nums = [100,4,200,1,3,2]
 * Output: 4
 * Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.
 * 
 * Input: nums = [0,3,7,2,5,8,4,6,0,1]
 * Output: 9
 * 
 * Companies: Amazon, Google, Facebook, Microsoft
 * Difficulty: Hard
 * Pattern: Hash Set, Union Find
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
    int longestConsecutive(std::vector<int>& nums) {
        if (nums.empty()) return 0;
        
        std::unordered_set<int> numSet(nums.begin(), nums.end());
        int maxLength = 0;
        
        for (int num : numSet) {
            // Only start counting from the beginning of a sequence
            if (numSet.find(num - 1) == numSet.end()) {
                int currentNum = num;
                int currentLength = 1;
                
                // Count consecutive numbers
                while (numSet.find(currentNum + 1) != numSet.end()) {
                    currentNum++;
                    currentLength++;
                }
                
                maxLength = std::max(maxLength, currentLength);
            }
        }
        
        return maxLength;
    }
    
    // Approach 2: Hash Map with memoization
    // Time: O(n), Space: O(n)
    int longestConsecutiveMemo(std::vector<int>& nums) {
        if (nums.empty()) return 0;
        
        std::unordered_map<int, int> memo; // num -> length of sequence starting at num
        std::unordered_set<int> numSet(nums.begin(), nums.end());
        int maxLength = 0;
        
        for (int num : numSet) {
            maxLength = std::max(maxLength, dfs(num, numSet, memo));
        }
        
        return maxLength;
    }
    
    // Approach 3: Union Find
    // Time: O(n α(n)), Space: O(n)
    int longestConsecutiveUnionFind(std::vector<int>& nums) {
        if (nums.empty()) return 0;
        
        std::unordered_set<int> numSet(nums.begin(), nums.end());
        std::unordered_map<int, int> parent;
        std::unordered_map<int, int> size;
        
        // Initialize Union Find
        for (int num : numSet) {
            parent[num] = num;
            size[num] = 1;
        }
        
        // Union consecutive numbers
        for (int num : numSet) {
            if (numSet.count(num + 1)) {
                unionSets(num, num + 1, parent, size);
            }
        }
        
        int maxLength = 0;
        for (const auto& p : size) {
            maxLength = std::max(maxLength, p.second);
        }
        
        return maxLength;
    }
    
    // Approach 4: Sorting (not O(n) but included for comparison)
    // Time: O(n log n), Space: O(1)
    int longestConsecutiveSort(std::vector<int>& nums) {
        if (nums.empty()) return 0;
        
        std::sort(nums.begin(), nums.end());
        
        int maxLength = 1;
        int currentLength = 1;
        
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == nums[i-1]) {
                continue; // Skip duplicates
            } else if (nums[i] == nums[i-1] + 1) {
                currentLength++;
            } else {
                maxLength = std::max(maxLength, currentLength);
                currentLength = 1;
            }
        }
        
        return std::max(maxLength, currentLength);
    }
    
    // Approach 5: Hash Map Range Tracking
    // Time: O(n), Space: O(n)
    int longestConsecutiveRange(std::vector<int>& nums) {
        if (nums.empty()) return 0;
        
        std::unordered_map<int, int> ranges; // num -> length of sequence containing num
        int maxLength = 0;
        
        for (int num : nums) {
            if (ranges.count(num)) continue; // Already processed
            
            int leftLength = ranges.count(num - 1) ? ranges[num - 1] : 0;
            int rightLength = ranges.count(num + 1) ? ranges[num + 1] : 0;
            int totalLength = leftLength + rightLength + 1;
            
            ranges[num] = totalLength;
            maxLength = std::max(maxLength, totalLength);
            
            // Update boundary points
            ranges[num - leftLength] = totalLength;
            ranges[num + rightLength] = totalLength;
        }
        
        return maxLength;
    }
    
    // Approach 6: Optimized Set with early termination
    // Time: O(n), Space: O(n)
    int longestConsecutiveOptimized(std::vector<int>& nums) {
        if (nums.empty()) return 0;
        if (nums.size() == 1) return 1;
        
        std::unordered_set<int> numSet(nums.begin(), nums.end());
        int maxLength = 0;
        
        for (int num : numSet) {
            if (numSet.find(num - 1) == numSet.end()) {
                int currentLength = 1;
                
                while (numSet.find(num + currentLength) != numSet.end()) {
                    currentLength++;
                    // Early termination if we can't beat current max
                    if (maxLength > currentLength + (numSet.size() - currentLength)) {
                        break;
                    }
                }
                
                maxLength = std::max(maxLength, currentLength);
            }
        }
        
        return maxLength;
    }
    
private:
    // DFS with memoization helper
    int dfs(int num, const std::unordered_set<int>& numSet, std::unordered_map<int, int>& memo) {
        if (memo.count(num)) return memo[num];
        
        if (numSet.count(num + 1)) {
            memo[num] = 1 + dfs(num + 1, numSet, memo);
        } else {
            memo[num] = 1;
        }
        
        return memo[num];
    }
    
    // Union Find helpers
    int find(int x, std::unordered_map<int, int>& parent) {
        if (parent[x] != x) {
            parent[x] = find(parent[x], parent);
        }
        return parent[x];
    }
    
    void unionSets(int x, int y, std::unordered_map<int, int>& parent, std::unordered_map<int, int>& size) {
        int rootX = find(x, parent);
        int rootY = find(y, parent);
        
        if (rootX != rootY) {
            if (size[rootX] < size[rootY]) {
                parent[rootX] = rootY;
                size[rootY] += size[rootX];
            } else {
                parent[rootY] = rootX;
                size[rootX] += size[rootY];
            }
        }
    }
};

/*
 * Complexity Analysis:
 * 
 * Approach 1 (Hash Set):
 * - Time: O(n) - each number visited at most twice
 * - Space: O(n) - hash set storage
 * 
 * Approach 2 (Memoization):
 * - Time: O(n) - each number processed once with memoization
 * - Space: O(n) - memo table + recursion stack
 * 
 * Approach 3 (Union Find):
 * - Time: O(n α(n)) - amortized almost linear
 * - Space: O(n) - parent and size arrays
 * 
 * Approach 4 (Sorting):
 * - Time: O(n log n) - sorting dominates
 * - Space: O(1) - in-place sorting
 * 
 * Approach 5 (Range Tracking):
 * - Time: O(n) - each number processed once
 * - Space: O(n) - range map
 * 
 * Hash Table Optimization Tricks:
 * 1. Only start counting from sequence beginnings
 * 2. Use unordered_set for O(1) lookup
 * 3. Memoization prevents recomputation
 * 4. Early termination when impossible to beat current max
 * 5. Range tracking maintains sequence boundaries
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

void testLongestConsecutive() {
    Solution solution;
    
    // Test case 1
    std::vector<int> nums1 = {100, 4, 200, 1, 3, 2};
    std::cout << "Test 1 - nums: ";
    printVector(nums1);
    std::cout << " -> " << solution.longestConsecutive(nums1) 
              << " (expected: 4)" << std::endl;
    
    // Test case 2
    std::vector<int> nums2 = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
    std::cout << "Test 2 - nums: ";
    printVector(nums2);
    std::cout << " -> " << solution.longestConsecutive(nums2) 
              << " (expected: 9)" << std::endl;
    
    // Edge case: Empty array
    std::vector<int> nums3 = {};
    std::cout << "Test 3 - empty: " << solution.longestConsecutive(nums3) 
              << " (expected: 0)" << std::endl;
    
    // Edge case: Single element
    std::vector<int> nums4 = {1};
    std::cout << "Test 4 - single: " << solution.longestConsecutive(nums4) 
              << " (expected: 1)" << std::endl;
    
    // Edge case: All same elements
    std::vector<int> nums5 = {1, 1, 1, 1};
    std::cout << "Test 5 - duplicates: " << solution.longestConsecutive(nums5) 
              << " (expected: 1)" << std::endl;
    
    // Edge case: No consecutive sequence
    std::vector<int> nums6 = {1, 3, 5, 7, 9};
    std::cout << "Test 6 - no sequence: " << solution.longestConsecutive(nums6) 
              << " (expected: 1)" << std::endl;
    
    // Negative numbers
    std::vector<int> nums7 = {-1, -2, 0, 1, 2};
    std::cout << "Test 7 - negative: " << solution.longestConsecutive(nums7) 
              << " (expected: 5)" << std::endl;
    
    // Performance comparison
    std::cout << "\nPerformance comparison:" << std::endl;
    
    // Large array with long consecutive sequence
    std::vector<int> largeNums;
    for (int i = 0; i < 100000; i++) {
        largeNums.push_back(i);
    }
    // Shuffle to make it unsorted
    std::random_shuffle(largeNums.begin(), largeNums.end());
    
    auto start = std::chrono::high_resolution_clock::now();
    int hashSetResult = solution.longestConsecutive(largeNums);
    auto end = std::chrono::high_resolution_clock::now();
    auto hashSetTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    start = std::chrono::high_resolution_clock::now();
    int memoResult = solution.longestConsecutiveMemo(largeNums);
    end = std::chrono::high_resolution_clock::now();
    auto memoTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    start = std::chrono::high_resolution_clock::now();
    int rangeResult = solution.longestConsecutiveRange(largeNums);
    end = std::chrono::high_resolution_clock::now();
    auto rangeTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    start = std::chrono::high_resolution_clock::now();
    int sortResult = solution.longestConsecutiveSort(largeNums);
    end = std::chrono::high_resolution_clock::now();
    auto sortTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Hash Set approach: " << hashSetTime.count() << " μs, result: " 
              << hashSetResult << std::endl;
    std::cout << "Memoization approach: " << memoTime.count() << " μs, result: " 
              << memoResult << std::endl;
    std::cout << "Range tracking: " << rangeTime.count() << " μs, result: " 
              << rangeResult << std::endl;
    std::cout << "Sorting approach: " << sortTime.count() << " μs, result: " 
              << sortResult << std::endl;
    
    // Correctness verification
    std::cout << "\nCorrectness verification:" << std::endl;
    std::vector<int> testNums = {4, 0, -4, -2, 2, 5, 2, 0, -8, -8, -8, -8, -1, 7, 4, 5, 5, -4, 6, 6, -3};
    std::cout << "Test array: ";
    printVector(testNums);
    std::cout << std::endl;
    
    std::cout << "Hash Set: " << solution.longestConsecutive(testNums) << std::endl;
    std::cout << "Memoization: " << solution.longestConsecutiveMemo(testNums) << std::endl;
    std::cout << "Union Find: " << solution.longestConsecutiveUnionFind(testNums) << std::endl;
    std::cout << "Sort: " << solution.longestConsecutiveSort(testNums) << std::endl;
    std::cout << "Range: " << solution.longestConsecutiveRange(testNums) << std::endl;
    std::cout << "Optimized: " << solution.longestConsecutiveOptimized(testNums) << std::endl;
}

int main() {
    testLongestConsecutive();
    return 0;
}