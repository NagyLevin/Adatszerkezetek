#include "DynamicIntQueue.h"
#include <iostream>

using namespace std;

int main() {
    cout << "Test the Dynamic Queue" << endl;

    DynamicIntQueue queue;

    // empty queue
    cout << "\n/**********Empty Queue**********\\" << endl;
    cout << "isEmpty(): " << queue.isEmpty() << endl; // 1 (true)
    cout << "print(): ";
    queue.print();
    cout << endl;

    cout << "first(): ";
    cout << queue.first() << endl; // exception

    cout << "out(): ";
    cout << queue.out() << endl; // exception

    // in & check
    cout << "\n/**********In to Queue**********\\" << endl;

    queue.in(1);
    queue.in(2);
    queue.in(3);
    queue.in(4);
    queue.in(5);

    cout << "After 5 items: ";
    queue.print();
    cout << endl;

    queue.in(6);
    queue.in(7);
    queue.in(8);
    queue.in(9);
    queue.in(10);

    cout << "After 10 items: ";
    queue.print();
    cout << endl;
    cout << "isEmpty(): " << queue.isEmpty() << endl; // 0 (false)

    queue.in(11);

    cout << "After 11 items: ";
    queue.print();
    cout << endl;

    // out
    cout << "\n/**********Out from Queue**********\\" << endl;

    cout << "first(): " << queue.first() << endl;
    cout << "out(): " << queue.out() << endl;
    cout << "out(): " << queue.out() << endl;
    cout << "out(): " << queue.out() << endl;
    cout << "out(): " << queue.out() << endl;
    cout << "out(): " << queue.out() << endl;
    cout << "After 5 items: ";
    queue.print();
    cout << endl;
    cout << "first(): " << queue.first() << endl;
    cout << "out(): " << queue.out() << endl;
    cout << "out(): " << queue.out() << endl;
    cout << "out(): " << queue.out() << endl;
    cout << "out(): " << queue.out() << endl;
    cout << "out(): " << queue.out() << endl;
    cout << "out(): " << queue.out() << endl;

    return 0;
}