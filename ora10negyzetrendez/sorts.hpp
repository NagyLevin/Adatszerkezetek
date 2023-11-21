#ifndef SORTS_HPP
#define SORTS_HPP

#include <cstddef>

/// Segéd függvények
void swap(int &a, int &b) { // Hagyományos cserélő függvény
  int tmp = a;              // Segédváltozóra van szükség a cseréhez
  a = b;
  b = tmp;
}

/// ========== BUBURÉKRENDEZÉS ==========
void bubbleSort(int *a, int n) {
    for (int j = n - 1; j >= 1; --j) {
        for (int i = 0; i <= j - 1; ++i) { // Végigjárja előről hátra a tömböt
            if (a[i] <= a[i + 1]) { // Ha az aktuális elem kisebb, mint a következő
                // skip               // akkor nem történik semmi
            } else { // Ha az aktuális elem nagyobb, mint a következő
                swap(a[i], a[i + 1]); // akkor megcseréljük a két elemet
            }
        }
    }
}

/// ========== MAXIMUM KIVÁLASZTÁSOS RENDEZÉS ==========
// A rendező Segédfüggvénye: megkeresi a maximális értékű elemet a megadott
// tartományban (j-ig)
int maxSel(const int *a, int j) {


    int index = 0;

    for (int i = 0; i < j; ++i) {
        if(a[i+1] > a[index]){

            index = i+1;
        }


    }


    return index; // Visszatér a maximális értékű elem indexével
}

void maxSort(int *a, int n) {


    // Végigjárja hátulról előrefelé a tömböt. Megkeresi a maximumot az elejétõl j-ig. A megtalált maximális elemet kicseréljük az aktuális hátsó elemmel

    for (int i = n-1; i > 0; --i) {
        int index = maxSel(a,i);
        swap(a[index],a[i]);    //ket elem megcserel

    }


}

/// ========== BESZÚRÓ RENDEZÉS ==========
void insertionSort(int *a, int n) {

    for (int j = 0; j < n-1; ++j) {
        int v = a[j+1];

        int i = j;
        while (i >= 0 && a[i] > v){
            a[i+1] = a[i];
            i = i -1;

        }
        a[i+1] = v; //beszurjuk a helyere


    }


}

#endif
