/*
 * LeetCode 14: Longest Common Prefix
 * 
 * Problem: Write a function to find the longest common prefix string amongst an array of strings.
 * If there is no common prefix, return an empty string "".
 * 
 * Examples:
 * Input: strs = ["flower","flow","flight"]
 * Output: "fl"
 * 
 * Input: strs = ["dog","racecar","car"]
 * Output: ""
 * 
 * Companies: Amazon, Google, Facebook, Microsoft, Apple
 * Difficulty: Easy
 * Pattern: String Comparison
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Solution {
public:
    // Approach 1: Vertical Scanning (Character by Character)
    // Time: O(S), Space: O(1) where S is sum of all characters
    std::string longestCommonPrefix(std::vector<std::string>& strs) {
        if (strs.empty()) return "";
        
        for (int i = 0; i < strs[0].length(); i++) {
            char c = strs[0][i];
            for (int j = 1; j < strs.size(); j++) {
                if (i >= strs[j].length() || strs[j][i] != c) {
                    return strs[0].substr(0, i);
                }
            }
        }
        
        return strs[0];
    }
    
    // Approach 2: Horizontal Scanning (String by String)
    // Time: O(S), Space: O(1)
    std::string longestCommonPrefixHorizontal(std::vector<std::string>& strs) {
        if (strs.empty()) return "";
        
        std::string prefix = strs[0];
        
        for (int i = 1; i < strs.size(); i++) {
            while (strs[i].find(prefix) != 0) {
                prefix = prefix.substr(0, prefix.length() - 1);
                if (prefix.empty()) return "";
            }
        }
        
        return prefix;
    }
    
    // Approach 3: Divide and Conquer
    // Time: O(S), Space: O(m*log(n)) where m is length of longest string
    std::string longestCommonPrefixDivideConquer(std::vector<std::string>& strs) {
        if (strs.empty()) return "";
        return longestCommonPrefixHelper(strs, 0, strs.size() - 1);
    }
    
private:
    std::string longestCommonPrefixHelper(std::vector<std::string>& strs, int left, int right) {
        if (left == right) {
            return strs[left];
        }
        
        int mid = (left + right) / 2;
        std::string leftLCP = longestCommonPrefixHelper(strs, left, mid);
        std::string rightLCP = longestCommonPrefixHelper(strs, mid + 1, right);
        
        return commonPrefix(leftLCP, rightLCP);
    }
    
    std::string commonPrefix(const std::string& left, const std::string& right) {
        int minLen = std::min(left.length(), right.length());
        for (int i = 0; i < minLen; i++) {
            if (left[i] != right[i]) {
                return left.substr(0, i);
            }
        }
        return left.substr(0, minLen);
    }
    
public:
    // Approach 4: Binary Search
    // Time: O(S*log(m)), Space: O(1) where m is length of shortest string
    std::string longestCommonPrefixBinarySearch(std::vector<std::string>& strs) {
        if (strs.empty()) return "";
        
        int minLen = strs[0].length();
        for (const auto& str : strs) {
            minLen = std::min(minLen, (int)str.length());
        }
        
        int low = 1, high = minLen;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (isCommonPrefix(strs, mid)) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        
        return strs[0].substr(0, (low + high) / 2);
    }
    
private:
    bool isCommonPrefix(std::vector<std::string>& strs, int len) {
        std::string prefix = strs[0].substr(0, len);
        for (int i = 1; i < strs.size(); i++) {
            if (!strs[i].substr(0, len).compare(prefix) != 0) {
                return false;
            }
        }
        return true;
    }
    
public:
    // Approach 5: Trie-based Solution
    // Time: O(S), Space: O(S)
    std::string longestCommonPrefixTrie(std::vector<std::string>& strs) {
        if (strs.empty()) return "";
        
        TrieNode* root = buildTrie(strs);
        std::string result = "";
        
        TrieNode* current = root;
        while (current->children.size() == 1 && !current->isEnd) {
            for (auto& pair : current->children) {
                result += pair.first;
                current = pair.second;
            }
        }
        
        // Clean up memory
        deleteTrie(root);
        
        return result;
    }
    
private:
    struct TrieNode {
        std::unordered_map<char, TrieNode*> children;
        bool isEnd;
        
        TrieNode() : isEnd(false) {}
    };
    
    TrieNode* buildTrie(std::vector<std::string>& strs) {
        TrieNode* root = new TrieNode();
        
        for (const std::string& str : strs) {
            TrieNode* current = root;
            for (char c : str) {
                if (current->children.find(c) == current->children.end()) {
                    current->children[c] = new TrieNode();
                }
                current = current->children[c];
            }
            current->isEnd = true;
        }
        
        return root;
    }
    
    void deleteTrie(TrieNode* node) {
        if (!node) return;
        for (auto& pair : node->children) {
            deleteTrie(pair.second);
        }
        delete node;
    }
    
public:
    // Approach 6: Using STL algorithms
    // Time: O(S), Space: O(1)
    std::string longestCommonPrefixSTL(std::vector<std::string>& strs) {
        if (strs.empty()) return "";
        
        // Find the lexicographically smallest and largest strings
        auto minmax = std::minmax_element(strs.begin(), strs.end());
        std::string& minStr = *minmax.first;
        std::string& maxStr = *minmax.second;
        
        // Find common prefix between min and max
        int i = 0;
        while (i < minStr.length() && i < maxStr.length() && minStr[i] == maxStr[i]) {
            i++;
        }
        
        return minStr.substr(0, i);
    }
    
    // Approach 7: Optimized with early termination
    // Time: O(S), Space: O(1)
    std::string longestCommonPrefixOptimized(std::vector<std::string>& strs) {
        if (strs.empty()) return "";
        if (strs.size() == 1) return strs[0];
        
        // Find shortest string length for early termination
        int minLen = strs[0].length();
        for (const auto& str : strs) {
            minLen = std::min(minLen, (int)str.length());
            if (minLen == 0) return ""; // Early termination
        }
        
        for (int i = 0; i < minLen; i++) {
            char c = strs[0][i];
            for (int j = 1; j < strs.size(); j++) {
                if (strs[j][i] != c) {
                    return strs[0].substr(0, i);
                }
            }
        }
        
        return strs[0].substr(0, minLen);
    }
    
    // Bonus: Find longest common suffix
    std::string longestCommonSuffix(std::vector<std::string>& strs) {
        if (strs.empty()) return "";
        
        int minLen = strs[0].length();
        for (const auto& str : strs) {
            minLen = std::min(minLen, (int)str.length());
        }
        
        for (int i = 1; i <= minLen; i++) {
            char c = strs[0][strs[0].length() - i];
            for (int j = 1; j < strs.size(); j++) {
                if (strs[j][strs[j].length() - i] != c) {
                    return strs[0].substr(strs[0].length() - i + 1);
                }
            }
        }
        
        return strs[0].substr(strs[0].length() - minLen);
    }
};

// Test function
void testLongestCommonPrefix() {
    Solution sol;
    
    std::vector<std::vector<std::string>> testCases = {
        {"flower", "flow", "flight"},     // Expected: "fl"
        {"dog", "racecar", "car"},        // Expected: ""
        {"interspecies", "interstellar", "interstate"}, // Expected: "inters"
        {"throne", "throne"},             // Expected: "throne"
        {""},                             // Expected: ""
        {"a"},                            // Expected: "a"
        {"ab", "a"},                      // Expected: "a"
        {"abcdefgh", "abcdefg", "abcdef"}, // Expected: "abcdef"
        {"", "b"},                        // Expected: ""
        {"abc", "abc", "abc"},            // Expected: "abc"
    };
    
    std::cout << "Testing Longest Common Prefix:\n";
    std::cout << "==============================\n";
    
    for (auto testCase : testCases) {
        auto strs1 = testCase, strs2 = testCase, strs3 = testCase;
        auto strs4 = testCase, strs5 = testCase, strs6 = testCase, strs7 = testCase;
        
        std::string result1 = sol.longestCommonPrefix(strs1);
        std::string result2 = sol.longestCommonPrefixHorizontal(strs2);
        std::string result3 = sol.longestCommonPrefixDivideConquer(strs3);
        std::string result4 = sol.longestCommonPrefixBinarySearch(strs4);
        std::string result5 = sol.longestCommonPrefixSTL(strs5);
        std::string result6 = sol.longestCommonPrefixOptimized(strs6);
        std::string suffix = sol.longestCommonSuffix(strs7);
        
        std::cout << "Input: [";
        for (int i = 0; i < testCase.size(); i++) {
            std::cout << "\"" << testCase[i] << "\"";
            if (i < testCase.size() - 1) std::cout << ", ";
        }
        std::cout << "]\n";
        
        std::cout << "Vertical Scanning: \"" << result1 << "\"\n";
        std::cout << "Horizontal Scanning: \"" << result2 << "\"\n";
        std::cout << "Divide & Conquer: \"" << result3 << "\"\n";
        std::cout << "Binary Search: \"" << result4 << "\"\n";
        std::cout << "STL Algorithm: \"" << result5 << "\"\n";
        std::cout << "Optimized: \"" << result6 << "\"\n";
        std::cout << "Common Suffix: \"" << suffix << "\"\n";
        std::cout << "---\n";
    }
}

int main() {
    testLongestCommonPrefix();
    return 0;
}

/*
 * Key Insights:
 * 1. Vertical scanning is most intuitive - compare character by character
 * 2. Horizontal scanning reduces the prefix with each string
 * 3. Binary search optimizes by searching for the length
 * 4. Divide & conquer breaks down the problem recursively
 * 
 * Time Complexity Comparison:
 * - Vertical Scanning: O(S) where S is sum of all characters
 * - Horizontal Scanning: O(S) 
 * - Divide & Conquer: O(S) but with recursion overhead
 * - Binary Search: O(S * log(m)) where m is shortest string length
 * - STL Algorithm: O(S) leveraging lexicographic properties
 * 
 * Space Complexity:
 * - Most approaches: O(1) constant space
 * - Divide & Conquer: O(m * log(n)) due to recursion stack
 * - Trie approach: O(S) for storing all strings
 * 
 * Common Mistakes:
 * 1. Not handling empty input array
 * 2. Not checking for empty strings in the array
 * 3. Index out of bounds when comparing characters
 * 4. Not considering strings of different lengths
 * 
 * Follow-up Questions:
 * 1. What if we need to find the longest common subsequence instead?
 * 2. What if we want to find common prefix of suffixes?
 * 3. What if we need to handle case-insensitive comparison?
 * 4. What if we want to find all common prefixes above a certain length?
 */