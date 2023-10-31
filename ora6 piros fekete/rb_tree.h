#ifndef RB_TREE_HPP_INCLUDED
#define RB_TREE_HPP_INCLUDED

#include "exceptions.h"

#include <cassert>
//nullpointer helyett emptyleaf


// Orai kod - statikus _min, _max, _prev, _next fuggvenyekkel

//
// Piros-fekete fa osztály
// DEFINÍCIÓ
//
template <class T> class rb_tree {

    // Szín felsoroló típus
    enum color_t { black, red };

    // Belső csúcs struktúra
    struct node {
        node *parent;
        node *left, *right;
        color_t color;
        T key;

        // Az alapértelmezett konstruktor csak az empty_leaf létrehozására szolgál
        node() : parent(this), left(this), right(this), color(black), key() {}

        // Konstruktor csúcs létrehozására beszúráskor
        node(const T &k, node *p)
                : parent(p), left(empty_leaf), right(empty_leaf), color(red), key(k) {}
    };

    // Adattagok
    // node() default konstruktor meghívása -> _empty_leaf létrejön
    static inline node _empty_leaf;
    // empty_leaf a _empty_leaf-re mutató pointer
    static inline node *empty_leaf = &_empty_leaf;

    // Peldany valtozo
    node *root;

    // Felszabadító függvény
    static void _destroy(node *x);

    // Segédfüggvények
    static node *_min(node *x);
    static node *_max(node *x);
    static node *_next(node *x);
    static node *_prev(node *x);

    static size_t _size(node *x);

    // Kiegyensúlyozásért felelős függvények
    void _rotate_left(node *x);
    void _rotate_right(node *x);

    void _rebalance_after_insert(node *x);
    void _rebalance_after_remove(node *x);


    // Ellenőrző segédfüggvények
    static size_t _validate(node *x);

public:
    // Konstruktor és destruktor
    rb_tree() : root(empty_leaf) {}
    ~rb_tree() { _destroy(root); }

    // Másoló konstruktor és operátor egyelőre nincs implementálva
    rb_tree(const rb_tree & t) = delete;
    rb_tree &operator=(const rb_tree & t) =delete;
    // Alapműveletek
    [[nodiscard]] size_t size() const { return _size(root); }

    bool find(const T &k) const;
    void insert(const T &k);
    void remove(const T &k);

    // Ellenőrző függvény
    void validate() const;

};

//
// Piros-fekete fa osztály
// FÜGGVÉNYIMPLEMENTÁCIÓK
//
// Rekurzívan felszabadítja a csúcsokat.
// A destruktor hívja meg a gyökérre.
template <class T> void rb_tree<T>::_destroy(node *x) {
    if (x != empty_leaf) {
        _destroy(x->left);
        _destroy(x->right);
        delete x;
    }
}



// Visszaadja az x gyökerű részfa legkisebb értékű csúcsát.
// Előfeltétel: x != empty_leaf
template <class T> typename rb_tree<T>::node *rb_tree<T>::_min(node *x) {
    while (x->left != empty_leaf)
        x = x->left;
    return x;
}

// Visszaadja az x gyökerű részfa legnagyobb értékű csúcsát.
// Előfeltétel: x != empty_leaf
template <class T> typename rb_tree<T>::node *rb_tree<T>::_max(node *x) {
    while (x->right != empty_leaf)
        x = x->right;
    return x;
}

// Visszaadja a fából az x csúcs rákövetkezőjét,
// vagy empty_leaf-t, ha x a legnagyobb kulcsú elem.
// Előfeltétel: x != empty_leaf
template <class T> typename rb_tree<T>::node *rb_tree<T>::_next(node *x) {
    if (x->right != empty_leaf)
        return _min(x->right);

    node *y = x->parent;
    while (y != empty_leaf && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}

// Visszaadja a fából az x csúcs megelőzőjét,
// vagy empty_leaf-t, ha x a legkisebb kulcsú elem.
// Előfeltétel: x != empty_leaf
template <class T> typename rb_tree<T>::node *rb_tree<T>::_prev(node *x) {
    if (x->left != empty_leaf)
        return _max(x->left);

    node *y = x->parent;
    while (y != empty_leaf && x == y->left) {
        x = y;
        y = y->parent;
    }
    return y;
}

// Rekurzívan meghatározza, és visszaadja
// az x gyökerű részfa elemeinek számát.
// Megjegyzés: üres fára is működik -> 0-t ad vissza
template <class T> size_t rb_tree<T>::_size(node *x) {
    if (x == empty_leaf)
        return 0;
    else
        return _size(x->left) + _size(x->right) + 1;
}

// Balra forgatás ...
// az x csúcs körül, illetve más szóhasználattal
// az x csúcs és a jobb gyereke közötti él mentén.
// Előfeltétel, hogy x létezik és a jobb gyereke nem empty_leaf.
template <class T> void rb_tree<T>::_rotate_left(node *x) {
    assert(nullptr != x && "Balra forgatas nullptr-en");
    assert(empty_leaf != x->right && "Balra forgatas nem letezo jobb gyerekkel");
    // y-nak nevezzük el x jobb gyerekét
    // a forgatás az x-y él mentén történik
    node *y = x->right;

    // y bal gyereke forgatás után x jobb gyereke lesz
    // a gyerek szülő mezőjét is frissíteni kell
    x->right = y->left;
    if (y->left != empty_leaf) /* a feltétel opcionális */
        y->left->parent = x;

    // az adott részfának mostantól y lesz a gyökere
    // így megkapja x szülőjét, és
    // a szülőnél is be kell állítani, hogy mostantól y az ő gyereke
    y->parent = x->parent;
    if (x->parent == empty_leaf)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    // végül beállítjuk x és y között a szülő-gyerek kapcsolatot
    y->left = x;
    x->parent = y;
}

// Jobbra forgatás ...
// az x csúcs körül, illetve más szóhasználattal
// az x csúcs és a bal gyereke közötti él mentén.
// Előfeltétel, hogy x létezik és a bal gyereke nem empty_leaf.
template <class T> void rb_tree<T>::_rotate_right(node *x) {
    assert(nullptr != x && "Jobbra forgatas nullptr-en");
    assert(empty_leaf != x->left && "Jobbra forgatas nem letezo bal gyerekkel");
    // y-nak nevezzük el x bal gyerekét
    // a forgatás az x-y él mentén történik
    node *y = x->left;

    // y jobb gyereke forgatás után x bal gyereke lesz
    // a gyerek szülő mezőjét is frissíteni kell
    x->left = y->right;
    if (y->right != empty_leaf) /* a feltétel opcionális */
        y->right->parent = x;

    // az adott részfának mostantól y lesz a gyökere
    // így megkapja x szülőjét, és
    // a szülőnél is be kell állítani, hogy mostantól y az ő gyereke
    y->parent = x->parent;
    if (x->parent == empty_leaf)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    // végül beállítjuk x és y között a szülő-gyerek kapcsolatot
    y->right = x;
    x->parent = y;
}

// Beszúrás utáni kiegyensúlyozás
// A beszúrt piros csúcsra kell meghívni
template <class T> void rb_tree<T>::_rebalance_after_insert(node *x ) {
    // x: problemas node - (piros szulo) piros gyermeke
    // u: x nagybacsija
    // p: szulo
    // g: nagyszulo

    /* *******************
     * pl.    g          *
     *       / \         *
     *      p   u        *
     *     /             *
     *    x              *
     *********************/

    // A while ciklus minden egyes lefutasara egy adott szinten tortenik
    // a PF fa tulajdonsagok helyreallitasa.

    while (x->parent->color == red){
        if(x->parent == x->parent->parent->left){ //ha az x a nagybasi, akkor o u
            node *u = x->parent->parent->right; //u a nagybacsi

            if(u->color == red){

                // 1. eset:
                //    -- elofeltetel  : u PIROS
                //    -- kovetkezmeny : g PIROS , p FEKETE , u FEKETE
                //                      Ket szintel feljebb lepve kezdjuk elorol a 1. esettol

                x->parent->color = black;
                u->color = black;
                x->parent->parent->color = red;
                x = x->parent->parent;
                continue;
                //elso eset vege
            }


            if(x == x->parent->right){
                // 2. eset:
                //    -- elofeltetel  : u FEKETE , x JOBB gyermek
                //    -- kovetkezmeny : x BAL gyermek
                x = x->parent;
                _rotate_left(x);
                //2 eset vege, utana egybol harmadik eset

            }


            // 3. eset:
            //    -- elofeltetel  : u FEKETE , x BAL gyermek
            //    -- kovetkezmeny : a PF fa tulajdonsagai helyrealltak
            x->parent->color = black;
            x->parent->parent->color = red;
            _rotate_right(x->parent->parent);
            //harmadik eset vege





        }
        else{

            node *u = x->parent->parent->left; //u a nagybacsi

            if(u->color == red){

                // 1. eset:
                //    -- elofeltetel  : u PIROS
                //    -- kovetkezmeny : g PIROS , p FEKETE , u FEKETE
                //                      Ket szintel feljebb lepve kezdjuk elorol a 1. esettol

                x->parent->color = black;
                u->color = black;
                x->parent->parent->color = red;
                x = x->parent->parent;
                continue;
                //elso eset vege
            }


            if(x == x->parent->left){
                // 2. eset:
                //    -- elofeltetel  : u FEKETE , x JOBB gyermek
                //    -- kovetkezmeny : x BAL gyermek
                x = x->parent;
                _rotate_right(x);
                //2 eset vege, utana egybol harmadik eset

            }


            // 3. eset:
            //    -- elofeltetel  : u FEKETE , x BAL gyermek
            //    -- kovetkezmeny : a PF fa tulajdonsagai helyrealltak
            x->parent->color = black;
            x->parent->parent->color = red;
            _rotate_left(x->parent->parent);
            //harmadik eset vege


        }



    }
    root->color = black;


}

// Törlés utáni utáni kiegyensúlyozás
// A kivágott csúcs gyerekére kell meghívni, amely most
// piros-fekete vagy kétszeresen fekete.
template <class T> void rb_tree<T>::_rebalance_after_remove(node * x) {
    // x: problemas node (DUPLA FEKETE)
    // w: x testvere

    // A while ciklus minden egyes lefutasara egy adott szinten tortenik
    // a PF fa tulajdonsagok helyreallitasa.
    //
    // Felfele haladunk. Ha elerunk egy piros nodot, vagy a gyokeret,
    // akkor vegeztunk a helyreallitassal.




    while (x != root && x->color == black){ //amig nem ertunk el a fekete gyokerhez

        if(x == x->parent->left){   //ha mi a balgyerek vagyunk akkor w a jobbgyerek
            node *w = x->parent->right;

            // 1. eset
            //    -- elofeltetel  : w->color == red   [a testver PIROS]
            //    -- kovetkezmeny : w->color == black [a testver FEKETE] (2. eset, 3.
            //    eset vagy 4. eset)

            if(w->color == red){ //testvér piros
                w->color = black;
                x->parent->color = red;
                _rotate_left(x->parent);
                w = x->parent->right;


            }
            //1. eset vege


            // 2. eset
            //    -- elofeltetel  : w es w mindket gyermeke FEKETE
            //    -- kovetkezmeny : a duple fekete eggyel feljebb propagal,
            //                      ezen a szinten nincs tobb keresnivalonk
            //                      Elorol az egeszet a x->parent node-al.

            if(w->left->color == black && w->right->color == black){

                w->color = red;



                x = x->parent; //feljebb lepes
                continue;//kovetkezo iteracioban folytat

            }

            // 3. eset
            //    -- elofeltetel  : w FEKETE , w->left PIROS , w->right FEKETE
            //    -- kovetkezmeny : w FEKETE , w->left ????? , w->right PIROS   (4. eset)
            if(w->right->color == black){ //ha fekete, akkor a bal gyerekkel megcsereljuk a szinet
                w->left->color = black;
                w->color = red;
                _rotate_left(w); //pirosat agyerekebe
                w = x->parent->right;


            }

            // 4. eset: w fekete, w->right
            //    -- elofeltetel  : w FEKETE , w->right PIROS
            //    -- kovetkezmeny : a PF fa tulajdonsagai helyrealltak

            w->color = x->parent->color; //testver szine megcserelve a szulovel
            x->parent->color =black;
            w->right->color = black;
            _rotate_left(x->parent);

            break;





        }
        else {  //ha mi jobbgyerekek vagyunk

            node *w = x->parent->left;

            // 1. eset
            //    -- elofeltetel  : w->color == red   [a testver PIROS]
            //    -- kovetkezmeny : w->color == black [a testver FEKETE] (2. eset, 3.
            //    eset vagy 4. eset)

            if(w->color == red){ //testvér piros
                w->color = black;
                x->parent->color = red;
                _rotate_right(x->parent);
                w = x->parent->left;


            }
            //1. eset vege


            // 2. eset
            //    -- elofeltetel  : w es w mindket gyermeke FEKETE
            //    -- kovetkezmeny : a duple fekete eggyel feljebb propagal,
            //                      ezen a szinten nincs tobb keresnivalonk
            //                      Elorol az egeszet a x->parent node-al.

            if(w->left->color == black && w->right->color == black){

                w->color = red;



                x = x->parent; //feljebb lepes
                continue;//kovetkezo iteracioban folytat

            }

            // 3. eset
            //    -- elofeltetel  : w FEKETE , w->left PIROS , w->right FEKETE
            //    -- kovetkezmeny : w FEKETE , w->left ????? , w->right PIROS   (4. eset)
            if(w->right->color == black){ //ha fekete, akkor a bal gyerekkel megcsereljuk a szinet
                w->left->color = black;
                w->color = red;
                _rotate_right(w); //pirosat agyerekebe
                w = x->parent->left;


            }

            // 4. eset: w fekete, w->right
            //    -- elofeltetel  : w FEKETE , w->right PIROS
            //    -- kovetkezmeny : a PF fa tulajdonsagai helyrealltak

            w->color = x->parent->color; //testver szine megcserelve a szulovel
            x->parent->color =black;
            w->left->color = black;
            _rotate_right(x->parent);
            break;
        }





    }







    x->color = black;
}

// Lekérdezi, hogy található-e k kulcs a fában.
// Igazat ad vissza, ha található.
template <class T> bool rb_tree<T>::find(const T &k) const {
    node *x = root;
    while (x != empty_leaf && k != x->key)
        if (k < x->key)
            x = x->left;
        else
            x = x->right;
    return x != empty_leaf;
}

// Beszúrja a k értéket a fába.
// Ha már van k érték a fában, akkor nem csinál semmit.
template <class T> void rb_tree<T>::insert(const T &k) {
    // Keresés
    node *y = empty_leaf;
    node *x = root;
    while (x != empty_leaf && k != x->key) {
        y = x;
        if (k < x->key)
            x = x->left;
        else
            x = x->right;
    }

    // Ha van már ilyen kulcsú elem a fában, úgy nincs dolgunk.
    if (x != empty_leaf)
        return;

    // Új csúcs létrehozása és bekötése
    node *z = new node(k, y);
    if (y == empty_leaf)
        root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;

    // Beszúrás utáni kiegyensúlyozás
    _rebalance_after_insert(z);
}

// Eltávolítja a k értéket a fából.
// Ha nem volt k érték a fában, akkor nem csinál semmit.
template <class T> void rb_tree<T>::remove(const T &k) {
    // Keresés
    node *z = root;
    while (z != empty_leaf && k != z->key)
        if (k < z->key)
            z = z->left;
        else
            z = z->right;

    // Ha nincs ilyen kulcsú elem a fában, úgy nincs dolgunk.
    if (z == empty_leaf)
        return;

    // Csúcs kivágása a fából és felszabadítás
    node *y;
    if (z->left == empty_leaf || z->right == empty_leaf)
        y = z;
    else
        y = _next(z);

    node *x;
    if (y->left != empty_leaf)
        x = y->left;
    else
        x = y->right;

    // FIGYELEM: A következő sor módosíthatja a empty_leaf csúcsot!
    x->parent = y->parent;
    if (y->parent == empty_leaf)
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    if (y != z)
        z->key = y->key;

    bool y_black = y->color == black;
    delete y;

    // Törlés utáni kiegyensúlyozás
    if (y_black)
        _rebalance_after_remove(x);
}

// Rekurzív segédfüggvény a piros-fekete tulajdonságok ellenőrzéséhez
// Paraméterül kapja az ellenőrizendő részfa gyökerét, és visszaadja
// a részfa fekete-magasságát.
template <class T> size_t rb_tree<T>::_validate(node *x) {
    // empty_leaf fekete-magassága nulla
    if (x == empty_leaf)
        return 0;

    // "Minden csúcs színe piros vagy fekete."
    if (x->color != red && x->color != black)
        throw invalid_rb_tree("se nem piros se nem fekete csucs.");

    // "Minden piros csúcs mindkét gyereke fekete."
    if (x->color == red && x->parent->color == red)
        throw invalid_rb_tree("piros violation: piros csucs gyereke piros.");

    // Rekurzív ellenőrzés és fekete-magasság meghatározása
    size_t left_black_height = _validate(x->left);
    size_t right_black_height = _validate(x->right);

    // "Bármely gyökértől levélig vezető úton
    // a fekete csúcsok száma egyenlő."
    if (left_black_height != right_black_height)
        throw invalid_rb_tree("fekete violation: fekete magassagok nem egyeznek.");

    // Visszaadjuk a részfa fekete-magasságát
    return left_black_height + (x->color == black);
}

// Ez a függvény a debugolást segíti.
// Ellenőrzi, hogy a gyökérből elérhető fa érvényes
// bináris keresőfa, illetve érvényes piros-fekete fa-e.
template <class T> void rb_tree<T>::validate() const {
    // Keresőfa tulajdonság ellenőrzése bejárással
    if (root != empty_leaf) {
        node *x = _min(root);
        T prev = x->key;
        while ((x = _next(x)) != empty_leaf) {
            if (!(prev < x->key))
                throw invalid_binary_search_tree();
            prev = x->key;
        }
    }

    //
    // Piros-fekete fa tulajdonságok ellenőrzése
    //

    // empty_leaf csúcs ellenőzése
    // "Minden levél színe fekete."
    if (empty_leaf->left != empty_leaf || empty_leaf->right != empty_leaf ||
        empty_leaf->color != black)
        throw invalid_rb_tree("empty_leaf ertekei megvaltoztak.");

    // "A gyökér színe fekete."
    if (root->color != black)
        throw invalid_rb_tree("gyoker nem fekete!");

    // A fa rekurzív ellenőrzése
    _validate(root);




}




#endif // RB_TREE_HPP_INCLUDED
