#include "FixedQueue.h"

FixedQueue::FixedQueue() {

}

FixedQueue::~FixedQueue() {}

bool FixedQueue::isEmpty() const {
    return empty;
}

bool FixedQueue::isFull() const {//a diaban azt irjak hogy nem szerepel XDDDDDDDDDDDDDDDDD
    return head == tail && !isEmpty(); //eleje es vege ugyanott van es ures
}

void FixedQueue::in(int new_item) {//uj elem hozzaadas
    if(isFull()) return; //ha head es tail ugyanott al
    empty = false;

    array[tail] = new_item ; //hozzáadunk egy uj elemet
    if(tail == CAPACITY-1){
        tail=0; //ekkor elore helyezem, es onnan toltom fel
    }

    else{

        tail++;  //tail eltolva 1-el

    }

}

int FixedQueue::out() {     //heades elem lesz torolve, mert hatulrol allnak ki a sorbol
    if(head == tail){
        empty = true;
    }

    int temp = array[head];

    if(head == CAPACITY-1){
        head = 0;
    }
    else{
        head++;
    }


    return temp;


}

int FixedQueue::first() const {
    if(tail == 0){
        return array[CAPACITY-1];
    }

    return array[tail-1];

}

void FixedQueue::print() const {
    if (isEmpty()) {
        return;
    }

    if (head < tail) { // alap eset, amíg a head elött van a tail
        for (int i = head; i < tail - 1; i++) {
            std::cout << array[i] << ", ";
        }
        std::cout << array[tail - 1] << std::endl;
    } else { // ha már körbe fordult a tail
        // akkor head-től a tömb végéig (ami valahol a sor közepén van)
        for (int i = head; i < CAPACITY; i++) {
            std::cout << array[i] << ", ";
        }
        for (int i = 0; i < tail; i++) { // majd előről a tail-ig
            std::cout << array[i] << ", ";
        }
    }
}
