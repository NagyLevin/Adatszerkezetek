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
using namespace std;

template <class I> bool validateHeap(I first, I last);

template <class T> class Heap {
  /**
   *   Konténer vektor
   */
  std::vector<T> v; //vektorban tarolt fa

  /**
   * Kupacban elemet feljebbmozgató eljárás
   *
   * @param index az elem indexe, amit feljebb kell mozgatni
   */
  void liftUp(std::size_t index) {  //ezt irtuk oran

      if(index >= v.size()){
          throw InvalidIndex(); //a sizen kivuli indexet ne lehet felfele buborekoltatni
      }
      std::size_t parent = getParent(index);
      while (index != 0 && v[parent] < v[index]){
         std::swap(v[parent],v[index]) ; //megcsereljuk a kettot
         index = parent; //egyel feljebb lepunk
         parent = getParent(index);

      }



  }

  /**
   * Kupacban elemet lejjebbmozgató eljárás
   *
   * @param index az elem indexe, amit lejjebb kell mozgatni
   */
  void liftDown(std::size_t index) { //ezt irtuk oran

      if(index >= v.size()){
          throw InvalidIndex(); //a sizen kivuli indexet ne lehet felfele buborekoltatni
      }

      std::size_t left_child = leftChild(index);
      std::size_t right_child = rightChild(index);


      while ((right_child < v.size() && v[index] < v[right_child]) ||
             (left_child < v.size() && v[index] < v[left_child])){
          if(right_child < v.size() && v[left_child] < v[right_child]){
              std::swap(v[right_child],v[index]);
              index = right_child;


          } else{
              std::swap(v[left_child],v[index]);
              left_child = leftChild(index);
              right_child = rightChild(index);

          }
          left_child = leftChild(index) ;

      }



  }

  std::size_t getParent(std::size_t index) { return (index - 1) / 2; }//parent kiszamol

  std::size_t leftChild(std::size_t index) { return 2 * index + 1; }    //balgyerek kiszamol

  std::size_t rightChild(std::size_t index) { return 2 * index + 2; }   //jobbgyerek kiszamol

public:
  Heap() {}
  Heap(const std::vector<T> &v_) : v(v_) {//vektorban rendezzuk az elemeket
    for (int i = static_cast<int>(v.size() / 2) - 1; i >= 0; --i)//eleg a feleig, mert onnantol csak levelek vannask
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
