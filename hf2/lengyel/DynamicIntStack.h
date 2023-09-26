#ifndef DYNAMICINTSTACK_H_
#define DYNAMICINTSTACK_H_

#include <iostream>

class DynamicIntStack {
private:

    int elemszam;

    class Node {
    public:
        char value;
        Node* pNext;



        Node() : value(0), pNext(nullptr) {}
        Node(const char& _value) : value(_value), pNext(nullptr) {}
        Node(const char& _value, Node* _pNext) :	value(_value), pNext(_pNext) {}
    };
    Node* pHead;

public:
    DynamicIntStack();
    DynamicIntStack(const DynamicIntStack& other);
    DynamicIntStack(DynamicIntStack&& other) noexcept;
    DynamicIntStack& operator= (const DynamicIntStack& rhs);
    DynamicIntStack& operator= (DynamicIntStack&& rhs) noexcept;
    ~DynamicIntStack();

    void push_back(char new_item);
    char pop_back();
    char top() const;
    bool isEmpty() const;
    void print() const;
    int size();
    void clear();
};

#endif /* DYNAMICINTSTACK_H_ */