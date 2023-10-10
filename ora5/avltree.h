#ifndef AVLTREE_HPP_INCLUDED
#define AVLTREE_HPP_INCLUDED

#include <algorithm>
#include <iostream>

#include "exceptions.h"

//
// AVL fa osztály
// DEFINÍCIÓ
//
template <class T> class AvlTree {
private:
    // Belsõ csúcs struktúra, kiegészítve a magassággal
    class Node {
    public:
        Node *parent;
        Node *left, *right;
        int height; //új meta-adat a részfa ideiglenes magasságának tárolásához
        T key;

        explicit Node(const T &k)
                : parent(nullptr), left(nullptr), right(nullptr), height(1), key(k) {}
        Node(const T &k, Node *p)
                : parent(p), left(nullptr), right(nullptr), height(1), key(k) {}

        //-2, -1, 0, 1 és 2 lehet, megfeleltethető a diákban szereplő --, ++, stb.
        // jelölésnek
        int balanceFactor() const { return _height(right) - _height(left); }

        void updateHeight() {
            height = std::max(_height(left), _height(right)) + 1;
        }

    private:
        // Segédfüggvény NULL Node-ok magasságához
        static int _height(const Node *x) { return (x == nullptr) ? 0 : x->height; }
    };

    // Gyökér elem
    Node *root;

    // Felszabadító függvény
    void _destroy(Node *x);

    // Bináris keresőfa segédfüggvények
    static Node *_min(Node *x);
    static Node *_max(Node *x);
    static Node *_next(Node *x);
    static Node *_prev(Node *x);

    static std::ostream &_inorder(Node *i, std::ostream &o);
    static std::ostream &_preorder(Node *i, std::ostream &o);
    static std::ostream &_postorder(Node *i, std::ostream &o);

    static std::size_t _size(Node *x);

    // Új kereső segédfüggvény
    Node *_find(const T &key) const;

    // AVL kiegyensúlyozó függvények
    void _rotateLeft(Node *x);
    void _rotateRight(Node *x);
    void _rebalance(Node *x);

    // Ellenõrzõ segédfüggvény
    static void _validateAvl(Node *x);

public:
    // Konstruktor és destruktor
    AvlTree() : root(nullptr) {}
    ~AvlTree() { _destroy(root); }

    // Másoló konstruktor és értékadás operátor, valamint segéd függgvényeik
    AvlTree(const AvlTree<T> &t);
    AvlTree &operator=(const AvlTree<T> &t);
    Node *getRoot() const;
    Node *copyOf(Node *n, Node *p);

    // Alapmûveletek
    std::size_t size() const { return _size(root); }
    bool isEmpty() const { return root == nullptr; }

    bool find(const T &k) const;
    void insert(const T &k);
    void remove(const T &k);

    std::ostream &inorder(std::ostream &o);
    std::ostream &preorder(std::ostream &o);
    std::ostream &postorder(std::ostream &o);

    // Ellenõrzõ függvény
    void validate() const;
};

//
// AVL fa osztály
// FÜGGVÉNYIMPLEMENTÁCIÓK
//

// Balra forgatás ...
// az x csúcs körül, illetve más szóhasználattal
// az x csúcs és a jobb gyereke közötti él mentén.
// Előfeltétel, hogy x és a jobb gyereke létezzenek.
template <class T> void AvlTree<T>::_rotateLeft(Node * /*x*/) {
    // TODO
}

// Jobbra forgatás ...
// az x csúcs körül, illetve más szóhasználattal
// az x csúcs és a bal gyereke közötti él mentén.
// Előfeltétel, hogy x és a bal gyereke létezzenek.
template <class T> void AvlTree<T>::_rotateRight(Node * /*x*/) {
    // TODO
}

// Az újrakiegyensúlyozó függvény
// ** Az AVL fa lelke **
//
// Miután a módosító mûveletet (beszúrást vagy törlést) a bináris keresõfáknál
// tanult módon végrehajtottuk, ezt a függvényt kell meghívni a beszúrt, illetve
// az eltávolítottuk csúcs szülõjére, hogy a fában felfelé haladva frissítse a
// magasságinformációkat, és szükség esetén forgatásokkal helyreállítsa az AVL
// fa tulajdonságait.
//
// Pontos elõfeltételek:
// x NULL, vagy
// x mindkét részfája érvényes, kiegyensúlyozott AVL fa helyes
// magasságértékekkel (üres részfa is helyes AVL fa)
template <class T> void AvlTree<T>::_rebalance(Node * /*x*/) {
    // TODO
}

// Rekurzívan felszabadítja a csúcsokat.
// A destruktor hívja meg a gyökérre.
template <class T> void AvlTree<T>::_destroy(Node *x) {
    if (x != nullptr) {
        _destroy(x->left);
        _destroy(x->right);
        delete x;
    }
}

// Segéd függvény a copy constructor-hoz valamint assigment operator-hoz
template <class T>
typename AvlTree<T>::Node *AvlTree<T>::copyOf(Node *n, Node *p) {

    if (n == nullptr)
        return nullptr; // Ha a másolandó node üres nincs dolgunk

    Node *x = new Node(n->key, p); // Létrehozzuk az új node-ot a másik fa a
    // alapján, de az új fához kapcsoljuk
    x->left = copyOf(n->left, x);
    x->right = copyOf(n->right, x);

    return x;
}

// Másoló konstruktor (klónozás - meglévő fából készít másolatot)
template <class T> AvlTree<T>::AvlTree(const AvlTree<T> &t) {

    root = copyOf(t.getRoot(), nullptr);
}

// Assigment operator (meglévő fát tesz egyenlővé egy másikkal)
template <class T> AvlTree<T> &AvlTree<T>::operator=(const AvlTree<T> &t) {

    if (&t == this)
        return *this; // Ha a két fa megegyezik nincs dolgunk

    _destroy(root); // Ha nem, akkor először töröljük a már meglévő fát

    root = copyOf(t.getRoot(), nullptr);

    return *this;
}

// Visszaadja az x gyökerű részfa legkisebb értékű csúcsát.
// Előfeltétel: x != nil
template <class T> typename AvlTree<T>::Node *AvlTree<T>::_min(Node *x) {
    while (x->left != 0)
        x = x->left;
    return x;
}

// Visszaadja az x gyökerű részfa legnagyobb értékű csúcsát.
// Előfeltétel: x != nil
template <class T> typename AvlTree<T>::Node *AvlTree<T>::_max(Node *x) {
    while (x->right != 0)
        x = x->right;
    return x;
}

// Visszaadja a fából az x csúcs rákövetkezőjét,
// vagy nil-t, ha x az legnagyobb kulcsú elem.
// Előfeltétel: x != nilif(isEmpty())
template <class T> typename AvlTree<T>::Node *AvlTree<T>::_next(Node *x) {
    if (x->right != 0)
        return _min(x->right);

    Node *y = x->parent;
    while (y != 0 && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}

// Visszaadja a fából az x csúcs megelőzőjét,
// vagy nil-t, ha x az legkisebb kulcsú elem.
// Előfeltétel: x != nil
template <class T> typename AvlTree<T>::Node *AvlTree<T>::_prev(Node *x) {
    if (x->left != 0)
        return _max(x->left);

    Node *y = x->parent;
    while (y != 0 && x == y->left) {
        x = y;
        y = y->parent;
    }
    return y;
}

// Rekurzívan meghatározza, és visszaadja
// az x gyökerû részfa elemeinek számát.
// Megjegyzés: üres fára is mûködik -> 0-t ad vissza
template <class T> std::size_t AvlTree<T>::_size(Node *x) {
    if (x == nullptr)
        return 0;
    else
        return _size(x->left) + _size(x->right) + 1;
}

// Lekérdezi, hogy található-e k kulcs a fában.
template <class T>
typename AvlTree<T>::Node *AvlTree<T>::_find(const T &key) const {
    Node *x = root;
    while (x != nullptr) {
        if (key < x->key) {
            x = x->left;
        } else if (x->key < key) {
            x = x->right;
        } else {
            return x;
        }
    }
    return nullptr;
}

// Lekérdezi, hogy található-e k kulcs a fában.
// Igazat ad vissza, ha található.
template <class T> bool AvlTree<T>::find(const T &k) const {
    return _find(k) != nullptr;
}

// Beszúrja a k értéket a fába.
// Ha már van k érték a fában, akkor nem csinál semmit.
template <class T> void AvlTree<T>::insert(const T &k) {
    // Keresés
    Node *p = nullptr; // p: parent
    Node *x = root;

    while (x != nullptr) {
        p = x;
        if (k < x->key) {
            x = x->left;
        } else if (x->key < k) {
            x = x->right;
        }
            // Ha megtaláltuk a beszúrandó elemet, nincs más dolgunk.
        else {
            return;
        }
    }

    // Új csúcs létrehozása és bekötése
    x = new Node(k, p);
    if (p == nullptr)
        root = x;
    else if (x->key < p->key)
        p->left = x;
    else
        p->right = x;

    // Beszúrás utáni kiegyensúlyozás
    _rebalance(p);
}

// Eltávolítja a k értéket a fából.
// Ha nem volt k érték a fában, akkor nem csinál semmit.
template <class T> void AvlTree<T>::remove(const T &k) {
    // Keresés
    Node *z = _find(k);

    // Ha nincs ilyen kulcsú elem a fában, úgy nincs dolgunk.
    if (z == nullptr)
        return;

    // Csúcs kivágása a fából és felszabadítás
    // y: az a csúcs, amit törölni fogunk
    // w: 'y' szülõje
    // x: 'y' gyereke (ha van neki)
    Node *x, *y, *w;

    if (z->left == nullptr || z->right == nullptr)
        y = z;
    else
        y = _next(z);

    w = y->parent;
    if (y->left != nullptr)
        x = y->left;
    else
        x = y->right;

    if (x != nullptr)
        x->parent = y->parent;
    if (y->parent == nullptr)
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    if (y != z)
        z->key = y->key;
    delete y;

    // Törlés utáni kiegyensúlyozás
    if (w != nullptr) {
        _rebalance(w);
    }
}

// Rekurzív segédfüggvény a validate() függvényhez
// Ellenõrzi, hogy az x gyökerû fára teljesülnek-e az AVL tulajdonságok.
template <class T> void AvlTree<T>::_validateAvl(Node *x) {
    if (x != nullptr) {
        _validateAvl(x->left);
        _validateAvl(x->right);

        // Magasság ellenõrzése
        int h = x->height;
        x->updateHeight();
        if (x->height != h) {
            throw InvalidAvlTree();
        }

        // AVL tulajdonság ellenõrzése
        if (std::abs(x->balanceFactor()) > 1) {
            throw InvalidAvlTree();
        }
    }
}

// Ez a függvény a debuggolást segíti.
// Ellenõrzi, hogy a gyökérbõl elérhetõ fa érvényes
// bináris keresõfa, illetve érvényes AVL fa-e.
template <class T> void AvlTree<T>::validate() const {
    // Keresõfa tulajdonság ellenõrzése bejárással
    if (root != nullptr) {
        Node *x = _min(root);
        T prev = x->key;
        x = _next(x);
        while (x) {
            if (!(prev < x->key)) {
                throw InvalidBinarySearchTree();
            }
            prev = x->key;
            x = _next(x);
        }
    }

    // AVL fa tulajdonság ellenõrzése
    _validateAvl(root);
}

// Bináris keresőfa bejárások kívülről elérhető függvényei.
template <class T> std::ostream &AvlTree<T>::preorder(std::ostream &o) {
    if (isEmpty()) {
        o << "A fa ures!" << std::endl;
        return o;
    }
    return _preorder(root, o);
}

template <class T> std::ostream &AvlTree<T>::postorder(std::ostream &o) {
    if (isEmpty()) {
        o << "A fa ures!" << std::endl;
        return o;
    }
    return _postorder(root, o);
}

template <class T> std::ostream &AvlTree<T>::inorder(std::ostream &o) {
    if (isEmpty()) {
        o << "A fa ures!" << std::endl;
        return o;
    }
    return _inorder(root, o);
}

// Bináris keresőfa bejárások implementációi.
// Preorder bejárás.
template <class T>
std::ostream &AvlTree<T>::_preorder(Node *i, std::ostream &o) {
    o << i->key << ", ";
    if (i->left != nullptr)
        _preorder(i->left, o);
    if (i->right != nullptr)
        _preorder(i->right, o);
    return o;
}

// Postorder bejárás.
template <class T>
std::ostream &AvlTree<T>::_postorder(Node *i, std::ostream &o) {
    if (i->left != nullptr)
        _postorder(i->left, o);
    if (i->right != nullptr)
        _postorder(i->right, o);
    o << i->key << ", ";
    return o;
}

// Inorder bejárás.
template <class T>
std::ostream &AvlTree<T>::_inorder(Node *i, std::ostream &o) {
    if (i->left != nullptr)
        _inorder(i->left, o);
    o << i->key << ", ";
    if (i->right != nullptr)
        _inorder(i->right, o);
    return o;
}

template <class T> typename AvlTree<T>::Node *AvlTree<T>::getRoot() const {
    if (isEmpty())
        throw InternalError("A fa ures.");
    return root;
}

#endif // AVLTREE_HPP_INCLUDED