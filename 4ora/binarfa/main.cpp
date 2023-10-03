#include <ctime>
#include <iostream>
#include "bs_tree.h"

using namespace std;

int main() {
    srand(time(0));

    try {
        cout << "\n*** Binaris keresofa teszt futtatas: ***\n" << endl;

        int myArray[10] = { 44, 61, 68, 67, 40, 20, 74, 17, 36, 60 };

        Bs_tree<int> myShort;
        for (int i = 0; i < 10; i++) {
            cout << i << " elem beszurasa...";

            int x = myArray[i]; //rand();
            myShort.insert(x);

            cout << " Sikerult " << myArray[i] << "-t beszurni." << endl;

        }

        if (myShort.size() != 10) {
            throw internal_error("Meret nem megfelelo!");
        }
        cout << "\nMeret rendben.\n" << endl;

        //olvassuk ki inorder módon egy tömbbe
        cout << "\nInorder kiolvasas: ";
        myShort.inorder(cout);

        cout << "\nPreorder kiolvasas: ";
        myShort.preorder(cout);

        cout << "\nPostorder kiolvasas: ";
        myShort.postorder(cout);
        cout << endl;

        cout << "\nMin: " << myShort.min() << "\n";
        if (myShort.min() != 17) {
            throw internal_error("Min nem megfelelo!");
        }
        cout << "\nMax: " << myShort.max() << "\n";
        if (myShort.max() != 74) {
            throw internal_error("Max nem megfelelo!");
        }

        // másoljuk le a fát és irassuk ki ezt is
        Bs_tree<int> myShort2(myShort);
        cout << "\nInorder kiolvasas 2: ";
        myShort2.inorder(cout);

        cout << "\nPreorder kiolvasas 2: ";
        myShort2.preorder(cout);

        cout << "\nPostorder kiolvasas 2: ";
        myShort2.postorder(cout);
        cout << endl;

        cout << "\nTorles tesztelese:\n";

        myShort.remove(20);
        myShort.remove(44);
        myShort.remove(17);
        myShort.remove(40);
        myShort.remove(60);

        //Mi van most a gyökérben?
        cout << "A gyoker == " << myShort.getroot() << endl;

        //Üres fa tesztelése
        Bs_tree<int> uresFa;
        cout << "\n Probaljunk kiolvasni egy ures fat: \n";
        uresFa.inorder(cout);
    } catch (const exception& e) {
        cout << "HIBA: " << e.what() << endl;
    }

    return 0;
}