#ifndef LINKED_LIST_COMMON_H
#define LINKED_LIST_COMMON_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <climits>

using namespace std;

// Definition for singly-linked list
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// Definition for linked list with random pointer
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};

// Definition for multilevel doubly linked list
class MultiLevelNode {
public:
    int val;
    MultiLevelNode* prev;
    MultiLevelNode* next;
    MultiLevelNode* child;
    
    MultiLevelNode() {}
    MultiLevelNode(int _val) {
        val = _val;
        prev = nullptr;
        next = nullptr;
        child = nullptr;
    }
};

// Utility functions for testing
ListNode* createLinkedList(vector<int>& vals) {
    if (vals.empty()) return nullptr;
    
    ListNode* head = new ListNode(vals[0]);
    ListNode* current = head;
    
    for (int i = 1; i < vals.size(); i++) {
        current->next = new ListNode(vals[i]);
        current = current->next;
    }
    
    return head;
}

void printLinkedList(ListNode* head) {
    while (head) {
        cout << head->val;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << endl;
}

int getLength(ListNode* head) {
    int length = 0;
    while (head) {
        length++;
        head = head->next;
    }
    return length;
}

// Create cycle in linked list (for testing cycle problems)
void createCycle(ListNode* head, int pos) {
    if (!head || pos < 0) return;
    
    ListNode* tail = head;
    ListNode* cycleNode = nullptr;
    int index = 0;
    
    while (tail->next) {
        if (index == pos) {
            cycleNode = tail;
        }
        tail = tail->next;
        index++;
    }
    
    if (cycleNode) {
        tail->next = cycleNode;
    }
}

#endif // LINKED_LIST_COMMON_H