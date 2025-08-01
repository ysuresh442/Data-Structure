/*
 * LeetCode 202: Happy Number
 * 
 * Problem: Write an algorithm to determine if a number n is happy.
 * A happy number is a number defined by the following process:
 * - Starting with any positive integer, replace the number by the sum of the squares of its digits.
 * - Repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1.
 * - Those numbers for which this process ends in 1 are happy.
 * 
 * Examples:
 * Input: n = 19
 * Output: true
 * Explanation: 1² + 9² = 82, 8² + 2² = 68, 6² + 8² = 100, 1² + 0² + 0² = 1
 * 
 * Input: n = 2
 * Output: false
 * 
 * Companies: Amazon, Google, Microsoft
 * Difficulty: Easy
 * Pattern: Hash Table, Math, Two Pointers
 */

#include <iostream>
#include <unordered_set>
#include <chrono>

class Solution {
public:
    // Approach 1: Hash Set to detect cycle
    // Time: O(log n), Space: O(log n)
    bool isHappy(int n) {
        std::unordered_set<int> seen;
        
        while (n != 1 && seen.find(n) == seen.end()) {
            seen.insert(n);
            n = getSumOfSquares(n);
        }
        
        return n == 1;
    }
    
    // Approach 2: Floyd's Cycle Detection (Two Pointers)
    // Time: O(log n), Space: O(1)
    bool isHappyFloyd(int n) {
        int slow = n;
        int fast = n;
        
        do {
            slow = getSumOfSquares(slow);
            fast = getSumOfSquares(getSumOfSquares(fast));
        } while (slow != fast);
        
        return slow == 1;
    }
    
    // Approach 3: Hardcoded cycle detection
    // Time: O(log n), Space: O(1)
    bool isHappyHardcoded(int n) {
        std::unordered_set<int> knownUnhappyCycle = {4, 16, 37, 58, 89, 145, 42, 20};
        
        while (n != 1 && knownUnhappyCycle.find(n) == knownUnhappyCycle.end()) {
            n = getSumOfSquares(n);
        }
        
        return n == 1;
    }
    
    // Approach 4: Recursive with memoization
    // Time: O(log n), Space: O(log n)
    bool isHappyRecursive(int n) {
        std::unordered_set<int> seen;
        return isHappyHelper(n, seen);
    }
    
    // Approach 5: Optimized digit extraction
    // Time: O(log n), Space: O(log n)
    bool isHappyOptimized(int n) {
        std::unordered_set<int> seen;
        
        while (n != 1 && !seen.count(n)) {
            seen.insert(n);
            n = getSumOfSquaresFast(n);
        }
        
        return n == 1;
    }
    
private:
    // Helper function to calculate sum of squares of digits
    int getSumOfSquares(int n) {
        int sum = 0;
        while (n > 0) {
            int digit = n % 10;
            sum += digit * digit;
            n /= 10;
        }
        return sum;
    }
    
    // Optimized version using bit operations where possible
    int getSumOfSquaresFast(int n) {
        int sum = 0;
        while (n) {
            int digit = n % 10;
            sum += digit * digit;
            n /= 10;
        }
        return sum;
    }
    
    // Recursive helper
    bool isHappyHelper(int n, std::unordered_set<int>& seen) {
        if (n == 1) return true;
        if (seen.count(n)) return false;
        
        seen.insert(n);
        return isHappyHelper(getSumOfSquares(n), seen);
    }
};

/*
 * Complexity Analysis:
 * 
 * Approach 1 (Hash Set):
 * - Time: O(log n) - number of digits determines iterations
 * - Space: O(log n) - hash set stores visited numbers
 * 
 * Approach 2 (Floyd's Cycle Detection):
 * - Time: O(log n) - same iteration count
 * - Space: O(1) - only two pointers
 * 
 * Approach 3 (Hardcoded Cycle):
 * - Time: O(log n) - until hit known cycle or 1
 * - Space: O(1) - fixed set of unhappy numbers
 * 
 * Approach 4 (Recursive):
 * - Time: O(log n) - same logic as iterative
 * - Space: O(log n) - recursion stack + memoization
 * 
 * Hash Table Optimization Tricks:
 * 1. Use unordered_set for O(1) cycle detection
 * 2. Floyd's algorithm eliminates space complexity
 * 3. Precomputed unhappy cycles can optimize common cases
 * 4. Early termination on reaching 1 or detecting cycle
 * 
 * Mathematical Insights:
 * - All unhappy numbers eventually reach the cycle: 4 → 16 → 37 → 58 → 89 → 145 → 42 → 20 → 4
 * - For any starting number, the sum of squares decreases the number of digits
 * - Maximum sum for a 3-digit number: 999 → 243 (3 * 9²)
 */

// Test helper functions
void testIsHappy() {
    Solution solution;
    
    // Test case 1: Happy number
    int n1 = 19;
    std::cout << "Test 1 - " << n1 << ": " << std::boolalpha 
              << solution.isHappy(n1) << " (expected: true)" << std::endl;
    
    // Show the process for 19
    std::cout << "Process for 19: ";
    int temp = 19;
    std::unordered_set<int> seen;
    while (temp != 1 && seen.find(temp) == seen.end()) {
        std::cout << temp << " → ";
        seen.insert(temp);
        int sum = 0;
        while (temp > 0) {
            int digit = temp % 10;
            sum += digit * digit;
            temp /= 10;
        }
        temp = sum;
    }
    std::cout << temp << std::endl;
    
    // Test case 2: Unhappy number
    int n2 = 2;
    std::cout << "Test 2 - " << n2 << ": " << std::boolalpha 
              << solution.isHappy(n2) << " (expected: false)" << std::endl;
    
    // Test case 3: Single digit happy numbers
    std::vector<int> singleDigits = {1, 7, 10};
    for (int num : singleDigits) {
        std::cout << "Test - " << num << ": " << std::boolalpha 
                  << solution.isHappy(num) << std::endl;
    }
    
    // Test case 4: Known unhappy numbers
    std::vector<int> unhappyNumbers = {2, 3, 4, 5, 6, 8, 9};
    std::cout << "\nUnhappy numbers: ";
    for (int num : unhappyNumbers) {
        std::cout << num << ":" << solution.isHappy(num) << " ";
    }
    std::cout << std::endl;
    
    // Test case 5: Known happy numbers
    std::vector<int> happyNumbers = {1, 7, 10, 13, 19, 23, 28, 31};
    std::cout << "Happy numbers: ";
    for (int num : happyNumbers) {
        std::cout << num << ":" << solution.isHappy(num) << " ";
    }
    std::cout << std::endl;
    
    // Performance comparison
    std::cout << "\nPerformance comparison:" << std::endl;
    
    auto start = std::chrono::high_resolution_clock::now();
    bool hashResult = solution.isHappy(999999);
    auto end = std::chrono::high_resolution_clock::now();
    auto hashTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    start = std::chrono::high_resolution_clock::now();
    bool floydResult = solution.isHappyFloyd(999999);
    end = std::chrono::high_resolution_clock::now();
    auto floydTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    start = std::chrono::high_resolution_clock::now();
    bool hardcodedResult = solution.isHappyHardcoded(999999);
    end = std::chrono::high_resolution_clock::now();
    auto hardcodedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Hash Set approach: " << hashTime.count() << " μs, result: " 
              << std::boolalpha << hashResult << std::endl;
    std::cout << "Floyd's approach: " << floydTime.count() << " μs, result: " 
              << std::boolalpha << floydResult << std::endl;
    std::cout << "Hardcoded approach: " << hardcodedTime.count() << " μs, result: " 
              << std::boolalpha << hardcodedResult << std::endl;
    
    // Show the unhappy cycle
    std::cout << "\nUnhappy cycle starting from 4: ";
    temp = 4;
    seen.clear();
    do {
        std::cout << temp << " → ";
        seen.insert(temp);
        int sum = 0;
        while (temp > 0) {
            int digit = temp % 10;
            sum += digit * digit;
            temp /= 10;
        }
        temp = sum;
    } while (seen.find(temp) == seen.end());
    std::cout << temp << " (cycle detected)" << std::endl;
    
    // Correctness verification
    std::cout << "\nCorrectness verification for n=19:" << std::endl;
    std::cout << "Hash Set: " << solution.isHappy(19) << std::endl;
    std::cout << "Floyd's: " << solution.isHappyFloyd(19) << std::endl;
    std::cout << "Hardcoded: " << solution.isHappyHardcoded(19) << std::endl;
    std::cout << "Recursive: " << solution.isHappyRecursive(19) << std::endl;
    std::cout << "Optimized: " << solution.isHappyOptimized(19) << std::endl;
}

int main() {
    testIsHappy();
    return 0;
}