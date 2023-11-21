#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

#include "quicksort.hpp"
#include "sorts.hpp"
#include "timer.hpp"

using namespace std;

/**    ----- Konstansok -----   **/
constexpr size_t N = 100000;             // A nagyteszt mérete
constexpr bool PERFORMANCE_TEST = false; // Futassunk-e teljesítmény tesztet

/**    ----- Segéd függvény -----    **/
template <class T> void printArray(T *A, size_t len) {
    cout << "{";
    for (size_t i = 0; i < len; i++) {
        cout << (i == 0 ? "" : ", ") << A[i];
    }
    cout << "}" << endl;
}

/**    ----- Rendezett? -----    **/
bool isSorted(const int *a, size_t len) {
    for (size_t i = 1; i < len; ++i) {
        if (a[i - 1] > a[i]) {
            return false;
        }
    }
    return true;
}

/**    ----- Beépített rendező -----    **/
void stdSort(int *a, int len) { std::sort(a, a + len); }

void testOnArray(int *a, int len, void (*sort_fn)(int *, int)) {
    if (PERFORMANCE_TEST) {
        Timer t{};
        sort_fn(a, len);
    } else {
        sort_fn(a, len);
        if (len < 20) {
            printArray(a, len);
        }
        std::cout << "Sikerült a rendezés: " << std::boolalpha << (isSorted(a, len)?"igen":"NEM SIKERULT!")
                  << std::endl;
    }
}

/**    ----- Tesztelő segédfüggvény -----    **/
void testAllOnArray(const int *a, int len) {
    if (len < 20) {
        std::cout << "Eredeti tömb: ................ ";
        printArray(a, len);
    }
    std::vector<int> tmp(a, a + len);

    std::cout << "Buborékrendező:                ";
    testOnArray(tmp.data(), len, bubbleSort);
    std::copy(a, a + len, tmp.begin());

    std::cout << "Maximum-kiválasztásos rendező: ";
    testOnArray(tmp.data(), len, maxSort);
    std::copy(a, a + len, tmp.begin());

    std::cout << "Beszúró rendező:               ";
    testOnArray(tmp.data(), len, insertionSort);
    std::copy(a, a + len, tmp.begin());

    std::cout << "Gyorsrendező:                  ";
    testOnArray(tmp.data(), len, quickSort);
    std::copy(a, a + len, tmp.begin());

    std::cout << "Beépített rendező:             ";
    testOnArray(tmp.data(), len, stdSort);
}

/**    ----- Main függvény -----    **/
int main() {
    // Teszteléshez mindig érdemes reprodukálható méréseket végezni, különben
    // nagyon nehéz debuggolni.
    srand(0);

    std::cout << "===================================================="
              << std::endl;
    std::cout << "Kisebb tesztek:" << std::endl;
    {
        // Üres tömb
        const std::vector<int> test_array{};
        testAllOnArray(test_array.data(), 0);
    }

    {
        // Egy elem
        const std::vector<int> test_array{1};
        testAllOnArray(test_array.data(), 1);
    }

    {
        // Két elem, rendezett
        const std::vector<int> test_array{1, 4};
        testAllOnArray(test_array.data(), 2);
    }

    {
        // Két elem, rendezetlen
        const std::vector<int> test_array{5, 2};
        testAllOnArray(test_array.data(), 2);
    }

    {
        // Kevés elem
        const std::vector<int> test_array{1, 3, 4, 2, 0, -1};
        testAllOnArray(test_array.data(), 6);
    }

    {
        // Végéről visszavinni az első elemet
        const std::vector<int> test_array{2, 3, 4, 5, 1};
        testAllOnArray(test_array.data(), 5);
    }

    {
        // 3 elem, nem kell felosztani
        const std::vector<int> test_array{2, 1, 3};
        testAllOnArray(test_array.data(), 3);
    }

    {
        // 3 elem, fel kell osztani
        const std::vector<int> test_array{2, 3, 1};
        testAllOnArray(test_array.data(), 3);
    }

    {
        std::cout << "===================================================="
                  << std::endl;
        std::cout << "Kis véletlenszerű:" << std::endl;
        std::vector<int> test_array(N);
        for (size_t i = 0; i < 128; ++i) {
            // Így pont nem fog a speciális swap-unk túlcsordulni.
            test_array[i] = rand() % (std::numeric_limits<int>::max() / 2);
        }
        testAllOnArray(test_array.data(), 1000);
    }

    {
        std::cout << "===================================================="
                  << std::endl;
        std::cout << "Rendezett:" << std::endl;
        std::vector<int> test_array(N);
        for (size_t i = 0; i < N; ++i) {
            test_array[i] = i;
        }
        testAllOnArray(test_array.data(), N);
    }

    {
        std::cout << "===================================================="
                  << std::endl;
        std::cout << "Fordítva rendezett:" << std::endl;
        std::vector<int> test_array(N);
        for (size_t i = 0; i < N; ++i) {
            test_array[i] = N - i;
        }
        testAllOnArray(test_array.data(), N);
    }

    {
        std::cout << "===================================================="
                  << std::endl;
        std::cout << "Véletlenszerű:" << std::endl;
        std::vector<int> test_array(N);
        for (size_t i = 0; i < N; ++i) {
            // Így pont nem fog a speciális swap-unk túlcsordulni.
            test_array[i] = rand() % (std::numeric_limits<int>::max() / 2);
        }
        testAllOnArray(test_array.data(), 1000);
    }

    {
        std::cout << "===================================================="
                  << std::endl;
        std::cout << "Ugyanakkora:" << std::endl;
        std::vector<int> test_array(N);
        for (size_t i = 0; i < N; ++i) {
            // Így pont nem fog a speciális swap-unk túlcsordulni.
            test_array[i] = std::numeric_limits<int>::max() / 2;
        }
        testAllOnArray(test_array.data(), 1000);
    }

    return 0;
}