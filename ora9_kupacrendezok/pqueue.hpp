
/**
 *
 * @file pqueue.hpp
 * @author tekda & horar
 * Prioritásos sor csomagolóosztály, kupaccal
 *
 */

#ifndef PQUEUE_HPP
#define PQUEUE_HPP

#include "heap.hpp"
#include <iostream>
#include <vector>

/**
 *
 * Elsőbbségi sor csomagolóosztály
 *
 */
template <class T> class PriorityQueue {
private:
  struct Node {
    T value;
    int priority;
    Node(T value_, int priority_) : value(value_), priority(priority_) {}
    bool operator<(const Node &x) const { return priority < x.priority; }
    bool operator>(const Node &x) const { return priority > x.priority; }
  };

protected:
  Heap<Node> heap;

public:
  PriorityQueue() {}

  PriorityQueue(const std::vector<T> &arr, const std::vector<int> &pri) {
    for (int i = 0; i < arr.size(); i++)
      heap.push(Node(arr[i], pri[i]));
  }

  bool empty() const { return heap.empty(); }

  size_t size() const { return heap.size(); }

  const T &top() const {
    return heap.top().value;
  }

  void push(const T &x, int priority) { heap.push(Node(x, priority)); }

  void pop() {
    heap.pop();
  }

  /**
   * Ellenőrző függvény
   *
   * @return megfelelő-e a prioritásos sor
   */
  bool validate() const {
    if (!empty()) return heap.check();
    return true;
  }
};

#endif // PQUEUE_HPP
