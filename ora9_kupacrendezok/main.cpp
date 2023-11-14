/**
 *
 * @file main.cpp
 * @author tekda
 * @author horar
 * Főprogram, kupac és prioritásos sor demonstrálására
 *
 */

#include "pqueue.hpp"
#include <cstdlib>
#include <iostream>
#include <vector>

/**
 * Spéci típus a kupac tesztelésére. Csak összehasonlító operátora van.
 */
struct DummyType {
  int a;
  bool operator<(DummyType rhs) const { return this->a < rhs.a; }
};

int main() {
  // Reproducibilis mérések
  srand(0);
  try {
    {
      std::cout << std::endl << "-----------------------------" << std::endl;
      std::cout << "Ures kupac";
      std::cout << std::endl << "-----------------------------" << std::endl;
      Heap<int> heap;
      std::cout << "empty: " << (heap.empty() ? "OK" : "NOK") << std::endl;
      try {
        heap.top();
        std::cout << "top: exception hianyzik!" << std::endl;
      } catch (EmptyHeap &) {
        std::cout << "top: OK" << std::endl;
      }
      try {
        heap.pop();
        std::cout << "pop: exception hianyzik!" << std::endl;
      } catch (EmptyHeap &) {
        std::cout << "pop: OK" << std::endl;
      }
    }
    {
      std::cout << std::endl << "-----------------------------" << std::endl;
      std::cout << "Egy elem";
      std::cout << std::endl << "-----------------------------" << std::endl;
      Heap<int> heap;
      heap.push(1);
      std::cout << "empty: " << (!heap.empty() ? "OK" : "NOK") << std::endl;
      std::cout << "size:  vart: 1, tenyleges: " << heap.size() << std::endl;
      std::cout << "top:  vart: 1, tenyleges: " << heap.top() << std::endl;
      heap.pop();
      std::cout << "pop:  OK" << std::endl;
      std::cout << "Most, hogy kiurult:" << std::endl;
      std::cout << "empty: " << (heap.empty() ? "OK" : "NOK") << std::endl;
      try {
        heap.top();
        std::cout << "top: exception hianyzik!" << std::endl;
      } catch (EmptyHeap &) {
        std::cout << "top: OK" << std::endl;
      }
      try {
        heap.pop();
        std::cout << "pop: exception hianyzik!" << std::endl;
      } catch (EmptyHeap &) {
        std::cout << "pop: OK" << std::endl;
      }
    }
    {
      std::cout << std::endl << "-----------------------------" << std::endl;
      std::cout << "Nehany elem";
      std::cout << std::endl << "-----------------------------" << std::endl;
      Heap<int> heap;
      heap.push(3);
      heap.push(2);
      heap.push(1);
      heap.push(5);
      heap.push(4);
      heap.validate();
      std::cout << "size:  vart: 5, tenyleges: " << heap.size() << std::endl;
      std::cout << "top:  vart: 5, tenyleges: " << heap.top() << std::endl;
      heap.pop();
      std::cout << "top:  vart: 4, tenyleges: " << heap.top() << std::endl;
      heap.pop();
      std::cout << "top:  vart: 3, tenyleges: " << heap.top() << std::endl;
      heap.pop();
      std::cout << "top:  vart: 2, tenyleges: " << heap.top() << std::endl;
      heap.pop();
      std::cout << "top:  vart: 1, tenyleges: " << heap.top() << std::endl;
      heap.pop();
    }

    {
      std::cout << std::endl << "-----------------------------" << std::endl;
      std::cout << "Felepites vektorbol";
      std::cout << std::endl << "-----------------------------" << std::endl;

      std::vector<int> v;
      std::cout << "Eredeti vektor: ";
      for (int i = 0; i < 30; ++i) {
        v.push_back(rand() % 100);
        std::cout << v[i] << ' ';
      }
      std::cout << std::endl;
      Heap<int> heap(v);
      heap.validate(true);
      std::cout << "Vektor merete: " << v.size()
                << ", kupac merete: " << heap.size() << std::endl;
      std::cout << "Kupacbol egyesevel kiveve: ";
      while (!heap.empty()) {
        std::cout << heap.top() << ' ';
        heap.pop();
      }
    }

    {
      std::cout << std::endl << "-----------------------------" << std::endl;
      std::cout << "Sajat tipus";
      std::cout << std::endl << "-----------------------------" << std::endl;
      Heap<DummyType> heap;
      heap.push({3});
      heap.push({2});
      heap.push({1});
      heap.push({5});
      heap.push({4});
      // Nem tudjuk kiíratni a képernyőre
      std::cout << "Validate: " << (heap.check() ? "OK" : "NOK") << std::endl;
    }

    {
      std::cout << std::endl << "-----------------------------" << std::endl;
      std::cout << "Prioritasos sor";
      std::cout << std::endl << "-----------------------------" << std::endl;

      PriorityQueue<int> pq;
      std::cout << std::endl;
      std::cout << "Beillesztunk elemeket: ";

      for (int i = 0; i < 30; ++i) {
        int val = rand() % 100;
        std::cout << val << " ";
        pq.push(val,
                val); // itt most teszteljük, hogy a priority és a value
                      // ugyanaz pq.push(val, rand()%100/20.0);
      }
      std::cout << std::endl
                << (pq.validate() ? "Rendben van!" : "Valami nem oke!")
                << std::endl;
      std::cout << std::endl;
      std::cout << std::endl;
      std::cout << "Kiveszunk egy par elemet: ";
      for (int i = 0; i < 5; ++i) {
        std::cout << pq.top() << " ";
        pq.pop();
      }
      std::cout << std::endl
                << (pq.validate() ? "Rendben van!" : "Valami nem oke!")
                << std::endl;
      std::cout << std::endl;
      std::cout << std::endl;
      std::cout << "A sorban maradt elemek: ";
      while (!pq.empty()) {
        std::cout << pq.top() << " ";
        pq.pop();
      }
      std::cout << std::endl
                << (pq.validate() ? "Rendben van!" : "Valami nem oke!")
                << std::endl;
    }

    std::cout << std::endl
              << "----------------------------------------------------------"
              << std::endl;
    std::cout << "Veget ert a program futasa, ha minden rendben van, akkor "
                 "minden rendben van!";
    std::cout << std::endl
              << "----------------------------------------------------------"
              << std::endl;

  } catch (HeapException &e) {
    std::cout << "HIBA: " << e.what() << std::endl;
  }

  return 0;
}
