#include "DynamicIntQueue.h"

#include <iostream>

DynamicIntQueue::DynamicIntQueue(const DynamicIntQueue &other)
        : head{nullptr}, tail{nullptr} {
    for (Node *node = other.head; node != nullptr; node = node->pNext) {
        in(node->value);
    }
}

DynamicIntQueue::DynamicIntQueue(DynamicIntQueue &&other)
        : head{other.head}, tail{other.tail} {
    other.head = other.tail = nullptr;
}

DynamicIntQueue &DynamicIntQueue::operator=(DynamicIntQueue &rhs) {
    if (&rhs != this) {
        // RAII -- copy ctor
        DynamicIntQueue temp{rhs};
        temp.swap(*this);
        // temp destruktora elintézi a mi régi implementációnkat
    }

    return *this;
}

DynamicIntQueue &DynamicIntQueue::operator=(DynamicIntQueue &&rhs) {
    swap(rhs);
    return *this;
}

DynamicIntQueue::~DynamicIntQueue() {
    while (!isEmpty()) {
        out();
    }
}

void DynamicIntQueue::swap(DynamicIntQueue &other) noexcept {
    std::swap(this->head, other.head);
    std::swap(this->tail, other.tail);
}

bool DynamicIntQueue::isEmpty() const {
    return (head == nullptr); //ha head nullptr akkor ures


}

void DynamicIntQueue::in(int new_item) {
Node * p = new Node(new_item); //uj nodenak uj ertek
if(isEmpty()){
    head = p;
    tail = p;
}else{
    tail->pNext = p; //tail az ujnodera mutasson
    tail =p;


}

}

int DynamicIntQueue::out() {
    if(isEmpty()){
        return -1;
    }
    Node * p = head;
    head = head->pNext;
    int temp = p->value; //int?
    delete p;
    if(head == nullptr){
        tail = nullptr;
    }

    return temp;



}

int DynamicIntQueue::first() const {
    if(isEmpty()){
        return -1;
    }

    return head->value;

}

void DynamicIntQueue::print() const {
    for (Node *i = head; i != nullptr; i = i->pNext) {
        std::cout << i->value << " ";
    }
}