#ifndef DYNAMICINTSTACK_H_
#define DYNAMICINTSTACK_H_

#include <iostream>

class DynamicIntStack {
private:
    class Node {
    public:
        int value;
        Node* pNext;

        Node() : value(0), pNext(nullptr) {}
        Node(const int& _value) : value(_value), pNext(nullptr) {}
        Node(const int& _value, Node* _pNext) :	value(_value), pNext(_pNext) {}
    };
    Node* pHead;

public:
    DynamicIntStack();
    DynamicIntStack(const DynamicIntStack& other);
    DynamicIntStack(DynamicIntStack&& other) noexcept;
    DynamicIntStack& operator= (const DynamicIntStack& rhs);
    DynamicIntStack& operator= (DynamicIntStack&& rhs) noexcept;
    ~DynamicIntStack();

    void push(int new_item);
    int pop();
    int top() const;
    bool isEmpty() const;
    void print() const;
};

#endif /* DYNAMICINTSTACK_H_ */