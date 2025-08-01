/*
 * LeetCode 20: Valid Parentheses
 * 
 * Problem: Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', 
 * determine if the input string is valid.
 * 
 * An input string is valid if:
 * 1. Open brackets must be closed by the same type of brackets.
 * 2. Open brackets must be closed in the correct order.
 * 3. Every close bracket has a corresponding open bracket of the same type.
 * 
 * Companies: Amazon, Google, Facebook, Microsoft, Apple
 * Difficulty: Easy
 * Pattern: Stack
 */

#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

class Solution {
public:
    // Approach 1: Stack with HashMap (Most Common)
    // Time: O(n), Space: O(n)
    bool isValid(std::string s) {
        std::stack<char> st;
        std::unordered_map<char, char> mapping = {
            {')', '('},
            {'}', '{'},
            {']', '['}
        };
        
        for (char c : s) {
            if (mapping.find(c) != mapping.end()) {
                // Closing bracket
                if (st.empty() || st.top() != mapping[c]) {
                    return false;
                }
                st.pop();
            } else {
                // Opening bracket
                st.push(c);
            }
        }
        
        return st.empty();
    }
    
    // Approach 2: Stack without HashMap
    // Time: O(n), Space: O(n)
    bool isValidSimple(std::string s) {
        std::stack<char> st;
        
        for (char c : s) {
            if (c == '(' || c == '{' || c == '[') {
                st.push(c);
            } else {
                if (st.empty()) return false;
                
                char top = st.top();
                st.pop();
                
                if ((c == ')' && top != '(') ||
                    (c == '}' && top != '{') ||
                    (c == ']' && top != '[')) {
                    return false;
                }
            }
        }
        
        return st.empty();
    }
    
    // Approach 3: Stack with switch statement
    // Time: O(n), Space: O(n)
    bool isValidSwitch(std::string s) {
        std::stack<char> st;
        
        for (char c : s) {
            switch (c) {
                case '(':
                case '{':
                case '[':
                    st.push(c);
                    break;
                case ')':
                    if (st.empty() || st.top() != '(') return false;
                    st.pop();
                    break;
                case '}':
                    if (st.empty() || st.top() != '{') return false;
                    st.pop();
                    break;
                case ']':
                    if (st.empty() || st.top() != '[') return false;
                    st.pop();
                    break;
                default:
                    // Invalid character
                    return false;
            }
        }
        
        return st.empty();
    }
    
    // Approach 4: String replacement (Less efficient but clever)
    // Time: O(n²), Space: O(n)
    bool isValidReplacement(std::string s) {
        while (s.find("()") != std::string::npos ||
               s.find("{}") != std::string::npos ||
               s.find("[]") != std::string::npos) {
            
            size_t pos = s.find("()");
            if (pos != std::string::npos) {
                s.erase(pos, 2);
                continue;
            }
            
            pos = s.find("{}");
            if (pos != std::string::npos) {
                s.erase(pos, 2);
                continue;
            }
            
            pos = s.find("[]");
            if (pos != std::string::npos) {
                s.erase(pos, 2);
                continue;
            }
        }
        
        return s.empty();
    }
    
    // Approach 5: Array as stack (for better performance)
    // Time: O(n), Space: O(n)
    bool isValidArray(std::string s) {
        std::vector<char> stack;
        
        for (char c : s) {
            if (c == '(' || c == '{' || c == '[') {
                stack.push_back(c);
            } else {
                if (stack.empty()) return false;
                
                char last = stack.back();
                stack.pop_back();
                
                if ((c == ')' && last != '(') ||
                    (c == '}' && last != '{') ||
                    (c == ']' && last != '[')) {
                    return false;
                }
            }
        }
        
        return stack.empty();
    }
};

// Test function
void testValidParentheses() {
    Solution sol;
    
    std::vector<std::string> testCases = {
        "()",        // true
        "()[]{}",    // true
        "(]",        // false
        "([)]",      // false
        "{[]}",      // true
        "",          // true (edge case)
        "(",         // false
        ")",         // false
        "(((",       // false
        ")))",       // false
        "({[]})",    // true
    };
    
    std::cout << "Testing Valid Parentheses:\n";
    std::cout << "==========================\n";
    
    for (const auto& test : testCases) {
        bool result1 = sol.isValid(test);
        bool result2 = sol.isValidSimple(test);
        bool result3 = sol.isValidSwitch(test);
        bool result4 = sol.isValidReplacement(test);
        bool result5 = sol.isValidArray(test);
        
        std::cout << "Input: \"" << test << "\"\n";
        std::cout << "HashMap approach: " << (result1 ? "true" : "false") << "\n";
        std::cout << "Simple approach: " << (result2 ? "true" : "false") << "\n";
        std::cout << "Switch approach: " << (result3 ? "true" : "false") << "\n";
        std::cout << "Replacement approach: " << (result4 ? "true" : "false") << "\n";
        std::cout << "Array approach: " << (result5 ? "true" : "false") << "\n";
        std::cout << "---\n";
    }
}

int main() {
    testValidParentheses();
    return 0;
}

/*
 * Key Insights:
 * 1. Stack is the natural data structure for this problem
 * 2. We can use HashMap for cleaner code or switch/if statements for efficiency
 * 3. Always check if stack is empty before popping
 * 4. The string is valid only if the stack is empty at the end
 * 
 * Common Mistakes:
 * 1. Not checking if stack is empty before accessing top
 * 2. Forgetting to check if stack is empty at the end
 * 3. Not handling edge cases like empty strings
 * 
 * Follow-up Questions:
 * 1. What if we have other types of brackets?
 * 2. What if we need to return the position of the first invalid bracket?
 * 3. What if we need to handle nested structures with other characters?
 */