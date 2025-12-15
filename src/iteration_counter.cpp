module; 

#include <cstdlib>
#include <limits>
#include <iostream>

module benchpp;

#define M_ITERATION_INIT_VAL std::numeric_limits<std::size_t>::max()

namespace benchpp {

namespace {

[[nodiscard]]
std::size_t& 
M_iteration(void) noexcept {
  static std::size_t s_iteration{M_ITERATION_INIT_VAL};
  return s_iteration;
}

[[nodiscard]]
bool M_doubleStartIteration(void) noexcept {
  return M_iteration() != M_ITERATION_INIT_VAL;
}

}

std::size_t
currentIteration(void) noexcept {
  return M_iteration();
}

void 
startIteration(const std::size_t num) {
  if (M_doubleStartIteration()) {
    std::cerr << "double start called on this iteration!";
    std::abort();
  }

  M_iteration() = num;
}

}
