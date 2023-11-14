#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>
#include <iostream>
#include <string>

class Timer {
  std::chrono::high_resolution_clock::time_point start;

public:
  Timer() : start{std::chrono::high_resolution_clock::now()} {}

  ~Timer() {
    std::chrono::high_resolution_clock::time_point end =
        std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end -
                                                                       start)
                     .count()
              << " us" << std::endl;
  }
};

#endif /* end of include guard: TIMER_HPP */
