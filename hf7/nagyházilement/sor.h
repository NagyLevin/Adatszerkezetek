//
// Created by Kolos on 2022. 10. 09..
//

#ifndef NHF1_SKELETON_SOR_H
#define NHF1_SKELETON_SOR_H

#include "list.h"

using namespace std;

struct Mezo{
    int x;
    double data;
    Mezo(int x,double data):x(x),data(data){};
};

class Sor : public List<Mezo>{
private:
    int y;
    double defValue;
public:
    Sor(int y,double defValue):List(),y(y),defValue(defValue){
        head = nullptr;
        tail = nullptr;
    };

    Sor(const Sor other,double defVal) noexcept {
        head = nullptr;
        tail = nullptr;
        defValue = defVal;
        y = other.y;
        for(Node *node = other.head; node != nullptr; node = node->next){
            //Mezo tag = Mezo(node->data);
            Node* tmp = new Node(Mezo(node->data));
            if(head == nullptr){
                head = tmp;
                tail = head;
            }else if(head == tail){
                tmp->prev = head;
                tail = tmp;
                head->next = tail;
            }else{
                tmp->prev = tail;
                //Node *newtag = new Node(tag,tail,nullptr);
                tail->next = tmp;
                tail = tmp;
            }
        };
    };

    ~Sor()= default;

    int gety(){
        return y;
    };

    void setdefValue(double defval){
        defValue = defval;
    }

    void setdata(int x,double val){
        bool found = false;
        //Mezo newmezo = Mezo(x,val);
        Node *node = new Node(Mezo(x,val));
        if(head == nullptr){
            head = node;
            tail = node;
        }else {
            for (Node *j = head; j != nullptr; j = j->next) {
                if (j->data.x == x) {
                    j->data.data = val;
                    found = true;
                    break;
                } else if (j->data.x > x) {
                    if (j == head) {
                        node->next = head;
                        head->prev = node;
                        head = node;
                    } else {
                        Node *oldnode = j->prev;                                                 //
                        node->next = j;
                        node->prev = oldnode;
                        oldnode->next = node;
                        j->prev = node;
                    }
                    found = true;
                    break;
                }
            }
            if(!found){
                node->prev = tail;                                                               //
                tail->next = node;
                tail = node;
            }
        }
    }


    double operator()(int x) const{
       for (Node *j = head; j != nullptr; j = j->next) {
            if(x < j->data.x) {
                return defValue;
            }else if(x == j->data.x){
                return j->data.data;                   //j->data mátrix data ami egy sor / mező , j->data.data mező tipusu adat
            }
        }
       return defValue;
    }


    void deletenode(Node *node){
        if(node == head && tail == node){
            delete head;
            head = nullptr;
            tail = nullptr;
        }else if(node == head){
            head = node->next;
            head->prev = nullptr;
            delete node;
        }else if(node == tail){
            tail = node->prev;
            tail->next = nullptr;
            delete node;
        }else{
            node->prev->next = node->next;
            node->next->prev = node->prev;
            delete node;
        }
    }

    bool clear(int x){ // utolso létező elemet is kiszedtük a listából akkor töröljük a sor
        for(Node *node = head; node != nullptr; node = node->next){
            if(node->data.x == x){
                Node *tmp = node->prev; //van-e még adat a sorban
                deletenode(node);
                if(tmp == nullptr && head == nullptr){
                    return true;
                }else{
                    return false;
                }
            }
        }
        return false;
    }

    bool clearemptys(){ //üres sorok keresése
        Node *node = head;
        while(node != nullptr){
            if(node->data.data == defValue){
                Node *tmp = node->prev;
                deletenode(node);
                if(tmp == nullptr){
                    node = head;
                }else{
                    node = tmp->next;
                }
            }else {
                node = node->next;
            }
        }
        return false;
    }

    Node* gethead(){
        return head;
    };

    void addline(Sor other, int sizex){ //összefésülés
        Node *node = head;
        Node *othernode = other.head;
        for(int i = 0;i<sizex-1;i++){
            double newdata = 0;
            if(node != nullptr && othernode != nullptr) {
                if (node->data.x == i && othernode->data.x == i) {
                    newdata = node->data.data + othernode->data.data;
                    node = node->next;
                    othernode = othernode->next;
                } else if (node->data.x == i) {
                    newdata = node->data.data + other.defValue;
                    node = node->next;
                } else if (othernode->data.x == i) {
                    newdata = othernode->data.data + defValue;
                    othernode = othernode->next;
                }
            }else if(node != nullptr){
                if(node->data.x == i){
                    newdata = node->data.data + other.defValue;
                    node = node->next;
                }
            }else if(othernode != nullptr){
                if (othernode->data.x == i) {
                    newdata = othernode->data.data + defValue;
                    othernode = othernode->next;
                }
            }
            if (newdata != 0) {
                setdata(i, newdata);
            }
        }
        defValue += other.defValue;
    }

    void print(int sizex) const {
        Node* j = head;
        for (int i = 0; i < sizex-1; i++) {
            if(j == nullptr || j->data.x > i) {
                cout << defValue << " ";
            }else{
                cout << j->data.data << " ";
                j = j->next;
            }
        }
    }
};

#endif //NHF1_SKELETON_SOR_H
