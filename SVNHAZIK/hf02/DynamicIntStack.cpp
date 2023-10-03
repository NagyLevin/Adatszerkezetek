#include "DynamicIntStack.h"

DynamicIntStack::DynamicIntStack() {
    pHead = nullptr;
    elemszam = 0;
}

DynamicIntStack::~DynamicIntStack() { //Destruktor, felszabaditja a memoriateruletet
    while (!isEmpty()) {
        pop_back();
    }
}
void DynamicIntStack::clear() {
    while (!isEmpty()) {


        pop_back();

    }
    elemszam = 0;
}

bool DynamicIntStack::isEmpty() const {
    return (pHead == nullptr);
}

void DynamicIntStack::push_back(char new_item) {
    Node* p = new Node(new_item); //uj memoriaterulet lefoglalasa
    p->pNext = pHead; //uj node nextjet az uj headre
    pHead = p; //head lesz az egesz tetejen
    elemszam = elemszam + 1;

}

char DynamicIntStack::top() const {

    if(isEmpty()){
        return -1;
    }
    return pHead->value;
}
int DynamicIntStack::size(){

    return elemszam;
};

char DynamicIntStack::pop_back() {
    if(isEmpty()){
        return -1;
    }
    int tmp = pHead->value; //elmentjuk egy ideglenes valtozoba
    Node* p = pHead;
    pHead = pHead->pNext;
    delete p;
    elemszam = elemszam -1;
    return  tmp;

}

void DynamicIntStack::print() const {
    for (Node* i = pHead; i != nullptr; i = i->pNext) {
        std::cout << i->value << " ";
    }
    std::cout << ""  <<std::endl;
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
            pop_back();
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
            pop_back();
        }
        // pHead = std::exchange(other.pHead, nullptr);
        pHead = rhs.pHead;
        rhs.pHead = nullptr;
    }
    return *this;
}