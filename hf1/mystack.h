
#ifndef MYSTACK_H
#define MYSTACK_H

#include <iostream>

class MyStack {
public:
    MyStack();
    virtual ~MyStack();
    void push(int new_item);
    int pop();
    int top() const;
    bool isEmpty() const;
    void print() const;

private:
    static const int max = 10; //array merete(tarolo merete)
    int array[max]; //tomb merettel egyutt
    int head; //mutato, ami a legutobb belerakott elemet mutatja
};

#endif //MyStack
