#ifndef FIXEDQUEUE_H_
#define FIXEDQUEUE_H_

#include <iostream>

class FixedQueue {
public:
    FixedQueue();
    ~FixedQueue();
    void in(int new_item);
    int out();
    int first() const;
    bool isEmpty() const;
    bool isFull() const;
    void print() const;

private:
    static const int CAPACITY = 10; //tomb merete
    int array[CAPACITY]; //tomb beallitasa
    int head = 0;
    int tail = 0; // sor első eleme, sor első szabad helye

    bool empty = true; // ha az előző kettő egyenlő akkor a sor vagy üres vagy teli
};

#endif /* FIXEDQUEUE_H_ */