#ifndef HASHTABLE_HPP_INCLUDED
#define HASHTABLE_HPP_INCLUDED

#include <iostream>
#include <list>
#include <vector>

// HashTable osztály
// Halmazként működik - minden elemet csak egyszer tárolunk el benne
class HashTable {
    std::vector<std::list<int>> table;

    int capacity; // Hashtábla kapacitása (különböző hashek száma)
    // Nem egyenlő a maximális mérettel, tetszőleges mennyiségű
    // elemet el tudunk tárolni!
    int actualsize; // Hashtáblában éppen megtalálható elemek száma
    // Nem egyenlő a kapacitással!
public:
    // Konstruktor, a hashtábla kapacitását kell átadni neki
    explicit HashTable(int capacity): table(capacity),capacity(capacity),actualsize(0) {

        //vagy
        // table = capacity;
        //capacity = capacity;
        //actualsize = 0;


    }

    // Visszaadja a hashtáblában található elemek számát
    int size() { return actualsize; }

    // Visszaadja, hogy üres-e a hastábla
    bool empty() { return actualsize == 0; }

    // Kitörli az összes elemet a hashtáblából
    void clear() {
        for (int i = 0; i < capacity; ++i) {
            table[i].clear();


        }
        actualsize = 0;

    }

    // Új elemet szúr be a hashtáblába, ha nincs még ilyen elem benne
    // Ha van már ilyen elem, nem csinál semmit
    void insert(const int & key) {
        int myhash = getHash(key);

        for (std::list<int>::iterator it = table[myhash].begin(); it != table[myhash].end(); ++it) { //iteratoros bejaras

            if(*it == key){
                return;
            }

        }
        table[myhash].push_back(key);   //ha nincs akkor a vegere rakaja
        actualsize = actualsize +1; //meret megnovelese

    }

    // Megkeresi, hogy egy adott elem megtalálható-e a hashtáblában
    bool find(const int & key) {
        int myhash = getHash(key);
        for (std::list<int>::iterator it = table[myhash].begin(); it != table[myhash].end(); ++it) { //iteratoros bejaras

            if(*it == key){
                return true;
            }

        }
        return false;
    }

    // Kitöröl egy adott elemet, ha megtalálható a hashtáblában
    // Ha nem található meg, nem csinál semmit
    void erase(const int & key) {
        int myhash = getHash(key);
        for (std::list<int>::iterator it = table[myhash].begin(); it != table[myhash].end(); ++it) { //iteratoros bejaras

            if(*it == key){
                table[myhash].erase(it);
                actualsize = actualsize -1;
                return;


            }

        }

    }

    // Kiírja a hashtábla tartalmát
    // Soronként egy hashérték, majd szóközzel elválasztva a benne található
    // értékek
    void print() {

        for (int i = 0; i < capacity; ++i)
        {
            std::cout << i << ": " ;
            for (std::list<int>::iterator it = table[i].begin(); it !=
        table[i].end(); ++it)
            {
                std::cout << *it << " " ;
            }
            std::cout << std::endl ;
        }

    }

private:
    // Visszaadja egy adott kulcs hashét
    int getHash(const int & key) {
        //std::cout << key << std::endl;
        return key % capacity;

    }
};

#endif // HASHTABLE_HPP_INCLUDED