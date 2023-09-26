#include "list.h"
#include <iostream>

using namespace std;

int main() {
    try {
        List<int> fibonacci;
        cout << "--- Egy \"int\"-eket tartalmazo lista tesztelese ---\n";
        cout << "Be: 0" << endl;
        fibonacci.insertLast(0);
        cout << "Be: 1" << endl;
        fibonacci.insertLast(1);
        cout << "Be: 1" << endl;
        fibonacci.insertLast(1);
        cout << "Be: 2" << endl;
        fibonacci.insertLast(2);
        cout << "Be: 3" << endl;
        fibonacci.insertLast(3);
        cout << "Be: 5" << endl;
        fibonacci.insertLast(5);
        cout << "Be: 8" << endl;
        fibonacci.insertLast(8);

        cout << "\nA lista tartalma: " << endl;
        fibonacci.print();

        cout << "\nAz aktualis elem ilyenkor az utolsonak betett elem" << endl;
        cout << "Cur: " << fibonacci.getValue() << endl;

        cout << "\nAllitsuk az aktualis elemet az elso elemre" << endl;
        fibonacci.toFirst();
        cout << "Cur: " << fibonacci.getValue() << endl;

        cout << "\nLepjunk harmat elore (Harom stepNext utan): " << endl;
        fibonacci.stepNext();
        fibonacci.stepNext();
        fibonacci.stepNext();
        cout << "Cur: " << fibonacci.getValue() << endl;
        ;

        cout << "\nAz aktualis elem torlesre kerul" << endl;
        fibonacci.removeCur();
        cout << "Egyreszt eltunt a szam a listabol: " << endl;
        fibonacci.print();
        cout << "Masreszt az aktualis elem a torolt utani lett: " << endl;
        cout << "Cur: " << fibonacci.getValue();

        cout << "\n\nIrassuk ki ujra a listat:" << endl;
        fibonacci.print();

        List<string> stringek;
        cout << "\n\n\n--- Egy \"string\"-eket tartalmazo lista tesztelese ---\n";
        cout << "Be: Januar" << endl;
        stringek.insertFirst("Januar");
        cout << "Be: Februar" << endl;
        stringek.insertFirst("Februar");
        cout << "Be: Kazuar" << endl;
        stringek.insertFirst("Kazuar");
        cout << "Be: Jaguar" << endl;
        stringek.insertFirst("Jaguar");

        cout << "\nA lista tartalma ekkor: " << endl;
        stringek.print();

        cout << "\nAz aktualis elem ilyenkor az elso elem" << endl;
        cout << "Cur: " << stringek.getValue() << endl;

        cout << "\nEgy stepNext utan: " << endl;
        stringek.stepNext();
        cout << "Cur: " << stringek.getValue() << endl;
        ;

        cout << "\nHa torlom az aktualis elemet" << endl;
        stringek.removeCur();
        cout << "Egyreszt eltunik a szoveg a listabol: " << endl;
        stringek.print();
        cout << "Masreszt az aktualis elem a torolt utani elem lesz: " << endl;
        cout << "Cur: " << stringek.getValue();
        cout << endl;


    } catch (std::exception &e) {
        cout << "\n***HIBA tortent!*** " << e.what() << endl;
    }

    // Az udvarias program elköszön
    cout << "\n\nA program befejezte a futtasat, viszontlatasra!" << endl;
}