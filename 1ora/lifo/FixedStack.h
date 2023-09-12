#ifndef FIXEDSTACK_H_
#define FIXEDSTACK_H_

#include <iostream>

class FixedStack {
public:
	FixedStack();
	virtual ~FixedStack();
	void push(int new_item);
	int pop();
	int top() const;
	bool isEmpty() const;
	void print() const;

private:
	static const int max = 10;
	int array[max];
	int head;
};

#endif /* FIXEDSTACK_H_ */