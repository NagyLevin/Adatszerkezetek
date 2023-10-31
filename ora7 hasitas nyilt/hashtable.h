#ifndef HASHTABLE_HPP_INCLUDED
#define HASHTABLE_HPP_INCLUDED

#include <iostream>
#include <list>
#include <vector>

// Exception annak kezelésére, ha túlcsordul a túlcsordulási területünk is
class OverflowError : public std::exception {
public:
    const char *what() const noexcept override {
        return "Elfogyott a tulcsordulasi teruletunk!";
    }
};

// Intből int ujjlenyomatot képező funktor
class IntFingerprint {
public:
    int operator()(int key) { return key; }
};

// Stringből int ujjlenyomatot képező funktor
class StringFingerprint {
public:
    int operator()(const std::string &key) {
        unsigned h = 0;
        for (unsigned int i = 0; i < key.size(); ++i) {
            h += (256 * h + key[i]) % 16777213;//osszuk hogy beleferjen 32 bitbe
        }
        return int(h);
    }
};

// Telefonszámot tartalmazó stringből int ujjlenyomatot képező funktor
// Utolsó 9 számjegy (az mindig belefér 32 bitbe)
class PhoneNumberFingerprint {
public:
    int operator()(const std::string &key) {
        int sum = 0;
        for (int i = std::max(0, (int)(key.size() - 9)); i < (int)key.size(); ++i) {
            sum = sum * 10 + (key[i] - '0');
        }
        return sum;
    }
};

// HashTable osztály
// Halmazként működik - minden elemet csak egyszer tárolunk el benne
// Két template paraméter:
//   Key: kulcs típusa
//   Fingerprint: ujjlenyomatfunktor
template <class Key, class Fingerprint> class HashTable {
    // Egy rekesz állapota
    enum state_t { FREE, ERASED, USED };

    // Belső struktúra, egy elem a hashtáblában
    struct Node {
        Key key;       // A tárolt kulcs
        state_t state; // A rekesz állapota
        Node() : state(FREE) {}
    };

    const int logtablesize; // A táblaméret 2-es alapú logaritmusa
    const int tablesize;    // Hashtábla mérete (különböző hashek száma)

    int actualsize; // Hashtáblában éppen megtalálható elemek száma
    // Nem egyenlő a kapacitással!

    std::vector<Node> table; // A hashtábla tárterülete

    Fingerprint fingerprint; // Ujjlenyomatfunktor egy példánya

    // Visszaadja egy adott kulcs hashét
    int getHash(const Key &key, int i) {
        static const unsigned s = 2654435769U; // == 2**32 * (sqrt(5) - 1)/2
        unsigned k = fingerprint(key);
        unsigned h = (k * s) >> (32 - logtablesize);
        return (h + i) % tablesize;
    }

    // Feladat 4
    // Táblaméret kerekítése a következő kettőhatványra.
    // A megfelelő kettőhatvány logaritmusát adjuk vissza.
    static int round_tablesize(int _tablesize) {
        int i = 4; // Minimális táblaméret: 2**4 == 16
        // Túl kicsi hash táblának amúgy sincs értelme.
        while ((1 << i) < _tablesize) { //bitshift
            ++i;
        }
        return i;
    }

public:
    // Konstruktor, a hashtábla kapacitását kell átadni neki
    explicit HashTable(int _tablesize)
            : logtablesize(round_tablesize(_tablesize)), tablesize(1 << logtablesize),
              actualsize(0),
              table(tablesize) // Létrehozza az adott méretű vektort a hashtáblához
    {}

    // Visszaadja a hashtáblában található elemek számát
    int size() { return actualsize; }

    // Visszaadja, hogy üres-e a hastábla
    bool empty() { return actualsize == 0; }

    // Kitörli az összes elemet a hashtáblából
    void clear() {
        for (int i = 0; i < tablesize; ++i) {
            table[i].state = FREE;
        }
    }

    // Új elemet szúr be a hashtáblába, ha nincs még ilyen elem benne
    // Ha van már ilyen elem, nem csinál semmit
    void insert(const Key &key) {

        for (int i = 0; i < tablesize; ++i) {
            int pos = getHash(key,i);
            if(table[pos].state != USED){
                table[pos].key = key;
                table[pos].state = USED;
                actualsize = actualsize +1;
                return;
            }
            else if(table[pos].key == key){ //ha megvan a key
                return;

            }

        }

        throw OverflowError(); //megtelet a tabla
    }

    // Megkeresi, hogy egy adott elem megtalálható-e a hashtáblában
    bool find(const Key &key) {

        for (int i = 0; i < tablesize; ++i) {
            int pos = getHash(key,i);
           if(table[pos].key == key){ //ha megvan a key
                return true;

            }

        }
        return false;


    }

    // Kitöröl egy adott elemet, ha megtalálható a hashtáblában
    // Ha nem található meg, nem csinál semmit
    void erase(const Key &key) {    //ha torlunk akkor erasedre allitjuk
        for (int i = 0; i < tablesize; ++i) {
            int pos = getHash(key,i);
            if(table[pos].key == key){ //ha megvan a key

                table[pos].state = FREE;


                actualsize = actualsize -1;


                return;

            }

        }

    }

    // Kiírja a hashtábla tartalmát
    // Soronként egy hashérték, majd a táblában levő kulcs
    void print() {
        for (int i = 0; i < tablesize; ++i) {
            std::cout << i << ": ";
            if (table[i].state == USED) {
                std::cout << table[i].key;
            } else if (table[i].state == ERASED) {
                std::cout << "-T-";
            }
            std::cout << std::endl;
        }
    }
};

#endif // HASHTABLE_HPP_INCLUDED