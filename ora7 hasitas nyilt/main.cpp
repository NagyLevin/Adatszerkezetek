#include "hashtable.h"
#include <iostream>
#include <random>

int main() {
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 20);

    /// Int teszt
    std::cout << "== INT teszt ==" << std::endl;
    HashTable<int, IntFingerprint> hashtable(11);

    for (int i = 0; i < 10; ++i) {
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
    for (int i = 0; i < 10; ++i) {
        int sz = dist(gen);
        hashtable.erase(sz);
        std::cout << sz << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Torles utan" << std::endl;
    hashtable.print();

    /// String teszt
    std::cout << std::endl << "== STRING teszt ==" << std::endl;
    HashTable<std::string, StringFingerprint> hashtable_string(11);
    hashtable_string.insert("Sanyi");
    hashtable_string.insert("Bela");
    hashtable_string.insert("Geza");
    hashtable_string.insert("Jancsi");
    hashtable_string.insert("Jozsi");
    hashtable_string.insert("Aladar");
    hashtable_string.insert("Gizi");
    hashtable_string.insert("Piroska");
    hashtable_string.insert("Farkas");
    hashtable_string.print();

    // String keresés
    std::cout << std::endl;
    std::cout << "String kereses" << std::endl;
    std::cout << "Aladar: " << hashtable_string.find("Aladar") << std::endl;
    std::cout << "Gizi: " << hashtable_string.find("Gizi") << std::endl;
    std::cout << "Balint: " << hashtable_string.find("Balint") << std::endl;

    // String törlés
    std::cout << std::endl;
    std::cout << "String torles" << std::endl;
    std::cout << "Aladar" << std::endl;
    hashtable_string.erase("Aladar");
    std::cout << "Gizi" << std::endl;
    hashtable_string.erase("Gizi");
    std::cout << "Balint" << std::endl;
    hashtable_string.erase("Balint");
    hashtable_string.print();

    /// Telefonszám teszt
    std::cout << std::endl << "== TELEFONSZAM teszt ==" << std::endl;
    HashTable<std::string, PhoneNumberFingerprint> hashtable_phone(11);
    hashtable_phone.insert("3613504712");
    hashtable_phone.insert("36304578712");
    hashtable_phone.insert("36304721877");
    hashtable_phone.insert("3688312222");
    hashtable_phone.insert("330687712345");
    hashtable_phone.insert("4547687712345");
    hashtable_phone.print();

    // Telefonszám keresés
    std::cout << std::endl;
    std::cout << "Telefonszam kereses" << std::endl;
    std::cout << "3613504712: " << hashtable_phone.find("3613504712")
              << std::endl;
    std::cout << "36304578712: " << hashtable_phone.find("36304578712")
              << std::endl;
    std::cout << "8547687712345: " << hashtable_phone.find("8547687712345")
              << std::endl;

    // Telefonszám törlés
    std::cout << std::endl;
    std::cout << "Telefonszam torles" << std::endl;
    std::cout << "3613504712" << std::endl;
    hashtable_phone.erase("3613504712");
    std::cout << "36304578712" << std::endl;
    hashtable_phone.erase("36304578712");
    std::cout << "8547687712345" << std::endl;
    hashtable_phone.erase("8547687712345");
    hashtable_phone.print();

    return 0;
}