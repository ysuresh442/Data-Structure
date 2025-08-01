/*
 * LeetCode 8: String to Integer (atoi)
 * 
 * Problem: Implement the myAtoi(string s) function, which converts a string to a 32-bit signed integer.
 * 
 * Algorithm:
 * 1. Read in and ignore any leading whitespace.
 * 2. Check if the next character is '-' or '+'. Read this character if it is either.
 * 3. Read in the next characters until a non-digit character or end of input is reached.
 * 4. Convert these digits into an integer.
 * 5. Clamp the integer to the 32-bit signed integer range [-2³¹, 2³¹ - 1].
 * 6. Return the integer as the final result.
 * 
 * Companies: Amazon, Google, Facebook, Microsoft, Apple
 * Difficulty: Medium
 * Pattern: String Parsing, Edge Case Handling
 */

#include <iostream>
#include <string>
#include <climits>
#include <cctype>

class Solution {
public:
    // Approach 1: Standard Implementation
    // Time: O(n), Space: O(1)
    int myAtoi(std::string s) {
        int i = 0;
        int sign = 1;
        long result = 0;
        
        // Skip leading whitespaces
        while (i < s.length() && s[i] == ' ') {
            i++;
        }
        
        // Handle sign
        if (i < s.length() && (s[i] == '+' || s[i] == '-')) {
            sign = (s[i] == '-') ? -1 : 1;
            i++;
        }
        
        // Process digits
        while (i < s.length() && std::isdigit(s[i])) {
            int digit = s[i] - '0';
            
            // Check for overflow before adding digit
            if (result > (LLONG_MAX - digit) / 10) {
                return (sign == 1) ? INT_MAX : INT_MIN;
            }
            
            result = result * 10 + digit;
            i++;
        }
        
        result *= sign;
        
        // Clamp to 32-bit integer range
        if (result > INT_MAX) return INT_MAX;
        if (result < INT_MIN) return INT_MIN;
        
        return (int)result;
    }
    
    // Approach 2: Without using long (more careful overflow handling)
    // Time: O(n), Space: O(1)
    int myAtoiNoLong(std::string s) {
        int i = 0;
        int sign = 1;
        int result = 0;
        
        // Skip whitespaces
        while (i < s.length() && s[i] == ' ') {
            i++;
        }
        
        // Handle sign
        if (i < s.length() && (s[i] == '+' || s[i] == '-')) {
            sign = (s[i] == '-') ? -1 : 1;
            i++;
        }
        
        // Process digits with overflow check
        while (i < s.length() && std::isdigit(s[i])) {
            int digit = s[i] - '0';
            
            // Check overflow conditions
            if (result > INT_MAX / 10 || 
                (result == INT_MAX / 10 && digit > INT_MAX % 10)) {
                return (sign == 1) ? INT_MAX : INT_MIN;
            }
            
            result = result * 10 + digit;
            i++;
        }
        
        return result * sign;
    }
    
    // Approach 3: State Machine Approach
    // Time: O(n), Space: O(1)
    int myAtoiStateMachine(std::string s) {
        enum State { START, SIGN, NUMBER, END };
        State state = START;
        
        int sign = 1;
        long result = 0;
        
        for (char c : s) {
            switch (state) {
                case START:
                    if (c == ' ') {
                        // Stay in START state
                    } else if (c == '+' || c == '-') {
                        sign = (c == '-') ? -1 : 1;
                        state = SIGN;
                    } else if (std::isdigit(c)) {
                        result = c - '0';
                        state = NUMBER;
                    } else {
                        state = END;
                    }
                    break;
                    
                case SIGN:
                    if (std::isdigit(c)) {
                        result = c - '0';
                        state = NUMBER;
                    } else {
                        state = END;
                    }
                    break;
                    
                case NUMBER:
                    if (std::isdigit(c)) {
                        int digit = c - '0';
                        if (result > (LLONG_MAX - digit) / 10) {
                            return (sign == 1) ? INT_MAX : INT_MIN;
                        }
                        result = result * 10 + digit;
                    } else {
                        state = END;
                    }
                    break;
                    
                case END:
                    break;
            }
            
            if (state == END) break;
        }
        
        result *= sign;
        
        if (result > INT_MAX) return INT_MAX;
        if (result < INT_MIN) return INT_MIN;
        
        return (int)result;
    }
    
    // Approach 4: Recursive Implementation
    // Time: O(n), Space: O(n) - due to recursion stack
    int myAtoiRecursive(std::string s) {
        return myAtoiHelper(s, 0, 0, 1, false);
    }
    
private:
    int myAtoiHelper(const std::string& s, int index, long result, int sign, bool started) {
        // Base case
        if (index >= s.length() || (!started && !std::isspace(s[index]) && 
                                    s[index] != '+' && s[index] != '-' && !std::isdigit(s[index]))) {
            result *= sign;
            if (result > INT_MAX) return INT_MAX;
            if (result < INT_MIN) return INT_MIN;
            return (int)result;
        }
        
        char c = s[index];
        
        // Skip leading spaces
        if (!started && c == ' ') {
            return myAtoiHelper(s, index + 1, result, sign, false);
        }
        
        // Handle sign
        if (!started && (c == '+' || c == '-')) {
            return myAtoiHelper(s, index + 1, result, (c == '-') ? -1 : 1, true);
        }
        
        // Handle digits
        if (std::isdigit(c)) {
            int digit = c - '0';
            if (result > (LLONG_MAX - digit) / 10) {
                return (sign == 1) ? INT_MAX : INT_MIN;
            }
            return myAtoiHelper(s, index + 1, result * 10 + digit, sign, true);
        }
        
        // Any other character ends the conversion
        result *= sign;
        if (result > INT_MAX) return INT_MAX;
        if (result < INT_MIN) return INT_MIN;
        return (int)result;
    }
    
public:
    // Approach 5: Optimized with early termination
    // Time: O(n), Space: O(1)
    int myAtoiOptimized(std::string s) {
        if (s.empty()) return 0;
        
        int i = 0, n = s.length();
        int sign = 1;
        long result = 0;
        
        // Skip leading whitespaces
        while (i < n && s[i] == ' ') i++;
        
        // No more characters
        if (i == n) return 0;
        
        // Handle sign
        if (s[i] == '+' || s[i] == '-') {
            sign = (s[i] == '-') ? -1 : 1;
            i++;
        }
        
        // Process digits
        while (i < n && std::isdigit(s[i])) {
            int digit = s[i] - '0';
            
            // Early overflow detection
            if (result > 214748364 || (result == 214748364 && digit > 7)) {
                return (sign == 1) ? INT_MAX : INT_MIN;
            }
            
            result = result * 10 + digit;
            i++;
        }
        
        return (int)(result * sign);
    }
    
    // Bonus: Handle different bases (not part of original problem)
    int myAtoiBase(std::string s, int base = 10) {
        if (base < 2 || base > 36) return 0;
        
        int i = 0;
        int sign = 1;
        long result = 0;
        
        // Skip whitespaces
        while (i < s.length() && s[i] == ' ') i++;
        
        // Handle sign
        if (i < s.length() && (s[i] == '+' || s[i] == '-')) {
            sign = (s[i] == '-') ? -1 : 1;
            i++;
        }
        
        // Process characters
        while (i < s.length()) {
            char c = s[i];
            int digit = -1;
            
            if (c >= '0' && c <= '9') {
                digit = c - '0';
            } else if (c >= 'A' && c <= 'Z') {
                digit = c - 'A' + 10;
            } else if (c >= 'a' && c <= 'z') {
                digit = c - 'a' + 10;
            }
            
            if (digit == -1 || digit >= base) break;
            
            if (result > (LLONG_MAX - digit) / base) {
                return (sign == 1) ? INT_MAX : INT_MIN;
            }
            
            result = result * base + digit;
            i++;
        }
        
        result *= sign;
        
        if (result > INT_MAX) return INT_MAX;
        if (result < INT_MIN) return INT_MIN;
        
        return (int)result;
    }
};

// Test function
void testStringToInteger() {
    Solution sol;
    
    std::vector<std::string> testCases = {
        "42",              // Expected: 42
        "   -42",          // Expected: -42
        "4193 with words", // Expected: 4193
        "words and 987",   // Expected: 0
        "-91283472332",    // Expected: INT_MIN
        "91283472332",     // Expected: INT_MAX
        "",                // Expected: 0
        " ",               // Expected: 0
        "+1",              // Expected: 1
        "+-12",            // Expected: 0
        "   +0 123",       // Expected: 0
        "2147483648",      // Expected: INT_MAX (overflow)
        "-2147483649",     // Expected: INT_MIN (underflow)
        "0-1",             // Expected: 0
        " 0000000000012345678", // Expected: 12345678
    };
    
    std::cout << "Testing String to Integer (atoi):\n";
    std::cout << "================================\n";
    
    for (const auto& test : testCases) {
        int result1 = sol.myAtoi(test);
        int result2 = sol.myAtoiNoLong(test);
        int result3 = sol.myAtoiStateMachine(test);
        int result4 = sol.myAtoiRecursive(test);
        int result5 = sol.myAtoiOptimized(test);
        
        std::cout << "Input: \"" << test << "\"\n";
        std::cout << "Standard: " << result1 << "\n";
        std::cout << "No Long: " << result2 << "\n";
        std::cout << "State Machine: " << result3 << "\n";
        std::cout << "Recursive: " << result4 << "\n";
        std::cout << "Optimized: " << result5 << "\n";
        std::cout << "---\n";
    }
    
    // Test different bases
    std::cout << "\nTesting different bases:\n";
    std::cout << "Base 16 'FF': " << sol.myAtoiBase("FF", 16) << "\n";
    std::cout << "Base 8 '77': " << sol.myAtoiBase("77", 8) << "\n";
    std::cout << "Base 2 '1010': " << sol.myAtoiBase("1010", 2) << "\n";
}

int main() {
    testStringToInteger();
    return 0;
}

/*
 * Key Insights:
 * 1. Handle edge cases: leading whitespace, signs, overflow, invalid characters
 * 2. Use long to detect overflow before clamping to int range
 * 3. Stop parsing at first non-digit character
 * 4. Be careful with overflow detection when not using long
 * 
 * Edge Cases to Consider:
 * 1. Leading/trailing whitespace
 * 2. Multiple signs (++, -+, etc.)
 * 3. Numbers with leading zeros
 * 4. Overflow and underflow
 * 5. Empty string or only whitespace
 * 6. Non-numeric characters
 * 7. Sign without digits
 * 
 * Common Mistakes:
 * 1. Not handling integer overflow correctly
 * 2. Forgetting to trim leading whitespace
 * 3. Not stopping at first non-digit character
 * 4. Incorrect sign handling
 * 5. Off-by-one errors in overflow detection
 * 
 * Follow-up Questions:
 * 1. What if we need to support different number bases?
 * 2. What if we need to handle floating point numbers?
 * 3. What if we need to return error codes instead of clamping?
 * 4. What if we need to handle different locales/number formats?
 */