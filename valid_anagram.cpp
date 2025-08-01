/*
 * LeetCode 242: Valid Anagram
 * 
 * Problem: Given two strings s and t, return true if t is an anagram of s, and false otherwise.
 * An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase,
 * typically using all the original letters exactly once.
 * 
 * Examples:
 * Input: s = "anagram", t = "nagaram"
 * Output: true
 * 
 * Input: s = "rat", t = "car"
 * Output: false
 * 
 * Companies: Amazon, Google, Facebook, Microsoft, Apple
 * Difficulty: Easy
 * Pattern: Hash Table, Sorting
 */

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <array>

class Solution {
public:
    // Approach 1: Hash Table (Frequency Count)
    // Time: O(n), Space: O(1) for ASCII or O(k) for Unicode
    bool isAnagram(std::string s, std::string t) {
        if (s.length() != t.length()) return false;
        
        std::unordered_map<char, int> charCount;
        
        // Count characters in s
        for (char c : s) {
            charCount[c]++;
        }
        
        // Subtract characters in t
        for (char c : t) {
            charCount[c]--;
            if (charCount[c] < 0) return false;
        }
        
        // Check if all counts are zero
        for (const auto& pair : charCount) {
            if (pair.second != 0) return false;
        }
        
        return true;
    }
    
    // Approach 2: Sorting
    // Time: O(n log n), Space: O(1)
    bool isAnagramSort(std::string s, std::string t) {
        if (s.length() != t.length()) return false;
        
        std::sort(s.begin(), s.end());
        std::sort(t.begin(), t.end());
        
        return s == t;
    }
    
    // Approach 3: ASCII Array (for lowercase letters only)
    // Time: O(n), Space: O(1)
    bool isAnagramArray(std::string s, std::string t) {
        if (s.length() != t.length()) return false;
        
        std::array<int, 26> charCount = {0};
        
        for (int i = 0; i < s.length(); i++) {
            charCount[s[i] - 'a']++;
            charCount[t[i] - 'a']--;
        }
        
        for (int count : charCount) {
            if (count != 0) return false;
        }
        
        return true;
    }
    
    // Approach 4: Single Pass with HashMap
    // Time: O(n), Space: O(1)
    bool isAnagramSinglePass(std::string s, std::string t) {
        if (s.length() != t.length()) return false;
        
        std::unordered_map<char, int> charCount;
        
        for (int i = 0; i < s.length(); i++) {
            charCount[s[i]]++;
            charCount[t[i]]--;
        }
        
        for (const auto& pair : charCount) {
            if (pair.second != 0) return false;
        }
        
        return true;
    }
    
    // Approach 5: Prime Numbers (Unique factorization)
    // Time: O(n), Space: O(1)
    // Note: This can overflow for large strings
    bool isAnagramPrime(std::string s, std::string t) {
        if (s.length() != t.length()) return false;
        
        // Prime numbers for each letter a-z
        std::vector<int> primes = {
            2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 
            43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101
        };
        
        long long productS = 1, productT = 1;
        
        for (char c : s) {
            productS *= primes[c - 'a'];
        }
        
        for (char c : t) {
            productT *= primes[c - 'a'];
        }
        
        return productS == productT;
    }
    
    // Approach 6: XOR (Alternative mathematical approach)
    // Time: O(n), Space: O(1)
    // Note: This doesn't work for anagrams! XOR cancels duplicate chars
    bool isAnagramXOR(std::string s, std::string t) {
        if (s.length() != t.length()) return false;
        
        int xorResult = 0;
        
        for (int i = 0; i < s.length(); i++) {
            xorResult ^= s[i];
            xorResult ^= t[i];
        }
        
        // This approach doesn't work correctly for anagrams
        // because XOR cancels out duplicate characters
        // Keeping for educational purposes
        return xorResult == 0; // This is incorrect for anagrams
    }
    
    // Approach 7: Two separate frequency maps
    // Time: O(n), Space: O(1)
    bool isAnagramTwoMaps(std::string s, std::string t) {
        if (s.length() != t.length()) return false;
        
        std::unordered_map<char, int> mapS, mapT;
        
        for (char c : s) mapS[c]++;
        for (char c : t) mapT[c]++;
        
        return mapS == mapT;
    }
    
    // Approach 8: Optimized for very long strings
    // Time: O(n), Space: O(1)
    bool isAnagramOptimized(std::string s, std::string t) {
        if (s.length() != t.length()) return false;
        
        // Early exit for different first characters
        if (s.empty()) return true;
        
        std::array<int, 26> count = {0};
        int uniqueChars = 0;
        
        // First pass: count unique characters
        for (char c : s) {
            if (count[c - 'a'] == 0) uniqueChars++;
            count[c - 'a']++;
        }
        
        // Second pass: decrement and check
        for (char c : t) {
            count[c - 'a']--;
            if (count[c - 'a'] == 0) uniqueChars--;
            else if (count[c - 'a'] < 0) return false;
        }
        
        return uniqueChars == 0;
    }
    
    // Bonus: Check if string is anagram of any permutation of another string
    bool isAnagramOfAnyPermutation(std::string s, std::string pattern) {
        if (s.length() < pattern.length()) return false;
        
        std::array<int, 26> patternCount = {0};
        std::array<int, 26> windowCount = {0};
        
        // Count pattern characters
        for (char c : pattern) {
            patternCount[c - 'a']++;
        }
        
        // Sliding window
        for (int i = 0; i < s.length(); i++) {
            // Add current character
            windowCount[s[i] - 'a']++;
            
            // Remove leftmost character if window is too large
            if (i >= pattern.length()) {
                windowCount[s[i - pattern.length()] - 'a']--;
            }
            
            // Check if current window is anagram
            if (i >= pattern.length() - 1 && windowCount == patternCount) {
                return true;
            }
        }
        
        return false;
    }
    
    // Bonus: Find all anagrams of a string in another string
    std::vector<int> findAnagrams(std::string s, std::string p) {
        std::vector<int> result;
        if (s.length() < p.length()) return result;
        
        std::array<int, 26> pCount = {0};
        std::array<int, 26> windowCount = {0};
        
        // Count characters in pattern
        for (char c : p) {
            pCount[c - 'a']++;
        }
        
        // Sliding window
        for (int i = 0; i < s.length(); i++) {
            // Add current character
            windowCount[s[i] - 'a']++;
            
            // Remove leftmost character if window is too large
            if (i >= p.length()) {
                windowCount[s[i - p.length()] - 'a']--;
            }
            
            // Check if current window is anagram
            if (i >= p.length() - 1 && windowCount == pCount) {
                result.push_back(i - p.length() + 1);
            }
        }
        
        return result;
    }
};

// Test function
void testValidAnagram() {
    Solution sol;
    
    std::vector<std::pair<std::string, std::string>> testCases = {
        {"anagram", "nagaram"},     // Expected: true
        {"rat", "car"},             // Expected: false
        {"listen", "silent"},       // Expected: true
        {"hello", "bello"},         // Expected: false
        {"", ""},                   // Expected: true
        {"a", "ab"},                // Expected: false
        {"ab", "a"},                // Expected: false
        {"abc", "bca"},             // Expected: true
        {"aabbcc", "abcabc"},       // Expected: true
        {"aab", "baa"},             // Expected: true
    };
    
    std::cout << "Testing Valid Anagram:\n";
    std::cout << "=====================\n";
    
    for (const auto& test : testCases) {
        bool result1 = sol.isAnagram(test.first, test.second);
        bool result2 = sol.isAnagramSort(test.first, test.second);
        bool result3 = sol.isAnagramArray(test.first, test.second);
        bool result4 = sol.isAnagramSinglePass(test.first, test.second);
        bool result5 = sol.isAnagramPrime(test.first, test.second);
        bool result6 = sol.isAnagramTwoMaps(test.first, test.second);
        bool result7 = sol.isAnagramOptimized(test.first, test.second);
        
        std::cout << "Input: s = \"" << test.first << "\", t = \"" << test.second << "\"\n";
        std::cout << "Hash Table: " << (result1 ? "true" : "false") << "\n";
        std::cout << "Sorting: " << (result2 ? "true" : "false") << "\n";
        std::cout << "Array: " << (result3 ? "true" : "false") << "\n";
        std::cout << "Single Pass: " << (result4 ? "true" : "false") << "\n";
        std::cout << "Prime: " << (result5 ? "true" : "false") << "\n";
        std::cout << "Two Maps: " << (result6 ? "true" : "false") << "\n";
        std::cout << "Optimized: " << (result7 ? "true" : "false") << "\n";
        std::cout << "---\n";
    }
    
    // Test find anagrams
    std::cout << "\nTesting Find Anagrams:\n";
    std::string s = "abab", p = "ab";
    std::vector<int> anagramIndices = sol.findAnagrams(s, p);
    std::cout << "Find anagrams of \"" << p << "\" in \"" << s << "\": ";
    for (int idx : anagramIndices) {
        std::cout << idx << " ";
    }
    std::cout << "\n";
}

int main() {
    testValidAnagram();
    return 0;
}

/*
 * Key Insights:
 * 1. Anagrams have the same character frequency distribution
 * 2. Sorting both strings should yield identical results for anagrams
 * 3. HashMap/Array approach is more efficient than sorting
 * 4. Consider character set size for space complexity analysis
 * 
 * Time Complexity Comparison:
 * - Hash Table: O(n) - linear scan with constant time operations
 * - Sorting: O(n log n) - dominated by sorting algorithm
 * - Array: O(n) - linear scan with array indexing
 * - Prime Numbers: O(n) - but can overflow for large strings
 * 
 * Space Complexity:
 * - Hash Table: O(k) where k is number of unique characters
 * - Sorting: O(1) if in-place, O(n) if creating copies
 * - Array: O(1) for fixed character set (e.g., 26 lowercase letters)
 * - Prime Numbers: O(1) excluding the prime lookup table
 * 
 * Common Mistakes:
 * 1. Not checking if strings have the same length first
 * 2. Forgetting to handle empty strings
 * 3. Using XOR which doesn't work for anagrams with duplicate characters
 * 4. Integer overflow with prime number approach
 * 
 * Follow-up Questions:
 * 1. What if strings contain Unicode characters?
 * 2. What if we need to find all anagrams in a list of strings?
 * 3. What if we need to handle case-insensitive anagrams?
 * 4. What if we want to find anagram substrings in a larger string?
 */