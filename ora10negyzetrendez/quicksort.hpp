#ifndef QUICKSORT_HPP
#define QUICKSORT_HPP

#include <cstddef>

/// Segéd függvény
void swapInt(int &a, int &b) { // Egészeket cserélő függvény
  a = a + b;                   // Nincs szükség segédváltozóra
  b = a - b;
  a = a - b;
}

/// ========== GYORS RENDEZÉS ==========
// A gyorsrendező felosztó függvénye
int divide(int *a, int down, int up) {

    int pivot_index = down+ (int )(up-down)/2;//mi van ha mást valasztunk
    int pivot = a[pivot_index]; //elso eleme
    swapInt(a[down],a[pivot_index]);//mi van ha mást valasztunk

    int left = down;
    int right = up;
    //addig lepegetunk veluk amig a 2 nem talalkozik

    while (right > left){
        while (a[left] <= pivot && left < up){ //fel
            left = left +1;


        }
        while (a[right] >= pivot && right > down){ //le
            right = right -1;


        }
        if(left < right){
            swapInt(a[left],a[right]);

        }

    }

    a[down] = a[right]; //ha elereik egymast
    a[right] = pivot;
    return right;











}

void quickSort(int *A, int down, int up) {
  if (down < up) {
    int q = divide(A, down, up);
    quickSort(A, down, q - 1);
    quickSort(A, q + 1, up);
  }
}

void quickSort(int *A, int len) { quickSort(A, 0, len - 1); }

#endif
