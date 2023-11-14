/**
 *
 * @file heap.hpp
 * @author tekda
 * Max-kupac adatszerkezet iterátorokkal
 * Prioritásos sor csomagolóosztály, kupaccal
 *
 */

#ifndef HEAP_HPP
#define HEAP_HPP

#include "heap_exceptions.hpp"
#include <cmath>
#include <iostream>
#include <vector>

template <class I> bool validateHeap(I first, I last);

template <class T> class Heap {
  /**
   *   Konténer vektor
   */
  std::vector<T> v;

  /**
   * Kupacban elemet feljebbmozgató eljárás
   *
   * @param index az elem indexe, amit feljebb kell mozgatni
   */
  void liftUp(std::size_t index) {

  }

  /**
   * Kupacban elemet lejjebbmozgató eljárás
   *
   * @param index az elem indexe, amit lejjebb kell mozgatni
   */
  void liftDown(std::size_t index) {

  }

  std::size_t getParent(std::size_t index) { return (index - 1) / 2; }

  std::size_t leftChild(std::size_t index) { return 2 * index + 1; }

  std::size_t rightChild(std::size_t index) { return 2 * index + 2; }

public:
  Heap() {}
  Heap(const std::vector<T> &v_) : v(v_) {
    for (int i = static_cast<int>(v.size() / 2) - 1; i >= 0; --i)
      liftDown(i);
  }

  /**
   *
   * Üres-e a kupac
   *
   * @return igaz, hogyha a kupac üres
   *
   */
  bool empty() const { return v.empty(); }

  /**
   *
   * A kupac mérete
   *
   * @return a kupac mérete.
   *
   */
  size_t size() const { return v.size(); }

  /**
   *
   * Kupacba elemet betevő eljárás
   *
   * @param item a beszúrandó elem
   *
   */
  void push(T item) {
    v.push_back(item);
    liftUp(v.size() - 1);
  }

  /**
   *
   * Kupac maximális elemét lekérdező művelet
   *
   * @return kupac tetején lévő elem
   *
   */
  const T &top() const {
    if (empty()) {
      throw EmptyHeap();
    }
    return v[0];
  }

  /**
   *
   * Kupacból kivesszük a legfelső elemet
   *
   */
  void pop() {
    if (!empty()) {
      std::swap(v[0], v[v.size() - 1]);
      v.pop_back();

      if (!empty()) {
        liftDown(0);
      }
    } else {
      throw EmptyHeap();
    }
  }

  /**
   *
   * Ellenőrző függvény
   *
   */
  void validate(bool print = false) const {
    if (print) {
      for (unsigned int i = 0; i < v.size(); ++i)
        std::cout << v[i] << " ";
      std::cout << std::endl;
    }
    std::cout << "A vektor"
              << (validateHeap(v.begin(), v.end()) ? " " : " NEM ")
              << "teljesiti a kupac-tulajdonsagot!" << std::endl;
  }

  bool check() const { return validateHeap(v.begin(), v.end()); }
};

template <class I> bool validateHeap(I first, I last) {
  if (last > first) {
    for (int i = 0; i < (last - first) / 2; ++i) {
      if ((first + 2 * i + 1) < last && *(first + i) < *(first + 2 * i + 1))
        return false;
      if ((first + 2 * i + 2) < last && *(first + i) < *(first + 2 * i + 2))
        return false;
    }
    return true;
  } else
    throw InvalidIterator();
}

#endif // HEAP_HPP
