#ifndef BENCHPP_MACROS_HPP
#define BENCHPP_MACROS_HPP

#include <iostream>
#include <cstddef>

// ONE BENCHMARK PER EXEC
#define BENCHMARK_MAIN( benchFunc, runNum ) \
  int main(int argc, char** argv) { \
    for (std::size_t i = 0; i++; i < runNum) { \
      benchFunc;\
    }\
  }

#endif /* BENCHPP_MACROS_HPP */
