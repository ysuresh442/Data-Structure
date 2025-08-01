/*
 * LeetCode 3: Longest Substring Without Repeating Characters
 * 
 * Problem: Given a string s, find the length of the longest substring 
 * without repeating characters.
 * 
 * Examples:
 * Input: s = "abcabcbb"
 * Output: 3 (The answer is "abc", with the length of 3)
 * 
 * Input: s = "bbbbb"
 * Output: 1 (The answer is "b", with the length of 1)
 * 
 * Companies: Amazon, Google, Facebook, Microsoft, Apple
 * Difficulty: Medium
 * Pattern: Sliding Window, Hash Table
 */

#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>

class Solution {
public:
    // Approach 1: Sliding Window with HashMap (Optimal)
    // Time: O(n), Space: O(min(m,n)) where m is character set size
    int lengthOfLongestSubstring(std::string s) {
        std::unordered_map<char, int> charIndex;
        int maxLen = 0;
        int start = 0;
        
        for (int end = 0; end < s.length(); end++) {
            char currentChar = s[end];
            
            // If character is already seen and is within current window
            if (charIndex.find(currentChar) != charIndex.end() && 
                charIndex[currentChar] >= start) {
                start = charIndex[currentChar] + 1;
            }
            
            charIndex[currentChar] = end;
            maxLen = std::max(maxLen, end - start + 1);
        }
        
        return maxLen;
    }
    
    // Approach 2: Sliding Window with HashSet
    // Time: O(2n) = O(n), Space: O(min(m,n))
    int lengthOfLongestSubstringSet(std::string s) {
        std::unordered_set<char> window;
        int maxLen = 0;
        int left = 0, right = 0;
        
        while (right < s.length()) {
            // Expand window
            while (right < s.length() && window.find(s[right]) == window.end()) {
                window.insert(s[right]);
                maxLen = std::max(maxLen, right - left + 1);
                right++;
            }
            
            // Contract window
            while (left < right && window.find(s[right]) != window.end()) {
                window.erase(s[left]);
                left++;
            }
        }
        
        return maxLen;
    }
    
    // Approach 3: ASCII Array (for ASCII characters only)
    // Time: O(n), Space: O(1) - fixed 128 space
    int lengthOfLongestSubstringASCII(std::string s) {
        std::vector<int> charIndex(128, -1);
        int maxLen = 0;
        int start = 0;
        
        for (int end = 0; end < s.length(); end++) {
            if (charIndex[s[end]] >= start) {
                start = charIndex[s[end]] + 1;
            }
            charIndex[s[end]] = end;
            maxLen = std::max(maxLen, end - start + 1);
        }
        
        return maxLen;
    }
    
    // Approach 4: Brute Force (for comparison)
    // Time: O(n³), Space: O(min(m,n))
    int lengthOfLongestSubstringBruteForce(std::string s) {
        int maxLen = 0;
        
        for (int i = 0; i < s.length(); i++) {
            for (int j = i; j < s.length(); j++) {
                if (isUnique(s, i, j)) {
                    maxLen = std::max(maxLen, j - i + 1);
                }
            }
        }
        
        return maxLen;
    }
    
    // Helper function for brute force
    bool isUnique(const std::string& s, int start, int end) {
        std::unordered_set<char> chars;
        for (int i = start; i <= end; i++) {
            if (chars.find(s[i]) != chars.end()) {
                return false;
            }
            chars.insert(s[i]);
        }
        return true;
    }
    
    // Approach 5: Optimized with early termination
    // Time: O(n), Space: O(min(m,n))
    int lengthOfLongestSubstringOptimized(std::string s) {
        if (s.empty()) return 0;
        
        std::unordered_map<char, int> charIndex;
        int maxLen = 0;
        int start = 0;
        
        for (int end = 0; end < s.length(); end++) {
            char c = s[end];
            
            if (charIndex.count(c) && charIndex[c] >= start) {
                start = charIndex[c] + 1;
            }
            
            charIndex[c] = end;
            maxLen = std::max(maxLen, end - start + 1);
            
            // Early termination optimization
            if (maxLen >= s.length() - start) {
                break;
            }
        }
        
        return maxLen;
    }
    
    // Approach 6: Return the actual substring (bonus)
    std::string longestSubstringWithoutRepeating(std::string s) {
        std::unordered_map<char, int> charIndex;
        int maxLen = 0;
        int start = 0;
        int bestStart = 0;
        
        for (int end = 0; end < s.length(); end++) {
            char currentChar = s[end];
            
            if (charIndex.find(currentChar) != charIndex.end() && 
                charIndex[currentChar] >= start) {
                start = charIndex[currentChar] + 1;
            }
            
            charIndex[currentChar] = end;
            if (end - start + 1 > maxLen) {
                maxLen = end - start + 1;
                bestStart = start;
            }
        }
        
        return s.substr(bestStart, maxLen);
    }
};

// Test function
void testLongestSubstring() {
    Solution sol;
    
    std::vector<std::string> testCases = {
        "abcabcbb",    // Expected: 3 ("abc")
        "bbbbb",       // Expected: 1 ("b")
        "pwwkew",      // Expected: 3 ("wke")
        "",            // Expected: 0
        "au",          // Expected: 2 ("au")
        "dvdf",        // Expected: 3 ("vdf")
        "abcdef",      // Expected: 6 ("abcdef")
        "aab",         // Expected: 2 ("ab")
        "cdd",         // Expected: 2 ("cd")
        "abba",        // Expected: 2 ("ab" or "ba")
    };
    
    std::cout << "Testing Longest Substring Without Repeating Characters:\n";
    std::cout << "=====================================================\n";
    
    for (const auto& test : testCases) {
        int result1 = sol.lengthOfLongestSubstring(test);
        int result2 = sol.lengthOfLongestSubstringSet(test);
        int result3 = sol.lengthOfLongestSubstringASCII(test);
        int result4 = sol.lengthOfLongestSubstringBruteForce(test);
        int result5 = sol.lengthOfLongestSubstringOptimized(test);
        std::string substring = sol.longestSubstringWithoutRepeating(test);
        
        std::cout << "Input: \"" << test << "\"\n";
        std::cout << "HashMap approach: " << result1 << "\n";
        std::cout << "HashSet approach: " << result2 << "\n";
        std::cout << "ASCII array approach: " << result3 << "\n";
        std::cout << "Brute force approach: " << result4 << "\n";
        std::cout << "Optimized approach: " << result5 << "\n";
        std::cout << "Longest substring: \"" << substring << "\"\n";
        std::cout << "---\n";
    }
}

int main() {
    testLongestSubstring();
    return 0;
}

/*
 * Key Insights:
 * 1. Sliding window technique is perfect for substring problems
 * 2. HashMap stores the most recent index of each character
 * 3. When duplicate found, move start pointer to avoid the duplicate
 * 4. Keep track of maximum length seen so far
 * 
 * Time Complexity Analysis:
 * - HashMap approach: O(n) - each character visited at most twice
 * - HashSet approach: O(n) - in worst case, each character added and removed once
 * - ASCII array: O(n) - similar to HashMap but with constant space for character set
 * - Brute force: O(n³) - check all substrings
 * 
 * Space Complexity:
 * - HashMap/HashSet: O(min(m,n)) where m is character set size
 * - ASCII array: O(1) - fixed 128 characters
 * 
 * Common Mistakes:
 * 1. Not updating start pointer correctly when duplicate found
 * 2. Forgetting to handle empty string
 * 3. Off-by-one errors in window calculation
 * 4. Not considering that duplicate might be outside current window
 * 
 * Follow-up Questions:
 * 1. What if we need to find all longest substrings?
 * 2. What if we want to allow k duplicate characters?
 * 3. What if we need to handle Unicode characters?
 * 4. What if we want the lexicographically smallest longest substring?
 */