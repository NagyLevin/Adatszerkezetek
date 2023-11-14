#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

#include "heap_sort.hpp"
#include "timer.hpp"

using namespace std;

/**    ----- Konstansok -----   **/
constexpr size_t N = 1000000;            // A nagyteszt mérete
constexpr bool PERFORMANCE_TEST = false; // Futassunk-e teljesítmény tesztet

/**    ----- Segéd függvény -----    **/
template <class T> void printArray(const std::vector<T> &v) {
  cout << "{";
  for (size_t i = 0; i < v.size(); ++i) {
    cout << (i == 0 ? "" : ", ") << v[i];
  }
  cout << "}" << endl;
}

/**    ----- Beépített rendező -----    **/
template <typename T> void stdSort(std::vector<T> &v) {
  std::sort(v.begin(), v.end());
}

template <typename T>
void testOnArray(std::vector<T> &v, void (*sort_fn)(std::vector<T> &)) {
  if (PERFORMANCE_TEST) {
    Timer t{};
    sort_fn(v);
  } else {
    sort_fn(v);
    if (v.size() < 20) {
      printArray(v);
    }
    std::cout << "Sikerült a rendezés: " << std::boolalpha
              << std::is_sorted(v.begin(), v.end()) << std::endl;
  }
}

/**    ----- Tesztelő segédfüggvény -----    **/
template <typename T> void testAllOnArray(const std::vector<T> &v) {
  if (v.size() < 20) {
    std::cout << "Eredeti tömb: ................ ";
    printArray(v);
  }
  std::vector<int> tmp(v);

  std::cout << "Kupacrendező:                  ";
  testOnArray(tmp, heapSort);
  std::copy(v.begin(), v.end(), tmp.begin());

  std::cout << "Beépített rendező:             ";
  testOnArray(tmp, stdSort);
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
    testAllOnArray(test_array);
  }

  {
    // Egy elem
    const std::vector<int> test_array{1};
    testAllOnArray(test_array);
  }

  {
    // Két elem, rendezett
    const std::vector<int> test_array{1, 4};
    testAllOnArray(test_array);
  }

  {
    // Két elem, rendezetlen
    const std::vector<int> test_array{5, 2};
    testAllOnArray(test_array);
  }

  {
    // Kevés elem
    const std::vector<int> test_array{1, 3, 4, 2, 0, -1};
    testAllOnArray(test_array);
  }

  {
    // Végéről visszavinni az első elemet
    const std::vector<int> test_array{2, 3, 4, 5, 1};
    testAllOnArray(test_array);
  }

  {
    // 3 elem, nem kell felosztani
    const std::vector<int> test_array{2, 1, 3};
    testAllOnArray(test_array);
  }

  {
    // 3 elem, fel kell osztani
    const std::vector<int> test_array{2, 3, 1};
    testAllOnArray(test_array);
  }

  {
    std::cout << "===================================================="
              << std::endl;
    std::cout << "Rendezett:" << std::endl;
    std::vector<int> test_array(N);
    for (size_t i = 0; i < N; ++i) {
      test_array[i] = i;
    }
    testAllOnArray(test_array);
  }

  {
    std::cout << "===================================================="
              << std::endl;
    std::cout << "Fordítva rendezett:" << std::endl;
    std::vector<int> test_array(N);
    for (size_t i = 0; i < N; ++i) {
      test_array[i] = N - i;
    }
    testAllOnArray(test_array);
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
    testAllOnArray(test_array);
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
    testAllOnArray(test_array);
  }

  return 0;
}
