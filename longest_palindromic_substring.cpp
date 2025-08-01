/*
 * LeetCode 5: Longest Palindromic Substring
 * 
 * Problem: Given a string s, return the longest palindromic substring in s.
 * 
 * Examples:
 * Input: s = "babad"
 * Output: "bab" (Note: "aba" is also a valid answer)
 * 
 * Input: s = "cbbd"
 * Output: "bb"
 * 
 * Companies: Amazon, Google, Facebook, Microsoft, Apple
 * Difficulty: Medium
 * Pattern: Expand Around Center, Dynamic Programming
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    // Approach 1: Expand Around Center (Optimal for most cases)
    // Time: O(n²), Space: O(1)
    std::string longestPalindrome(std::string s) {
        if (s.empty()) return "";
        
        int start = 0, maxLen = 1;
        
        for (int i = 0; i < s.length(); i++) {
            // Check for odd length palindromes (center at i)
            int len1 = expandAroundCenter(s, i, i);
            // Check for even length palindromes (center between i and i+1)
            int len2 = expandAroundCenter(s, i, i + 1);
            
            int currentMax = std::max(len1, len2);
            if (currentMax > maxLen) {
                maxLen = currentMax;
                start = i - (currentMax - 1) / 2;
            }
        }
        
        return s.substr(start, maxLen);
    }
    
    // Helper function for expand around center
    int expandAroundCenter(const std::string& s, int left, int right) {
        while (left >= 0 && right < s.length() && s[left] == s[right]) {
            left--;
            right++;
        }
        return right - left - 1;
    }
    
    // Approach 2: Dynamic Programming
    // Time: O(n²), Space: O(n²)
    std::string longestPalindromeDP(std::string s) {
        int n = s.length();
        if (n == 0) return "";
        
        // dp[i][j] = true if substring s[i...j] is palindrome
        std::vector<std::vector<bool>> dp(n, std::vector<bool>(n, false));
        
        int start = 0, maxLen = 1;
        
        // All single characters are palindromes
        for (int i = 0; i < n; i++) {
            dp[i][i] = true;
        }
        
        // Check for 2-character palindromes
        for (int i = 0; i < n - 1; i++) {
            if (s[i] == s[i + 1]) {
                dp[i][i + 1] = true;
                start = i;
                maxLen = 2;
            }
        }
        
        // Check for palindromes of length 3 and more
        for (int len = 3; len <= n; len++) {
            for (int i = 0; i < n - len + 1; i++) {
                int j = i + len - 1;
                
                if (s[i] == s[j] && dp[i + 1][j - 1]) {
                    dp[i][j] = true;
                    start = i;
                    maxLen = len;
                }
            }
        }
        
        return s.substr(start, maxLen);
    }
    
    // Approach 3: Manacher's Algorithm (Most efficient)
    // Time: O(n), Space: O(n)
    std::string longestPalindromeManacher(std::string s) {
        if (s.empty()) return "";
        
        // Preprocess: insert '#' between characters
        std::string processed = "#";
        for (char c : s) {
            processed += c;
            processed += "#";
        }
        
        int n = processed.length();
        std::vector<int> P(n, 0); // Array to store radius of palindrome
        int center = 0, right = 0; // Center and rightmost boundary of current palindrome
        
        int maxLen = 0, centerIndex = 0;
        
        for (int i = 0; i < n; i++) {
            // Mirror of i with respect to center
            int mirror = 2 * center - i;
            
            // If i is within the right boundary, we can use previously computed values
            if (i < right) {
                P[i] = std::min(right - i, P[mirror]);
            }
            
            // Try to expand around i
            try {
                while (i + P[i] + 1 < n && i - P[i] - 1 >= 0 &&
                       processed[i + P[i] + 1] == processed[i - P[i] - 1]) {
                    P[i]++;
                }
            } catch (...) {
                // Handle boundary cases
            }
            
            // If palindrome centered at i extends past right, adjust center and right
            if (i + P[i] > right) {
                center = i;
                right = i + P[i];
            }
            
            // Update maximum length palindrome
            if (P[i] > maxLen) {
                maxLen = P[i];
                centerIndex = i;
            }
        }
        
        // Extract the actual palindrome from original string
        int start = (centerIndex - maxLen) / 2;
        return s.substr(start, maxLen);
    }
    
    // Approach 4: Brute Force (for comparison)
    // Time: O(n³), Space: O(1)
    std::string longestPalindromeBruteForce(std::string s) {
        int n = s.length();
        if (n == 0) return "";
        
        std::string longest = "";
        
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                std::string substr = s.substr(i, j - i + 1);
                if (isPalindrome(substr) && substr.length() > longest.length()) {
                    longest = substr;
                }
            }
        }
        
        return longest;
    }
    
    // Helper function to check if string is palindrome
    bool isPalindrome(const std::string& s) {
        int left = 0, right = s.length() - 1;
        while (left < right) {
            if (s[left] != s[right]) return false;
            left++;
            right--;
        }
        return true;
    }
    
    // Approach 5: Optimized Expand Around Center with early termination
    // Time: O(n²) average, O(n) best case, Space: O(1)
    std::string longestPalindromeOptimized(std::string s) {
        if (s.empty()) return "";
        
        int start = 0, maxLen = 1;
        
        for (int i = 0; i < s.length(); i++) {
            // Early termination: if remaining characters can't form longer palindrome
            if (s.length() - i <= maxLen / 2) break;
            
            int len1 = expandAroundCenterOptimized(s, i, i, maxLen);
            int len2 = expandAroundCenterOptimized(s, i, i + 1, maxLen);
            
            int currentMax = std::max(len1, len2);
            if (currentMax > maxLen) {
                maxLen = currentMax;
                start = i - (currentMax - 1) / 2;
            }
        }
        
        return s.substr(start, maxLen);
    }
    
    // Optimized expand with early termination
    int expandAroundCenterOptimized(const std::string& s, int left, int right, int maxLen) {
        while (left >= 0 && right < s.length() && s[left] == s[right]) {
            // Early termination if we can't beat current max
            if (right - left + 1 > maxLen) {
                left--;
                right++;
            } else {
                break;
            }
        }
        return right - left - 1;
    }
    
    // Bonus: Return all longest palindromes if there are multiple
    std::vector<std::string> allLongestPalindromes(std::string s) {
        std::vector<std::string> result;
        if (s.empty()) return result;
        
        int maxLen = 0;
        
        // First pass: find maximum length
        for (int i = 0; i < s.length(); i++) {
            int len1 = expandAroundCenter(s, i, i);
            int len2 = expandAroundCenter(s, i, i + 1);
            maxLen = std::max(maxLen, std::max(len1, len2));
        }
        
        // Second pass: collect all palindromes of maximum length
        for (int i = 0; i < s.length(); i++) {
            // Check odd length
            if (expandAroundCenter(s, i, i) == maxLen) {
                int start = i - (maxLen - 1) / 2;
                std::string palindrome = s.substr(start, maxLen);
                if (std::find(result.begin(), result.end(), palindrome) == result.end()) {
                    result.push_back(palindrome);
                }
            }
            
            // Check even length
            if (expandAroundCenter(s, i, i + 1) == maxLen) {
                int start = i - (maxLen - 2) / 2;
                std::string palindrome = s.substr(start, maxLen);
                if (std::find(result.begin(), result.end(), palindrome) == result.end()) {
                    result.push_back(palindrome);
                }
            }
        }
        
        return result;
    }
};

// Test function
void testLongestPalindrome() {
    Solution sol;
    
    std::vector<std::string> testCases = {
        "babad",       // Expected: "bab" or "aba"
        "cbbd",        // Expected: "bb"
        "a",           // Expected: "a"
        "ac",          // Expected: "a" or "c"
        "racecar",     // Expected: "racecar"
        "abcdcba",     // Expected: "abcdcba"
        "abacabad",    // Expected: "abacaba"
        "",            // Expected: ""
        "bb",          // Expected: "bb"
        "ccc",         // Expected: "ccc"
        "abacabadabacaba", // Expected: "abacabadabacaba"
    };
    
    std::cout << "Testing Longest Palindromic Substring:\n";
    std::cout << "=====================================\n";
    
    for (const auto& test : testCases) {
        std::string result1 = sol.longestPalindrome(test);
        std::string result2 = sol.longestPalindromeDP(test);
        std::string result3 = sol.longestPalindromeManacher(test);
        std::string result4 = sol.longestPalindromeBruteForce(test);
        std::string result5 = sol.longestPalindromeOptimized(test);
        std::vector<std::string> allResults = sol.allLongestPalindromes(test);
        
        std::cout << "Input: \"" << test << "\"\n";
        std::cout << "Expand Around Center: \"" << result1 << "\"\n";
        std::cout << "Dynamic Programming: \"" << result2 << "\"\n";
        std::cout << "Manacher's Algorithm: \"" << result3 << "\"\n";
        std::cout << "Brute Force: \"" << result4 << "\"\n";
        std::cout << "Optimized: \"" << result5 << "\"\n";
        std::cout << "All longest palindromes: ";
        for (const auto& p : allResults) {
            std::cout << "\"" << p << "\" ";
        }
        std::cout << "\n---\n";
    }
}

int main() {
    testLongestPalindrome();
    return 0;
}

/*
 * Key Insights:
 * 1. Expand around center is intuitive and efficient for most cases
 * 2. Consider both odd and even length palindromes
 * 3. Dynamic programming builds solution bottom-up
 * 4. Manacher's algorithm is optimal but complex to implement
 * 
 * Time Complexity Comparison:
 * - Expand Around Center: O(n²) - for each center, expand outward
 * - Dynamic Programming: O(n²) - fill DP table
 * - Manacher's Algorithm: O(n) - linear time with preprocessing
 * - Brute Force: O(n³) - check all substrings
 * 
 * Space Complexity:
 * - Expand Around Center: O(1) - constant space
 * - Dynamic Programming: O(n²) - DP table
 * - Manacher's Algorithm: O(n) - preprocessed string and auxiliary array
 * - Brute Force: O(1) - constant space
 * 
 * Common Mistakes:
 * 1. Forgetting to handle even length palindromes
 * 2. Off-by-one errors in substring extraction
 * 3. Not handling edge cases (empty string, single character)
 * 4. Incorrect center calculation for even length palindromes
 * 
 * Follow-up Questions:
 * 1. What if we need to find all palindromic substrings?
 * 2. What if we need the k longest palindromes?
 * 3. What if we want to modify the string to make it a palindrome?
 * 4. What if we need to handle case-insensitive palindromes?
 */