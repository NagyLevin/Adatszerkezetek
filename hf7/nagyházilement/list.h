//
// Created by Kolos on 2022. 10. 08..
//

#ifndef NHF1_SKELETON_LIST_H
#define NHF1_SKELETON_LIST_H

#include "exceptions.h"

using namespace std;

template <class T>
class List{
protected:
    struct Node{
        T data;
        Node *prev;
        Node *next;
        Node(T data0) : data(data0), prev(nullptr), next(nullptr) {}
        Node(T data0, Node *prev0, Node *next0)
                : data(data0), prev(prev0), next(next0) {}
        };
    Node *head;
    Node *tail;
public:

    List() {
        head = nullptr;
        tail = nullptr;
    }

    ~List() {
        typename List<T>::Node* i;
        typename List<T>::Node* j;
        i = this->head;
        while(i != nullptr){
            j = i;
            i = i->next;
            delete j;
        }
        //this->head = nullptr;
        //this->tail = nullptr;

        /*for(Node* i = head; i != nullptr; ) {
            if (i != nullptr) {
                Node *tmp = i;
                i = i->next;
                delete tmp;
            }
        }

        head = nullptr;*/

    }

    bool isEmpty() const { // üres a lista
        return (head == nullptr);
    }

    T out() {
        Node *newhead;
        if (isEmpty()) {
            throw UnderFlowException();
        } else {
            T olddata = T(head->data);
            if(head->next == tail) {
                delete head;
                tail->prev = nullptr;
                head = tail;
            }else if(head == tail){
                delete head;
                head = nullptr;
                tail = nullptr;
            }else{
                newhead = head->next;
                delete head;
                head = newhead;
                head->prev = nullptr;
            }
            return olddata;
        }
    }

    void in(T new_item) {
        Node* p = new Node(new_item);
        if(isEmpty()){
            head = tail = p;
        }else{
            tail->next = p;
            p->prev = tail;
            tail = p;
        }
    }

    T first() const {
        if (isEmpty()) {
            throw UnderFlowException();
        }
        return head->data;
    }

    double size(){
        typename List<T>::Node* i;
        double j;
        i = this->head;
        while(i != nullptr){
            i = i->next;
            j++;
        }
        return j;
    };


};




#endif //NHF1_SKELETON_LIST_H
