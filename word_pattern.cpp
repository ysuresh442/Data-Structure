/*
 * LeetCode 290: Word Pattern
 * 
 * Problem: Given a pattern and a string s, find if s follows the same pattern.
 * Here follow means a full match, such that there is a bijection between a letter in pattern 
 * and a non-empty word in s.
 * 
 * Examples:
 * Input: pattern = "abba", s = "dog cat cat dog"
 * Output: true
 * 
 * Input: pattern = "abba", s = "dog cat cat fish"
 * Output: false
 * 
 * Input: pattern = "aaaa", s = "dog cat cat dog"
 * Output: false
 * 
 * Companies: Amazon, Google, Microsoft
 * Difficulty: Easy
 * Pattern: Hash Table, String
 */

#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <sstream>
#include <chrono>

class Solution {
public:
    // Approach 1: Two Hash Maps (bidirectional mapping)
    // Time: O(n + m), Space: O(w) where w is number of unique words
    bool wordPattern(std::string pattern, std::string s) {
        std::vector<std::string> words = splitString(s);
        
        if (pattern.length() != words.size()) return false;
        
        std::unordered_map<char, std::string> charToWord;
        std::unordered_map<std::string, char> wordToChar;
        
        for (int i = 0; i < pattern.length(); i++) {
            char c = pattern[i];
            const std::string& word = words[i];
            
            // Check char -> word mapping
            if (charToWord.find(c) != charToWord.end()) {
                if (charToWord[c] != word) return false;
            } else {
                charToWord[c] = word;
            }
            
            // Check word -> char mapping
            if (wordToChar.find(word) != wordToChar.end()) {
                if (wordToChar[word] != c) return false;
            } else {
                wordToChar[word] = c;
            }
        }
        
        return true;
    }
    
    // Approach 2: Single Hash Map with Set
    // Time: O(n + m), Space: O(w)
    bool wordPatternWithSet(std::string pattern, std::string s) {
        std::vector<std::string> words = splitString(s);
        
        if (pattern.length() != words.size()) return false;
        
        std::unordered_map<char, std::string> mapping;
        std::unordered_set<std::string> usedWords;
        
        for (int i = 0; i < pattern.length(); i++) {
            char c = pattern[i];
            const std::string& word = words[i];
            
            if (mapping.find(c) != mapping.end()) {
                if (mapping[c] != word) return false;
            } else {
                if (usedWords.count(word)) return false; // Word already mapped
                mapping[c] = word;
                usedWords.insert(word);
            }
        }
        
        return true;
    }
    
    // Approach 3: Index-based comparison
    // Time: O(n + m), Space: O(w)
    bool wordPatternIndices(std::string pattern, std::string s) {
        std::vector<std::string> words = splitString(s);
        
        if (pattern.length() != words.size()) return false;
        
        std::unordered_map<char, int> charFirstIndex;
        std::unordered_map<std::string, int> wordFirstIndex;
        
        for (int i = 0; i < pattern.length(); i++) {
            char c = pattern[i];
            const std::string& word = words[i];
            
            int charIndex = charFirstIndex.count(c) ? charFirstIndex[c] : i;
            int wordIndex = wordFirstIndex.count(word) ? wordFirstIndex[word] : i;
            
            if (charIndex != wordIndex) return false;
            
            charFirstIndex[c] = charIndex;
            wordFirstIndex[word] = wordIndex;
        }
        
        return true;
    }
    
    // Approach 4: String stream parsing
    // Time: O(n + m), Space: O(w)
    bool wordPatternStream(std::string pattern, std::string s) {
        std::istringstream stream(s);
        std::string word;
        std::vector<std::string> words;
        
        while (stream >> word) {
            words.push_back(word);
        }
        
        if (pattern.length() != words.size()) return false;
        
        std::unordered_map<char, std::string> charToWord;
        std::unordered_set<std::string> usedWords;
        
        for (int i = 0; i < pattern.length(); i++) {
            char c = pattern[i];
            const std::string& w = words[i];
            
            auto it = charToWord.find(c);
            if (it != charToWord.end()) {
                if (it->second != w) return false;
            } else {
                if (usedWords.count(w)) return false;
                charToWord[c] = w;
                usedWords.insert(w);
            }
        }
        
        return true;
    }
    
    // Approach 5: Optimized early termination
    // Time: O(n + m), Space: O(w)
    bool wordPatternOptimized(std::string pattern, std::string s) {
        std::vector<std::string> words = splitStringFast(s);
        
        if (pattern.length() != words.size()) return false;
        
        // Quick check: if pattern has unique chars != unique words, return false
        std::unordered_set<char> uniqueChars(pattern.begin(), pattern.end());
        std::unordered_set<std::string> uniqueWords(words.begin(), words.end());
        if (uniqueChars.size() != uniqueWords.size()) return false;
        
        std::unordered_map<char, std::string> mapping;
        
        for (int i = 0; i < pattern.length(); i++) {
            char c = pattern[i];
            const std::string& word = words[i];
            
            auto it = mapping.find(c);
            if (it != mapping.end()) {
                if (it->second != word) return false;
            } else {
                mapping[c] = word;
            }
        }
        
        return true;
    }
    
private:
    // Helper function to split string by spaces
    std::vector<std::string> splitString(const std::string& s) {
        std::vector<std::string> words;
        std::string word;
        
        for (char c : s) {
            if (c == ' ') {
                if (!word.empty()) {
                    words.push_back(word);
                    word.clear();
                }
            } else {
                word += c;
            }
        }
        
        if (!word.empty()) {
            words.push_back(word);
        }
        
        return words;
    }
    
    // Optimized split function
    std::vector<std::string> splitStringFast(const std::string& s) {
        std::vector<std::string> words;
        int start = 0;
        
        for (int i = 0; i <= s.length(); i++) {
            if (i == s.length() || s[i] == ' ') {
                if (i > start) {
                    words.push_back(s.substr(start, i - start));
                }
                start = i + 1;
            }
        }
        
        return words;
    }
};

/*
 * Complexity Analysis:
 * 
 * Approach 1 (Two Hash Maps):
 * - Time: O(n + m) where n = pattern length, m = string length
 * - Space: O(w) where w = number of unique words
 * 
 * Approach 2 (Hash Map + Set):
 * - Time: O(n + m) - same as approach 1
 * - Space: O(w) - mapping + used words set
 * 
 * Approach 3 (Index-based):
 * - Time: O(n + m) - compare first occurrence indices
 * - Space: O(w) - index mappings
 * 
 * Approach 4 (String Stream):
 * - Time: O(n + m) - parsing + checking
 * - Space: O(w) - word storage + mappings
 * 
 * Approach 5 (Optimized):
 * - Time: O(n + m) - with early termination
 * - Space: O(w) - unique checks + mapping
 * 
 * Hash Table Optimization Tricks:
 * 1. Use bidirectional mapping for one-to-one correspondence
 * 2. Early termination if unique counts don't match
 * 3. Efficient string splitting using substr
 * 4. Use unordered_set for used word tracking
 * 5. Iterator-based hash map access for performance
 */

// Test helper functions
void testWordPattern() {
    Solution solution;
    
    // Test case 1: Valid pattern
    std::string pattern1 = "abba", s1 = "dog cat cat dog";
    std::cout << "Test 1 - pattern: \"" << pattern1 << "\", s: \"" << s1 << "\": " 
              << std::boolalpha << solution.wordPattern(pattern1, s1) 
              << " (expected: true)" << std::endl;
    
    // Test case 2: Invalid pattern - different word for same char
    std::string pattern2 = "abba", s2 = "dog cat cat fish";
    std::cout << "Test 2 - pattern: \"" << pattern2 << "\", s: \"" << s2 << "\": " 
              << std::boolalpha << solution.wordPattern(pattern2, s2) 
              << " (expected: false)" << std::endl;
    
    // Test case 3: Invalid pattern - same word for different chars
    std::string pattern3 = "aaaa", s3 = "dog cat cat dog";
    std::cout << "Test 3 - pattern: \"" << pattern3 << "\", s: \"" << s3 << "\": " 
              << std::boolalpha << solution.wordPattern(pattern3, s3) 
              << " (expected: false)" << std::endl;
    
    // Edge case: Single character and word
    std::string pattern4 = "a", s4 = "dog";
    std::cout << "Test 4 - pattern: \"" << pattern4 << "\", s: \"" << s4 << "\": " 
              << std::boolalpha << solution.wordPattern(pattern4, s4) 
              << " (expected: true)" << std::endl;
    
    // Edge case: Length mismatch
    std::string pattern5 = "abc", s5 = "dog cat";
    std::cout << "Test 5 - pattern: \"" << pattern5 << "\", s: \"" << s5 << "\": " 
              << std::boolalpha << solution.wordPattern(pattern5, s5) 
              << " (expected: false)" << std::endl;
    
    // Edge case: Multiple spaces
    std::string pattern6 = "ab", s6 = "dog  cat";
    std::cout << "Test 6 - pattern: \"" << pattern6 << "\", s: \"" << s6 << "\": " 
              << std::boolalpha << solution.wordPattern(pattern6, s6) 
              << " (expected: true)" << std::endl;
    
    // Complex case
    std::string pattern7 = "abcabc", s7 = "dog cat fish dog cat fish";
    std::cout << "Test 7 - pattern: \"" << pattern7 << "\", s: \"" << s7 << "\": " 
              << std::boolalpha << solution.wordPattern(pattern7, s7) 
              << " (expected: true)" << std::endl;
    
    // Performance comparison
    std::cout << "\nPerformance comparison:" << std::endl;
    
    // Large pattern and string
    std::string largePattern(10000, 'a');
    std::string largeS;
    for (int i = 0; i < 10000; i++) {
        if (i > 0) largeS += " ";
        largePattern[i] = 'a' + (i % 5); // Use 5 different characters
        largeS += "word" + std::to_string(i % 5); // 5 different words
    }
    
    auto start = std::chrono::high_resolution_clock::now();
    bool hashResult = solution.wordPattern(largePattern, largeS);
    auto end = std::chrono::high_resolution_clock::now();
    auto hashTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    start = std::chrono::high_resolution_clock::now();
    bool setResult = solution.wordPatternWithSet(largePattern, largeS);
    end = std::chrono::high_resolution_clock::now();
    auto setTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    start = std::chrono::high_resolution_clock::now();
    bool optimizedResult = solution.wordPatternOptimized(largePattern, largeS);
    end = std::chrono::high_resolution_clock::now();
    auto optimizedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Two Hash Maps: " << hashTime.count() << " μs, result: " 
              << std::boolalpha << hashResult << std::endl;
    std::cout << "Hash Map + Set: " << setTime.count() << " μs, result: " 
              << std::boolalpha << setResult << std::endl;
    std::cout << "Optimized: " << optimizedTime.count() << " μs, result: " 
              << std::boolalpha << optimizedResult << std::endl;
    
    // Correctness verification
    std::cout << "\nCorrectness verification:" << std::endl;
    std::string testPattern = "abab", testS = "dog cat dog cat";
    std::cout << "Test pattern: \"" << testPattern << "\", s: \"" << testS << "\"" << std::endl;
    std::cout << "Two Hash Maps: " << solution.wordPattern(testPattern, testS) << std::endl;
    std::cout << "Hash Map + Set: " << solution.wordPatternWithSet(testPattern, testS) << std::endl;
    std::cout << "Indices: " << solution.wordPatternIndices(testPattern, testS) << std::endl;
    std::cout << "Stream: " << solution.wordPatternStream(testPattern, testS) << std::endl;
    std::cout << "Optimized: " << solution.wordPatternOptimized(testPattern, testS) << std::endl;
}

int main() {
    testWordPattern();
    return 0;
}