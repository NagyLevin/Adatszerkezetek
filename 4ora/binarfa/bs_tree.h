#ifndef BIN_TREE_HPP_INCLUDED
#define BIN_TREE_HPP_INCLUDED

#include <algorithm>
#include <iostream>

#include "exceptions.h"

using namespace std;

//
// Bináris keresőfa osztály
// DEFINÍCIÓ
//
template<class T>
class Bs_tree {
    // Belső csúcs struktúra
    struct Node {
        Node *parent;
        Node *left, *right;
        T key;

        explicit Node(const T& k) :
                parent(nullptr), left(nullptr), right(nullptr), key(k) {
        }
        Node(const T& k, Node *p) :
                parent(p), left(nullptr), right(nullptr), key(k) {
        }
    };

    // Adattag
    Node *root;     //gyoker

    // Felszabadító függvény
    void _destroy(Node* x);

    // Segédfüggvények
    static Node* _min(Node* x);
    static Node* _max(Node* x);
    static Node* _next(Node* x);
    static Node* _prev(Node* x);

    ostream& _inorder(Node* i, ostream& o);
    ostream& _preorder(Node* i, ostream& o);
    ostream& _postorder(Node* i, ostream& o);

    size_t _size(Node* x) const;

    Node* _getroot() const;
    Node* _copyOf(Node* n, Node* p);

public:
    // Konstruktor és destruktor
    Bs_tree() : root(nullptr) {}

    ~Bs_tree() {
        _destroy(root);
    }

    // Másoló konstruktor és operátor, valamint segéd függvényeik
    Bs_tree(const Bs_tree<T>& t);
    Bs_tree& operator=(const Bs_tree<T>& t);

    // Alapműveletek
    size_t size() const {
        return _size(root);
    }
    bool isempty() const {
        return root == nullptr;
    }

    T getroot() const;
    bool find(const T& k) const;
    void insert(const T& k);
    void remove(const T& k);

    ostream& inorder(ostream& o);   //csak kiiras sorrendje
    ostream& preorder(ostream& o);  //csak kiiras sorrendje
    ostream& postorder(ostream& o); //csak kiiras sorrendje

    T min() const {
        if(isempty()) {
            throw internal_error("A fa ures.");
        }
        return _min(root)->key;
    }
    T max() const {
        if(isempty()) {
            throw internal_error("A fa ures.");
        }
        return _max(root)->key;
    }

};

//
// Bináris keresőfa osztály
// FÜGGVÉNYIMPLEMENTÁCIÓK
//

// Rekurzívan felszabadítja a csúcsokat.
// A destruktor hívja meg a gyökérre.
template<class T>
void Bs_tree<T>::_destroy(Node* x) {

    if(x != nullptr){   //ha nullptr akkor leallitja a rekurziot    //nem lehet mas sorrendben torlesnel nincs post, pre meg inorder
        _destroy(x->left);
        _destroy(x->right);
        delete x;

    }

}

// Segéd függvény a copy constructor-hoz valamint assigment operator-hoz
template<class T>
typename Bs_tree<T>::Node* Bs_tree<T>::_copyOf(Node* n, Node* p) {

    if(n == nullptr){//elertuk a fa leveleit (veget)
        return nullptr;
    }

    Node *x = new Node(n->_key, p); //key a tarolt ertek
    x->left = _copyOf(n->left,p);  //lemásoljuk a csucsot
    x->right =_copyOf(n->right,p);  //_copyOf(melyiket,hova);

    return x;   //visszaadjuk a node-ot
}

// Másoló konstruktor (klónozás - meglévő fából készít másolatot)
template<class T>
Bs_tree<T>::Bs_tree(const Bs_tree<T>& t) {
    root = _copyOf(t.root, nullptr);    //uj fa
}

// Assigment operator (meglévő fát tesz egyenlővé egy másikkal)
template<class T>
Bs_tree<T>& Bs_tree<T>::operator=(const Bs_tree<T>& t) {
  if(&t == this){   //nem azonos-e azzal ami mar van?
      return *this;//ha azonos, ugyanazt visszaadom
  }
    _destroy(root); //toroljuk az ertekul adott fat //felszabaditjuk a memot //nemtudjuk hogy egyforma meretu e a ket fa

    root = _copyOf(t.root); //uj fa beillsezstese a regi copyjabol

    return *this;

}

// Visszaadja az x gyökerű részfa legkisebb értékű csúcsát.
// Előfeltétel: x != nil
template<class T>
typename Bs_tree<T>::Node *Bs_tree<T>::_min(Node* x) {

    while (x->left != nullptr){   //fa bejarasa, amig van baloldali gyerek addig megyunk
        x = x->left;


    }
    return x;

}

// Visszaadja az x gyökerű részfa legnagyobb értékű csúcsát.
// Előfeltétel: x != nil
template<class T>
typename Bs_tree<T>::Node *Bs_tree<T>::_max(Node*x) {//ugyan az csak  //feltetelezzuk hogy a fa rendezett
    while (x->right != nullptr){
        x = x->right;


    }
    return x;
}

// Visszaadja a fából az x csúcs rákövetkezőjét,
// vagy nil-t, ha x az legnagyobb kulcsú elem.
// Előfeltétel: x != nilif(isempty())
template<class T>
typename Bs_tree<T>::Node *Bs_tree<T>::_next(Node* x) { //rakovetkezo elem megtalalasa

    if(x->right != nullptr){
        return _min(x->right);
    }

    Node *y = x->parent;

    while (y != nullptr && x== y->right){
        x = y;
        y = y->parent;

    }
    return y;

}

// Visszaadja a fából az x csúcs megelőzőjét,
// vagy nil-t, ha x az legkisebb kulcsú elem.
// Előfeltétel: x != nil
template<class T>
typename Bs_tree<T>::Node *Bs_tree<T>::_prev(Node* x) { //next hez kepest a masik agon valo fellepdeles
    if(x->left != nullptr){
        return _max(x->left);
    }

    Node *y = x->parent;

    while (y != nullptr && x== y->left){
        x = y;
        y = y->parent;

    }
    return y;




}

// Rekurzívan meghatározza, és visszaadja
// az x gyökerű részfa elemeinek számát.
// Megjegyzés: üres fára is működik -> 0-t ad vissza
template<class T>
size_t Bs_tree<T>::_size(Node* x) const {
if(x == nullptr){   //ha ures a fa
    return 0;
} else{

    return _size(x->left) + _size(x->right) + 1;    //jobb ag + bal ag + a csucs ami 1
}

}

template<class T>
T Bs_tree<T>::getroot() const {
if(isempty()){
    throw internal_error("A fa ures");
}

    return _getroot()->key; // visszaadja a gyoker erteket


}

// Lekérdezi, hogy található-e k kulcs a fában.
// Igazat ad vissza, ha található.
template<class T>
bool Bs_tree<T>::find(const T& k) const {   //visszaadja hogy van-e ilyen elem a faban
    Node *x = root ;
    while (x != nullptr && (k > x->key ||  x->key < k  )){
        if(k < x->key){
            x = x->left;
        } else{
            x = x->right;

        }
    }
    return x;   //vagy x!= nullptr
}

// Beszúrja a k értéket a fába.
// Ha már van k érték a fában, akkor nem csinál semmit.
template<class T>
void Bs_tree<T>::insert(const T& /*k*/) {
    // TODO
    throw method_not_implemented();
}

// Eltávolítja a k értéket a fából.
// Ha nem volt k érték a fában, akkor nem csinál semmit.
template<class T>
void Bs_tree<T>::remove(const T& k) {




}

// Bináris keresőfa bejárások kívülről elérhető függvényei.
template<class T>
ostream& Bs_tree<T>::preorder(ostream& /*o*/) {
    // TODO
    throw method_not_implemented();
}

template<class T>
ostream& Bs_tree<T>::postorder(ostream& /*o*/) {
    // TODO
    throw method_not_implemented();
}

template<class T>
ostream& Bs_tree<T>::inorder(ostream& /*o*/) {
    // TODO
    throw method_not_implemented();
}

// Bináris keresőfa bejárások implementációi.
// Preorder bejárás.
template<class T>
ostream& Bs_tree<T>::_preorder(Node* /*i*/, ostream& /*o*/) {
    // TODO
    throw method_not_implemented();
}

// Postorder bejárás.
template<class T>
ostream& Bs_tree<T>::_postorder(Node* /*i*/, ostream& /*o*/) {
    // TODO
    throw method_not_implemented();
}

// Inorder bejárás.
template<class T>
ostream& Bs_tree<T>::_inorder(Node* /*i*/, ostream& /*o*/) {
    // TODO
    throw method_not_implemented();
}

template<class T>
typename Bs_tree<T>::Node* Bs_tree<T>::_getroot() const {
    // TODO
    throw method_not_implemented();
}

#endif // BIN_TREE_HPP_INCLUDED