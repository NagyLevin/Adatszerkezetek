#include <iostream>
#include <exception>

#include "FixedStack.h"

using namespace std;

int main() {
    cout << "Test the Static Stack" << endl;
    FixedStack fixed_stack;

    // empty stack
    cout << "\n/**********Empty Stack**********\\" << endl;
    cout << "isEmpty(): " << fixed_stack.isEmpty() << endl;//1 (true)
    cout << "print(): ";
    fixed_stack.print();

    // push & check
    cout << "\n/**********Push to Stack**********\\" << endl;
    fixed_stack.push(1);
    fixed_stack.push(2);
    fixed_stack.push(3);
    fixed_stack.push(4);
    fixed_stack.push(5);

    cout << "After 5 item: "; fixed_stack.print();
    fixed_stack.push(6);
    fixed_stack.push(7);
    fixed_stack.push(8);
    fixed_stack.push(9);
    fixed_stack.push(10);

    cout << "After 10 item: "; fixed_stack.print();
    cout << "isEmpty(): " << fixed_stack.isEmpty() << endl;//0 (false)

    // pop
    cout << "\n/**********Pop from Stack**********\\" << endl;

    cout << "top(): " << fixed_stack.top() << endl;
    cout << "pop(): " << fixed_stack.pop() << endl;
    cout << "pop(): " << fixed_stack.pop() << endl;
    cout << "pop(): " << fixed_stack.pop() << endl;
    cout << "pop(): " << fixed_stack.pop() << endl;
    cout << "pop(): " << fixed_stack.pop() << endl;
    cout << "After 5 item: "; fixed_stack.print();
    cout << "top(): " << fixed_stack.top() << endl;
    cout << "pop(): " << fixed_stack.pop() << endl;
    cout << "pop(): " << fixed_stack.pop() << endl;
    cout << "pop(): " << fixed_stack.pop() << endl;
    cout << "pop(): " << fixed_stack.pop() << endl;
    cout << "pop(): " << fixed_stack.pop() << endl;

    return 0;
}
