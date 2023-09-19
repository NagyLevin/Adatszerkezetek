#include "DynamicIntStack.h"

DynamicIntStack::DynamicIntStack() {
    pHead = nullptr;
}

DynamicIntStack::~DynamicIntStack() { //Destruktor, felszabaditja a memoriateruletet
    while (!isEmpty()) {
        pop();
    }
}

bool DynamicIntStack::isEmpty() const {
    return (pHead == nullptr);
}

void DynamicIntStack::push(int new_item) {
    Node* p = new Node(new_item); //uj memoriaterulet lefoglalasa
    p->pNext = pHead; //uj node nextjet az uj headre
    pHead = p; //head lesz az egesz tetejen


}

int DynamicIntStack::top() const {

    if(isEmpty()){
        return -1;
    }
    return pHead->value;
}

int DynamicIntStack::pop() {
    if(isEmpty()){
        return -1;
    }
    int tmp = pHead->value; //elmentjuk egy ideglenes valtozoba
    Node* p = pHead;
    pHead = pHead->pNext;
    delete p;
    return  tmp;

}

void DynamicIntStack::print() const {
    for (Node* i = pHead; i != nullptr; i = i->pNext) {
        std::cout << i->value << " ";
    }
}

DynamicIntStack::DynamicIntStack(const DynamicIntStack& other) {
    if(nullptr != other.pHead) {
        pHead = new Node(other.pHead->value);
        Node *copied = pHead;
        for (Node *i = other.pHead->pNext; i != nullptr; i = i->pNext) {
            copied->pNext = new Node(i->value);
            copied = copied->pNext;
        }
    }
}

DynamicIntStack::DynamicIntStack(DynamicIntStack&& other) noexcept {
    // pHead = std::exchange(other.pHead, nullptr);
    pHead = other.pHead;
    other.pHead = nullptr;
}

DynamicIntStack& DynamicIntStack::operator= (const DynamicIntStack& rhs) {
    if(this != &rhs) {
        while (!isEmpty()) {
            pop();
        }
        if(nullptr != rhs.pHead) {
            pHead = new Node(rhs.pHead->value);
            Node *copied = pHead;
            for (Node *i = rhs.pHead->pNext; i != nullptr; i = i->pNext) {
                copied->pNext = new Node(i->value);
                copied = copied->pNext;
            }
        }
    }
    return *this;
}

DynamicIntStack& DynamicIntStack::operator= (DynamicIntStack&& rhs) noexcept{
    if(this != &rhs) {
        while (!isEmpty()) {
            pop();
        }
        // pHead = std::exchange(other.pHead, nullptr);
        pHead = rhs.pHead;
        rhs.pHead = nullptr;
    }
    return *this;
}