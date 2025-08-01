/*
 * LeetCode 205: Isomorphic Strings
 * 
 * Problem: Given two strings s and t, determine if they are isomorphic.
 * Two strings s and t are isomorphic if the characters in s can be replaced to get t.
 * All occurrences of a character must be replaced with the same character while preserving 
 * the order of characters. No two characters may map to the same character, but a character may map to itself.
 * 
 * Examples:
 * Input: s = "egg", t = "add"
 * Output: true
 * 
 * Input: s = "foo", t = "bar"
 * Output: false
 * 
 * Input: s = "paper", t = "title"
 * Output: true
 * 
 * Companies: Amazon, Google, Microsoft
 * Difficulty: Easy
 * Pattern: Hash Table, String
 */

#include <iostream>
#include <string>
#include <unordered_map>
#include <array>
#include <chrono>

class Solution {
public:
    // Approach 1: Two Hash Maps (bidirectional mapping)
    // Time: O(n), Space: O(k) where k is number of unique characters
    bool isIsomorphic(std::string s, std::string t) {
        if (s.length() != t.length()) return false;
        
        std::unordered_map<char, char> sToT;
        std::unordered_map<char, char> tToS;
        
        for (int i = 0; i < s.length(); i++) {
            char charS = s[i];
            char charT = t[i];
            
            // Check s -> t mapping
            if (sToT.find(charS) != sToT.end()) {
                if (sToT[charS] != charT) return false;
            } else {
                sToT[charS] = charT;
            }
            
            // Check t -> s mapping
            if (tToS.find(charT) != tToS.end()) {
                if (tToS[charT] != charS) return false;
            } else {
                tToS[charT] = charS;
            }
        }
        
        return true;
    }
    
    // Approach 2: Array-based mapping (for ASCII characters)
    // Time: O(n), Space: O(1) - fixed size arrays
    bool isIsomorphicArray(std::string s, std::string t) {
        if (s.length() != t.length()) return false;
        
        int sToT[256] = {0};  // ASCII mapping
        int tToS[256] = {0};
        
        for (int i = 0; i < s.length(); i++) {
            char charS = s[i];
            char charT = t[i];
            
            if (sToT[charS] == 0 && tToS[charT] == 0) {
                sToT[charS] = charT;
                tToS[charT] = charS;
            } else if (sToT[charS] != charT || tToS[charT] != charS) {
                return false;
            }
        }
        
        return true;
    }
    
    // Approach 3: Single Hash Map with transformation
    // Time: O(n), Space: O(k)
    bool isIsomorphicTransform(std::string s, std::string t) {
        return transformString(s) == transformString(t);
    }
    
    // Approach 4: First occurrence indices comparison
    // Time: O(n), Space: O(k)
    bool isIsomorphicIndices(std::string s, std::string t) {
        if (s.length() != t.length()) return false;
        
        std::unordered_map<char, int> sFirstIndex;
        std::unordered_map<char, int> tFirstIndex;
        
        for (int i = 0; i < s.length(); i++) {
            int sIndex = sFirstIndex.count(s[i]) ? sFirstIndex[s[i]] : i;
            int tIndex = tFirstIndex.count(t[i]) ? tFirstIndex[t[i]] : i;
            
            if (sIndex != tIndex) return false;
            
            sFirstIndex[s[i]] = sIndex;
            tFirstIndex[t[i]] = tIndex;
        }
        
        return true;
    }
    
    // Approach 5: Optimized with early termination
    // Time: O(n), Space: O(k)
    bool isIsomorphicOptimized(std::string s, std::string t) {
        if (s.length() != t.length()) return false;
        if (s == t) return true; // Same strings are always isomorphic
        
        std::unordered_map<char, char> mapping;
        std::unordered_map<char, bool> used;
        
        for (int i = 0; i < s.length(); i++) {
            char charS = s[i];
            char charT = t[i];
            
            if (mapping.find(charS) != mapping.end()) {
                if (mapping[charS] != charT) return false;
            } else {
                if (used[charT]) return false; // charT already mapped to another char
                mapping[charS] = charT;
                used[charT] = true;
            }
        }
        
        return true;
    }
    
private:
    // Helper function to transform string based on first occurrence
    std::string transformString(const std::string& str) {
        std::unordered_map<char, int> charToIndex;
        std::string result;
        int nextIndex = 0;
        
        for (char c : str) {
            if (charToIndex.find(c) == charToIndex.end()) {
                charToIndex[c] = nextIndex++;
            }
            result += std::to_string(charToIndex[c]) + ",";
        }
        
        return result;
    }
};

/*
 * Complexity Analysis:
 * 
 * Approach 1 (Two Hash Maps):
 * - Time: O(n) - single pass through strings
 * - Space: O(k) where k is number of unique characters
 * 
 * Approach 2 (Array-based):
 * - Time: O(n) - single pass through strings
 * - Space: O(1) - fixed size arrays for ASCII
 * 
 * Approach 3 (Transformation):
 * - Time: O(n) - transform both strings
 * - Space: O(n + k) - transformed strings + hash maps
 * 
 * Approach 4 (First Indices):
 * - Time: O(n) - compare first occurrence indices
 * - Space: O(k) - hash maps for indices
 * 
 * Approach 5 (Optimized):
 * - Time: O(n) - single pass with early termination
 * - Space: O(k) - mapping and used character tracking
 * 
 * Hash Table Optimization Tricks:
 * 1. Use bidirectional mapping to ensure one-to-one correspondence
 * 2. Use arrays instead of hash maps for ASCII characters
 * 3. Early termination when same strings detected
 * 4. Track used characters to prevent multiple mappings
 * 5. Transform to canonical form for comparison
 */

// Test helper functions
void testIsIsomorphic() {
    Solution solution;
    
    // Test case 1: Basic isomorphic
    std::string s1 = "egg", t1 = "add";
    std::cout << "Test 1 - \"" << s1 << "\" and \"" << t1 << "\": " 
              << std::boolalpha << solution.isIsomorphic(s1, t1) 
              << " (expected: true)" << std::endl;
    
    // Test case 2: Not isomorphic
    std::string s2 = "foo", t2 = "bar";
    std::cout << "Test 2 - \"" << s2 << "\" and \"" << t2 << "\": " 
              << std::boolalpha << solution.isIsomorphic(s2, t2) 
              << " (expected: false)" << std::endl;
    
    // Test case 3: Complex isomorphic
    std::string s3 = "paper", t3 = "title";
    std::cout << "Test 3 - \"" << s3 << "\" and \"" << t3 << "\": " 
              << std::boolalpha << solution.isIsomorphic(s3, t3) 
              << " (expected: true)" << std::endl;
    
    // Edge case: Empty strings
    std::string s4 = "", t4 = "";
    std::cout << "Test 4 - \"\" and \"\": " 
              << std::boolalpha << solution.isIsomorphic(s4, t4) 
              << " (expected: true)" << std::endl;
    
    // Edge case: Single character
    std::string s5 = "a", t5 = "b";
    std::cout << "Test 5 - \"a\" and \"b\": " 
              << std::boolalpha << solution.isIsomorphic(s5, t5) 
              << " (expected: true)" << std::endl;
    
    // Edge case: Same strings
    std::string s6 = "abc", t6 = "abc";
    std::cout << "Test 6 - \"abc\" and \"abc\": " 
              << std::boolalpha << solution.isIsomorphic(s6, t6) 
              << " (expected: true)" << std::endl;
    
    // Tricky case: One-to-many mapping
    std::string s7 = "ab", t7 = "aa";
    std::cout << "Test 7 - \"ab\" and \"aa\": " 
              << std::boolalpha << solution.isIsomorphic(s7, t7) 
              << " (expected: false)" << std::endl;
    
    // Performance comparison
    std::cout << "\nPerformance comparison:" << std::endl;
    
    // Large strings
    std::string largeS(100000, 'a');
    std::string largeT(100000, 'b');
    for (int i = 1; i < 100000; i += 2) {
        largeS[i] = 'c';
        largeT[i] = 'd';
    }
    
    auto start = std::chrono::high_resolution_clock::now();
    bool hashResult = solution.isIsomorphic(largeS, largeT);
    auto end = std::chrono::high_resolution_clock::now();
    auto hashTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    start = std::chrono::high_resolution_clock::now();
    bool arrayResult = solution.isIsomorphicArray(largeS, largeT);
    end = std::chrono::high_resolution_clock::now();
    auto arrayTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    start = std::chrono::high_resolution_clock::now();
    bool optimizedResult = solution.isIsomorphicOptimized(largeS, largeT);
    end = std::chrono::high_resolution_clock::now();
    auto optimizedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Hash Map approach: " << hashTime.count() << " μs, result: " 
              << std::boolalpha << hashResult << std::endl;
    std::cout << "Array approach: " << arrayTime.count() << " μs, result: " 
              << std::boolalpha << arrayResult << std::endl;
    std::cout << "Optimized approach: " << optimizedTime.count() << " μs, result: " 
              << std::boolalpha << optimizedResult << std::endl;
    
    // Correctness verification
    std::cout << "\nCorrectness verification:" << std::endl;
    std::string testS = "badc", testT = "baba";
    std::cout << "Test strings: \"" << testS << "\" and \"" << testT << "\"" << std::endl;
    std::cout << "Two Hash Maps: " << solution.isIsomorphic(testS, testT) << std::endl;
    std::cout << "Array-based: " << solution.isIsomorphicArray(testS, testT) << std::endl;
    std::cout << "Transform: " << solution.isIsomorphicTransform(testS, testT) << std::endl;
    std::cout << "Indices: " << solution.isIsomorphicIndices(testS, testT) << std::endl;
    std::cout << "Optimized: " << solution.isIsomorphicOptimized(testS, testT) << std::endl;
}

int main() {
    testIsIsomorphic();
    return 0;
}