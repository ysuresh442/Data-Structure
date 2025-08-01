/*
 * LeetCode 387: First Unique Character in a String
 * 
 * Problem: Given a string s, find the first non-repeating character in it and return its index. 
 * If it does not exist, return -1.
 * 
 * Examples:
 * Input: s = "leetcode"
 * Output: 0
 * 
 * Input: s = "loveleetcode"
 * Output: 2
 * 
 * Input: s = "aabb"
 * Output: -1
 * 
 * Companies: Amazon, Google, Microsoft, Apple
 * Difficulty: Easy
 * Pattern: Hash Table, String
 */

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <array>
#include <chrono>

class Solution {
public:
    // Approach 1: Hash Map - Two Pass
    // Time: O(n), Space: O(1) for ASCII or O(k) for unique characters
    int firstUniqChar(std::string s) {
        std::unordered_map<char, int> charCount;
        
        // First pass: count frequencies
        for (char c : s) {
            charCount[c]++;
        }
        
        // Second pass: find first unique character
        for (int i = 0; i < s.length(); i++) {
            if (charCount[s[i]] == 1) {
                return i;
            }
        }
        
        return -1;
    }
    
    // Approach 2: Array for ASCII characters (faster for ASCII)
    // Time: O(n), Space: O(1) - fixed size array
    int firstUniqCharArray(std::string s) {
        std::array<int, 26> charCount = {0};
        
        // Count frequencies
        for (char c : s) {
            charCount[c - 'a']++;
        }
        
        // Find first unique
        for (int i = 0; i < s.length(); i++) {
            if (charCount[s[i] - 'a'] == 1) {
                return i;
            }
        }
        
        return -1;
    }
    
    // Approach 3: Hash Map with Index Storage
    // Time: O(n), Space: O(k)
    int firstUniqCharWithIndex(std::string s) {
        std::unordered_map<char, std::pair<int, int>> charInfo; // {count, first_index}
        
        for (int i = 0; i < s.length(); i++) {
            char c = s[i];
            if (charInfo.find(c) == charInfo.end()) {
                charInfo[c] = {1, i};
            } else {
                charInfo[c].first++;
            }
        }
        
        int minIndex = s.length();
        for (const auto& pair : charInfo) {
            if (pair.second.first == 1) {
                minIndex = std::min(minIndex, pair.second.second);
            }
        }
        
        return minIndex == s.length() ? -1 : minIndex;
    }
    
    // Approach 4: Single Pass with Queue-like approach
    // Time: O(n), Space: O(k)
    int firstUniqCharSinglePass(std::string s) {
        std::unordered_map<char, int> charCount;
        std::vector<int> candidates;
        
        for (int i = 0; i < s.length(); i++) {
            char c = s[i];
            charCount[c]++;
            
            if (charCount[c] == 1) {
                candidates.push_back(i);
            }
        }
        
        for (int idx : candidates) {
            if (charCount[s[idx]] == 1) {
                return idx;
            }
        }
        
        return -1;
    }
    
    // Approach 5: Using string find functions
    // Time: O(n²), Space: O(1)
    int firstUniqCharBuiltIn(std::string s) {
        for (int i = 0; i < s.length(); i++) {
            char c = s[i];
            if (s.find(c) == i && s.find(c, i + 1) == std::string::npos) {
                return i;
            }
        }
        return -1;
    }
    
    // Approach 6: Optimized for lowercase English letters
    // Time: O(n), Space: O(1)
    int firstUniqCharOptimized(std::string s) {
        int charCount[26] = {0};
        
        // Count frequencies
        for (char c : s) {
            charCount[c - 'a']++;
        }
        
        // Find first unique
        for (int i = 0; i < s.length(); i++) {
            if (charCount[s[i] - 'a'] == 1) {
                return i;
            }
        }
        
        return -1;
    }
};

/*
 * Complexity Analysis:
 * 
 * Approach 1 (Hash Map - Two Pass):
 * - Time: O(n) - two passes through string
 * - Space: O(k) where k is number of unique characters
 * 
 * Approach 2 (Array for ASCII):
 * - Time: O(n) - two passes through string
 * - Space: O(1) - fixed size array of 26
 * 
 * Approach 3 (Hash Map with Index):
 * - Time: O(n) - single pass + iterate unique chars
 * - Space: O(k) - stores count and index
 * 
 * Approach 4 (Single Pass):
 * - Time: O(n) - one pass + candidates check
 * - Space: O(n) worst case for candidates
 * 
 * Approach 5 (Built-in functions):
 * - Time: O(n²) - find operations are O(n)
 * - Space: O(1) - no extra space
 * 
 * Hash Table Optimization Tricks:
 * 1. Use array instead of hash map for ASCII characters
 * 2. Two-pass approach is often cleaner than single-pass
 * 3. Store additional information (like index) to avoid second iteration
 * 4. Consider string's character set for space optimization
 */

// Test helper functions
void testFirstUniqChar() {
    Solution solution;
    
    // Test case 1
    std::string s1 = "leetcode";
    std::cout << "Test 1 - \"" << s1 << "\": " 
              << solution.firstUniqChar(s1) << " (expected: 0)" << std::endl;
    
    // Test case 2
    std::string s2 = "loveleetcode";
    std::cout << "Test 2 - \"" << s2 << "\": " 
              << solution.firstUniqChar(s2) << " (expected: 2)" << std::endl;
    
    // Test case 3
    std::string s3 = "aabb";
    std::cout << "Test 3 - \"" << s3 << "\": " 
              << solution.firstUniqChar(s3) << " (expected: -1)" << std::endl;
    
    // Edge case: Empty string
    std::string s4 = "";
    std::cout << "Test 4 - \"\": " 
              << solution.firstUniqChar(s4) << " (expected: -1)" << std::endl;
    
    // Edge case: Single character
    std::string s5 = "a";
    std::cout << "Test 5 - \"a\": " 
              << solution.firstUniqChar(s5) << " (expected: 0)" << std::endl;
    
    // Edge case: All same characters
    std::string s6 = "aaaa";
    std::cout << "Test 6 - \"aaaa\": " 
              << solution.firstUniqChar(s6) << " (expected: -1)" << std::endl;
    
    // Performance comparison
    std::cout << "\nPerformance comparison:" << std::endl;
    
    // Large string with unique character at end
    std::string largeStr(100000, 'a');
    for (int i = 1; i < 99999; i++) {
        largeStr[i] = 'a' + (i % 25); // Use 25 different characters
    }
    largeStr[99999] = 'z'; // Unique character at the end
    
    auto start = std::chrono::high_resolution_clock::now();
    int hashResult = solution.firstUniqChar(largeStr);
    auto end = std::chrono::high_resolution_clock::now();
    auto hashTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    start = std::chrono::high_resolution_clock::now();
    int arrayResult = solution.firstUniqCharArray(largeStr);
    end = std::chrono::high_resolution_clock::now();
    auto arrayTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    start = std::chrono::high_resolution_clock::now();
    int optimizedResult = solution.firstUniqCharOptimized(largeStr);
    end = std::chrono::high_resolution_clock::now();
    auto optimizedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Hash Map approach: " << hashTime.count() << " μs, result: " 
              << hashResult << std::endl;
    std::cout << "Array approach: " << arrayTime.count() << " μs, result: " 
              << arrayResult << std::endl;
    std::cout << "Optimized approach: " << optimizedTime.count() << " μs, result: " 
              << optimizedResult << std::endl;
    
    // Correctness verification
    std::cout << "\nCorrectness verification:" << std::endl;
    std::string testStr = "abccba";
    std::cout << "Test string: \"" << testStr << "\"" << std::endl;
    std::cout << "Hash Map: " << solution.firstUniqChar(testStr) << std::endl;
    std::cout << "Array: " << solution.firstUniqCharArray(testStr) << std::endl;
    std::cout << "With Index: " << solution.firstUniqCharWithIndex(testStr) << std::endl;
    std::cout << "Single Pass: " << solution.firstUniqCharSinglePass(testStr) << std::endl;
    std::cout << "Optimized: " << solution.firstUniqCharOptimized(testStr) << std::endl;
}

int main() {
    testFirstUniqChar();
    return 0;
}