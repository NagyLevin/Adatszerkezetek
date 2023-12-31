
#include "mystack.h"



MyStack::MyStack() {
    head = 0;
}

MyStack::~MyStack() {

}

bool MyStack::isEmpty() const {
    return (head == 0); //akkor ures, ha head 0

}


void MyStack::push(int new_item) {
    if (head == max) {
        return;  // Később megírjuk szebben is!
    }
    array[head] = new_item; //ha nincs tele, akkor belerakjuk, az uj elemet
    head++; //megnöveljük a fej erteket, hogy egyel elöbbre lepjen


}

int MyStack::top() const {
    if (isEmpty()) {
        return -1; // Később megírjuk szebben is!
    }
    return array[head-1]; //adjuk vissza a legutobb elmentett elemet



}

int MyStack::size(){
    return max;
}
char MyStack::GiveItem(int elemszam){
    return array[elemszam];

}


int MyStack::pop() {
    if (isEmpty()) {
        return -1; // Később megírjuk szebben is!
    }
    int temp = array[head-1];

    //array[head-1] = -1; //default ertek, hogy tudjam, hogy elrontottam valamit

    head--; //egyel lejjebb allitjuk a headet, mert egy elemet kiszedtunk

    return temp;
}


