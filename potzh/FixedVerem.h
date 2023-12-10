//
// Created by Levi on 2023. 12. 10..
//

#ifndef POTZHGYAK_FIXEDVEREM_H
#define POTZHGYAK_FIXEDVEREM_H

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
    static const int max = 10; //array merete(tarolo merete)
    int array[max]; //tomb merettel egyutt
    int head; //mutato, ami a legutobb belerakott elemet mutatja
};


FixedStack::FixedStack() {
    head = 0;
}

FixedStack::~FixedStack() {

}

bool FixedStack::isEmpty() const {
    return (head == 0); //akkor ures, ha head 0

}


void FixedStack::push(int new_item) {
    if (head == max) {
        return;  // Később megírjuk szebben is!
    }
    array[head] = new_item; //ha nincs tele, akkor belerakjuk, az uj elemet
    head++; //megnöveljük a fej erteket, hogy egyel elöbbre lepjen


}

int FixedStack::top() const {
    if (isEmpty()) {
        return -1; // Később megírjuk szebben is!
    }
    return array[head-1]; //adjuk vissza a legutobb elmentett elemet



}

int FixedStack::pop() {
    if (isEmpty()) {
        return -1; // Később megírjuk szebben is!
    }
    int temp = array[head-1];

    //array[head-1] = -1; //default ertek, hogy tudjam, hogy elrontottam valamit

    head--; //egyel lejjebb allitjuk a headet, mert egy elemet kiszedtunk

    return temp;
}

void FixedStack::print() const {

    if (isEmpty()) {
        std::cout << array[head-1] <<", ";
    }
    std::cout << "" << std::endl;
    for(int i =0; i < (head);i++){
        //std::cout << "head: " << head << std::endl;

        std::cout << array[i] << std::endl;
    }



}


#endif //POTZHGYAK_FIXEDVEREM_H
