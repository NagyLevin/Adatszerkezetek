
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
    int size();
    bool isEmpty() const;

    char GiveItem(int elemszam);


private:
    static const int max = 3; //array merete(tarolo merete)
    char array[max];
    //tomb merettel egyutt
    int head; //mutato, ami a legutobb belerakott elemet mutatja
};

#endif //MyStack
