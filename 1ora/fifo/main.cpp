#include "FixedQueue.h"
#include <iostream>

using namespace std;

int main(int, char **) {
  cout << "Test the Static Queue" << endl;

  FixedQueue fixed_queue;

  // empty queue
  cout << "\n/**********Empty Queue**********\\" << endl;
  cout << "isEmpty(): " << fixed_queue.isEmpty() << endl; // 1 (true)
  cout << "isFull(): " << fixed_queue.isFull() << endl;   // 0 (false)
  cout << "print(): ";
  fixed_queue.print();

  // in & check
  cout << "\n/**********In to Queue**********\\" << endl;
  fixed_queue.in(1);
  fixed_queue.in(2);
  fixed_queue.in(3);
  fixed_queue.in(4);
  fixed_queue.in(5);
  
  cout << "After 5 item: ";
  fixed_queue.print();

  fixed_queue.in(6);
  fixed_queue.in(7);
  fixed_queue.in(8);
  fixed_queue.in(9);
  fixed_queue.in(10);

  cout << "After 10 item: ";
  fixed_queue.print();
  
  cout << "\nisEmpty(): " << fixed_queue.isEmpty() << endl; // 0 (false)
  cout << "isFull(): " << fixed_queue.isFull() << endl;     // 1 (true)

  // A körkörös reprezentáció demonstrálása
  cout << "\n\nout(): " << fixed_queue.out() << endl;
  cout << "out(): " << fixed_queue.out() << endl;
  cout << "out(): " << fixed_queue.out() << endl;
  fixed_queue.print();
  cout << endl;
  fixed_queue.in(11);
  fixed_queue.in(12);
  fixed_queue.in(13);
  fixed_queue.print();
  cout << endl;


  // out
  cout << "\n/**********Out from Queue**********\\" << endl;

  cout << "first(): " << fixed_queue.first() << endl;
  cout << "out(): " << fixed_queue.out() << endl;
  cout << "out(): " << fixed_queue.out() << endl;
  cout << "out(): " << fixed_queue.out() << endl;
  cout << "out(): " << fixed_queue.out() << endl;
  cout << "out(): " << fixed_queue.out() << endl;
  cout << "After 5 item: ";
  fixed_queue.print();
  cout << endl;
  cout << "first(): " << fixed_queue.first() << endl;
  cout << "out(): " << fixed_queue.out() << endl;
  cout << "out(): " << fixed_queue.out() << endl;
  cout << "out(): " << fixed_queue.out() << endl;
  cout << "out(): " << fixed_queue.out() << endl;
  cout << "out(): " << fixed_queue.out() << endl;

  cout << "isEmpty(): " << fixed_queue.isEmpty() << endl; // 1 (true)

  return 0;
}