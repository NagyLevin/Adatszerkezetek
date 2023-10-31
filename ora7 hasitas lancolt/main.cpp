#include "hashtable.h"
#include <iostream>
#include <random>

int main() {
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 20);

    // Hashtábla 10-es kapacitással
    HashTable hashtable(10);

    // Int beszúrás
    for (int i = 0; i < 15; ++i) {
        hashtable.insert(dist(gen));
    }
    std::cout << "Beszuras utan" << std::endl;
    hashtable.print();

    // Int keresés
    std::cout << std::endl;
    std::cout << "Keresesek" << std::endl;
    for (int i = 0; i < 10; ++i) {
        int sz = dist(gen);
        std::cout << sz << ": " << hashtable.find(sz) << std::endl;
    }

    // Int törlés
    std::cout << std::endl;
    std::cout << "Torlesek" << std::endl;
    for (int i = 0; i < 15; ++i) {
        int sz = dist(gen);
        hashtable.erase(sz);
        std::cout << sz << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Torles utan" << std::endl;
    hashtable.print();

    return 0;
}