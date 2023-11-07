//
// Created by Németh Dániel on 2022. 09. 25..
//

#ifndef NHF1_SKELETON_SPARSEMATRIX_HPP
#define NHF1_SKELETON_SPARSEMATRIX_HPP

#include "list.h"
#include "sor.h"

using namespace std;

class SparseMatrix : public List<Sor>{
private:
    int sizex;
    int sizey;
    double defValue;
public:
    //Konstruktor
    SparseMatrix(int size_x, int size_y, double defaultValue):sizex(size_x),sizey(size_y),defValue(defaultValue){
        head = nullptr;
        tail = nullptr;
    };

    //Copy konstruktor
    SparseMatrix(const SparseMatrix &other) noexcept {
        head = nullptr;
        tail = nullptr;
        sizex = other.sizex;
        sizey = other.sizey;
        defValue = other.defValue;
        for(Node *node = other.head; node != nullptr; node = node->next){
            Sor row = Sor(node->data,other.defValue);
            if(head == nullptr){
                head = new Node(row);
                tail = new Node(row);
            }else if(head == tail){
                tail = new Node(row,head,nullptr);
                head->next = tail;
            }else{
                Node *newrow = new Node(row,tail,nullptr);
                tail->next = newrow;
                tail = newrow;
            }
        };
    };

    //Assignment operator
    SparseMatrix &operator=(const SparseMatrix &other) noexcept{
        Node* i;
        Node* j;
        i = this->head;
        while(i != nullptr){
            j = i;
            i = i->next;
            delete j;
        }
        this->head = nullptr;
        this->tail = nullptr;

        sizex = other.sizex;
        sizey = other.sizey;
        defValue = other.defValue;

        for(Node *node = other.head; node != nullptr; node = node->next) {
            Sor row = Sor(node->data, other.defValue);
            if (head == nullptr) {
                head = new Node(row);
                tail = new Node(row);
            } else if (head == tail) {
                tail = new Node(row, head, nullptr);
                head->next = tail;
            } else {
                Node *newrow = new Node(row, tail, nullptr);
                tail->next = newrow;
                tail = newrow;
            }
        }
        return *this;
    };


    //Destruktor
    ~SparseMatrix()= default;

    //Indexeles - kiindexeles eseten hibat dob
    double operator()(int x, int y) const{
        if(x < 0 || y < 0){                          //size-1 a méret?
            throw UnderFlowException();
        }else if(x > sizex-1 || y > sizey-1){
            throw OverFlowException();
        }else{
            if(head == nullptr){
                return defValue;
            }
            for(Node *node = head; node != nullptr; node = node->next){ //y koordinátájo sor létezik e
                if(node->data.gety() == y){ //létezik e az x koord oszlop
                    return node->data(x);
                }else if(node->data.gety() > y){
                    return  defValue;
                }
            }
            return defValue;//ha nincs több nem default sor
        }                              //x y értékkel tér vissza
    };

    //Teljes matrix kiiratasa consolera
    void printMatrix() const {
        Node* j = head;
        for (int i = 0; i < sizey-1; i++) {
            if(j == nullptr || j->data.gety() > i) {
                for(int k = 0;k < sizex-1;k++) {
                    cout << defValue << " ";
                }
            }else{
                j->data.print(sizex);
                j = j->next;
            }
        }
    };

    //Matrix elem ertekadas - ha letezik az ertek, felulirja
    //Kiindexeles eseten hibat dob
    void set(int x, int y, double value){
        if(x < 0 || y < 0){                          //size-1 a méret?
            throw UnderFlowException();
        }else if(x > sizex-1 || y > sizey-1){
            throw OverFlowException();
        }else{
           if(head == nullptr){//amikor teljesen üres a matrix
                Sor newsor = Sor(y,defValue);
                //Mezo newmezo = Mezo(x,value);
                //newsor.in(newmezo);

                head = new Node(newsor);
                tail = head;
               head->data.setdata(x,value);//fura
            }else {
               bool found = false;
               for (Node *node = head; node != nullptr; node = node->next) {
                   if (node->data.gety() == y) { //létezik a sor
                       //return node->data(x);
                       node->data.setdata(x, value);
                       found = true;
                       break;
                   } else if (node->data.gety() > y) { //nem létezik még a sor de nem utolsónak szúrunk be sort (köztessor)
                       Sor row = Sor(y, defValue);
                       Node *newnode = new Node(row);
                       found = true;
                       newnode->data.setdata(x, value);
                       if (head == node) { //a lista legelejére szurunk be uj sort akkor a head modosul, egyébként nem
                           newnode->next = head;
                           head->prev = newnode;
                           head = newnode;
                       } else {
                           newnode->next = node;
                           newnode->prev = node->prev;
                           newnode->prev->next = newnode;
                           node->prev = newnode;
                       }
                       break;
                   }
               }
               if(!found){//nem létezik a sor és a mátrix legvégére szurunk be
                   Sor row = Sor(y, defValue);
                   Node *newnode = new Node(row,tail,nullptr);
                   tail->next = newnode;
                   tail = newnode;
                   newnode->data.setdata(x, value);
               }
           }

        }
    };

    //Matrix elem torlese, ha nem letezik nem default ertek
    // az adott koordiniatan, akkor nem csinal semmit
    //Kiindexeles eseten hibat dob
    void clear(int x, int y){
        if(x < 0 || y < 0) {
            throw UnderFlowException();
        }else if(x > sizex-1 || y > sizey-1){
            throw OverFlowException();
        }else{
            if(head != nullptr) {
                for (Node *node = head; node != nullptr; node = node->next) {
                    if (node->data.gety() == y) { //létezik a sor
                        if(node->data.clear(x)){
                            deleterow(node);
                        }
                        break;
                    } else if (node->data.gety() >y) {
                        break;
                    }
                }
            }
        }
    }

    void deleterow(Node *node){
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

    void clearemptys(int x, int y){
        if(x < 0 || y < 0){                          //size-1 a méret?
            throw UnderFlowException();
        }else if(x > sizex-1 || y > sizey-1){
            throw OverFlowException();
        }else{
                Node *node = head;
                while(node != nullptr){
                    if(node->data.clearemptys()){
                        Node *tmp = node->prev;
                        deleterow(node);
                        if(tmp == nullptr){
                            node = head;
                        }else{
                            node = tmp->next;
                        }
                    }else {
                        node = node->next;
                    }
                }
        }
    };

    void setdefvalue(double setval2){
        defValue = setval2;
    }

    //Osszeadas operator - hibat dob ha nem azonos dimenzioju a 2 matrix
    SparseMatrix operator+(const SparseMatrix &other)const{//??????????????????????????????????????????????????????????
        if(sizex != other.sizex || sizey != other.sizey){
            throw NoMatchingMatrixException();
        }else {
                SparseMatrix newmatrix = SparseMatrix(sizex,sizey,defValue);
                Node *node = head;
                Node *othernode = other.head;
                for(int i = 0;i<sizey-1;i++) { //végigmegyünk a sizey-on
                    //double newdata = 0;
                    if (node != nullptr && othernode != nullptr) { //tartalmaz-e a két mátrix számunkra még érdekes sorokat
                        if (node->data.gety() == i && othernode->data.gety() == i) { //mind2 mátrix ugyanazon koordinátáin van-e adat
                            node->data.addline(othernode->data, sizex);
                            node = node->next;
                            othernode = othernode->next;
                        } else if (node->data.gety() == i) { //csak egyiknek van adat y-on
                            Sor newsor = Sor(i, other.defValue);
                            Node* tmp = new Node(newsor);
                            node->data.addline(tmp->data, sizex);
                            node = node->next;
                        } else if (othernode->data.gety() == i) { //csak másiknak van adata y-on
                            Sor newsor = Sor(i, defValue);
                            Node *tmp = new Node(newsor);
                            tmp->data.addline(othernode->data, sizex);
                            while(!tmp->data.isEmpty()){
                                int mx = tmp->data.gethead()->data.x;
                                //Mezo m = Mezo(tmp->data.out());
                                double md = tmp->data.out().data;
                                newmatrix.set(mx,i,md); //sorból kiszedjük egyesével az adatokat, és settel beirjuk a létrehozott táblázatba
                            }
                            othernode = othernode->next;
                        }
                    }
                    else if(node != nullptr){ //csak egyik matrixnak van még nem beírt sora
                        if(node->data.gety() == i){
                            Sor newsor = Sor(i, other.defValue);
                            node->data.addline(newsor, sizex);
                            node = node->next;
                        }
                    }else if(othernode != nullptr){ //másiknak -||-
                        if (othernode->data.gety() == i) {
                            Sor newsor = Sor(i, defValue);
                            Node *tmp = new Node(newsor);
                            tmp->data.addline(othernode->data, sizex);
                            while(!tmp->data.isEmpty()){
                                int mx = tmp->data.gethead()->data.x;
                                //Mezo m = Mezo(tmp->data.out());
                                double md = tmp->data.out().data;
                                newmatrix.set(mx,i,md); //sorból kiszedjük egyesével az adatokat, és settel beirjuk a létrehozott táblázatba
                            }
                        }
                    }else{
                        break;
                    }
                }

        newmatrix.defValue = defValue + other.defValue;
        return newmatrix;

        }//return smth

    };
    //ha van egyező adatos akkor összeadjuk
    //ha az egyik létezik a default értékkel módosítjuk
    //ha mind2nek defaultját össze kéne adni?


    int getsize_x(){
        return sizex;
    }
    int getsize_y(){
        return sizey;
    }
    double getdefValue(){
        return defValue;
    }
};
#endif //NHF1_SKELETON_SPARSEMATRIX_HPP
