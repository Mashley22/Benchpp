#ifndef BENCHPP_MACROS_HPP
#define BENCHPP_MACROS_HPP

#include <iostream>
#include <cstddef>

// ONE BENCHMARK PER EXEC
#define BENCHMARK_MAIN( benchFunc, runNum ) \
  int main(void) { \
    for (std::size_t i = 0; i < runNum; i++) { \
      benchFunc;\
    }\
  }

#endif /* BENCHPP_MACROS_HPP */
