/*
 * LeetCode 49: Group Anagrams
 * 
 * Problem: Given an array of strings strs, group the anagrams together. 
 * You can return the answer in any order.
 * 
 * An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase,
 * typically using all the original letters exactly once.
 * 
 * Examples:
 * Input: strs = ["eat","tea","tan","ate","nat","bat"]
 * Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
 * 
 * Input: strs = [""]
 * Output: [[""]]
 * 
 * Input: strs = ["a"]
 * Output: [["a"]]
 * 
 * Companies: Amazon, Google, Facebook, Microsoft, Uber
 * Difficulty: Medium
 * Pattern: Hash Table, Sorting
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <array>

class Solution {
public:
    // Approach 1: Sorting as Key
    // Time: O(n * k log k), Space: O(n * k) where n = number of strings, k = max length
    std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
        std::unordered_map<std::string, std::vector<std::string>> groups;
        
        for (const std::string& str : strs) {
            std::string key = str;
            std::sort(key.begin(), key.end());
            groups[key].push_back(str);
        }
        
        std::vector<std::vector<std::string>> result;
        for (const auto& pair : groups) {
            result.push_back(pair.second);
        }
        
        return result;
    }
    
    // Approach 2: Character Frequency as Key
    // Time: O(n * k), Space: O(n * k)
    std::vector<std::vector<std::string>> groupAnagramsFrequency(std::vector<std::string>& strs) {
        std::unordered_map<std::string, std::vector<std::string>> groups;
        
        for (const std::string& str : strs) {
            std::string key = getFrequencyKey(str);
            groups[key].push_back(str);
        }
        
        std::vector<std::vector<std::string>> result;
        for (const auto& pair : groups) {
            result.push_back(pair.second);
        }
        
        return result;
    }
    
private:
    std::string getFrequencyKey(const std::string& str) {
        std::array<int, 26> count = {0};
        for (char c : str) {
            count[c - 'a']++;
        }
        
        std::string key = "";
        for (int i = 0; i < 26; i++) {
            if (count[i] > 0) {
                key += std::string(1, 'a' + i) + std::to_string(count[i]);
            }
        }
        return key;
    }
    
public:
    // Approach 3: Prime Number Hashing
    // Time: O(n * k), Space: O(n * k)
    // Note: Can overflow for very long strings
    std::vector<std::vector<std::string>> groupAnagramsPrime(std::vector<std::string>& strs) {
        std::unordered_map<long long, std::vector<std::string>> groups;
        
        // Prime numbers for each letter a-z
        std::vector<int> primes = {
            2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 
            59, 61, 67, 71, 73, 79, 83, 89, 97, 101
        };
        
        for (const std::string& str : strs) {
            long long hash = 1;
            for (char c : str) {
                hash *= primes[c - 'a'];
            }
            groups[hash].push_back(str);
        }
        
        std::vector<std::vector<std::string>> result;
        for (const auto& pair : groups) {
            result.push_back(pair.second);
        }
        
        return result;
    }
    
    // Approach 4: Character Count Array as Key
    // Time: O(n * k), Space: O(n * k)
    std::vector<std::vector<std::string>> groupAnagramsArray(std::vector<std::string>& strs) {
        std::map<std::array<int, 26>, std::vector<std::string>> groups;
        
        for (const std::string& str : strs) {
            std::array<int, 26> count = {0};
            for (char c : str) {
                count[c - 'a']++;
            }
            groups[count].push_back(str);
        }
        
        std::vector<std::vector<std::string>> result;
        for (const auto& pair : groups) {
            result.push_back(pair.second);
        }
        
        return result;
    }
    
    // Approach 5: Custom Hash Function
    // Time: O(n * k), Space: O(n * k)
    std::vector<std::vector<std::string>> groupAnagramsCustomHash(std::vector<std::string>& strs) {
        std::unordered_map<size_t, std::vector<std::string>> groups;
        
        for (const std::string& str : strs) {
            size_t hash = computeAnagramHash(str);
            groups[hash].push_back(str);
        }
        
        std::vector<std::vector<std::string>> result;
        for (const auto& pair : groups) {
            result.push_back(pair.second);
        }
        
        return result;
    }
    
private:
    size_t computeAnagramHash(const std::string& str) {
        std::array<int, 26> count = {0};
        for (char c : str) {
            count[c - 'a']++;
        }
        
        size_t hash = 0;
        for (int i = 0; i < 26; i++) {
            // Use polynomial rolling hash
            hash = hash * 31 + count[i];
        }
        return hash;
    }
    
public:
    // Approach 6: Optimized with String Builder
    // Time: O(n * k), Space: O(n * k)
    std::vector<std::vector<std::string>> groupAnagramsOptimized(std::vector<std::string>& strs) {
        std::unordered_map<std::string, std::vector<std::string>> groups;
        
        for (const std::string& str : strs) {
            std::string key = buildFrequencyKey(str);
            groups[key].push_back(str);
        }
        
        std::vector<std::vector<std::string>> result;
        result.reserve(groups.size());
        for (auto& pair : groups) {
            result.push_back(std::move(pair.second));
        }
        
        return result;
    }
    
private:
    std::string buildFrequencyKey(const std::string& str) {
        std::array<int, 26> count = {0};
        for (char c : str) {
            count[c - 'a']++;
        }
        
        std::string key;
        key.reserve(52); // Rough estimate for key size
        
        for (int i = 0; i < 26; i++) {
            if (count[i] > 0) {
                key += char('a' + i);
                key += std::to_string(count[i]);
            }
        }
        return key;
    }
    
public:
    // Approach 7: Using std::multiset for deterministic ordering
    // Time: O(n * k log k), Space: O(n * k)
    std::vector<std::vector<std::string>> groupAnagramsDeterministic(std::vector<std::string>& strs) {
        std::map<std::string, std::vector<std::string>> groups;
        
        for (const std::string& str : strs) {
            std::string key = str;
            std::sort(key.begin(), key.end());
            groups[key].push_back(str);
        }
        
        std::vector<std::vector<std::string>> result;
        for (auto& pair : groups) {
            std::sort(pair.second.begin(), pair.second.end()); // Sort within groups
            result.push_back(std::move(pair.second));
        }
        
        return result;
    }
    
    // Bonus: Find the largest group of anagrams
    std::vector<std::string> largestAnagramGroup(std::vector<std::string>& strs) {
        std::unordered_map<std::string, std::vector<std::string>> groups;
        
        for (const std::string& str : strs) {
            std::string key = str;
            std::sort(key.begin(), key.end());
            groups[key].push_back(str);
        }
        
        std::vector<std::string> largest;
        for (const auto& pair : groups) {
            if (pair.second.size() > largest.size()) {
                largest = pair.second;
            }
        }
        
        return largest;
    }
    
    // Bonus: Count total number of anagram groups
    int countAnagramGroups(std::vector<std::string>& strs) {
        std::unordered_map<std::string, int> groups;
        
        for (const std::string& str : strs) {
            std::string key = str;
            std::sort(key.begin(), key.end());
            groups[key]++;
        }
        
        return groups.size();
    }
    
    // Bonus: Group anagrams with minimum group size
    std::vector<std::vector<std::string>> groupAnagramsMinSize(std::vector<std::string>& strs, int minSize) {
        std::unordered_map<std::string, std::vector<std::string>> groups;
        
        for (const std::string& str : strs) {
            std::string key = str;
            std::sort(key.begin(), key.end());
            groups[key].push_back(str);
        }
        
        std::vector<std::vector<std::string>> result;
        for (const auto& pair : groups) {
            if (pair.second.size() >= minSize) {
                result.push_back(pair.second);
            }
        }
        
        return result;
    }
};

// Test function
void testGroupAnagrams() {
    Solution sol;
    
    std::vector<std::vector<std::string>> testCases = {
        {"eat", "tea", "tan", "ate", "nat", "bat"},
        {""},
        {"a"},
        {"abc", "bca", "cab", "xyz", "zyx", "yxz"},
        {"ab", "ba", "cd", "dc", "ef"},
        {"listen", "silent", "hello", "world"},
        {"rat", "tar", "art", "star", "tars", "rats"},
    };
    
    std::cout << "Testing Group Anagrams:\n";
    std::cout << "======================\n";
    
    for (auto testCase : testCases) {
        auto strs1 = testCase, strs2 = testCase, strs3 = testCase;
        auto strs4 = testCase, strs5 = testCase, strs6 = testCase, strs7 = testCase;
        
        auto result1 = sol.groupAnagrams(strs1);
        auto result2 = sol.groupAnagramsFrequency(strs2);
        auto result3 = sol.groupAnagramsPrime(strs3);
        auto result4 = sol.groupAnagramsArray(strs4);
        auto result5 = sol.groupAnagramsCustomHash(strs5);
        auto result6 = sol.groupAnagramsOptimized(strs6);
        auto result7 = sol.groupAnagramsDeterministic(strs7);
        
        std::cout << "Input: [";
        for (int i = 0; i < testCase.size(); i++) {
            std::cout << "\"" << testCase[i] << "\"";
            if (i < testCase.size() - 1) std::cout << ", ";
        }
        std::cout << "]\n";
        
        std::cout << "Sorting approach groups: " << result1.size() << "\n";
        std::cout << "Frequency approach groups: " << result2.size() << "\n";
        std::cout << "Prime approach groups: " << result3.size() << "\n";
        std::cout << "Array approach groups: " << result4.size() << "\n";
        std::cout << "Custom hash approach groups: " << result5.size() << "\n";
        std::cout << "Optimized approach groups: " << result6.size() << "\n";
        std::cout << "Deterministic approach groups: " << result7.size() << "\n";
        
        // Show the actual groups for the first approach
        std::cout << "Groups (Sorting): ";
        for (const auto& group : result1) {
            std::cout << "[";
            for (int i = 0; i < group.size(); i++) {
                std::cout << "\"" << group[i] << "\"";
                if (i < group.size() - 1) std::cout << ", ";
            }
            std::cout << "] ";
        }
        std::cout << "\n";
        
        // Test bonus functions
        auto largest = sol.largestAnagramGroup(testCase);
        int groupCount = sol.countAnagramGroups(testCase);
        auto minSize2 = sol.groupAnagramsMinSize(testCase, 2);
        
        std::cout << "Largest anagram group size: " << largest.size() << "\n";
        std::cout << "Total anagram groups: " << groupCount << "\n";
        std::cout << "Groups with min size 2: " << minSize2.size() << "\n";
        std::cout << "---\n";
    }
}

int main() {
    testGroupAnagrams();
    return 0;
}

/*
 * Key Insights:
 * 1. Anagrams have identical sorted character sequences
 * 2. Anagrams have identical character frequency distributions
 * 3. Hash table groups strings by their anagram signature
 * 4. Choice of key representation affects performance and memory
 * 
 * Time Complexity Comparison:
 * - Sorting approach: O(n * k log k) - dominated by sorting each string
 * - Frequency approach: O(n * k) - linear scan to build frequency key
 * - Prime approach: O(n * k) - but with potential overflow issues
 * - Array approach: O(n * k) - using fixed-size array as key
 * 
 * Space Complexity:
 * - All approaches: O(n * k) for storing groups and keys
 * - Additional space for keys varies by approach
 * 
 * Key Generation Strategies:
 * 1. Sorted string: Simple but requires O(k log k) time
 * 2. Frequency string: Linear time but longer keys
 * 3. Prime product: Compact but overflow risk
 * 4. Array hash: Good balance of time and space
 * 
 * Common Mistakes:
 * 1. Not handling empty strings
 * 2. Overflow in prime number approach
 * 3. Inefficient key generation
 * 4. Not considering memory usage for large inputs
 * 
 * Follow-up Questions:
 * 1. What if we need to handle Unicode characters?
 * 2. What if we want to group by partial anagrams?
 * 3. What if we need to stream the input?
 * 4. What if we want case-insensitive grouping?
 * 5. How to handle very large datasets that don't fit in memory?
 */