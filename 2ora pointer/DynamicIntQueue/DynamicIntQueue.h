#ifndef DYNAMICINTQUEUE_H_
#define DYNAMICINTQUEUE_H_

class DynamicIntQueue {
public:
    DynamicIntQueue() : head{nullptr}, tail{nullptr} {}
    DynamicIntQueue(const DynamicIntQueue &other);
    DynamicIntQueue(DynamicIntQueue &&other);
    DynamicIntQueue &operator=(DynamicIntQueue &rhs);
    DynamicIntQueue &operator=(DynamicIntQueue &&rhs);
    ~DynamicIntQueue();
    void swap(DynamicIntQueue &other) noexcept;
    void in(int new_item);
    int out();
    int first() const;
    bool isEmpty() const;
    void print() const;

private:
    struct Node {
        int value;
        Node *pNext;

        Node() : value(0), pNext(nullptr) {}
        Node(int _value) : value(_value), pNext(nullptr) {}
        Node(int _value, Node *_pNext) : value(_value), pNext(_pNext) {}
    };

    Node *head, *tail;
};

#endif /* DYNAMICINTQUEUE_H_ */